#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

//using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

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
    vector<int> *array = new vector<int>(size_array);
    for(unsigned i = 0; i < size_array; i++) {
        array->at(i) = rand() % 100;
    }
    // endregion Заполнение массива

    // Поиск в отсортированном массиве
    sort(array->begin(), array->end());
    // Вывод отсортированного массива
    cout << "Sorted array: " << endl;
    for(int i : *array) {
        cout << i << " ";
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

    unsigned choise;
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
        cout << "Searching element: " << array->at(element_index) << endl << endl;
    }
    // endregion Вывод найденного значения

    //delete[] array;
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

    const clock_t start_time = clock();    // Начальное время

    int average_index = 0;              // Индекс среднего элемента массива
    int first_index = 0;                // Индекс первого элемента в массиве
    int last_index = array->size()-1;   // Индекс последнего элемента в массиве
    int index = -1;                     // Индекс искомого элемента (-1 - не найден)

    while(first_index < last_index) {
        average_index = first_index + (last_index-first_index) / 2;     // Изменить индекс среднего значения
        // Найден ключевой элемент или нет
        if(element <= array->at(average_index)) {
            last_index = average_index;
        }
        else {
            first_index = average_index + 1;
        }
    }
    // Элемент искомый найден
    if(array->at(last_index) == element)
        index = last_index;

    // Время выполнения алгоритма
    clock_t end_time = clock();
    cout << "Algorithm time = " << (double) (end_time-start_time)/CLOCKS_PER_SEC << endl << endl;

    return index;
}
// endregion Бинарный поиск

// endregion Поиск