#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/floyd_warshall_algorithm

template <typename T>
void floyd_warshall(vector<vector<T>>& adj_mat) {
    size_t n = adj_mat.size();
    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (adj_mat[i][k] != numeric_limits<T>::max() && adj_mat[k][j] != numeric_limits<T>::max()) {
                    adj_mat[i][j] = min(adj_mat[i][j], adj_mat[i][k] + adj_mat[k][j]);
                }
            }
        }
    }
}
