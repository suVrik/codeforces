#pragma once

#include "includes.h"

// Бинарный поиск. Binary search.
// Предикат возвращает true если нужно искать справа от координаты.
// Для возрастающей последовательности это как правило это оператор "меньше"
// где справа от оператора референсное значение.
// Для убывающей последовательности это как правило оператор "больше"
// где справа от оператора референсное значение.
// По сути возвращает первое false среди "true, true, true, false, false, false".

template <typename Index, typename Pred>
Index bin_search(Index l, Index r, Pred pred) {
    while (l <= r) {
        Index m = l + (r - l) / 2;
        if (pred(m)) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    return l;
}

// Тернарный поиск на непрерывной функции.
// Предикат возвращает значение по координате.
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

// Тернарный поиск на дискретной функции.
// Предикат возвращает значение по координате.

template <bool minima, typename Index, typename Pred>
Index ternary_search(Index l, Index r, Pred pred) {
    while (r - l >= 3) {
        Index ml = l + (r - l) / 3;
        Index mr = r - (r - l) / 3;
        if ((pred(ml) > pred(mr)) == minima) {
            l = ml;
        } else {
            r = mr;
        }
    }
    Index result = l++;
    for (Index i = l; i <= r; i++) {
        if ((pred(i) < pred(result)) == minima) {
            result = i;
        }
    }
    return result;
}
