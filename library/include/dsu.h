#pragma once

#include "includes.h"

// Система непересекающихся множеств. Disjoint-set.
// http://e-maxx.ru/algo/dsu

template <typename Index>
struct DSU {
    void build(size_t size) {
        parent.assign(size, 0);
        for (size_t i = 0; i < size; i++) {
            parent[i] = i;
        }

        rank.assign(size, 0);
    }

    Index find_set(Index v) {
        assert(!parent.empty());
        assert(v < Index(parent.size()));

        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }

    void union_sets(Index a, Index b) {
        assert(!parent.empty());
        assert(a < Index(parent.size()));
        assert(b < Index(parent.size()));

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

    vector<Index> parent;
    vector<Index> rank;
};
