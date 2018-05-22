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

	char* FileName = DB_FILE_NAME;
	char Sep = '\t';
	int COUNT, INTsize = sizeof(int);
	FILE* SysFile = fopen(SYS_FILE, "rb");
	if (!SysFile){
		FILE* SysFile = fopen(SYS_FILE, "wb");
		COUNT = 0;
		PUT_COUNT(COUNT);
	}
	fclose(SysFile);

	CheckSizeOfFile(FileName);

	Menu(FileName, Sep);

}
