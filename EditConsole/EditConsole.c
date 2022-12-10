#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>


void ClearConsoleToColors(int ForgC, int BackC)
{
    
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    //Get the handle to the current output buffer...
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //This is used to reset the carat/cursor to the top left.
    COORD coord = { 0, 0 };
    //A return value... indicating how many chars were written
    //   not used but we need to capture this since it will be
    //   written anyway (passing NULL causes an access violation).
    DWORD count;

    //This is a structure containing all of the console info
    // it is used here to find the size of the console.
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //Here we will set the current color
    SetConsoleTextAttribute(hStdOut, wColor);
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //This fills the buffer with a given character (e.g 32=space).
        FillConsoleOutputCharacter(hStdOut, (TCHAR)32
            , csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes
            , csbi.dwSize.X * csbi.dwSize.Y, coord, &count);


        //This will set our cursor position for the next print statement.
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}

void SelectorColor(int ForgC) {
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

int main()
{
	system("chcp 1251>null");
	//SelectorColor(1);

    ClearConsoleToColors(1, 5);

    CONSOLE_FONT_INFOEX cfon;
    ZeroMemory(&cfon, sizeof(CONSOLE_FONT_INFOEX));
    cfon.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    cfon.nFont = 12;
    cfon.dwFontSize.X = 7;
    cfon.dwFontSize.Y = 24;
    cfon.FontFamily = 54; // Lucida Console
    cfon.FontWeight = 400;
    lstrcpyW(cfon.FaceName, L"Lucida Console");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfon);


	printf("dqd");
    return 0;

}


