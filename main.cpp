#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void foo(int* data, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1; j++) {
            if(data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
        }
    }
}

int main() {

    int arr[5] = { 8, 4, 3, 19, 1 };
    foo(arr, 5);

    for(int i = 0; i < 5; i++)
        cout << arr[i] << endl;

    return 0;
}