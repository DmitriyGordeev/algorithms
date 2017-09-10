#include "Algos.h"
#include <string>
#include <iostream>

using namespace std;

void Algos::bubble_sort(int *data, int n) {
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < n - 1; j++) {
            if(data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
        }
    }
}

void Algos::second_bubble_sort(int *data, int n) {

    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(data[i] > data[j]) {
                swap(data[i], data[j]);
            }
        }
    }
}


void Algos::qsort_rec(int* data, int b, int e) {

    int l = b;
    int r = e;
    int p = data[(l + r) / 2];

    while(l <= r)
    {
        while(data[l] < p) l++;
        while(data[r] > p) r--;

        if(l <= r)
            swap(data[l++], data[r--]);
    }

    if(b < r)
        qsort_rec(data, b, r);
    if(e > l)
        qsort_rec(data, l, e);
}

void Algos::qsort(int* data, int n) {
    qsort_rec(data, 0, n - 1);
}


void Algos::insertion_sort(int* data, int n) {

    for(int i = 0 ; i < n; i++)
    {
        for(int j = i; j > 0; j--) {
            if(data[j] < data[j - 1])
                swap(data[j], data[j - 1]);
            else
                break;
        }
    }
}

void Algos::selection_sort(int* data, int n) {

    for(int i = 0; i < n - 1; i++)
    {
        int start_index = i;

        // 1. search min element in current subsequence:
        int min_value = data[start_index];
        int min_index = start_index;
        for(int j = start_index + 1; j < n; j++) {
            if(data[j] < min_value) {
                min_value = data[j];
                min_index = j;
            }
        }

        cout << "min element: " << min_value << " | min_index = " << min_index << endl;

        // 2. proceeding to find first unordered occurence:
        for(int j = start_index; j < n - 1; j++) {
            if(data[j] > data[min_index]) {
                swap(data[j], data[min_index]);
                cout << "swap(" << data[j] << ", " << data[j + 1] << ")" << endl;
                break;
            }
        }


        for(size_t l = 0; l < n; l++)
            cout << data[l] << " , ";
        cout << endl;

    }

}

void Algos::shaker_sort(int* data, int n) {

    for (int l = 0, r = n - 1; l < r;)
    {
        // from beginning:
        for (int i = l; i < r; i++) {
            if (data[i + 1] < data[i]) {
                swap(data[i], data[i + 1]);
                cout << "right: swap(" << data[i] << ", " << data[i + 1] << ")" << endl;
            }
        }
        r--;


        // output:
        for(size_t i = 0; i < n; i++) {
            cout << data[i] << " , ";
        }
        cout << endl;


        // from end:
        for (int i = r; i > l; i--) {
            if (data[i - 1] >  data[i]) {
                swap(data[i - 1], data[i]);
                cout << "left: swap(" << data[i - 1] << ", " << data[i] << ")" << endl;
            }
        }
        l++;


        // output:
        for(size_t i = 0; i < n; i++) {
            cout << data[i] << " , ";
        }
        cout << endl << endl;

    }

}