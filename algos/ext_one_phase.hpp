#pragma once
#include "ext_utils.hpp"
#include <cstddef>
#include <vector>

namespace sorte {
template <class T>
void ext_one_phase(std::vector<T>& v) {
    if (v.size() < 2) return;
    aux::TempPool pool;
    const auto src = pool.make("op_src");
    auto a = pool.make("op_a"), b = pool.make("op_b"), na = pool.make("op_na"), nb = pool.make("op_nb");
    aux::dump(src, v);
    aux::split_fixed<T>(src, a, b, 1);
    for (std::size_t len = 1; len < v.size();) {
        aux::merge_and_split<T>(a, b, na, nb, len);
        a.swap(na); b.swap(nb);
        if (len > v.size() / 2) break;
        len *= 2;
    }
    v = aux::load<T>(a);
}
extern template void ext_one_phase<int>(std::vector<int>&);
extern template void ext_one_phase<double>(std::vector<double>&);
}