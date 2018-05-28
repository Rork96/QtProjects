#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// region Функции поиска

template<class T>
T linearSearch(vector<T>*, T);        // Линейный поиск

template<class T>
T binarySearch(vector<T>*, T);        // Бинарный поиск


// endregion Функции поиска

int main()
{
    srand(time(NULL));

    cout << "Enter array length: ";
    unsigned long size_array;           // длинна массива
    cin >> size_array;

    // region Заполнение массива
    //cout << "Array:" << endl;
    vector<int> *array = new vector<int>(size_array);
    for(int i = 0; i < size_array; i++) {
        array->at(i) = rand() % 100;
        //cout << array->at(i) << " ";
    }
    //cout << "\n";
    // endregion Заполнение массива

    // Поиск в отсортированном массиве
    sort(array->begin(), array->end());
    // Вывод отсортированного массива
    cout << "Sorted array: " << endl;
    for(int i = 0; i < array->size(); i++) {
        cout << array->at(i) << " ";
    }
    cout << "\n";

    int element;                // Искомый элемент (значение)
    int element_index = -1;     // Индекс искомого элемента (-1 - не найден)
    cout << "Enter searching element: ";
    cin >> element;
    cout << "\n";

    // region Выбор типа поиска
    cout << "Select searching algorithm:" << endl;
    cout << "1. Linear;" << endl;
    cout << "2. Binary;" << endl;

    int choise;
    cin >> choise;

    switch(choise) {
        case 1:
            element_index = linearSearch(array, element);   // Линейный поиск
            break;
        case 2:
            element_index = binarySearch(array, element);   // Бинарный поиск
            break;
        default:
            cout << "Wrong number!";
            return 0;
    }
    // endregion Выбор типа поиска

    // region Вывод найденного значения
    if (element_index == -1) {
        cout << "Element " << element << " not found" << endl;
    }
    else {
        cout << "Element found at number: " << element_index + 1 << endl;
        cout << "Searching element: " << array->at(element_index) << endl;
    }
    // endregion Вывод найденного значения

    delete[] array;
    system("pause");
    return 0;
}

// region Поиск

// region Линейный поиск

template<class T>
T linearSearch(vector<T> *array, T element)
{
    /* * * Линейный поиск * * */

    const clock_t start_time = clock();    // Начальное время

    int index = -1; // Индекс искомого элемента (-1 - не найден)

    // Поочередный перебор элементов массива
    for(int i = 0; i < array->size(); i++) {
        if(array->at(i) == element) {
            index = i;
            break;  // Искать первое вхождение
        }
    }

    // Время выполнения алгоритма
    clock_t end_time = clock();
    cout << "Algorithm time = " << (double) (end_time-start_time)/CLOCKS_PER_SEC << endl << endl;

    return index;  // Индекс элемента
}
// endregion Линейный поиск


// region Бинарный поиск

template<class T>
T binarySearch(vector<T> *array, T element)
{
    /* * * Бинарный поиск * * */
}
// endregion Бинарный поиск

// endregion Поиск