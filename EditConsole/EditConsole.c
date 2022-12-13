
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
DWORD ConsoleRead();

HKEY hMyKey;
DWORD bold = 0;
DWORD ColorText = 7;
DWORD FontSize = 16;
DWORD BackGround = 0;


void GetSettings() {
    HANDLE hMyKey;
    DWORD dw;
    DWORD size = sizeof(dw);
    if (RegGetValueW(hMyKey, NULL, L"style", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        bold = dw;
    }
    dw = 0;
    if (RegGetValueW(hMyKey, NULL, L"size", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        FontSize = dw;
    }
    dw = 0;
    if (RegGetValueW(hMyKey, NULL, L"Fcolor", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        ColorText = dw;
    }
    dw = 0;
    if (RegGetValueW(hMyKey, NULL, L"Bcolor", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        BackGround = dw;
    }
}
void RegSettings() {
    WORD wColor;
    if (RegSetValueEx(hMyKey, L"size", 0, REG_DWORD, (const BYTE*)&st, sizeof(st)) == ERROR_SUCCESS) {
        bold = st;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    };
    if (RegSetValueEx(hMyKey, L"style", 0, REG_DWORD, (const BYTE*)&st, sizeof(st)) == ERROR_SUCCESS) {
        FontSize = st;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    };
    if (BackGround == 0) {
        wColor = wColor = ((BackGround & 0x0F) << 4);
        RegSetValueEx(hMyKey, L"Fcolor", 0, REG_DWORD, (const BYTE*)&BackGround, sizeof(Color));

    }
    else {
        wColor = (ColorText & 0x0F);
        RegSetValueEx(hMyKey, L"Bcolor", 0, REG_DWORD, (const BYTE*), sizeof(Color));
        BackGround = Color;
    }
}




void ClearConsoleToColors(int ForgC, int BackC, int FontSizeC, int BoldFontC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    CONSOLE_FONT_INFOEX cfon;

    SetConsoleTextAttribute(hStdOut, wColor);
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //This fills the buffer with a given character (e.g 32=space).
        FillConsoleOutputCharacter(hStdOut, (TCHAR)32
            , csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes
            , csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        cfon.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        cfon.dwFontSize.Y = FontSizeC;
        if (BoldFontC == 0) 
            cfon.FontWeight = 600;
        
        if (BoldFontC == 1) 
            cfon.FontWeight = 100;
        
        if (BoldFontC == 2) 
            cfon.FontWeight = 1000;
        

        //This will set our cursor position for the next print statement.
        SetConsoleCursorPosition(hStdOut, coord);
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfon);
    }
    return;
}

int main()
{

	system("chcp 1251>null");
    //ClearConsoleToColors(7, 0, 16, 0);
   // ConsoleRead();
    //SetBackground(1);

    char choose;
    
    DWORD bold = 0;
    DWORD ColorText = 7;
    DWORD FontSize = 16;
    DWORD BackGround = 0;
    //ClearConsoleToColors(ColorText, BackGround, FontSize, bold);
    while (1)
    {
        system("cls");
        printf("Выберите нужную настройку командной строки\n 1 - настройка стиля шрифта\n 2 - настройка цвета шрифта\n 3 - настройка размера шрифта\n 4 - настройка цвета заднего фона\n");
        gets(&choose);
        if (choose == '1') {
            printf("0 - default\n1 - Тонкий\n2 - bold\n");
            scanf_s("%d", &bold);
            ClearConsoleToColors(ColorText, BackGround, FontSize, bold);
            printf("Пример текста....");
        }
        if (choose == '2') {
            printf("Число от 0 до 199\n");
            scanf_s("%d", &ColorText);
            ClearConsoleToColors(ColorText, BackGround, FontSize, bold);
            printf("Пример текста....");
        }
        if (choose == '3') {
            printf("Число от 0 до 100\n");
            scanf_s("%d", &FontSize);
            ClearConsoleToColors(ColorText, BackGround, FontSize, bold);
            printf("Пример текста....");
        }
        if (choose == '4') {
            printf("Число от 0 до 100\n");
            scanf_s("%d", &BackGround);
            ClearConsoleToColors(ColorText, BackGround, FontSize, bold);
            printf("Пример текста....");
        }

    }
    

    HKEY hKey = NULL;
    if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS) // Открываем раздел в реестре 
        return 1;

    HKEY nametmp = NULL;
    if (RegCreateKey(hKey, L"Time", &nametmp) == ERROR_SUCCESS) { // Создаём раздел в HKEY_CURRENT_USER
        //RegCloseKey(nametmp); // Если закрыть, то нельзя создать по этому пути параметр в ново созданном разделе
        MessageBox(NULL, L"Успешно создан", L"Оповещение", MB_OK);
    }


    DWORD StrParam = 0;
    gets(StrParam);
    DWORD StrParamLen = wcslen(StrParam);

    if (RegSetValueW(hKey, L"Time", REG_DWORD, StrParam, StrParamLen * sizeof(WCHAR)) == ERROR_SUCCESS) { // Создаём подраздел + задаём значение + указываем тип 
        MessageBox(NULL, L"Значение присвоено", L"Оповещение", MB_OK);
    }



	printf("dqd");
    return 0;
}


DWORD ConsoleRead() {
    DWORD retur;
    scanf_s("%d",&retur);
    return retur;
}