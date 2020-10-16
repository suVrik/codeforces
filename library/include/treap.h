#pragma once

#include "includes.h"

// http://e-maxx.ru/algo/treap

template <typename ValueType>
class Treap {
public:
    struct Node {
        ValueType value;
        int priority;
        size_t count;
        Node* left;
        Node* right;
    };

    ~Treap() {
        destroy(root);
    }

    void insert(size_t key, ValueType value) {
        assert(key <= size());
        insert(root, new Node{ value, rand(), 1, nullptr, nullptr }, key);
    }

    void erase(size_t key) {
        assert(key < size());
        erase(root, key);
    }

    ValueType get(size_t position) {
        assert(position < size());
        // TODO
    }

    template <typename Operation, typename... Args>
    Operation::ReturnType operation(size_t left, size_t right, Args... args) {
        assert(left <= right);
        assert(right < size());
        Node* t1, t2, t3; // TODO: ????
        split(root, t1, t2, left); // ???? and below
        split(t2, t2, t3, right - left + 1);
        t2->Operation::operation(args...);
        merge(root, t1, t2);
        merge(root, root, t3);
    }

    // (*Pred)(size_t idx, T value)
    template <typename Pred>
    void traverse(const Pred& pred) {
        traverse(root, pred, 0);
    }

    size_t size() {
        return root != nullptr ? root->count : 0;
    }

    Node* root = nullptr;

private:
    void destroy(Node* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    size_t count(Node* node) {
        return node != nullptr ? node->count : 0;
    }

    void update_count(Node* node) {
        if (node != nullptr) {
            node->count = count(node->left) + count(node->right) + 1;
        }
    }

    void split(Node* node, Node*& left, Node*& right, size_t key, size_t offset) {
        if (node == nullptr) {
            left = right = nullptr;
        } else {
            (node->Operations::push(node->value, node->left, node->right), ...);
            if (key <= offset + count(node->left)) {
                split(node->left, left, node->left, key, offset);
                right = node;
            } else {
                split(node->right, node->right, right, key, offset + count(node->left) + 1);
                left = node;
            }
            update_count(node);
            (node->Operations::pop(node->value, node->left, node->right), ...);
        }
    }

    void insert(Node*& node, Node* new_node, size_t key, size_t offset) {
        if (node == nullptr) {
            node = new_node;
        } else if (new_node->priority > node->priority) {
            split(node, new_node->left, new_node->right, key, offset);
            node = new_node;
        } else {
            (node->Operations::push(node->value, node->left, node->right), ...);
            if (key <= offset + count(node->left)) {
                insert(node->left, new_node, key, offset);
            } else {
                insert(node->right, new_node, key, offset + count(node->left) + 1);
            }
            (node->Operations::pop(node->value, node->left, node->right), ...);
        }
    }

    void merge(Node*& node, Node* left, Node* right) {
        if (left != nullptr) {
            (left->Operations::push(left->value, left->left, left->right), ...);
        }
        if (right != nullptr) {
            (right->Operations::push(right->value, right->left, right->right), ...);
        }
        if (left == nullptr || right == nullptr) {
            node = left != nullptr ? left : right;
        } else if (left->priority > right->priority) {
            merge(left->right, left->right, right);
            node = left;
        } else {
            merge(right->left, left, right->left);
            node = right;
        }
        update_count(node);
        if (right != nullptr) {
            (right->Operations::pop(right->value, right->left, right->right), ...);
        }
        if (left != nullptr) {
            (left->Operations::pop(left->value, left->left, left->right), ...);
        }
    }

    void erase(Node*& node, size_t key) {
        if (node != nullptr) {
            if (node->key == key) {
                delete node;
                merge(node, node->left, node->right);
            } else {
                erase(key < node->key ? node->left : node->right, key);
            }
        }
    }

    template <typename Pred>
    void traverse(Node* node, const Pred& pred, size_t index) {
        if (node != nullptr) {
            (node->Operations::push(node->value, node->left, node->right), ...);
            traverse(node->left, pred, index);
            pred(index, node->value);
            traverse(node->right, pred, index + count(node->left) + 1);
            (node->Operations::pop(node->value, node->left, node->right), ...);
        }
    }
};
