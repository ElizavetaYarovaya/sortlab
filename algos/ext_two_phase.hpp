#pragma once
#include "ext_utils.hpp"
#include <cstddef>
#include <vector>

namespace sorte {
template <class T>
void ext_two_phase(std::vector<T>& v) {
    if (v.size() < 2) return;
    aux::TempPool pool;
    const auto main_f = pool.make("tp_main"), f1 = pool.make("tp_f1"), f2 = pool.make("tp_f2");
    aux::dump(main_f, v);
    for (std::size_t len = 1; len < v.size();) {
        aux::split_fixed<T>(main_f, f1, f2, len);
        aux::merge_fixed<T>(f1, f2, main_f, len);
        if (len > v.size() / 2) break;
        len *= 2;
    }
    v = aux::load<T>(main_f);
}
extern template void ext_two_phase<int>(std::vector<int>&);
extern template void ext_two_phase<double>(std::vector<double>&);
}