#include "bucket_sort.h"
using std::set;

bucket_sort::bucket_sort(size_t max_bucket_size) : m_max_bucket_size(max_bucket_size) {}

void bucket_sort::add(int value) {

    if (m_buckets.empty()) {
        set<int> s;
        s.insert(value);
        m_buckets.push_back(std::move(s));
    }

    // 1. определить в какой бакет положить новое значение
    // 2. превысим ли макс значение max_bucket_size, если положим? - нужно ли создавать новый бакет?



    int suitable_bucket_index = find_bucket(value);
    if (suitable_bucket_index < 0) {
        // create new bucket with new value and insert at the beginning
        set<int> new_bucket {value};
        m_buckets.insert(m_buckets.begin(), new_bucket);
    }
    else if (suitable_bucket_index == m_buckets.size()) {
        // create new bucket with new value and push back to the end
        set<int> new_bucket {value};
        m_buckets.push_back(new_bucket);
    }
    else {
        // insert new value into found bucket and split,
        // if size will exceed max allowed bucket size
        if (m_buckets.size() == m_max_bucket_size) {
            add_split_bucket(suitable_bucket_index, value);
        }
        else
            m_buckets[suitable_bucket_index].insert(value);
    }
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
                // вышел за рамки текущего бакета
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


void bucket_sort::add_split_bucket(int bucket_index, int value) {
    std::set<int>& bucket = m_buckets[bucket_index];
    int middle_value = (*bucket.begin() + *bucket.rbegin()) / 2;
    set<int> s2;

    auto itr = bucket.begin();
    for(; itr != bucket.end(); ++itr) {
        if (*itr <= middle_value) {
            s2.insert(*itr);
        }
        else
            break;
    }

    // s2 stores values <= middle_value
    // 'bucket' stores values higher than middle_value
    bucket.erase(bucket.begin(), itr);

    if (value <= middle_value)
        s2.insert(value);
    else
        bucket.insert(value);

    std::swap(s2, bucket);
    m_buckets.insert(m_buckets.begin() + bucket_index + 1, s2);
}