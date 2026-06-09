// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << filename << std::endl;
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        // проверяем, является ли символ латинской буквой (A-Z, a-z)
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            // преобразуем в нижний регистр и добавляем к текущему слову
            word += tolower(ch);
        } else {
            // если символ не буква и слово не пустое, добавляем его в дерево
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    file.close();
}
void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(),        //сортировка по повторениям
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error: Cannot create result/freq.txt" << std::endl;
        return;
    }
    std::cout << "\n=== Word Frequency Analysis ===" << std::endl;
    std::cout << "Total unique words: " << nodes.size() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "\nTop 20 most frequent words:" << std::endl;
    outFile << "Words sorted by frequency (descending):\n";
    int count = 0;
    for (const auto& node : nodes) {
        count++;
        if (count <= 20) {
            std::cout << count << ". \"" << node.first << "\" - " << node.second << " times" << std::endl;
        }
        outFile << count << ". \"" << node.first << "\" - " << node.second << " times\n";
    }
    outFile.close();
}
