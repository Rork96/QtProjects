#include <iostream>
#include <ctime>

//using namespace std;
using std::cout;
using std::cin;
using std::endl;

unsigned long long recursive_factorial(unsigned int);       // Факториал (рекурсивно)
unsigned long long iterative_factorial(unsigned int);       // Факториал (итеративно)

int main() {
    cout << "Factorial" << endl << endl;
    cout << "Enter number: ";
    unsigned number;
    cin >> number;
    cout << endl << endl;

    // region Факториал (итеративно)
    const clock_t s_time = clock();    // Начальное время

    unsigned long long fact = recursive_factorial(number);      // Факториал (итеративно)
    cout << "Factorial: " << fact << endl;

    // Время выполнения алгоритма
    clock_t e_time = clock();
    cout << "Iteration algorithm time = " << (double) (e_time-s_time)/CLOCKS_PER_SEC << endl << endl;
    // endregion Факториал (итеративно)

    // region Факториал (рекурсивно)
    const clock_t start_time = clock();    // Начальное время

    unsigned long long factor = iterative_factorial(number);    // Факториал (рекурсивно)
    cout << "Factorial: " << factor << endl;

    // Время выполнения алгоритма
    clock_t end_time = clock();
    cout << "Recursion algorithm time = " << (double) (end_time-start_time)/CLOCKS_PER_SEC << endl << endl;
    // endregion Факториал (рекурсивно)

    return 0;
}

// region Факториал

unsigned long long recursive_factorial(unsigned int n)
{
    /* * * Факториал (рекурсивно) * * */

    if(n < 2) {
        return 1;
    }
    else {
        return n * recursive_factorial( n - 1 );
    }
    //return n < 2 ? 1 : n * recursive_factorial( n - 1 );
}

unsigned long long iterative_factorial(unsigned int n)
{
    /* * * Факториал (итеративно) * * */

    unsigned long long factorial = 1;

    for(unsigned i = 2; i <= n; i++)
        factorial *= i;

    return factorial;
}
// endregion Факториал