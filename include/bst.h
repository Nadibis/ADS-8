// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    void insert(Node*& node, const T& value) {  //добавление узла
        if (node == nullptr) {
            node = new Node(value);
            return;
        }
        if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }
    void inorder(Node* node) const {           //вывод в алфовитном порядке
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->data << ": " << node->count << std::endl;
            inorder(node->right);
        }
    }
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& nodes) const {  //добавление пар (ключ/значение) в вектор
        if (node != nullptr) {
            collectNodes(node->left, nodes);
            nodes.push_back({node->data, node->count});
            collectNodes(node->right, nodes);
        }
    }
    int getHeight(Node* node) const {     //высота
        if (node == nullptr) return 0;
        return std::max(getHeight(node->left), getHeight(node->right));
    }
    Node* findNode(Node* node, const T& value) const {   //бинарный поиск
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return findNode(node->left, value);
        } else {
            return findNode(node->right, value);
        }
    }
    void clear(Node* node) {          //очисткка
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        clear(root);
    }
    void insert(const T& value) {
        insert(root, value);
    }
    void printInorder() const {
        inorder(root);
    }
    int depth() const {
        return getHeight(root);
    }
    int search(const T& value) const {
    Node* node = findNode(root, value);
    if (node == nullptr) {
      return 0;
    }
    return node->count;
    }
    bool isEmpty() const {
        return root == nullptr;
    }
    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<std::pair<T, int>> nodes;   //создание вектора
        collectNodes(root, nodes);              //добывление узлов в вектор
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
