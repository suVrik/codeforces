#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/fenwick_tree

template <typename T>
struct FenwickTree {
    void build(size_t size) {
        data.assign(size + 1, 0);
    }

    void add(size_t index, T value) {
        assert(index > 0);
        for (; index < data.size(); index += index & -intptr_t(index)) {
            data[index] += value;
        }
    }

    T sum(size_t index) {
        T result = T();
        for (index = min(index, data.size() - 1); index > 0; index -= index & -intptr_t(index)) {
            result += data[index];
        }
        return result;
    }

    T sum(size_t left, size_t right) {
        assert(left > 0);
        return sum(right) - sum(left - 1);
    }

    T get(size_t index) {
        assert(index > 0);
        return sum(index) - sum(index - 1);
    }

    size_t search(T sum_value) {
        size_t index = 0;
        for (intptr_t bit_index = 22; bit_index >= 0; bit_index--) {
            size_t new_index = index | (1 << bit_index);
            if (new_index < data.size() && sum_value > data[new_index]) {
                index = new_index;
                sum_value -= data[new_index];
            }
        }
        return index + 1;
    }

    vector<T> data;
};

// TODO: min-fenwick

//struct Fenwick {
//    static constexpr ll N = 524288;
//
//    Fenwick() {
//        clear();
//    }
//
//    void clear() {
//        for (ll i = 0; i < 1048576; i++) {
//            a[i] = numeric_limits<ll>::max();
//        }
//    }
//
//    void set_min(ll pos, ll x) {
//        for (ll i = pos + N; i; i >>= 1) {
//            a[i] = min(a[i], x);
//        }
//    }
//
//    ll get_min(ll L, ll R) const {
//        ll res = numeric_limits<ll>::max();
//        for (L += N, R += N; L < R; L >>= 1, R >>= 1) {
//            if (L & 1) {
//                res = min(res, a[L]);
//                L++;
//            }
//            if (R & 1) {
//                R--;
//                res = min(res, a[R]);
//            }
//        }
//        return res;
//    }
//
//    ll a[N * 2];
//};
