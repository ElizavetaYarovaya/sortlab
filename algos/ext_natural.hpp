#pragma once
#include "ext_utils.hpp"
#include <vector>

namespace sorte {
template <class T>
void ext_natural(std::vector<T>& v) {
    if (v.size() < 2) return;
    aux::TempPool pool;
    const auto main_f = pool.make("nat_main"), f1 = pool.make("nat_f1"), f2 = pool.make("nat_f2");
    aux::dump(main_f, v);
    while (true) {
        const std::size_t runs = aux::split_natural<T>(main_f, f1, f2);
        if (runs <= 1) { v = aux::load<T>(f1); return; }
        aux::merge_natural<T>(f1, f2, main_f);
    }
}
extern template void ext_natural<int>(std::vector<int>&);
extern template void ext_natural<double>(std::vector<double>&);
}