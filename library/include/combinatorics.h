#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/binomial_coeff

// Сочетания: C(n, k) = n! / (k! * (n - k)!)
// 1 2
// 1 3
// 1 4
// 2 3
// 2 4
// 3 4

// Сочетания с повторениями: C((n), k) = C(n + k - 1, n - 1)  = (n + k - 1)! / (k! * (n - 1)!)
// 1 1
// 1 2
// 1 3
// 1 4
// 2 2
// 2 3
// 2 4
// 3 3
// 3 4
// 4 4

ll c(ll n, ll k) {
    ll result = 1;
    for (ll i = 1; i <= k; i++) {
        result = result * (n - k + i) / i;
    }
    return result;
}

vector<vector<ll>> build_pascal_triangle(size_t n) {
    vector<vector<ll>> result(n + 1, vector<ll>(n + 1));
    for (size_t i = 0; i <= n; i++) {
        result[i][0] = result[i][i] = 1;
        for (size_t k = 1; k < i; k++) {
            result[i][k] = result[i - 1][k - 1] + result[i - 1][k];
        }
    }
    return result;
}

// Перестановки: P(n) = n!
// 1 2 3
// 1 3 2
// 2 1 3
// 2 3 1
// 3 1 2
// 3 2 1

// Перестановки без повторений: n! / (a! * b! * ... * z!)
// 1 1 2 2
// 1 2 1 2
// 1 2 2 1
// 2 1 1 2
// 2 1 2 1
// 2 2 1 1

ll fac(ll n) {
    ll result = 1;
    while (n > 0) {
        result *= n--;
    }
    return result;
}

// Размещения: A(n, k) = n! / (n - k)!
// 1 2
// 1 3
// 2 1
// 2 3
// 3 1
// 3 2

// Размещения с повторениями: A(n, -k) = n^k
// 0 0 0
// 0 0 1
// 0 1 0
// 0 1 1
// 1 0 0
// 1 0 1
// 1 1 0
// 1 1 1
