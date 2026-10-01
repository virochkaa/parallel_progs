#include <omp.h>
#include <iostream>

using namespace std;

int main()
{
    char hello_string[] = "Hello World from thread";

    int id = 1234;
    int size = 0;

    cout << "Initial thread: id = " << id
         << ", size = " << size << endl;

    #pragma omp parallel shared(id, hello_string)
    {
        int size = omp_get_num_threads();

        cout << "Number of threads = " << size << endl;
        cout.flush();

        id = omp_get_thread_num();

        cout << hello_string << " " << id << endl;
        cout.flush();
    }

    return 0;
}