#ifndef ALGORITHMS_BUCKET_SORT_H
#define ALGORITHMS_BUCKET_SORT_H

#include <set>
#include <vector>

class bucket_sort {
public:
    bucket_sort(size_t max_bucket_size);
    int add_value(int value);

    // todo: переделать коменты
    /* returns -1 or n = m_buckets.size()
     * if need to create a new bucket before or after existing range */
    int find_bucket(int value);

protected:
    size_t m_max_bucket_size;
    std::vector<std::set<int>> m_buckets;
};


#endif //ALGORITHMS_BUCKET_SORT_H
