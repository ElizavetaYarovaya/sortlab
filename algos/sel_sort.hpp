#pragma once
#include <cstddef>
#include <utility>
#include <vector>

namespace sorte {
template <class T>
void sel_sort(std::vector<T>& arr) {
    for (std::size_t i = 0; i < arr.size(); ++i) {
        std::size_t best = i;
        for (std::size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[best]) best = j;
        }
        if (best != i) std::swap(arr[i], arr[best]);
    }
}
extern template void sel_sort<int>(std::vector<int>&);
extern template void sel_sort<double>(std::vector<double>&);
}