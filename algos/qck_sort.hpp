#pragma once
#include <cstddef>
#include <utility>
#include <vector>

namespace sorte {
namespace inner {
template <class T>
void qck_impl(std::vector<T>& arr, std::ptrdiff_t lo, std::ptrdiff_t hi) {
    while (lo < hi) {
        const T pivot = arr[lo + (hi - lo) / 2];
        std::ptrdiff_t lt = lo, cur = lo, gt = hi;
        while (cur <= gt) {
            if (arr[cur] < pivot) std::swap(arr[lt++], arr[cur++]);
            else if (pivot < arr[cur]) std::swap(arr[cur], arr[gt--]);
            else ++cur;
        }
        if (lt - lo < hi - gt) { qck_impl(arr, lo, lt - 1); lo = gt + 1; }
        else { qck_impl(arr, gt + 1, hi); hi = lt - 1; }
    }
}
}
template <class T>
void qck_sort(std::vector<T>& arr) {
    if (arr.size() > 1) {
        inner::qck_impl(arr, 0, static_cast<std::ptrdiff_t>(arr.size()) - 1);
    }
}
extern template void qck_sort<int>(std::vector<int>&);
extern template void qck_sort<double>(std::vector<double>&);
}