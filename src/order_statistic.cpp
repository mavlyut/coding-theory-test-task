//
// Created by mavlyut on 07/07/23.
//

#include "include/order_statistic.h"

order_statistic::order_statistic(matrix const& gen) : gen(gen), generator(rd()) {
    srand(time(nullptr));
}

std::vector<bool> order_statistic::decode(std::vector<bool> const& y, double stn_ratio, std::size_t t)  {
    get_likelihood_ratios_for_awgn_channel(y, stn_ratio);
    find_perm();
    matrix g_perm = gen.applyPermutation(perm);
    perm = g_perm.gauss(perm);
    std::vector<bool> rev_ans = find_codeword(g_perm, t);
    std::vector<bool> ans(gen.n);
    for (std::size_t i = 0; i < gen.n; i++) {
        ans[perm[i]] = rev_ans[i];
    }
    return ans;
}

std::vector<bool> order_statistic::next_codeword() const {
    return gen.multiply(rand() % (1 << gen.size()));
}

permutation order_statistic::find_perm() {
    std::size_t n = gen.n;
    std::vector<std::pair<double, int>> abs_l_indexed(n);
    for (std::size_t i = 0; i < n; i++) {
        abs_l_indexed[i] = {std::abs(l[i]), i};
    }
    std::sort(abs_l_indexed.begin(), abs_l_indexed.end());
    std::reverse(abs_l_indexed.begin(), abs_l_indexed.end());
    perm.resize(n);
    for (std::size_t i = 0; i < n; i++) {
        perm[i] = abs_l_indexed[i].second;
    }
    return perm;
}

std::vector<bool> order_statistic::find_codeword(matrix const& g, std::size_t t) const {
    std::size_t n = gen.n, k = gen.k;
    std::vector<bool> ans, y_perm(n), y_perm_info(k);
    for (std::size_t i = 0; i < n; i++) {
        y_perm[i] = (l[perm[i]] > 0);
        if (i < k) {
            y_perm_info[i] = y_perm[i];
        }
    }
    long double mu0 = INF;
    std::function<void(std::size_t, std::size_t, std::size_t)> rec = [&](std::size_t e, std::size_t wt, std::size_t ind) {
        if (ind == n || wt > t) {
            return;
        }
        std::vector<bool> z = y_perm_info + e;
        std::vector<bool> c = z * g;
        std::vector<bool> x = c + y_perm;
        long double mu = 0;
        for (std::size_t i = 0; i < n; i++) {
            mu += x[i] * std::abs(l[perm[i]]);
        }
        if (mu < mu0) {
            ans = c;
            mu0 = mu;
        }
        rec(e, wt, ind + 1);
        rec(e + (1 << ind), wt + 1, ind + 1);
    };
    rec(0, 0, 0);
    return ans;
}

// alpha -- отношение сигнал/шум на бит в дБ
// alpha = 10 * lg(Eb / N0)
// Eb / N0 = 10^(alpha/10) = beta = Es / (R * N0) = 1 / (k/n * 2sigma^2)
// 1 / beta = (2 * sigma^2 * k) / n
// sigma^2 = n / (2 * k * beta)
void order_statistic::get_likelihood_ratios_for_awgn_channel(std::vector<bool> const& y, double alpha) {
    std::size_t n = gen.n;
    l.resize(n);
    double beta = pow(10, alpha / 10);
    double sigma_sqr = sqrt(static_cast<double>(n) / (static_cast<double>(2 * gen.k) * beta));
    std::normal_distribution<double> norm_distr(0, sigma_sqr);
    for (std::size_t i = 0; i < n; i++) {
        l[i] = (y[i] ? 1 : -1) + norm_distr(generator);
    }
}
