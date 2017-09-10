#include <iostream>
#include <vector>
#include "Algos.h"
using namespace std;


int main()
{
    int arr[5] = { 8, 1, 5, 17, 6 };
    for(size_t i = 0; i < 5; i++) {
        cout << arr[i] << " , ";
    }
    cout << endl << endl;


    Algos::shaker_sort(arr, 5);
    cout << endl << "final: " << endl;
    for(size_t i = 0; i < 5; i++) {
        cout << arr[i] << " , ";
    }

    return 0;
}