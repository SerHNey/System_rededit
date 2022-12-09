#include <Windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
    HKEY hKey = NULL;
    if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS) // Открываем раздел в реестре 
        return 1;

    HKEY nametmp = NULL;
    if (RegCreateKey(hKey, L"Time", &nametmp) == ERROR_SUCCESS) { // Создаём раздел в HKEY_CURRENT_USER
        //RegCloseKey(nametmp); // Если закрыть, то нельзя создать по этому пути параметр в ново созданном разделе
        MessageBox(NULL, L"Успешно создан", L"Оповещение", MB_OK);
    }

    LPWSTR StrParam = L"Изменённый параметр1";
    DWORD StrParamLen = wcslen(StrParam);

    if (RegSetValue(hKey, L"Time", REG_SZ, StrParam, StrParamLen * sizeof(WCHAR)) == ERROR_SUCCESS) { // Создаём подраздел + задаём значение + указываем тип 
        MessageBox(NULL, L"Значение присвоено", L"Оповещение", MB_OK);
    }

    StrParam = L"Изменённый параметр2";

    if (RegSetValueExW(nametmp, L"time", NULL, REG_SZ, StrParam, StrParamLen * sizeof(WCHAR)) == ERROR_SUCCESS) { // Создание ключа в разделе
        MessageBox(NULL, L"Параметр успешно создан и ему присвоенно значение", L"Оповещение", MB_OK);
    }

    DWORD flag = 0;
    LPWSTR readtext = malloc(512);
    DWORD len = 500;

    if (RegGetValue(nametmp, NULL, L"time",  RRF_RT_ANY, flag, readtext, &len) == ERROR_SUCCESS) {
        MessageBox(NULL, readtext, L"Оповещение", MB_OK);
    }
}

int main()
{

}

