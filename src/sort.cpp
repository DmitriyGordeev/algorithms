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
    if (!data || n <= 1) return;

    for (int l = 0, r = n - 1; l < r;)
    {
        // from beginning:
        for (int i = l; i < r; i++) {
            if (data[i + 1] < data[i])
                swap(data[i], data[i + 1]);
        }
        r--;

        // from end:
        for (int i = r; i > l; i--) {
            if (data[i - 1] >  data[i])
                swap(data[i - 1], data[i]);
        }
        l++;
    }
}

void sort::counting_sort(int* data, int n, int min_value, int max_value) {
    if (!data || n <= 1 || min_value >= max_value)
        return;

    // 1. allocate hashing array and init with zeros
    auto size = max_value - min_value;
    int* hash_array = new int[size];
    for (int i = 0; i < size; i++)
        hash_array[i] = 0;

    // 2. go through original array and hash it
    for(int i = 0; i < n; i++) {
        if (data[i] > max_value) {
            cout << "array has a value at index " << i << " greater than specified max_value " << max_value << "\n";
            return;
        }
        if (data[i] < min_value) {
            cout << "array has a value at index " << i << " lower than specified min_value " << min_value << "\n";
            return;
        }

        int hashing_index = data[i] - min_value;    // write normalized index (from 0 to (max_value - min_value))
        hash_array[hashing_index] += 1;
    }

    // 3. iterate through filled hash array to sort original array
    int i = 0;
    int j = 0;
    while(i < size) {
        while (hash_array[i] > 0) {
            data[j] = i + min_value;    // restore original value from index
            hash_array[i]--;
            j++;
        }
        i++;
    }

    // cleanup temporary memory
    delete[] hash_array;
}



int* sort::merge_sort_rec(int* data, int l, int r, int* output) {

    if (l == r) {
        output[l] = data[l];
        return output + l;
    }

    int middle = (l + r) / 2;
    int *left = merge_sort_rec(data, l, middle, output);
    int *right = merge_sort_rec(data, middle + 1, r, output);

    merge_sort_merge(left, middle - l + 1, l,
                     right, r - middle,
                     output);

    return output + l;
}

void sort::merge_sort_merge(int* left, int left_size, int left_index,
                             int* right, int right_size,
                             int* output) {

    int l = 0;
    int r = 0;
    int i = 0;

    int* temporary = new int[left_size + right_size];

    while(l < left_size && r < right_size) {
        if (left[l] <= right[r]) {
            temporary[i] = left[l];
            l++;
        }
        else {
            temporary[i] = right[r];
            r++;
        }
        i++;
    }

    // one of the subarrays will not be copied fully, we need to copy remaining tail
    if(l < left_size) {
        for(;l < left_size; l++) {
            temporary[i] = left[l];
            i++;
        }
    }
    else if(r < right_size) {
        for(;r < right_size; r++) {
            temporary[i] = right[r];
            i++;
        }
    }

    // overwrite slice of 'output' with values from 'temporary' and cleanup memory
    for(int j = 0; j < left_size + right_size; j++)
        output[left_index + j] = temporary[j];
    delete[] temporary;
}

int* sort::merge_sort(int* data, int n) {
    if (n <= 1)
        return data;
    int* output = new int[n];
    output = merge_sort_rec(data, 0, n - 1, output);
    // todo: change 'data' and delete 'output' ?
    return output;
}


struct radix_node {
    radix_node() = default;
    radix_node(int value) : m_value(value) {}
    radix_node* next {nullptr};
    int m_value {0};
};

int* sort::radix_sort(int* data, int n) {
    if (n <= 1 || !data)
        return data;

    // 1. searching for the max element
    int max_value = data[0];
    for(int i = 1; i < n; i++) {
        if (data[i] > max_value)
            max_value = data[i];
    }

    // 2. number of digits of the max value
    int d = 1;
    int m = 10;
    while(max_value / m > 1) {
        m *= 10;
        d++;
    }

    radix_node** buckets = new radix_node*[10](); // each bucket is a list

    for(int r = 0; r < d; r++) {    // r - current digit starting from the lowest order

        // loop through array and calculate target digit depending on r
        for(int i = 0; i < n; i++) {
             int digit = (int)(data[i] / pow(10, r)) % 10;

             // add to the bucket by index of [digit]
             if (!buckets[digit]) {
                 // if no nodes in the bucket - create one
                 buckets[digit] = new radix_node(data[i]);
             }
             else {
                 // add to the last existing node
                 radix_node* cursor = buckets[digit];
                 while(cursor->next)
                     cursor = cursor->next;
                 cursor->next = new radix_node(data[i]);
             }
        }

        // Extract one by one from bucketed structure changing original 'data' array
        int data_index = 0;
        for(int i = 0; i < 10; i++) {
            if (!buckets[i])
                continue;

            // TODO: удалить элемент, когда из его убирают из bucket

            // iterate through current bucket's inner list and extract values into 'data'
            radix_node* cursor = buckets[i];

            if (data_index >= n) {      // todo: удалить сообщение
                cout << "[0] Error: data_index should not be greater than original array size (n)" << endl;
                return nullptr;
            }

            data[data_index] = cursor->m_value;
            data_index++;
            buckets[i] = nullptr;


            radix_node* prev_node = cursor;
            while(cursor->next) {
                cursor = cursor->next;
                delete prev_node;   // deleting previously saved node's ref after switching cursor

                if (data_index >= n) {  // todo: удалить сообщение
                    cout << "[1] Error: data_index should not be greater than original array size (n)" << endl;
                    return nullptr;
                }

                data[data_index] = cursor->m_value;
                data_index++;
                prev_node = cursor;
            }

            delete prev_node;
        }
    }

    delete[] buckets;
    return data;
}