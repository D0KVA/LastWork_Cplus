#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

int main() {

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        string inputStr;
        string inputChars;

        cout << "Введите строку: ";
        getline(cin, inputStr);

        cout << "Введите символы для поиска: ";
        getline(cin, inputChars);

        cout << "Содержит ли строка: '" + inputStr + "' cимволы: '" + inputChars + "'" << endl;

        HINSTANCE hLib = LoadLibrary(L"DynamicLib.dll");
        if (hLib == NULL) {
            cerr << "Не удалось загрузить библиотеку!" << endl;
            return 1;
        }

        ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib, "contains_all_chars");
        if (contains_all_chars == NULL) {
            cerr << "Не удалось получить адрес функции!" << endl;
            FreeLibrary(hLib);
            return 1;
        }

        bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

        if (result) {
            cout << "Да!" << endl;
        }
        else {
            cout << "Нет!" << endl;
        }

        FreeLibrary(hLib);

        return 0;
}



