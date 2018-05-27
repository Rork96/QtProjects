#include <iostream>
#include <vector>

using namespace std;

// region Функции сортировки

template<class T>
void bubbleSort(vector<T>*);        // Сортировка пузырьком
template<class T>
void insertSort(vector<T>*);        // Сортировка вставками
template<class T>
void selectSort(vector<T>*);        // Сортировка выбором
template<class T>
void merge(vector<T>*, T, T);       // Функция, сливающая массивы (для сортировки слиянием)
template<class T>
void mergeSort(vector<T>*, T, T);   // Рекурсивная процедура сортировки слиянием
template<class T>
void combSort(vector<T>*);          // Сортировка рассческой
template<class T>
void shellSort(vector<T>*);         // Сортировка методом Шелла
template<class T>
void quickSort(vector<T>*, T, T);   // Быстрая сортировка

// endregion Функции сортировки

int main(int argc, char* argv[])
{
    srand(time(NULL));

    cout << "Enter array length: ";
    unsigned long size_array;           // длинна массива
    cin >> size_array;

    // region Заполнение массива
    cout << "Array:" << endl;
    vector<int> *sorted_array = new vector<int>(size_array);
    for(int i = 0; i < size_array; i++) {
        sorted_array->at(i) = rand() % 100;
        cout << sorted_array->at(i) << " ";
    }
    cout << "\n";
    // endregion Заполнение массива

    // region Выбор типа сортировки
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
            bubbleSort(sorted_array);         // Сортировка пузырьком
            break;
        case 2:
            insertSort(sorted_array);         // Сортировка вставками
            break;
        case 3:
            selectSort(sorted_array);         // Сортировка выбором
            break;
        case 4:
            mergeSort(sorted_array, 0,  (int) sorted_array->size()-1);     // Сортировка слиянием
            break;
        case 5:
            combSort(sorted_array);           // Сортировка рассческой
            break;
        case 6:
            shellSort(sorted_array);          // Сортировка Шелла
            break;
        case 7:
            quickSort(sorted_array, 0, (int) sorted_array->size()-1);          // Быстрая сортировка2
            break;
        default:
            cout << "Wrong number!";
            return 0;
    }
    // endregion Выбор типа сортировки

    // region Вывод отсортированного массива
    cout << "Sorted array:" << endl;
    for(int i = 0; i < size_array; ++i) {
        cout << sorted_array->at(i) << " ";
    }
    cout << "\n";
    // endregion Вывод отсортированного массива

    delete[] sorted_array;
    system("pause");
    return 0;
}

// region Cортировки

// region Сортировка пузырьком

template<class T>
void bubbleSort(vector<T> *array)
{
    /* * * Сортировка пузырьком * * */
    bool exit = false; // болевая переменная для выхода из цикла, если массив отсортирован
    unsigned long length = array->size();

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
// endregion Сортировка пузырьком

// region Сортировка вставками

template<class T>
void insertSort(vector<T> *array)
{
    /* * * Сортировка вставками * * */

    unsigned long length = array->size();

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
// endregion Сортировка вставками

// region Сортировка выбором

template<class T>
void selectSort(vector<T> *array)
{
    /* * * Сортировка выбором * * */

    unsigned long length = array->size();

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
// endregion Сортировка выбором

// region Сортировка слиянием

template<class T>
void merge(vector<T> *array, T first, T last)
{
    /* * * Функция, сливающая массивы (для сортировки слиянием) * * */

    T middle, start, final;
    vector<T> *mas = new vector<T>(array->size());

    middle = (first+last)/2;                // вычисление среднего элемента
    start = first;                          // начало левой части
    final = middle+1;                       // начало правой части

    for(T j = first; j <= last; j++) {    // выполнять от начала до конца
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
    for(T j = first; j <= last; j++)
        array->at(j) = mas->at(j);

    //delete[] mas;
}

template<class T>
void mergeSort(vector<T> *array, T first, T last)
{
    /* * * Рекурсивная процедура сортировки слиянием * * */

    if(first < last) {
        mergeSort(array, first, (first+last)/2);        // сортировка левой части
        mergeSort(array, ((first+last)/2)+1, last);     // сортировка правой части
        merge(array, first, last);                      // слияние двух частей
    }
}
// endregion Сортировка слиянием

// region Сортировка рассческой

template<class T>
void combSort(vector<T> *array)
{
    /* * * Сортировка рассческой * * */

    unsigned long length = array->size();
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
    bubbleSort(array);
}
// endregion Сортировка рассческой

// region Сортировка Шелла

template<class T>
void shellSort(vector<T> *array)
{
    /* * * Сортировка методом Шелла * * */

// Обычная последовательность Шилла

    unsigned long length = array->size();
    long int step = length/2;   // шаг

    while(step > 0) { // пока шаг не 0
        for(int i = 0; i < length-step; i++) {
            int j = i;  // начиная с i-го элемента
            while (j >= 0 && array->at(j) > array->at(j+step)) {
                // пока не пришли к началу массива и пока рассматриваемый элемент больше,
                // чем элемент находящийся на расстоянии шага
                swap(array->at(j), array->at(j+step));  // перестановка элементов массива
                j--;
            }
        }
        step = step/2;  // уменьшить шаг
    }
}
// endregion Сортировка Шелла

// region Быстрая сортировка

template<class T>
void quickSort(vector<T> *array, T left, T right)
{
    /* * * Быстрая сортировка * * */

    // указатели на исходные места
    T i = left;
    T j = right;
    // центральный элемент массива
    T pivot = array->at((left+right)/2);

    // разделение массива
    while(i <= j) {
        while(array->at(i) < pivot) i++;
        while (array->at(j) > pivot) j--;
        if (i <= j) {
            // перестановка элементов массива
            swap(array->at(i), array->at(j));
            i++;
            j--;
        }
    }
    // рекурсивные вызовы, если есть, что сортировать
    if(left < j)
        quickSort(array, left, j);
    if(i < right)
        quickSort(array, i, right);
}
// endregion Быстрая сортировка

// endregion Сортировки