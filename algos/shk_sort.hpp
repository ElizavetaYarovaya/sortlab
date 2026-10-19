#pragma once
#include <cstddef>
#include <utility>
#include <vector>

namespace sorte {
template <class T>
void shk_sort(std::vector<T>& arr) {
    if (arr.size() < 2) return;
    std::size_t left = 0;
    std::size_t right = arr.size() - 1;
    while (left < right) {
        for (std::size_t i = left; i < right; ++i) {
            if (arr[i + 1] < arr[i]) std::swap(arr[i], arr[i + 1]);
        }
        --right;
        for (std::size_t i = right; i > left; --i) {
            if (arr[i] < arr[i - 1]) std::swap(arr[i], arr[i - 1]);
        }
        ++left;
    }
}
extern template void shk_sort<int>(std::vector<int>&);
extern template void shk_sort<double>(std::vector<double>&);
}