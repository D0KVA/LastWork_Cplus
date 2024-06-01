#include <iostream>
#include <windows.h>
#include <string>
#include <memory>

using namespace std;

// Определение типа функции, которую мы собираемся загрузить из DLL
typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

// Структура для автоматического освобождения DLL
struct DllDeleter {
    typedef HINSTANCE pointer; // typedef для указателя на DLL
    // Оператор(), который вызывается при удалении unique_ptr
    void operator()(HINSTANCE hLib) const {
        if (hLib != NULL) {
            FreeLibrary(hLib); // Освободить DLL, если она была загружена
        }
    }
};

int main() {

    // Устанавливаем кодировку консоли на 1251 (Windows-1251)
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string inputStr; // Строка для хранения ввода пользователя
    string inputChars; // Строка для хранения символов, которые нужно найти

    // Спрашиваем у пользователя строку и символы
    cout << "Пожалуйста, введите строку: ";
    getline(cin, inputStr);

    cout << "Пожалуйста, введите символы, которые нужно найти: ";
    getline(cin, inputChars);

    cout << "Проверка, содержит ли строка: '" + inputStr + "' все символы: '" + inputChars + "'" << endl;

    // Загружаем DLL и оборачиваем её в умный указатель для автоматического освобождения
    unique_ptr<HINSTANCE, DllDeleter> hLib(LoadLibrary(L"DynamicLib.dll"));
    if (hLib == NULL) {
        cerr << "Ошибка при загрузке библиотеки" << endl;
        return 1; // Если DLL не загрузилась, выводим ошибку и завершаем программу
    }

    // Извлекаем функцию из DLL
    ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib.get(), "contains_all_chars");
    if (contains_all_chars == NULL) {
        cerr << "Ошибка при получении адреса функции" << endl;
        return 1; // Если функция не найдена, выводим ошибку и завершаем программу
    }

    // Вызываем функцию с введенной строкой и символами
    bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

    // Выводим результат
    if (result) {
        cout << "Да!" << endl;
    }
    else {
        cout << "Нет!" << endl;
    }

    // DLL будет автоматически освобождена при выходе из функции благодаря unique_ptr
    return 0;
}
