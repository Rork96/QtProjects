#include <iostream>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    std::wstring str = L"консоли!";
    std::wcout << L"Русские буквы в " << str << std::endl << std::endl;

    system("pause");

    return 0;
}