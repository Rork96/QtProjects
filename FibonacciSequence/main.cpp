#include <iostream>
#include <ctime>

//using namespace std;
using std::cout;
using std::cin;
using std::endl;

unsigned long long fibSequence(unsigned short);     // Последовательность Фибоначчи (рекурсивный способ)
int fSequence(int);                                 // Последовательность Фибоначчи (итеративный способ)

int main() {
    // Последовательность Фибоначчи: 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233
    // Новое число равно сумме предыдущих двух: 1+1=2 ...
    cout << "Fibonacci sequence" << endl << endl;
    cout << "Enter how long you wish the Fibanacci series to display: ";
    unsigned short number;
    cin >> number;
    cout << endl << endl;

    // region Последовательность Фибоначчи (итеративный способ)
    const clock_t s_time = clock();    // Начальное время

    int fSeq = fSequence(number);                       // Последовательность Фибоначчи (итеративный способ)
    cout << "Fibonacci sequence: " << fSeq << endl;

    // Время выполнения алгоритма
    clock_t e_time = clock();
    cout << "Quick algorithm time = " << (double) (e_time-s_time)/CLOCKS_PER_SEC << endl << endl;
    // endregion Последовательность Фибоначчи (быстрый способ)

    // region Последовательность Фибоначчи (рекурсия)
    const clock_t start_time = clock();    // Начальное время

    unsigned long long sequence = fibSequence(number);  // Последовательность Фибоначчи (рекурсивный способ)
    cout << "Fibonacci sequence: " << sequence << endl;

    // Время выполнения алгоритма
    clock_t end_time = clock();
    cout << "Recursion algorithm time = " << (double) (end_time-start_time)/CLOCKS_PER_SEC << endl << endl;
    // endregion Последовательность Фибоначчи (рекурсия)

    return 0;
}

// region Последовательность Фибоначчи

unsigned long long fibSequence(unsigned short number)
{
    /* * * Последовательность Фибоначчи (рекурсивный способ) * * */

    // fibSequence(0) = 0 и fibSequence(1) = 1
    if(number < 2) {
        return number;
    }
    else {
        return fibSequence(number-1) + fibSequence(number-2);
    }
    //return number < 2? number : fibSequence(number-1) + fibSequence(number-2);
}

int fSequence(int number)
{
    /* * * Последовательность Фибоначчи (итеративный способ) * * */

    // Нужно хранить в памяти только два предыдущих числа
    unsigned long oldValue = 0;
    unsigned long value = 1;
    unsigned long hold;

    if(number < 1)
        return(0);

    for(int j = 1; j < number; j++) {
        hold = value;
        value += oldValue;
        oldValue = hold;
    }
    return value;
}
// endregion Последовательность Фибоначчи