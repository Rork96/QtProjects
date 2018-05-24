#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>

using namespace std;

void insertSort(int*, int);    // Сортировка вставками
void selectSort(int*, int);    // Сортировка выбором

int main()
{
    srand(time(NULL));

    cout << "Enter array length: ";
    int size_array; // длинна массива
    cin >> size_array;

    cout << "Array:" << endl;
    int *sorted_array = new int[size_array]; // одномерный динамический массив
    for (int counter = 0; counter < size_array; counter++) {
        sorted_array[counter] = rand() % 100; // заполняем массив случайными числами
        cout << setw(2) << sorted_array[counter] << "  "; // вывод массива на экран
    }
    cout << "\n";

    int choise;
    cout << "Select sorting algorithm:" << endl;
    cout << "1. Bubble;" << endl;
    cout << "2. Insertion;" << endl;
    cout << "3. Selection;" << endl;
    cout << "4. Merge;" << endl;
    cout << "5. Comb;" << endl;
    cout << "6. Shell." << endl;
    cin >> choise;

    switch (choise) {
        case 1:
            break;
        case 2:
            insertSort(sorted_array, size_array);   // Сортировка вставками
            break;
        case 3:
            selectSort(sorted_array, size_array);   // Сортировка выбором
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
    }

    cout << "Sorted array:" << endl;
    for (int counter = 0; counter < size_array; counter++)
    {
        cout << setw(2) << sorted_array[counter] << "  "; // печать отсортированного массива
    }
    cout << "\n";

    delete[] sorted_array;
    system("pause");
    return 0;
}

void insertSort(int *array, int length)
{
    /* * * Сортировка вставками * * */

    // Проход по всему массиву наччиная с 1-го (не 0-го)
    for (int counter = 1; counter < length; counter++) {
        int temp = array[counter]; // инициализируем временную переменную текущим значением элемента массива
        int item = counter-1; // запоминаем индекс предыдущего элемента массива
        while(item >= 0 && array[item] > temp) {
            // пока индекс не равен 0 и предыдущий элемент массива больше текущего
            // (обходим все элементы от предыдущего (текущего-1) до 0-го)
            array[item + 1] = array[item]; // перестановка элементов массива
            array[item] = temp;
            item--;
        }
    }
}

void selectSort(int *array, int length)
{
    /* * * Сортировка выбором * * */

    // Проход по всему массиву начиная с 0-го
    for (int repeat_counter = 0; repeat_counter < length; repeat_counter++) {
        // repeat_counter - текущий элемент (первый)
        for (int element_counter = repeat_counter + 1; element_counter < length; element_counter++) {
            // Проход со следующего элемента (repeat_counter+1) до конца массива
            if (array[repeat_counter] > array[element_counter]) {
                // если текущий элемент больше следующего - поменять их местами
                int temp = array[repeat_counter];
                array[repeat_counter] = array[element_counter];
                array[element_counter] = temp;
            }
        }
    }
}