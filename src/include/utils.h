//
// Created by mavlyut on 07/07/23.
//

#ifndef UNTITLED3_UTILS_H
#define UNTITLED3_UTILS_H

#include <chrono>
#include <iostream>
#include <vector>

// assume lhs.size() == rhs.size()
std::vector<bool>& operator+=(std::vector<bool>&, std::vector<bool> const&);

// rhs in 0 until 2^k
std::vector<bool>& operator+=(std::vector<bool>&, std::size_t const&);

// assume lhs.size() == rhs.size()
std::vector<bool> operator+(std::vector<bool>, std::vector<bool> const&);

// rhs in 0 until 2^k
std::vector<bool> operator+(std::vector<bool>, std::size_t const&);

// assume lhs.size() == rhs.size()
std::size_t operator*(std::vector<bool> const& lhs, std::vector<bool> const& rhs);

std::ostream& operator<<(std::ostream& out, std::vector<bool> const& code);

bool operator==(std::vector<bool> const& lhs, std::vector<bool> const& rhs);

double to_double(std::size_t const& x);

void log_message(std::string const& str);

#define now std::chrono::steady_clock::now
#define DIFF(t1) std::chrono::duration_cast<std::chrono::milliseconds>(now() - t1).count()


#endif //UNTITLED3_UTILS_H
