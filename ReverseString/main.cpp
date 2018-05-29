#include <iostream>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::swap;

template<class T>
void reverseString(vector<T>*); // Переворот строки

int main()
{
    vector<char> initial_string {'H', 'e', 'l', 'l', 'o', 'w', ' ', 'W', 'o', 'r', 'l', 'd'};
    cout << "String: ";
    for(int i = 0; i < initial_string.size(); i++) {
        cout << initial_string.at(i);
    }
    cout << endl << endl;

    reverseString(&initial_string);  // Переворот строки

    cout << "Reversed string: ";
    for(int i = 0; i < initial_string.size(); i++) {
        cout << initial_string.at(i);
    }
    cout << endl << endl;

    //delete[] initial_string;
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