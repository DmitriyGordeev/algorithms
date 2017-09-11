#include <iostream>
#include <vector>
#include "Sorters.h"
using namespace std;

int main()
{
    int arr[5] = {8, 2, 1, 5, 3};

    int* ptr = Sorters::merge_sort(arr, 5);
    for(int i = 0; i < 5; i++)
        cout << ptr[i] << " , ";


    return 0;
}