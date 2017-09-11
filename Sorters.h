#ifndef INHERITANCE_STDALGORITHMS_H
#define INHERITANCE_STDALGORITHMS_H


class Algos {
public:
    static void bubble_sort(int* data, int n);
    static void second_bubble_sort(int *data, int n);

    static void qsort_rec(int* data, int l, int r);
    static void qsort(int* data, int n);

    static void insertion_sort(int* data, int n);
    static void selection_sort(int* data, int n);
    static void shaker_sort(int* data, int n);
    static void counting_sort(int* data, int n, int MAX_VALUE);

    static int* merge_sort_rec(int* a, int* b, int begin, int end);
    static void merge_sort(int* data, int n);

    static void radix_sort(int* data, int n);
};


#endif //INHERITANCE_STDALGORITHMS_H
