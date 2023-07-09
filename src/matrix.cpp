//
// Created by mavlyut on 07/07/23.
//

#include "include/matrix.h"
#include "include/utils.h"

matrix::matrix(std::istream& in) {
    in >> n >> k;
    if (k > n) {
        throw std::runtime_error("k must be less or equals to n, find: k=" + std::to_string(k) + ", n=" + std::to_string(n));
    }
    arr = std::vector<std::vector<bool>>(k, std::vector<bool>(n));
    std::string tmp;
    for (std::size_t i = 0; i < k; i++) {
        in >> tmp;
        for (std::size_t j = 0; j < n; j++) {
            arr[i][j] = (tmp[j] == '1');
        }
    }
}

matrix::matrix(std::vector<std::vector<bool>> const& arr)
        : arr(arr), k(arr.size()), n(arr.front().size()) {}

matrix matrix::applyPermutation(permutation const& perm) const {
    std::vector<std::vector<bool>> arr_copy(arr);
    for (std::size_t i = 0; i < k; i++) {
        for (std::size_t j = 0; j < n; j++) {
            arr_copy[i][j] = arr[i][perm[j]];
        }
    }
    return matrix(arr_copy);
}

permutation matrix::gauss(permutation const& perm) {
    permutation fixed_perm(perm);
    for (std::size_t i = 0; i < k; i++) {
        if (arr[i][i] == 0) {
            // (exists j. j > i & a[j][i] == 1) => a[i] += a[j]
            for (std::size_t j = i + 1; j < k; j++) {
                if (arr[j][i]) {
                    arr[i] += arr[j];
                    break;
                }
            }
        }
        // (forall j. j > i -> a[j][i] == 0) => swap columns
        if (arr[i][i] == 0) {
            for (std::size_t j = i + 1; j < n; j++) {
                if (arr[i][j]) {
                    for (std::size_t t = 0; t < k; t++) {
                        std::swap(arr[t][i], arr[t][j]);
                    }
                    std::swap(fixed_perm[i], fixed_perm[j]);
                    break;
                }
            }
        }
        // arr[i][i] == 1
        for (std::size_t j = i + 1; j < k; j++) {
            if (arr[j][i]) {
                arr[j] += arr[i];
            }
        }
    }
    for (std::size_t i = k; i --> 0; ) {
        for (std::size_t j = i + 1; j < k; j++) {
            if (arr[i][j]) {
                arr[i] += arr[j];
            }
        }
    }
    return fixed_perm;
}

std::vector<bool> operator*(std::vector<bool> const& vec, matrix const& m) {
    std::vector<bool> ans(m.n);
    for (std::size_t i = 0; i < m.n; i++) {
        for (std::size_t j = 0; j < m.k; j++) {
            ans[i] = (ans[i] ^ (vec[j] & m.arr[j][i]));
        }
    }
    return ans;
}

std::vector<bool> matrix::multiply(std::size_t const& rhs) const {
    std::vector<bool> ans(n);
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < k; j++) {
            ans[i] = (ans[i] ^ ((rhs >> (k - j - 1)) & 1 & arr[j][i]));
        }
    }
    return ans;
}

std::ostream& operator<<(std::ostream& out, matrix const& m) {
    for (std::size_t i = 0; i < m.k; i++) {
        for (std::size_t j = 0; j < m.n; j++) {
            out << m.arr[i][j];
        }
        out << '\n';
    }
    return out;
}

std::size_t matrix::size() const {
    return k;
}
