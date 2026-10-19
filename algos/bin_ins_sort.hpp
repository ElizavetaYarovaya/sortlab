#pragma once
#include <cstddef>
#include <vector>

namespace sorte {
template <class T>
void bin_ins_sort(std::vector<T>& arr) {
    for (std::size_t i = 1; i < arr.size(); ++i) {
        T key = arr[i];
        std::size_t lo = 0;
        std::size_t hi = i;
        while (lo < hi) {
            const std::size_t mid = lo + (hi - lo) / 2;
            if (key < arr[mid]) hi = mid;
            else lo = mid + 1;
        }
        for (std::size_t j = i; j > lo; --j) {
            arr[j] = arr[j - 1];
        }
        arr[lo] = key;
    }
}
extern template void bin_ins_sort<int>(std::vector<int>&);
extern template void bin_ins_sort<double>(std::vector<double>&);
}