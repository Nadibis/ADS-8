// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>
#include <chrono>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    const char* filename = "war_peace.txt";
    makeTree(tree, filename);
    printFreq(tree);
    return 0;
}
