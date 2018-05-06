#include "DataFunc.h"

void main()
{
	//SetConsoleOutputCP(866);
	if (LOWORD(GetKeyboardLayout(0)) != 0x409) // меняет раскладку клавиатуры на eng (через shift - alt)
	{
		keybd_event(SHIFT, 0, 0, 0);
		keybd_event(ALT, 0, 0, 0);
		keybd_event(SHIFT, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(ALT, 0, KEYEVENTF_KEYUP, 0);
	}

	char* FileName = "DataFile.bin";
	char Sep = '\t';

	CheckSizeOfFile(FileName);

	Menu(FileName, Sep);

}
