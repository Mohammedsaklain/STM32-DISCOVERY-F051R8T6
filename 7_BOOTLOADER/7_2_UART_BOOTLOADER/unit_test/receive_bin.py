import serial
import os # Import os for file size check

OUTPUT_FILE = "received.bin"
SERIAL_PORT = "COM98"
BAUD_RATE = 115200

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
except serial.SerialException as e:
    print(f"Error opening serial port {SERIAL_PORT}: {e}")
    exit()

print(f"Listening on {SERIAL_PORT}...")

ser.flushInput()

with open(OUTPUT_FILE, "wb") as f:
    print("Receiving... Press Ctrl+C to stop.")
    total_bytes_received = 0
    try:
        while True:
            # Read up to CHUNK_SIZE (or whatever you expect the sender to send)
            data = ser.read(256)
            if data:
                f.write(data)
                total_bytes_received += len(data)
                print(f"Received {total_bytes_received} bytes...", end='\r') # Live update
            else:
                # If timeout occurs and no data is received, it will return empty bytes.
                # We might want to break the loop after some time if no more data is expected.
                # For continuous listening, remove this else block.
                # If you expect a fixed size file, you could check total_bytes_received.
                pass
    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        ser.close()
        print(f"\nData saved to {OUTPUT_FILE}")
        if os.path.exists(OUTPUT_FILE):
            print(f"Received file size: {os.path.getsize(OUTPUT_FILE)} bytes")
        else:
            print("Output file not found or was empty.")
