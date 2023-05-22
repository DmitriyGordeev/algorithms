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
    static void counting_sort(int* data, int n, int min_value, int max_value);

    static int* merge_sort_rec(int* data, int l, int r, int* output);
    static void merge_sort_merge(int* left, int left_size, int left_index, int* right, int right_size, int* output);
    static int* merge_sort(int* data, int n);

};


#endif //SORT_STDALGORITHMS_H
