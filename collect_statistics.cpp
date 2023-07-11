//
// Created by mavlyut on 05/07/23.
//

#include <future>
#include <iostream>
#include <iomanip>
#include <vector>

#include "src/include/order_statistic.h"
#include "src/include/utils.h"

#define TESTCNT 1000

std::size_t test(matrix const& m, std::size_t const& cnt, double const& stn_ratio, std::size_t const& t, bool log = false) {
    std::size_t errors = 0;
    std::vector<std::future<bool>> futures(cnt);
    for (std::size_t i = 0; i < cnt; i++) {
        futures[i] = std::async(std::launch::async, [&](){
            order_statistic decoder(m);
            auto start = now();
            std::vector<bool> y = decoder.next_codeword();
            if (log) log_message("Random: " + std::to_string(DIFF(start)) + "ms");
            bool ans = y != decoder.decode(y, stn_ratio, t);
            if (log) log_message("Decode: " + std::to_string(DIFF(start)) + "ms, answer is " + std::to_string(ans));
            return ans;
        });
    }
    for (std::future<bool>& f : futures) {
        errors += f.get();
    }
    return errors;
}

int main() {
    freopen("files/bch_32_21_6.gen", "r", stdin);
    freopen("STATS_2", "a", stdout);
    freopen(".log", "a", stderr);

    matrix const m(std::cin);
    std::cout << std::fixed << std::setprecision(7) << std::boolalpha;

    for (std::size_t t = 0; t < 4; t++) {
        std::cout << "t=" << t << "\n";
        auto start = now();
        for (std::size_t q = 0; q < 27; q++) {
            double stn_ratio = -0.25 + to_double(q) * 0.25;
            std::size_t all = 0;
            std::size_t errors = 0;
            while (errors == 0 && all < 50 * TESTCNT) {
                errors += test(m, TESTCNT, stn_ratio, t, true);
                all += TESTCNT;
            }
            std::cout << "ОСШ=" << stn_ratio << ", p_error=" << to_double(errors) / to_double(all) << ", all=" << all << std::endl;
        }
        std::cerr << "t=" << t << ", time=" << DIFF(start) << " ms\n";
        std::cout << "\n";
    }
}
