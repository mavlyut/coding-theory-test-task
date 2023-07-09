//
// Created by mavlyut on 07/07/23.
//

#include "include/utils.h"

std::vector<bool>& operator+=(std::vector<bool>& lhs, std::vector<bool> const& rhs) {
    for (std::size_t i = 0; i < lhs.size(); i++) {
        lhs[i] = lhs[i] ^ rhs[i];
    }
    return lhs;
}

std::vector<bool>& operator+=(std::vector<bool>& lhs, std::size_t const& rhs) {
    std::size_t k = lhs.size();
    for (std::size_t i = 0; i < k; i++) {
        lhs[i] = lhs[i] ^ ((rhs >> (k - i - 1)) & 1);
    }
    return lhs;
}

std::vector<bool> operator+(std::vector<bool> lhs, std::vector<bool> const& rhs) {
    return lhs += rhs;
}

std::vector<bool> operator+(std::vector<bool> lhs, std::size_t const& rhs) {
    return lhs += rhs;
}

std::size_t operator*(std::vector<bool> const& lhs, std::vector<bool> const& rhs) {
    std::size_t ans = 0;
    for (std::size_t i = 0; i < lhs.size(); i++) {
        ans += lhs[i] ^ rhs[i];
    }
    return ans;
}

std::ostream& operator<<(std::ostream& out, std::vector<bool> const& code) {
    for (bool i : code) {
        out << (i ? 1 : 0);
    }
    return out;
}

bool operator==(std::vector<bool> const& lhs, std::vector<bool> const& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (std::size_t i = 0; i < lhs.size(); i++) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

double to_double(std::size_t const& x) {
    return static_cast<double>(x);
}
