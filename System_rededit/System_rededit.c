#include <Windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    HKEY hKey = NULL;
    //if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS) // Открываем раздел в реестре 
    //    return 1;
    if (RegOpenKeyW(HKEY_CURRENT_USER, L"Time",&hKey) != ERROR_SUCCESS) // Открываем раздел в реестре 
        return 1;

    HKEY nametmp = NULL;
    if (RegCreateKey(hKey, L"Time", &nametmp) == ERROR_SUCCESS) { // Создаём раздел в HKEY_CURRENT_USER
        RegCloseKey(nametmp);
        MessageBox(NULL, L"Успешно создан", L"Оповещение", MB_OK);
    }

    if (RegSetValue(hKey, nametmp, REG_SZ, L"Значение по умолчанию", 10 * sizeof(WCHAR)) == ERROR_SUCCESS) { // Создаём подраздел + задаём значение + указываем тип 
        MessageBox(NULL, L"Значение присвоено", L"Оповезение", MB_OK);
    }

}

int main()
{

}

