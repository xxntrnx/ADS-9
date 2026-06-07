// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>
struct Node {
    char value;
    std::vector<Node*> children;
    Node(char v) : value(v) {}
};

class PMTree {
 private:
    Node* root;
    void buildTree(Node* node, std::vector<char> remaining); 
    void collectAll(Node* node, std::vector<char>& current, 
                    std::vector<std::vector<char>>& result);
    void findPermByNumber(Node* node, int target, int& counter, 
                          std::vector<char>& result, bool& found);

 public:
    explicit PMTree(const std::vector<char>& elements);
    ~PMTree();
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
