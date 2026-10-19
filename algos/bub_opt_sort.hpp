#pragma once
#include <cstddef>
#include <utility>
#include <vector>

namespace sorte {
template <class T>
void bub_opt_sort(std::vector<T>& arr) {
    std::size_t end = arr.size();
    while (end > 1) {
        std::size_t lastSwap = 0;
        for (std::size_t i = 1; i < end; ++i) {
            if (arr[i] < arr[i - 1]) {
                std::swap(arr[i], arr[i - 1]);
                lastSwap = i;
            }
        }
        if (lastSwap == 0) break;
        end = lastSwap;
    }
}
extern template void bub_opt_sort<int>(std::vector<int>&);
extern template void bub_opt_sort<double>(std::vector<double>&);
}