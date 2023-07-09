//
// Created by mavlyut on 07/07/23.
//

#ifndef UNTITLED3_ORDER_STATISTIC_H
#define UNTITLED3_ORDER_STATISTIC_H

#include <algorithm>
#include <random>

#include "matrix.h"
#include "utils.h"

struct order_statistic {
    order_statistic() = delete;

    explicit order_statistic(matrix const&);

    // order statistic method
    std::vector<bool> decode(std::vector<bool> const&, double, std::size_t);

    // random codeword
    std::vector<bool> next_codeword() const;

private:
    matrix const& gen;
    std::vector<double> l;
    permutation perm;
    double INF = 1. / .0;
    std::random_device rd;
    std::mt19937 generator;

private:
    permutation find_perm();

    std::vector<bool> find_codeword(matrix const&, std::size_t) const;

    void get_likelihood_ratios_for_awgn_channel(std::vector<bool> const&, double);
};


#endif //UNTITLED3_ORDER_STATISTIC_H
