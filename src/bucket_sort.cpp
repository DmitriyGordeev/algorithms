#include "bucket_sort.h"
using std::set;

bucket_sort::bucket_sort(size_t max_bucket_size) : m_max_bucket_size(max_bucket_size) {}

void bucket_sort::add(int value) {

    if (m_buckets.empty()) {
        set<int> s;
        s.insert(value);
        m_buckets.push_back(std::move(s));
    }

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
    int tgt_bucket_index = -1;
    for(int i = 0; i < m_buckets.size(); i++) {

        // bucket еще не полный
        if (m_buckets[i].size() < m_max_bucket_size) {
            tgt_bucket_index = i;
            continue;
        }

        // если value попадает внутрь крайних значений этого бакета - попали,
        // искать больше не нужно
        if (*m_buckets[i].begin() <= value && value < *m_buckets[i].rbegin()) {
            tgt_bucket_index = i;
            break;
        }


        // если бакет уже полный, а value больше его макс. значения, значит надо идти дальше
        if (m_buckets[i].size() == m_max_bucket_size && value > *m_buckets[i].rbegin()) {
            tgt_bucket_index = i + 1;
            continue;
        }
    }

    return tgt_bucket_index;
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