#pragma once

#include "includes.h"

// Нахождение кратчайших путей от заданной вершины до всех остальных вершин алгоритмом Дейкстры для разреженных графов.
// Dijkstra - finding shortest paths from given vertex to other vertices on sparse graphs.
// http://e-maxx.ru/algo/dijkstra_sparse

template <typename Index, typename Cost>
pair<vector<Index>, vector<Cost>> dijkstra(const vector<vector<pair<Index, Cost>>>& adj_list, Index start) {
    vector<Index> parent(adj_list.size(), numeric_limits<Index>::max());

    vector<Cost> cost(adj_list.size(), numeric_limits<Cost>::max());
    cost[start] = Cost();

    priority_queue<pair<Cost, Index>, vector<pair<Cost, Index>>, greater<pair<Cost, Index>>> open;
    open.emplace(0, start);

    while (!open.empty()) {
        auto [vcost, vidx] = open.top();
        open.pop();

        if (vcost == cost[vidx]) {
            for (size_t i = 0; i < adj_list[vidx].size(); i++) {
                Index nidx = adj_list[vidx][i].first;
                Cost ncost = vcost + adj_list[vidx][i].second;
                if (cost[nidx] > ncost) {
                    cost[nidx] = ncost;
                    parent[nidx] = vidx;
                    open.emplace(ncost, nidx);
                }
            }
        }
    }

    return { parent, cost };
}
