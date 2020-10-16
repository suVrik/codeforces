#pragma once

#include "includes.h"

template <typename T, typename U>
pair<vector<T>, vector<U>> dijkstra(const vector<vector<pair<T, U>>>& adj_list, T start) {
    vector<T> parent(adj_list.size(), numeric_limits<T>::max());

    vector<U> cost(adj_list.size(), numeric_limits<U>::max());
    cost[start] = U();

    priority_queue<pair<U, T>, vector<pair<U, T>>, greater<pair<U, T>>> open;
    open.emplace(0, start);

    while (!open.empty()) {
        auto [vcost, vidx] = open.top();
        open.pop();

        if (vcost == cost[vidx]) {
            for (size_t i = 0; i < adj_list[vidx].size(); i++) {
                T nidx = adj_list[vidx][i].first;
                U ncost = vcost + adj_list[vidx][i].second;
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
