#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/segment_tree

namespace query_on_range_change_single {

template <typename T>
class SegmentTree {
public:
    void build(size_t size_) {
        data.assign(size_ * 4, 0);
        size = size_;
    }

    void build(T* data, size_t size_) {
        build(size_);
        build(data, 1, 0, size - 1);
    }

    void build(const vector<T>& data) {
        build(data.data(), data.size());
    }

    T sum(size_t l, size_t r) {
        r = min(r, size - 1);
        l = min(l, r);
        return sum(1, 0, size - 1, l, r);
    }

    void update(size_t pos, T value) {
        if (pos < size) {
            update(1, 0, size - 1, pos, value);
        }
    }

    // (*Pred)(size_t idx, T value)
    template <typename Pred>
    void traverse(const Pred& pred) {
        traverse(1, 0, size - 1, pred);
    }

    vector<T> data;
    size_t size;

private:
    T merge(T l, T r) {
        return l + r;
    }

    void build(T* data, size_t v, size_t tl, size_t tr) {
        if (tl == tr) {
            data[v] = data[tl];
        } else {
            size_t tm = tl + (tr - tl) / 2;
            build(data, v * 2, tl, tm);
            build(data, v * 2 + 1, tm + 1, tr);
            data[v] = merge(data[v * 2], data[v * 2 + 1]);
        }
    }

    T sum(size_t v, size_t tl, size_t tr, size_t l, size_t r) {
        if (l > r) {
            return 0;
        } else if (l == tl && r == tr) {
            return data[v];
        } else {
            size_t tm = tl + (tr - tl) / 2;
            T ls = sum(v * 2, tl, tm, l, min(r, tm));
            T rs = sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
            return merge(ls, rs);
        }
    }

    void update(size_t v, size_t tl, size_t tr, size_t pos, T value) {
        if (tl == tr) {
            data[v] = value;
        } else {
            size_t tm = tl + (tr - tl) / 2;
            if (pos <= tm) {
                update(v * 2, tl, tm, pos, value);
            } else {
                update(v * 2 + 1, tm + 1, tr, pos, value);
            }
            data[v] = merge(data[v * 2], data[v * 2 + 1]);
        }
    }

    template <typename Pred>
    void traverse(size_t v, size_t tl, size_t tr, const Pred& pred) {
        if (tl == tr) {
            pred(tl, data[v]);
        } else {
            size_t tm = tl + (tr - tl) / 2;
            traverse(v * 2, tl, tm, pred);
            traverse(v * 2 + 1, tm + 1, tr, pred);
        }
    }
};

} // namespace query_on_range_change_single

namespace change_on_range_query_single {

template <typename T>
class SegmentTree {
public:
    void build(size_t size_) {
        data.assign(size_ * 4, 0);
        size = size_;
    }

    void build(T* data, size_t size_) {
        build(size_);
        build(data, 1, 0, size - 1);
    }

    void build(const vector<T>& data) {
        build(data.data(), data.size());
    }

    void add(size_t l, size_t r, T value) {
        add(1, 0, size - 1, min(l, min(r, size - 1)), min(r, size - 1), value);
    }

    T get(size_t pos) {
        if (pos < size) {
            return get(1, 0, size - 1, pos);
        }
        return T();
    }

    // (*Pred)(size_t idx, T value)
    template <typename Pred>
    void traverse(const Pred& pred) {
        traverse(1, 0, size - 1, pred);
    }

    vector<T> data;
    size_t size;

private:
    void build(T* data, size_t v, size_t tl, size_t tr) {
        if (tl == tr) {
            data[v] = data[tl];
        } else {
            size_t tm = tl + (tr - tl) / 2;
            build(data, v * 2, tl, tm);
            build(data, v * 2 + 1, tm + 1, tr);
            data[v] = 0;
        }
    }

    void push(size_t v) {
        if (data[v] != 0) {
            data[v * 2] += data[v];
            data[v * 2 + 1] += data[v];
            data[v] = 0;
        }
    }

    void add(size_t v, size_t tl, size_t tr, size_t l, size_t r, T value) {
        if (l > r) {
            return;
        } else if (l == tl && r == tr) {
            data[v] += value;
        } else {
            push(v);
            size_t tm = tl + (tr - tl) / 2;
            add(v * 2, tl, tm, l, min(r, tm), value);
            add(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, value);
        }
    }

    T get(size_t v, size_t tl, size_t tr, size_t pos) {
        if (tl == tr) {
            return data[v];
        } else {
            push(v);
            size_t tm = tl + (tr - tl) / 2;
            if (pos <= tm) {
                return get(v * 2, tl, tm, pos);
            } else {
                return get(v * 2 + 1, tm + 1, tr, pos);
            }
        }
    }

    template <typename Pred>
    void traverse(size_t v, size_t tl, size_t tr, const Pred& pred) {
        if (tl == tr) {
            pred(tl, data[v]);
        } else {
            push(v);
            size_t tm = tl + (tr - tl) / 2;
            traverse(v * 2, tl, tm, pred);
            traverse(v * 2 + 1, tm + 1, tr, pred);
        }
    }
};

} // namespace change_on_range_query_single
