// Copyright 2022 NNTU-CS
#include <algorithm>
#include <vector>
#include "tree.h"

int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;
    std::sort(remaining.begin(), remaining.end());
    for (size_t i = 0; i < remaining.size(); i++) {
        Node* child = new Node(remaining[i]);
        node->children.push_back(child);
        std::vector<char> next;
        for (size_t j = 0; j < remaining.size(); j++) {
            if (j != i) {
                next.push_back(remaining[j]);
            }
        }
        buildTree(child, next);
    }
}

PMTree::PMTree(const std::vector<char>& elements) {
    std::vector<char> sorted = elements;
    std::sort(sorted.begin(), sorted.end());
    size = sorted.size();
    root = new Node('\0');
    buildTree(root, sorted);
}

void PMTree::destroyTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        destroyTree(child);
    }
    delete node;
}

PMTree::~PMTree() {
    destroyTree(root);
}

PMTree::Node* PMTree::getRoot() const {
    return root;
}

int PMTree::getSize() const {
    return size;
}

void PMTree::collectAll(Node* node, std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
    if (node->value != '\0') {
        current.push_back(node->value);
    }
    if (node->children.empty() && node->value != '\0') {
        result.push_back(current);
    } else {
        for (Node* child : node->children) {
            collectAll(child, current, result);
        }
    }
    if (node->value != '\0') {
        current.pop_back();
    }
}

void PMTree::findPermByNumber(Node* node, int target, int& counter,
                              std::vector<char>& result, bool& found) {
    if (found) return;

    if (node->value != '\0') {
        result.push_back(node->value);
    }

    if (node->children.empty() && node->value != '\0') {
        counter++;
        if (counter == target) {
            found = true;
        }
        if (!found) {
            result.pop_back();
        }
        return;
    }

    for (Node* child : node->children) {
        findPermByNumber(child, target, counter, result, found);
        if (found) break;
    }

    if (!found && node->value != '\0') {
        result.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    PMTree* nonConst = const_cast<PMTree*>(&tree);
    nonConst->collectAll(nonConst->getRoot(), current, result);
    return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
    std::vector<char> result;
    std::vector<char> current;
    int counter = 0;
    bool found = false;
    if (num <= 0) return result;
    PMTree* nonConst = const_cast<PMTree*>(&tree);
    nonConst->findPermByNumber(nonConst->getRoot(), num, counter, result,
                               found);
    return result;
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
    std::vector<char> result;
    int n = tree.getSize();
    if (num < 1 || num > factorial(n)) {
        return result;
    }
    PMTree::Node* current = tree.getRoot();
    int target = num - 1;
    int currentN = n;
    while (current->children.size() > 0) {
        int block = factorial(currentN - 1);
        int idx = target / block;
        target = target % block;
        current = current->children[idx];
        result.push_back(current->value);
        currentN--;
    }
    return result;
}
