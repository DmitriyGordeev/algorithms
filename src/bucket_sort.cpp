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


// todo: сделать тесты
int bucket_sort::find__optimized(int value) {
    if (m_buckets.empty())
        return -1;

    if (value < *m_buckets[0].begin())
        return (m_buckets[0].size() < m_max_bucket_size) ? 0 : -1;

    if (value > *m_buckets.back().rbegin())
        return (m_buckets.back().size() < m_max_bucket_size) ? m_buckets.size() - 1 : m_buckets.size();

    int cursor = 0;
    int index_l = 0;
    int index_r = m_buckets.size() - 1;
    while(index_l != index_r) {
        cursor = (index_l + index_r) / 2;

        // check cursor-ed bucket ranges
        if (value >= *m_buckets[cursor].begin() && value <= *m_buckets[cursor].rbegin()) {
            return cursor;
        }

        // check the left neighbor
        if (cursor > 0) {
            if (value < *m_buckets[cursor - 1].rbegin()) {
                index_r = cursor - 1;
                continue;
            }
            if (value == *m_buckets[cursor - 1].rbegin())
                return cursor - 1;
        }

        // check the right neighbor
        if (cursor < m_buckets.size() - 1) {
            if (value > *m_buckets.back().begin()) {
                index_l = cursor + 1;
                continue;
            }
            if (value == *m_buckets.back().begin())
                return cursor + 1;
        }

        // if cursor didn't change we leave with cursor-ed bucket
        if (cursor == (index_l + index_r) / 2)
            return cursor;
    }

    return index_l;


//    int cursor = 0;
//    int index_l = 0;
//    int index_r = m_buckets.size() - 1;
//    while(index_l != index_r) {
//        cursor = (index_l + index_r) / 2;
//        if (value < *m_buckets[cursor].begin())
//            index_r = cursor;
//        if (value > *m_buckets[cursor].rbegin())
//            index_l = cursor;
//    }
//
//
//    if (m_buckets[cursor].size() == m_max_bucket_size) {
//        // меньше сущ. минимума
//        if (cursor == 0 && value < *m_buckets[cursor].begin())
//            return -1;
//
//        // больше сущ. максимума
//        if (cursor == m_buckets.size() - 1 && value > *m_buckets[cursor].rbegin())
//            return (int)m_buckets.size();
//    }





    return cursor;

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