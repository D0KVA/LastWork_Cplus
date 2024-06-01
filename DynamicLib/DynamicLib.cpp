#include <string>

using namespace std;

// Определение функции contains_all_chars
extern "C" __declspec(dllexport) bool contains_all_chars(const char* str, const char* chars) {
    // Создание объекта string из переданной строки str
    string s(str);

    // Перебор всех символов в строке chars
    for (const char* c = chars; *c != '\0'; ++c) {
        // Проверка, содержит ли строка s символ *c
        if (s.find(*c) == string::npos) {
            // Если символ не найден, возвращается false
            return false;
        }
    }

    // Если все символы найдены, возвращается true
    return true;
}