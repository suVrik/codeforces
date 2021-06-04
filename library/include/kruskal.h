#pragma once

#include "includes.h"
#include "dsu.h"

// Минимальное остовное дерево. Алгоритм Крускала с системой непересекающихся множеств.
// Minimum spanning tree. Kruskal algorithm with disjoint-set-union.
// http://e-maxx.ru/algo/mst_kruskal_with_dsu

template <typename Index, typename Cost>
vector<pair<Index, Index>> kruskal(size_t num_vertices, vector<tuple<Cost, Index, Index>>& edges) {
    sort(edges.begin(), edges.end());

    DSU<Index> dsu;
    dsu.build(num_vertices);

    vector<pair<Index, Index>> result;
    for (size_t i = 0; i < edges.size(); i++) {
        const auto& [w, a, b] = edges[i];
        if (dsu.find_set(a) != dsu.find_set(b)) {
            result.emplace_back(a, b);
            dsu.union_sets(a, b);
        }
    }
    return result;
}
