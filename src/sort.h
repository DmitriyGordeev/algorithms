#ifndef SORT_STDALGORITHMS_H
#define SORT_STDALGORITHMS_H


class sort {
public:
    static void bubble_sort(int* data, int n);

    static void qsort_rec(int* data, int l, int r);
    static void qsort(int* data, int n);

    static void insertion_sort(int* data, int n);
    static void selection_sort(int* data, int n);

    static void shaker_sort(int* data, int n);
    static void counting_sort(int* data, int n, int MAX_VALUE);

    static int* merge_sort_rec(int* data, int l, int r);
    static int* merge_sort_merge(int* left, int* right, int left_n, int right_n);
    static int* merge_sort(int* data, int n);

};


#endif //SORT_STDALGORITHMS_H
