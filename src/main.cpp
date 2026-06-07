// Copyright 2022 NNTU-CS
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>
#include "tree.h"

int factorial(int n) {
    int res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

int main() {
    std::vector<char> in1 = {'1', '2', '3'};
    PMTree tree1(in1);

    std::vector<std::vector<char>> perms = getAllPerms(tree1);
    for (size_t i = 0; i < perms.size(); i++) {
        for (char c : perms[i]) std::cout << c;
        std::cout << " ";
    }
    std::cout << std::endl;

    for (char c : getPerm1(tree1, 2)) std::cout << c;
    std::cout << std::endl;
    for (char c : getPerm2(tree1, 3)) std::cout << c;
    std::cout << std::endl;

    std::vector<char> in2 = {'1', '3', '5', '7'};
    PMTree tree2(in2);
    for (int i = 1; i <= 5; i++) {
        for (char c : getPerm2(tree2, i)) std::cout << c;
        std::cout << " ";
    }
    std::cout << std::endl;

    std::cout << "\nn\tall\tp1\tp2" << std::endl;

    unsigned int seed = static_cast<unsigned>(std::time(nullptr));

    for (int n = 3; n <= 8; n++) {
        std::vector<char> sym;
        for (int i = 0; i < n; i++) {
            sym.push_back('a' + i);
        }

        PMTree tree(sym);
        int num = rand_r(&seed) % factorial(n) + 1;

        auto start = std::chrono::high_resolution_clock::now();
        auto all = getAllPerms(tree);
        auto end = std::chrono::high_resolution_clock::now();
        int64_t tAll = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        auto p1 = getPerm1(tree, num);
        end = std::chrono::high_resolution_clock::now();
        int64_t tP1 = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        auto p2 = getPerm2(tree, num);
        end = std::chrono::high_resolution_clock::now();
        int64_t tP2 = std::chrono::duration_cast<
            std::chrono::microseconds>(end - start).count();

        std::cout << n << "\t" << tAll << "\t" << tP1 << "\t" << tP2
                  << std::endl;
    }

    return 0;
}
