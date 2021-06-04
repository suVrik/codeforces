#pragma once

#include "includes.h"

// Длинная арифметика. Big integer.
// http://e-maxx.ru/algo/big_integer
//
// Problems:
//   https://codeforces.com/problemsets/acmsguru/problem/99999/112
//   https://codeforces.com/contest/98/problem/B

class BigInteger {
public:
    static constexpr int BASE = 1000000000;
    static constexpr int BASE_DIGITS = 9;

    BigInteger(ll integer = 0) {
        while (integer > 0) {
            value.push_back(integer % BASE);
            integer /= BASE;
        }
    }

    BigInteger(const string& str) {
        for (int i = int(str.size()); i > 0; i -= BASE_DIGITS) {
            if (i < BASE_DIGITS) {
                value.push_back(atoi(str.substr(0, i).c_str()));
            } else {
                value.push_back(atoi(str.substr(i - BASE_DIGITS, BASE_DIGITS).c_str()));
            }
        }
        trim();
    }

    operator string() const {
        if (!value.empty()) {
            unique_ptr<char[]> data(new char[value.size() * BASE_DIGITS + 1]);
            char* current = data.get();
            int written =  sprintf(current, "%d", value.back());
            current += written;
            for (auto it = next(value.rbegin()); it != value.rend(); ++it) {
                written = sprintf(current, "%09d", *it);
                current += written;
            }
            return data.get();
        }
        return "0";
    }

    BigInteger& operator+=(const BigInteger& rhs) {
        int carry = 0;
        for (size_t i = 0; i < max(value.size(), rhs.value.size()) || carry; i++) {
            if (i == value.size()) {
                value.push_back(0);
            }
            value[i] += carry + (i < rhs.value.size() ? rhs.value[i] : 0);
            carry = value[i] >= BASE;
            if (carry) {
                value[i] -= BASE;
            }
        }
        return *this;
    }

    friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result = lhs;
        result += rhs;
        return result;
    }

    BigInteger& operator-=(const BigInteger& rhs) {
        int carry = 0;
        for (size_t i = 0; i < rhs.value.size() || carry; i++) {
            value[i] -= carry + (i < rhs.value.size() ? rhs.value[i] : 0);
            carry = value[i] < 0;
            if (carry) {
                value[i] += BASE;
            }
        }
        return trim();
    }

    friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger result = lhs;
        result -= rhs;
        return result;
    }

    BigInteger& operator*=(int rhs) {
        int carry = 0;
        for (size_t i = 0; i < value.size() || carry; i++) {
            if (i == value.size()) {
                value.push_back(0);
            }
            ll current = carry + ll(value[i]) * rhs;
            value[i] = int(current % BASE);
            carry = int(current / BASE);
        }
        return trim();
    }

    friend BigInteger operator*(const BigInteger& lhs, int rhs) {
        BigInteger result = lhs;
        result *= rhs;
        return result;
    }

    friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
        BigInteger c;
        c.value.assign(lhs.value.size() + rhs.value.size(), 0);
        for (size_t i = 0; i < lhs.value.size(); i++) {
            for (size_t j = 0, carry = 0; j < rhs.value.size() || carry; j++) {
                ll current = c.value[i + j] + ll(lhs.value[i]) * (j < rhs.value.size() ? rhs.value[j] : 0) + carry;
                c.value[i + j] = int(current % BASE);
                carry = int(current / BASE);
            }
        }
        return c.trim();
    }

    BigInteger& operator*=(const BigInteger& rhs) {
        return *this = *this * rhs;
    }

    BigInteger& operator/=(int rhs) {
        int carry = 0;
        for (auto it = value.rbegin(); it != value.rend(); ++it) {
            ll current = *it + ll(carry) * BASE;
            *it = int(current / rhs);
            carry = int(current % rhs);
        }
        return trim();
    }

    friend BigInteger operator/(const BigInteger& lhs, int rhs) {
        BigInteger result = lhs;
        result /= rhs;
        return result;
    }

    bool operator==(const BigInteger& rhs) const {
        if (value.size() == rhs.value.size()) {
            for (size_t i = 0; i < value.size(); i++) {
                if (value[i] != rhs.value[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool operator<(const BigInteger& rhs) const {
        if (value.size() == rhs.value.size()) {
            for (int i = value.size() - 1; i >= 0; i--) {
                if (value[i] < rhs.value[i]) {
                    return true;
                } else if (value[i] > rhs.value[i]) {
                    return false;
                }
            }
            return true;
        }
        return value.size() < rhs.value.size();
    }

    friend istream& operator>>(istream& stream, BigInteger& rhs) {
        string str;
        stream >> str;
        rhs = BigInteger(str);
        return stream;
    }

    friend ostream& operator<<(ostream& stream, const BigInteger& rhs) {
        stream << static_cast<string>(rhs);
        return stream;
    }

    vector<int> value;

private:
    BigInteger& trim() {
        while (!value.empty() && value.back() == 0) {
            value.pop_back();
        }
        return *this;
    }
};
