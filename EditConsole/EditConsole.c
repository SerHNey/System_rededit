#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
HANDLE hMyKey;

CONSOLE_FONT_INFOEX cfi;

DWORD BackGround = 0;
DWORD ForeGround = 0;

void GetSettings();
void SetFontSize(DWORD st);
void SetColor(DWORD Color, int Back);
void SetFontType(DWORD);


void SetColor(DWORD Color, int Back)
{
    WORD wColor;
    if (Back == 0) {
        wColor = wColor = ((BackGround & 0x0F) << 4) + (Color & 0x0F);
        RegSetValueEx(hMyKey, L"Fcolor", 0, REG_DWORD, (const BYTE*)&Color, sizeof(Color));
        ForeGround = Color;
    }
    else {
        wColor = wColor = ((Color & 0x0F) << 4) + (ForeGround & 0x0F);
        RegSetValueEx(hMyKey, L"Bcolor", 0, REG_DWORD, (const BYTE*)&Color, sizeof(Color));
        BackGround = Color;
    }

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SetConsoleTextAttribute(hStdOut, wColor);
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        FillConsoleOutputCharacter(hStdOut, (TCHAR)32
            , csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes
            , csbi.dwSize.X + 12 * csbi.dwSize.Y + 12, coord, &count);
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}

void GetSettings() {
    DWORD dw;
    DWORD size = sizeof(dw);
    if (RegGetValueW(hMyKey, NULL, L"style", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        cfi.FontWeight = dw;
    }
    dw = 0;
    if (RegGetValueW(hMyKey, NULL, L"size", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        cfi.dwFontSize.Y = dw;
    }
    dw = 0;
    if (RegGetValueW(hMyKey, NULL, L"Fcolor", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        SetColor(dw, 0);
    }
    dw = 0;
    if (RegGetValueW(hMyKey, NULL, L"Bcolor", RRF_RT_DWORD, NULL, (LPBYTE)&dw, &size) == ERROR_SUCCESS)
    {
        SetColor(dw, 1);
    }
}

void SetFontSize(DWORD st) {
    if (RegSetValueEx(hMyKey, L"size", 0, REG_DWORD, (const BYTE*)&st, sizeof(st)) == ERROR_SUCCESS) {
        cfi.dwFontSize.Y = st;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    };
}

void SetFontType(DWORD st) {
    if (RegSetValueEx(hMyKey, L"style", 0, REG_DWORD, (const BYTE*)&st, sizeof(st)) == ERROR_SUCCESS) {
        cfi.FontWeight = st;
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    };
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    RegCreateKeyW(HKEY_CURRENT_USER, L"MyKey", &hMyKey);
    cfi.cbSize = sizeof cfi;
    GetSettings();
    while (1)
    {
        system("cls");
        char text;
        printf("Цвет текста - 1\nЦвет фона - 2\nТип текста - 3\nРазмер текста - 4\nВыход - 0\n");
        scanf("%c", &text);
        DWORD i = 0;
        switch (text)
        {
        case '1':
            printf("Введите значение\n");
            scanf("%d", &i);
            SetColor(i, 0);
            break;
        case '2':
            printf("Введите значение\n");
            scanf("%d", &i);
            SetColor(i, 1);
            break;
        case '3':
            printf("Введите значение\n");
            scanf("%d", &i);
            SetFontType(i);
            break;
        case '4':
            printf("Введите значение\n");
            scanf("%d", &i);
            SetFontSize(i);
            break;
        case '0':
            return 0;
            break;
        }
    }
    return 0;
}
