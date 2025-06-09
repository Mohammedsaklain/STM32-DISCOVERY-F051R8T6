import serial   # Handles serial port communication
import time     # For introducing delays
import os       # For file handling

# --- Configuration Constants ---
BIN_FILE                = "D:/UART_BOOT_app_code.bin"
SERIAL_PORT             = "COM18"
BAUD_RATE               = 115200
PACKET_DATA_SIZE        = 20    # Max number of Data bytes to send in single WRITE command
DELAY_BETWEEN_PACKETS   = 0.3   # Adjusted to a more typical small delay

# --- Bootloader Protocol Constants (Must match STM32_bootloader.c) ---
START_BYTE              = 0x01
END_BYTE                = 0x02
ACK                     = 0xCC
NACK                    = 0xEE
READY                   = 0x06

# Commands
ERASE                   = 0x03
WRITE                   = 0x04
JUMP                    = 0x05


# To Calculates the 8-bit checksum for the packet payload to ensure data integrity
def calculate_checksum(data_bytes):
    checksum = sum(data_bytes)
    return checksum & 0xFF

# Constructs a full bootloader packet.
def create_packet(command, payload=b''):
    if len(payload) > PACKET_DATA_SIZE:
        raise ValueError(f"Payload too large ({len(payload)} bytes). Max is {PACKET_DATA_SIZE} bytes.")

    packet = bytearray()                # Creates a empty bytearray
    packet.append(START_BYTE)           # 1. add SB
    packet.append(command)              # 2. Command
    packet.append(len(payload) & 0xFF)  # 3. Data Length (1 byte)
    packet.extend(payload)              # Extends the packet data

    # Checksum includes command, length, and payload
    checksum_data = bytearray([command, len(payload) & 0xFF]) + payload
    checksum = calculate_checksum(checksum_data)
    
    packet.append(checksum)             # 4. Checksum
    packet.append(END_BYTE)             # 5. Finally add EB
    
    return packet                       # return the whole assembled packet


# Receive incoming message and decode whether ACK or NACK
def receive_ack_response(ser_port, timeout_msg="No response from bootloader (timeout)."):
    response = ser_port.read(1)
    if not response:
        print(f"\n[ERROR] {timeout_msg}")
        return None                     # Indicate timeout

    resp_byte = ord(response)           # convert byte to an integer object
    return resp_byte

# Sends a command packet and expects two ACKs back (packet ACK + operation ACK)
def send_command_and_expect_acks(ser_port, command, payload=b''):
    packet = create_packet(command, payload)
    ser_port.write(packet)
    ser_port.flush()
    time.sleep(DELAY_BETWEEN_PACKETS)

    # First ACK: Packet validation (CRC, END_BYTE)
    ack1 = receive_ack_response(ser_port, "No initial packet response from bootloader (timeout).")
    if ack1 is None:
        return False
    
    if ack1 != ACK:
        print(f"\n[ERROR] Bootloader sent {('NACK' if ack1 == NACK else f'unexpected 0x{ack1:02X}')} for packet validation.")
        return False

    # Second ACK: Operation status (Erase, Write, Jump)
    ack2 = receive_ack_response(ser_port, "No operation status response from bootloader (timeout).")
    if ack2 is None:
        return False

    if ack2 != ACK:
        print(f"\n[ERROR] Bootloader sent {('NACK' if ack2 == NACK else f'unexpected 0x{ack2:02X}')} for command 0x{command:02X} operation.")
        return False
    
    return True # Both ACKs received successfully

# Handles the initial READY/ACK handshake with the bootloader
def establish_handshake(ser_port):
    print("Waiting for bootloader READY signal...")
    response = ser_port.read(1)
    if not response:
        print("[ERROR] No 'READY' signal received from bootloader (timeout).")
        return False
    
    if ord(response) == READY:
        print("Bootloader is READY. Sending ACK...")
        ser_port.write(bytes([ACK]))
        ser_port.flush()
        
        ack_response = ser_port.read(1)
        if not ack_response or ord(ack_response) != ACK:
            print("[ERROR] Bootloader did not ACK our ACK.")
            return False
        print("Initial handshake complete.")
        return True
    else:
        print(f"[ERROR] Expected READY (0x{READY:02X}), got 0x{ord(response):02X}.")
        return False


# --- Main Upload Logic ---
def upload_firmware():
    ser = None # Initialize ser to None
    try:
        print(f"Connecting to bootloader on {SERIAL_PORT}...")
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=5)

        if not establish_handshake(ser):
            return # Handshake failed, exit

        print("\nSending ERASE command...")
        if not send_command_and_expect_acks(ser, ERASE):
            print("Erase command failed. Aborting.")
            return # Erase failed, exit

        print("Erase successful. Starting file transfer...")

        total_bytes_sent = 0
        file_size = os.path.getsize(BIN_FILE)

        with open(BIN_FILE, "rb") as f:
            while True:
                chunk = f.read(PACKET_DATA_SIZE)
                if not chunk:
                    break # End of file

                if not send_command_and_expect_acks(ser, WRITE, chunk):
                    print(f"Write command failed at byte {total_bytes_sent}. Aborting.")
                    return # Write failed, exit

                total_bytes_sent += len(chunk)
                progress = (total_bytes_sent / file_size) * 100
                print(f"Sent {total_bytes_sent}/{file_size} bytes ({progress:.2f}%)", end='\r')
            
        print(f"\nFile '{BIN_FILE}' sent successfully.")

        print("\nSending JUMP command...")
        ser.timeout = 2 # Give it a bit more time for the jump validation
        if not send_command_and_expect_acks(ser, JUMP):
            print("JUMP command failed or application validation failed. Aborting.")
            return # Jump failed, exit

        print("JUMP command successful. Bootloader should now execute application.")

    except serial.SerialException as e:
        print(f"Error opening serial port {SERIAL_PORT}: {e}")
    except FileNotFoundError:
        print(f"[ERROR] Binary file not found: {BIN_FILE}")
    except Exception as e:
        print(f"[ERROR] An unexpected error occurred: {e}")
    finally:
        if ser and ser.is_open:
            ser.close()
            print("Serial port closed.")

if __name__ == "__main__":
    upload_firmware()
