#pragma once
#include <cstddef>
#include <utility>
#include <vector>

namespace sorte {
template <class T>
void exc_sort(std::vector<T>& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[i]) std::swap(arr[i], arr[j]);
        }
    }
}
extern template void exc_sort<int>(std::vector<int>&);
extern template void exc_sort<double>(std::vector<double>&);
}