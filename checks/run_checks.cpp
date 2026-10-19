#include <iostream>
#include <vector>
#include <cassert>
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

template <class T>
void check(void (*fn)(std::vector<T>&), std::vector<T> input) {
    auto expected = input;
    std::sort(expected.begin(), expected.end());
    fn(input);
    if (input != expected) {
        std::cerr << "FAIL!\n";
        std::exit(1);
    }
}

template <class T, class F>А
void run_all(F fn) {
    check<T>(fn, {});
    check<T>(fn, {42});
    check<T>(fn, {-9, -3, 0, 2, 8, 17});
    check<T>(fn, {9, 7, 5, 3, 1, -1});
    check<T>(fn, {4, -2, 4, 0, -2, 9, 1, 0, -7});
    check<T>(fn, {12, 0, 5, 3, 11, 2, 8, 6, 1, 4, 7, 10, 9});
}

int main() {
    run_all<int>(ins_sort<int>);
    run_all<int>(sel_sort<int>);
    run_all<int>(exc_sort<int>);
    run_all<int>(bub_sort<int>);
    run_all<int>(bub_opt_sort<int>);
    run_all<int>(bin_ins_sort<int>);
    run_all<int>(shk_sort<int>);
    run_all<int>(shel_sort<int>);
    run_all<int>(qck_sort<int>);
    run_all<int>(ext_two_phase<int>);
    run_all<int>(ext_one_phase<int>);
    run_all<int>(ext_natural<int>);

    std::cout << "ALL TESTS PASSED!\n";
    return 0;
}