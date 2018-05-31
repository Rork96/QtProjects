#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::swap;

template<class T>
void reverseString(vector<T>*); // Переворот строки

void reverseString(std::string*);

int main()
{
    vector<char> initial_string {'H', 'e', 'l', 'l', 'o', 'w', ' ', 'W', 'o', 'r', 'l', 'd'};

    std::string init_string = "Hello for all";

    cout << "String 1: ";
    for(int i = 0; i < initial_string.size(); i++) {
        cout << initial_string.at(i);
    }
    cout << endl << endl;

    cout << "String 2: ";
    for(int i = 0; i < init_string.size(); i++) {
        cout << init_string.at(i);
    }
    cout << endl << endl;

    reverseString(&initial_string);
    reverseString(&init_string);

    //reverseString(&initial_string);  // Переворот строки

    cout << "Reversed string 1: ";
    for(int i = 0; i < initial_string.size(); i++) {
        cout << initial_string.at(i);
    }
    cout << endl << endl;

    cout << "Reversed string 2: ";
    for(int i = 0; i < init_string.size(); i++) {
        cout << init_string.at(i);
    }
    cout << endl << endl;

    //delete[] initial_string;
    //delete[] init_string;
    system("pause");
    return 0;
}

template<class T>
void reverseString(vector<T> *current_string)
{
    /* * * Переворот строки * * */

    int i = 0;                          // Крайний левый элемент
    int j = current_string->size()-1;   // Крайний правый элемент
    // Перебрать все элементы массива двигаясь от его краев к центру
    while(i < j) {
        // Поменять местами элементы масива
        swap(current_string->at(i), current_string->at(j));
        i++;
        j--;
    }
}

void reverseString(std::string *current_string)
{
    /* * * Переворот строки * * */

    int i = 0;                          // Крайний левый элемент
    int j = current_string->size()-1;   // Крайний правый элемент
    // Перебрать все элементы массива двигаясь от его краев к центру
    while(i < j) {
        // Поменять местами элементы масива
        char c = current_string->at(i);
        current_string->at(i) = current_string->at(j);
        current_string->at(j) = c;
        i++;
        j--;
    }
}