#pragma once
#include <cstddef>
#include <vector>

namespace sorte {
template <class T>
void shel_sort(std::vector<T>& arr) {
    for (std::size_t gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (std::size_t i = gap; i < arr.size(); ++i) {
            T key = arr[i];
            std::size_t j = i;
            while (j >= gap && key < arr[j - gap]) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}
extern template void shel_sort<int>(std::vector<int>&);
extern template void shel_sort<double>(std::vector<double>&);
}