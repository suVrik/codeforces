#pragma once

#include "includes.h"

// Модульная арифметика.
// https://brestprog.by/topics/modulo/

ll add(ll a, ll b, ll mod) {
    return ((a % mod) + (b % mod)) % mod;
}

ll dec(ll a, ll b, ll mod) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

ll mul(ll a, ll b, ll mod) {
    return ((a % mod) * (b % mod)) % mod;
}

ll fac(ll a, ll mod) {
    ll result = 1;
    for (ll i = 2; i <= a; i++) {
        result = result * i % mod;
    }
    return result;
}

ll binpow(ll a, ll n, ll mod) {
    ll res = 1;
    while (n != 0) {
        if ((n & 1) != 0) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        n >>= 1;
    }
    return res;
}

ll inverse_element(ll x, ll mod) {
    return binpow(x, mod - 2, mod);
}

ll div(ll a, ll b, ll mod) {
    return a * inverse_element(b, mod) % mod;
}
