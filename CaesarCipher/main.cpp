#include <iostream>

//using namespace std;
using std::cin;
using std::cout;
using std::getline;
using std::endl;
using std::string;

inline char encrypt(char, int, int, int);    // Шифрование символа
void ceasarCipher(string*, int);                // Шифрование текста шифром Цезаря

int main() {
    string init_text;
    cout << "The program encrypts text with Caesar's cipher" << endl << endl;
    cout << "Enter text for ciphering: " << endl;
    getline(cin, init_text);    // Считать строку
    cout << endl;
    int key;
    cout << "Enter key: ";
    cin >> key;
    cout << endl;

    // Шифрование текста шифром Цезаря
    ceasarCipher(&init_text, key);

    cout << "Encrypted text: " << init_text << endl << endl;
    system("pause");
    return 0;
}

// region Шифрование текста шифром Цезаря

inline char encrypt(char symbol, int key, int start, int end)
{
    /* * * Шифрование символа * * */

    int code = static_cast<int> (symbol);    // Код символа ASCII
    code += key;                // Шифрование
    if(code > end) {            // Если выход за границы (алфавит имеет кольцевой вид: a b c ... z a b c)
        code = start + (code - end);
    }
    return char(code);
}

void ceasarCipher(string *text, int key)
{
    /* * * Шифрование текста шифром Цезаря * * */

    // Перебор символов строки
    for(char &i : *text) {
        // Проверка вхождения в диапазон (замена только символов в диапазоне)
        if(i >= 'A' && i <= 'Z') {
            i = encrypt(i, key, 'A', 'Z');
        }
        else if(i >= 'a' && i <= 'z') {
            i = encrypt(i, key, 'a', 'z');
        }
    }
}
// endregion Шифрование текста шифром Цезаря