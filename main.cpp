//
// Created by mavlyut on 11/07/23.
//

#include <fstream>

#include "src/include/order_statistic.h"

int main(int argc, char** argv) {
    if (argc != 6) {
        throw std::runtime_error("Count of args must be equals to 5");
    }

#ifdef LOG
    freopen(".log", "a", stderr);
    auto start_time = std::chrono::system_clock::to_time_t(now());
    log_message("Program started at: " + std::string(std::ctime(&start_time)));
#endif
    std::ifstream fin(argv[1]);
    std::size_t t = std::stoi(argv[2]);
    double stn_ratio = std::stod(argv[3]);
    std::size_t max_error_count = std::stoi(argv[4]);
    std::size_t max_test_count = std::stoi(argv[5]);

    std::size_t errors = 0, all = 0;
    matrix m(fin);
    order_statistic decoder(m);

    for (; errors < max_error_count && all < max_test_count; all++) {
#ifdef LOG
        auto start = now();
#endif
        std::vector<bool> y = decoder.next_codeword();
        bool err = y != decoder.decode(y, stn_ratio, t);
        if (err && errors++ == max_error_count) {
            break;
        }
#ifdef LOG
        log_message("Decode: " + std::to_string(DIFF(start)) + " ms, answer: " + std::to_string(err));
#endif
    }
#ifdef LOG
    auto end_time = std::chrono::system_clock::to_time_t(now());
    log_message("\nProgram finished at: " + std::string(std::ctime(&end_time)));
#endif
    std::cout << "ОСШ=" << stn_ratio << ", p_error=" << to_double(errors) / to_double(all) << "\n";

}
