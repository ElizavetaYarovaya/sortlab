#pragma once
#include <atomic>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace sorte::aux {

class TempPool {
public:
    TempPool() = default;
    TempPool(const TempPool&) = delete;
    TempPool& operator=(const TempPool&) = delete;

    ~TempPool() {
        for (const auto& p : files_) {
            std::error_code ec;
            std::filesystem::remove(p, ec);
        }
    }

    std::filesystem::path make(const std::string& tag) {
        static std::atomic<unsigned long long> seq{0};
        const auto now = std::chrono::steady_clock::now().time_since_epoch().count();
        const auto id = seq.fetch_add(1, std::memory_order_relaxed);
        auto p = std::filesystem::temp_directory_path()
               / (tag + "_" + std::to_string(now) + "_" + std::to_string(id) + ".txt");
        files_.push_back(p);
        return p;
    }

private:
    std::vector<std::filesystem::path> files_;
};

template <class T>
void dump(const std::filesystem::path& p, const std::vector<T>& v) {
    std::ofstream out(p, std::ios::trunc);
    if (!out) throw std::runtime_error("Не открыть файл: " + p.string());
    for (const T& x : v) out << x << '\n';
}

template <class T>
std::vector<T> load(const std::filesystem::path& p) {
    std::ifstream in(p);
    if (!in) throw std::runtime_error("Не открыть файл: " + p.string());
    std::vector<T> v;
    T x{};
    while (in >> x) v.push_back(x);
    return v;
}

template <class T>
std::vector<T> read_fixed(std::ifstream& in, std::size_t max_len) {
    std::vector<T> run;
    run.reserve(max_len);
    T x{};
    while (run.size() < max_len && in >> x) run.push_back(x);
    return run;
}

template <class T>
void put_run(std::ostream& out, const std::vector<T>& run) {
    for (const T& x : run) out << x << '\n';
}

template <class T>
std::vector<T> merge_pair(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> r;
    r.reserve(a.size() + b.size());
    std::size_t i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (b[j] < a[i]) r.push_back(b[j++]);
        else r.push_back(a[i++]);
    }
    r.insert(r.end(), a.begin() + static_cast<std::ptrdiff_t>(i), a.end());
    r.insert(r.end(), b.begin() + static_cast<std::ptrdiff_t>(j), b.end());
    return r;
}

template <class T>
void split_fixed(const std::filesystem::path& src, const std::filesystem::path& dst1,
                 const std::filesystem::path& dst2, std::size_t run_len) {
    std::ifstream in(src);
    std::ofstream o1(dst1, std::ios::trunc), o2(dst2, std::ios::trunc);
    bool first = true;
    while (true) {
        auto run = read_fixed<T>(in, run_len);
        if (run.empty()) break;
        put_run(first ? static_cast<std::ostream&>(o1) : static_cast<std::ostream&>(o2), run);
        first = !first;
    }
}

template <class T>
void merge_fixed(const std::filesystem::path& a, const std::filesystem::path& b,
                 const std::filesystem::path& out, std::size_t run_len) {
    std::ifstream ia(a), ib(b);
    std::ofstream o(out, std::ios::trunc);
    while (true) {
        auto x = read_fixed<T>(ia, run_len), y = read_fixed<T>(ib, run_len);
        if (x.empty() && y.empty()) break;
        put_run(o, merge_pair(x, y));
    }
}

template <class T>
void merge_and_split(const std::filesystem::path& a, const std::filesystem::path& b,
                     const std::filesystem::path& o1, const std::filesystem::path& o2, std::size_t run_len) {
    std::ifstream ia(a), ib(b);
    std::ofstream f1(o1, std::ios::trunc), f2(o2, std::ios::trunc);
    bool first = true;
    while (true) {
        auto x = read_fixed<T>(ia, run_len), y = read_fixed<T>(ib, run_len);
        if (x.empty() && y.empty()) break;
        put_run(first ? static_cast<std::ostream&>(f1) : static_cast<std::ostream&>(f2), merge_pair(x, y));
        first = !first;
    }
}

template <class T>
std::size_t split_natural(const std::filesystem::path& src, const std::filesystem::path& dst1, const std::filesystem::path& dst2) {
    std::ifstream in(src);
    std::ofstream o1(dst1, std::ios::trunc), o2(dst2, std::ios::trunc);
    std::size_t count = 0;
    bool first = true;
    std::vector<T> run;
    T x{};
    while (in >> x) {
        if (!run.empty() && x < run.back()) {
            auto& tgt = first ? o1 : o2;
            put_run(tgt, run); tgt << '\n';
            ++count; first = !first; run.clear();
        }
        run.push_back(x);
    }
    if (!run.empty()) {
        auto& tgt = first ? o1 : o2;
        put_run(tgt, run); tgt << '\n'; ++count;
    }
    return count;
}

template <class T>
std::vector<T> read_block(std::ifstream& in) {
    std::vector<T> run;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r") == std::string::npos) {
            if (!run.empty()) return run;
            continue;
        }
        std::istringstream parser(line);
        T x{};
        if (!(parser >> x)) throw std::runtime_error("Некорректное значение");
        run.push_back(x);
    }
    return run;
}

template <class T>
void merge_natural(const std::filesystem::path& a, const std::filesystem::path& b, const std::filesystem::path& out) {
    std::ifstream ia(a), ib(b);
    std::ofstream o(out, std::ios::trunc);
    while (true) {
        auto x = read_block<T>(ia), y = read_block<T>(ib);
        if (x.empty() && y.empty()) break;
        put_run(o, merge_pair(x, y)); o << '\n';
    }
}

} 