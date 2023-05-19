#include "sort.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

void sort::bubble_sort(int *data, int n) {
    for(size_t i = 0; i < n; i++) {
        for(size_t j = 0; j < n - 1; j++) {
            if(data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
        }
    }
}

void sort::qsort_rec(int* data, int b, int e) {

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

void sort::qsort(int* data, int n) {
    qsort_rec(data, 0, n - 1);
}

void sort::insertion_sort(int* data, int n) {

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

void sort::selection_sort(int* data, int n) {
    if (n <= 1 || !data)
        return;

    int min_value = data[0];
    int min_j = 0;
    for(int i = 0; i < n - 1; i++) {
        min_j = i;
        min_value = data[i];

        for(int j = i + 1; j < n; j++) {
            if (data[j] < min_value) {
                min_value = data[j];
                min_j = j;
            }
        }

        if (min_value < data[i])
            swap(data[min_j], data[i]);
    }
}

void sort::shaker_sort(int* data, int n) {

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

void sort::counting_sort(int* data, int n, int MAX_VALUE) {

    int* c = new int[MAX_VALUE];
    for(int i = 0; i < MAX_VALUE; i++) {
        c[i] = 0;
    }

    // fill count array:
    for(int i = 0; i < n; i++) {
        if(data[i] > 0 && data[i] < MAX_VALUE) {
            c[data[i]]++;
        }
    }

    cout << "count array: ";
    for(size_t i = 0; i < MAX_VALUE; i++) {
        cout << c[i] << " , ";
    }
    cout << endl << endl;


    // change input array:
    int start_point = 0;
    for(int i = 0; i < MAX_VALUE; i++)
    {
        int count = c[i];
        int value = i;
        for(int j = 0; j < count; j++) {
            data[start_point + j] = value;
        }
        start_point += c[i];
    }

    delete c;
}

int* sort::merge_sort_rec(int* data, int l, int r) {

    if (l == r) {
        return data + l;
    }

    int middle = (l + r) / 2;
    int *left =  merge_sort_rec(data, l, middle);
    int *right = merge_sort_rec(data, middle + 1, r);

    return merge_sort_merge(left, right, middle - l + 1, r - middle);
}

int* sort::merge_sort_merge(int* left, int* right, int left_n, int right_n) {

    // TODO: refactor recursive "new"
    int* output = new int[left_n + right_n];

    int l = 0;
    int r = 0;
    int i = 0;

    while(l < left_n && r < right_n) {
        if(left[l] <= right[r]) {
            output[i] = left[l];
            i++;
            l++;
        }
        else {
            output[i] = right[r];
            i++;
            r++;
        }
    }


    // tails:
    if(l < left_n) {
        for(;l < left_n; l++) {
            output[i] = left[l];
            i++;
        }
    }
    else if(r < right_n) {
        for(;r < right_n; r++) {
            output[i] = right[r];
            i++;
        }
    }

    return output;
}

int* sort::merge_sort(int* data, int n) {
    return merge_sort_rec(data, 0, n - 1);
}