#pragma once

#include "includes.h"

// Дерево Фенвика. Fenwick tree.
// Очень быстрое вычисление суммы на отрезке.
// Индекс должен быть больше ноля и меньше или равен size.
// Возможна модификация одного элемента.
// Search выполняет поиск первого элемента на котором сумма элементов начиная с первого
// заканчивая этим элементом включительно больше или равна запрашиваемому значению
// (для строго больше можно добавить 1 к зачению).
// http://e-maxx.ru/algo/fenwick_tree

template <typename Value>
struct FenwickTree {
    void build(size_t size) {
        data.assign(size + 1, 0);
    }

    void add(size_t index, Value value) {
        assert(index > 0);
        for (; index < data.size(); index += index & -intptr_t(index)) {
            data[index] += value;
        }
    }

    Value sum(size_t index) {
        Value result = Value();
        for (index = min(index, data.size() - 1); index > 0; index -= index & -intptr_t(index)) {
            result += data[index];
        }
        return result;
    }

    Value sum(size_t left, size_t right) {
        assert(left > 0);
        return sum(right) - sum(left - 1);
    }

    Value get(size_t index) {
        assert(index > 0);
        return sum(index) - sum(index - 1);
    }

    size_t search(Value sum_value) {
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

    vector<Value> data;
};
