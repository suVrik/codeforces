#pragma once

#include "includes.h"

template <typename T, typename Pred, typename... Args>
T bin_search(T l, T r, Pred pred, const Args&... args) {
    while (l <= r) {
        T m = l + (r - l) / 2;
        if (pred(m)) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return l;
}

// Find first true in "false, false, false, true, true, true" array.

template <typename T, typename Pred, typename... Args>
T bin_search(T l, T r, Pred pred, const Args&... args) {
    while (l < r) {
        T m = l + (r - l) / 2;
        if (pred(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    return l;
}

// http://e-maxx.ru/algo/ternary_search

template <bool minima, typename Pred>
double ternary_search(double l, double r, double eps, Pred pred) {
    while (r - l > eps) {
        double ml = l + (r - l) / 3;
        double mr = r - (r - l) / 3;
        if ((pred(ml) > pred(mr)) == minima) {
            l = ml;
        } else {
            r = mr;
        }
    }
    return l;
}

template <bool minima, typename T, typename Pred>
T ternary_search(T l, T r, Pred pred) {
    while (r - l >= 3) {
        T ml = l + (r - l) / 3;
        T mr = r - (r - l) / 3;
        if ((pred(ml) > pred(mr)) == minima) {
            l = ml;
        } else {
            r = mr;
        }
    }
    T result = l++;
    for (T i = l; i <= r; i++) {
        if ((pred(i) < pred(result)) == minima) {
            result = i;
        }
    }
    return result;
}
