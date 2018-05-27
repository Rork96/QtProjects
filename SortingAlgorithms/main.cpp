#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <iterator>

using namespace std;

template<class T>
void bubbleSort(vector<T>*, unsigned long);                 // Сортировка пузырьком
template<class T>
void insertSort(vector<T>*, unsigned long);                 // Сортировка вставками
template<class T>
void selectSort(vector<T>*, unsigned long);                 // Сортировка выбором
template<class T>
void merge(vector<T>*, unsigned long, unsigned long);       // Функция, сливающая массивы (для сортировки слиянием)
template<class T>
void mergeSort(vector<T>*, unsigned long, unsigned long);   // Рекурсивная процедура сортировки слиянием
template<class T>
void combSort(vector<T>*, unsigned long);                   // Сортировка рассческой
template<class T>
void shellSort(vector<T>*, unsigned long);                  // Сортировка методом Шелла
template<class T>
void quickSort(vector<T>*, unsigned long);                  // Быстрая сортировка

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "Enter array length: ";
    unsigned long size_array;           // длинна массива
    cin >> size_array;

    cout << "Array:" << endl;
    vector<int> *sorted_array = new vector<int>(size_array);
    for(unsigned int counter = 0; counter < size_array; counter++) {
        sorted_array->at(counter) = rand() % 100;
        cout << setw(4) << sorted_array->at(counter);
    }
    cout << "\n";

    cout << "Select sorting algorithm:" << endl;
    cout << "1. Bubble;" << endl;
    cout << "2. Insertion;" << endl;
    cout << "3. Selection;" << endl;
    cout << "4. Merge;" << endl;
    cout << "5. Comb;" << endl;
    cout << "6. Shell;" << endl;
    cout << "7. Quick." << endl;

    int choise;
    cin >> choise;

    switch(choise) {
        case 1:
            bubbleSort(sorted_array, sorted_array->size());         // Сортировка пузырьком
            break;
        case 2:
            insertSort(sorted_array, sorted_array->size());         // Сортировка вставками
            break;
        case 3:
            selectSort(sorted_array, sorted_array->size());         // Сортировка выбором
            break;
        case 4:
            mergeSort(sorted_array, 0, sorted_array->size()-1);     // Сортировка слиянием
            break;
        case 5:
            combSort(sorted_array, sorted_array->size());           // Сортировка рассческой
            break;
        case 6:
            shellSort(sorted_array, sorted_array->size());          // Сортировка Шелла
            break;
        case 7:
            quickSort(sorted_array, sorted_array->size());          // Быстрая сортировка2
            break;
        default:
            cout << "Wrong number!";
            return 0;
    }

    cout << "Sorted array:" << endl;
    // печать отсортированного массива
    copy(sorted_array->begin(),              // итератор начала массива
         sorted_array->end(),                // итератор конца массива
         ostream_iterator<int>(cout, " ")    //итератор потока вывода
    );

    cout << "\n";

    delete[] sorted_array;
    system("pause");
    return 0;
}

template<class T>
void bubbleSort(vector<T> *array, unsigned long length)
{
    /* * * Сортировка пузырьком * * */
    bool exit = false; // болевая переменная для выхода из цикла, если массив отсортирован

    while(!exit) { // пока массив не отсортирован
        exit = true;
        for(int int_counter = 0; int_counter < length-1; int_counter++) { // внутренний цикл
            // сортировка пузырьком по возрастанию - знак >
            // сортировка пузырьком по убыванию - знак <
            if(array->at(int_counter) > array->at(int_counter+1)) { // сравниваем два соседних элемента
                // перестановка элементов массива
                swap(array->at(int_counter), array->at(int_counter+1));

                exit = false; // на очередной итерации была произведена перестановка элементов
            }
        }
    }
}

template<class T>
void insertSort(vector<T> *array, unsigned long length)
{
    /* * * Сортировка вставками * * */

    // Проход по всему массиву наччиная с 1-го (не 0-го)
    for(int counter = 1; counter < length; counter++) {
        T temp = array->at(counter); // инициализируем временную переменную текущим значением элемента массива
        int item = counter-1; // запоминаем индекс предыдущего элемента массива
        while(item >= 0 && array->at(item) > temp) {
            // пока индекс не равен 0 и предыдущий элемент массива больше текущего
            // (обходим все элементы от предыдущего (текущего-1) до 0-го)
            swap(array->at(item+1), array->at(item)); // перестановка элементов массива
            item--;
        }
    }
}

