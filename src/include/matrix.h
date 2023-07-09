//
// Created by mavlyut on 07/07/23.
//

#ifndef UNTITLED3_MATRIX_H
#define UNTITLED3_MATRIX_H

#include <iostream>
#include <vector>

using permutation = std::vector<std::size_t>;

struct matrix {
    friend struct order_statistic;

    explicit matrix(std::istream&);

    matrix applyPermutation(permutation const&) const;

    permutation gauss(permutation const&);

    friend std::vector<bool> operator*(std::vector<bool> const&, matrix const&);

    std::vector<bool> multiply(std::size_t const&) const;

    friend std::ostream& operator<<(std::ostream&, matrix const&);

    std::size_t size() const;

private:
    std::size_t n{}, k{};
    std::vector<std::vector<bool>> arr;

    explicit matrix(std::vector<std::vector<bool>> const&);
};


#endif //UNTITLED3_MATRIX_H
