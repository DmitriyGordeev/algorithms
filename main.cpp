#include <iostream>
#include <vector>
#include "Algos.h"
using namespace std;


int main()
{
    int arr[5] = { 8, 1, 19, 6, 4 };
    for(size_t i = 0; i < 5; i++) {
        cout << arr[i] << " , ";
    }
    cout << endl << endl;


    Algos::counting_sort(arr, 5, 100);
    cout << endl << "final: " << endl;
    for(size_t i = 0; i < 5; i++) {
        cout << arr[i] << " , ";
    }

    return 0;
}