#include "bucket_sort.h"
using std::set;

bucket_sort::bucket_sort(size_t max_bucket_size) : m_max_bucket_size(max_bucket_size) {}

int bucket_sort::add_value(int value) {

    if (m_buckets.empty()) {
        set<int> s;
        s.insert(value);
        m_buckets.push_back(std::move(s));
        return 0;
    }

    // 1. определить в какой бакет положить новое значение
    // 2. превысим ли макс значение max_bucket_size, если положим? - нужно ли создавать новый бакет?



    // todo: если tgt_bucket = -1 -> выход





    return 0;
}


int bucket_sort::find_bucket(int value) {
    int tgt_bucket = -1;
    for(int i = 0; i < m_buckets.size(); i++) {
        if (m_buckets[i].size() > 1) {

            if (*m_buckets[i].begin() <= value && value <= *m_buckets[i].rbegin()) {
                // попали
                tgt_bucket = i;
                break;
            }
            else if (value < *m_buckets[i].begin()) {
                // не стоит смотреть дальше
                break;
            }
            else {
                tgt_bucket = i + 1;
                continue;
            }

        }
        else if (m_buckets[i].size() == 1) {
            if (*m_buckets[i].begin() > value) {
                tgt_bucket = i;
                break;
            }
            else {
                tgt_bucket = i;
                continue;
            }
        }
        else {  // bucket is empty
            tgt_bucket = i;
        }
    }
    return tgt_bucket;
}