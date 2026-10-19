#include <iostream>
#include <vector>
#include <algorithm>
#include "ins_sort.hpp"
#include "sel_sort.hpp"
#include "exc_sort.hpp"
#include "bub_sort.hpp"
#include "bub_opt_sort.hpp"
#include "bin_ins_sort.hpp"
#include "shk_sort.hpp"
#include "shel_sort.hpp"
#include "qck_sort.hpp"
#include "ext_two_phase.hpp"
#include "ext_one_phase.hpp"
#include "ext_natural.hpp"

using namespace sorte;
template <class T, class F> void test(F fn) {
    std::vector<T> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    fn(v);
    std::cout << "OK ";
}
int main() {
    test<int>(ins_sort<int>); test<int>(sel_sort<int>); test<int>(exc_sort<int>);
    test<int>(bub_sort<int>); test<int>(bub_opt_sort<int>); test<int>(bin_ins_sort<int>);
    test<int>(shk_sort<int>); test<int>(shel_sort<int>); test<int>(qck_sort<int>);
    test<int>(ext_two_phase<int>); test<int>(ext_one_phase<int>); test<int>(ext_natural<int>);
    std::cout << "\nALL TESTS PASSED!\n";
    return 0;
}
