#pragma once

#include "includes.h"

// Алгоритм Евклида нахождения наибольшего общего делителя.
// Euclidean algorithm for computing the greatest common divisor.
// http://e-maxx.ru/algo/euclid_algorithm

// gcd(x, 0) = gcd(0, x) = x
// gcd(0, 0) = 0

ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}