template<class T>
void selectSort(vector<T> *array, unsigned long length)
{
    /* * * Сортировка выбором * * */

    // Проход по всему массиву начиная с 0-го
    for(int repeat_counter = 0; repeat_counter < length; repeat_counter++) {
        // repeat_counter - текущий элемент (первый)
        for(int element_counter = repeat_counter + 1; element_counter < length; element_counter++) {
            // Проход со следующего элемента (repeat_counter+1) до конца массива
            if(array->at(repeat_counter) > array->at(element_counter)) {
                // если текущий элемент больше следующего - поменять их местами и продолжить перебор
                swap(array->at(repeat_counter), array->at(element_counter));
            }
        }
    }
}

template<class T>
void merge(vector<T> *array, unsigned long first, unsigned long last)
{
    /* * * Функция, сливающая массивы (для сортировки слиянием) * * */

    T middle, start, final;
    auto *mas = new vector<T>(array->size());
    middle = (first+last)/2;                // вычисление среднего элемента
    start = first;                          // начало левой части
    final = middle+1;                       // начало правой части
    for(long int j = first; j <= last; j++) {    // выполнять от начала до конца
        if((start <= middle) && ((final > last) || (array->at(start) < array->at(final)))) {
            mas->at(j) = array->at(start);
            start++;
        }
        else {
            mas->at(j) = array->at(final);
            final++;
        }
    }
    // возвращение результата в список
    for(long int j = first; j <= last; j++)
        array->at(j) = mas->at(j);

    //delete[] mas;
}

template<class T>
void mergeSort(vector<T> *array, unsigned long first, unsigned long last)
{
    /* * * Рекурсивная процедура сортировки слиянием * * */

    if(first < last) {
        mergeSort(array, first, (first+last)/2);        // сортировка левой части
        mergeSort(array, ((first+last)/2)+1, last);     // сортировка правой части
        merge(array, first, last);                      // слияние двух частей
    }
}

template<class T>
void combSort(vector<T> *array, unsigned long length)
{
    /* * * Сортировка рассческой * * */

    double fakt = 1.2473309;        // фактор уменьшения
    long int step = length - 1;     // шаг

    while(step >= 1) {
        for(int i = 0; i + step < length; ++i) {
            // проход по массиву с шагом
            if(array->at(i) > array->at(i+step)) {
                // перестановка элементов массива
                swap(array->at(i), array->at(i+step));
            }
        }
        step /= fakt;   // уменьшить шаг
    }
    // сортировка пузырьком
    bubbleSort(array, length);
}

template<class T>
void shellSort(vector<T> *array, unsigned long length)
{
    /* * * Сортировка методом Шелла * * */

    long int step = length/2;   // шаг
    while(step > 0) { // пока шаг не 0
        for (int i = 0; i < (length-step); i++) {
            int j = i;  // начиная с i-го элемента
            while (j >= 0 && array->at(j) > array->at(j+step)) {
                // пока не пришли к началу массива и пока рассматриваемый элемент больше,
                // чем элемент находящийся на расстоянии шага
                swap(array->at(j), array->at(j+step));  // перестановка элементов массива
            }
        }
        step = step/2;  // уменьшить шаг
    }
}

template<class T>
void quickSort(vector<T> *array, unsigned long last)    // ?
{
    /* * * Быстрая сортировка * * */

    // указатели на исходные места
    int i = 0;
    long int j = last-1;
    T middle_element = array->at(last>>1);  // центральный элемент массива

    // разделение массива
    while(i <= j) {
        while(array->at(i) < middle_element) i++;
        while(array->at(j) > middle_element) j--;

        if(i <= j) {
            // перестановка элементов массива
            swap(array->at(i), array->at(j));
            i++;
            j--;
        }
    }
    // рекурсивные вызовы, если есть, что сортировать
    if(j > 0) quickSort(array, j);
    if(last > i) quickSort(array+i, last-i);
}