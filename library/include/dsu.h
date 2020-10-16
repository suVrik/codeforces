#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/dsu

template <typename T>
struct DSU {
    void build(size_t size) {
        parent.assign(size, 0);
        for (size_t i = 0; i < size; i++) {
            parent[i] = i;
        }

        rank.assign(size, 0);
    }

    T find_set(T v) {
        assert(!parent.empty());
        assert(v < T(parent.size()));

        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(T a, T b) {
        assert(!parent.empty());
        assert(a < T(parent.size()));
        assert(b < T(parent.size()));

        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b]) {
                ++rank[a];
            }
        }
    }

    vector<T> parent;
    vector<T> rank;
};
