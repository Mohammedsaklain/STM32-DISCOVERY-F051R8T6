#include "main.h"

int main()
{
	Lcd_Init();
	while(1)
	{
		Lcd_Scroll_Data(":) Hello! ",LEFT);
	}
	return 0;
}
