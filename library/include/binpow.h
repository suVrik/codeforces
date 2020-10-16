#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/binary_pow

ll binpow(ll a, ll n) {
    ll res = 1;
    while (n != 0) {
        if ((n & 1) != 0) {
            res *= a;
        }
        a *= a;
        n >>= 1;
    }
    return res;
}
