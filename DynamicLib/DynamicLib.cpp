#include <string>

using namespace std;

// ����������� ������� contains_all_chars
extern "C" __declspec(dllexport) bool contains_all_chars(const char* str, const char* chars) {
    // �������� ������� string �� ���������� ������ str
    string s(str);

    // ������� ���� �������� � ������ chars
    for (const char* c = chars; *c != '\0'; ++c) {
        // ��������, �������� �� ������ s ������ *c
        if (s.find(*c) == string::npos) {
            // ���� ������ �� ������, ������������ false
            return false;
        }
    }

    // ���� ��� ������� �������, ������������ true
    return true;
}