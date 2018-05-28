#include <iostream>
#include <vector>

using namespace std;

// region Функции поиска

template<class T>
void linearSearch(vector<T>*);        // Линейный поиск

template<class T>
void binarySearch(vector<T>*);        // Бинарный поиск


// endregion Функции поиска

int main()
{
    srand(time(NULL));

    cout << "Enter array length: ";
    unsigned long size_array;           // длинна массива
    cin >> size_array;

    // region Заполнение массива
    cout << "Array:" << endl;
    vector<int> *array = new vector<int>(size_array);
    for(int i = 0; i < size_array; i++) {
        array->at(i) = rand() % 100;
        cout << array->at(i) << " ";
    }
    cout << "\n";
    // endregion Заполнение массива

    // region Выбор типа поиска
    cout << "Select searching algorithm:" << endl;
    cout << "1. Linear;" << endl;
    cout << "2. Binary;" << endl;

    int choise;
    cin >> choise;

    switch(choise) {
        case 1:
            linearSearch(array);    // Линейный поиск
            break;
        case 2:
            binarySearch(array);    // Бинарный поиск
            break;
        default:
            cout << "Wrong number!";
            return 0;
    }
    // endregion Выбор типа поиска

    // region Вывод найденного значения
    cout << "array:" << endl;
    for(int i = 0; i < size_array; ++i) {
        cout << array->at(i) << " ";
    }
    cout << "\n";
    // endregion Вывод отсортированного массива

    delete[] array;
    system("pause");
    return 0;
}

// region Поиск

// region Линейный поиск

template<class T>
void linearSearch(vector<T>*)
{
    /* * * Линейный поиск * * */
}

//линейный поиск
int linearySearch(int arr[], int requiredKey, int arrSize)
{
    for (int i = 0; i < arrSize; i++)
    {
        if (arr[i] == requiredKey)
            return i;
    }
    return -1;
}
// endregion Линейный поиск


// region Бинарный поиск

template<class T>
void binarySearch(vector<T>*)
{
    /* * * Бинарный поиск * * */
}
// endregion Бинарный поиск

// endregion Поиск