#include <omp.h>
#include <iostream>
#include <cmath>

using namespace std;

double f(double x)
{
    double result = x;

    for (int j = 0; j < 1000000; j++)
    {
        result = sin(result) + cos(result) + sqrt(result * result + 1.0);
    }

    return result;
}

int main()
{
    double a[100], b[100];

    for (int i = 0; i < 100; i++)
        b[i] = i + 1;

    #pragma omp parallel for
    for (int i = 0; i < 100; i++)
    {
        a[i] = f(b[i]);
        b[i] = 2 * a[i];
    }

    double result = 0.0;

    #pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < 100; i++)
        result += (a[i] + b[i]);

    cout << "Result = " << result << endl;

    return 0;
}