#pragma once

#include "includes.h"
#include "dsu.h"

template <typename T, typename W>
vector<pair<T, T>> kruskal(size_t num_vertices, vector<tuple<W, T, T>>& edges) {
    sort(edges.begin(), edges.end());

    DSU<T> dsu;
    dsu.build(num_vertices);

    vector<pair<T, T>> result;
    for (size_t i = 0; i < edges.size(); i++) {
        const auto& [w, a, b] = edges[i];
        if (dsu.find_set(a) != dsu.find_set(b)) {
            result.emplace_back(a, b);
            dsu.union_sets(a, b);
        }
    }
    return result;
}
