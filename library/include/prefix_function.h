#pragma once

#include "includes.h"

// Префикс-функция. Алгоритм Кнута-Морриса-Пратта.
// Prefix function. Knuth–Morris–Pratt algorithm.
// https://e-maxx.ru/algo/prefix_function

template <typename T = string::size_type>
vector<T> prefix_function(const string& s) {
    vector<T> result(s.size());
    for (T i = 1; i < T(s.size()); ++i) {
        T j = result[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = result[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        result[i] = j;
    }
    return result;
}

// string: 1212123#12121212
// prefix: 0012340#12345656
//                       ^ the purpose of inner while loop
