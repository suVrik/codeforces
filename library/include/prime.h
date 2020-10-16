#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/eratosthenes_sieve

vector<ll> build_sieve(ll n) {
    vector<ll> sieve(n + 1, 0);
    for (ll i = 2; i <= n; i++) {
        if (sieve[i] == 0) {
            sieve[i] = i;
            for (ll j = i * i; j <= n; j += i) {
                if (sieve[j] == 0) {
                    sieve[j] = i;
                }
            }
        }
    }
    return sieve;
}

vector<bool> build_is_prime(ll n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

vector<ll> build_primes(ll n) {
    vector<bool> is_prime = build_is_prime(n);

    vector<ll> result;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            result.push_back(i);
        }
    }
    return result;
}

set<ll> build_primes_set(ll n) {
    vector<bool> is_prime = build_is_prime(n);

    set<ll> result;
    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            result.insert(i);
        }
    }
    return result;
}
