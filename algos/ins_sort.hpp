#pragma once
#include <cstddef>
#include <vector>

namespace sorte {
template <class T>
void ins_sort(std::vector<T>& arr) {
    for (std::size_t i = 1; i < arr.size(); ++i) {
        T cur = arr[i];
        std::size_t j = i;
        while (j > 0 && cur < arr[j - 1]) { arr[j] = arr[j - 1]; --j; }
        arr[j] = cur;
    }
}
extern template void ins_sort<int>(std::vector<int>&);
extern template void ins_sort<double>(std::vector<double>&);
}