#pragma once
#include <cstddef>
#include <utility>
#include <vector>

namespace sorte {
template <class T>
void bub_sort(std::vector<T>& arr) {
    for (std::size_t end = arr.size(); end > 1; --end) {
        for (std::size_t i = 1; i < end; ++i) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
            }
        }
    }
}
extern template void bub_sort<int>(std::vector<int>&);
extern template void bub_sort<double>(std::vector<double>&);
}