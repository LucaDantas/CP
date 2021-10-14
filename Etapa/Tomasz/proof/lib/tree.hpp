#ifndef _LIBGEN_TREE_HPP
#define _LIBGEN_TREE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.hpp"
#include "randomizer.hpp"

namespace libgen {

class Tree : public std::vector<std::pair<int,int>> {
public:
    template <typename Generator>
    void generate_prufer(int n, Generator& gen, int index = 1) {
        if(n == 1) return;
        this->resize(n-1);
        
        libgen::vector<int> prufer;
        prufer.generate(n-2, {0, n-1}, gen);

        std::vector<int> degree(n, 1);
        
        for(int x : prufer)
            ++degree[x];

        int ptr = 0, leaf;
        while(degree[ptr] != 1) ++ptr;
        leaf = ptr;

        for(int i = 0; i < n-2; i++) {
            (*this)[i] = std::pair<int,int>(leaf, prufer[i]);
            --degree[leaf];
            if(--degree[prufer[i]] == 1 && prufer[i] < ptr) leaf = prufer[i];
            else { while(degree[ptr] != 1) ++ptr; leaf = ptr; }
        }

        (*this)[n-2] = std::pair<int,int>(leaf, n-1);

        for(int i = 0; i < n-1; i++)
            (*this)[i].first += index, (*this)[i].second += index;

        std::shuffle(this->begin(), this->end(), gen);
    }

    template<typename Generator>
    void generate_blocks(int n, int group_size, Generator& gen, int index = 1) {
        std::vector<std::vector<int>> block;
        libgen::randomizer<int> rng(1, group_size);

        libgen::vector<int> ind;
        ind.permutation(n, 0, gen);

        this->resize(n-1);
        int pos = 0;
        for(int i = 0, sz = 0; sz < n; i++) {
            int b = std::min(n - sz, rng(gen));
            std::vector<int> here = {ind[sz]};
            for(int j = 1; j < b; j++) {
                here.push_back(ind[sz + j]);
                (*this)[pos++] = {ind[sz + j], ind[sz]};
            }
            block.push_back(here);
            sz += b;
        }

        Tree t;
        t.generate_prufer((int)block.size(), gen, 0);

        // It is too expensive to declare a libgen::randomizer<int> every time
        auto rnd = [&gen](int m) { return (int)(gen() % m + m) % m; };
        for(std::pair<int,int> p : t)
            (*this)[pos++] = {block[p.first][rnd((int)block[p.first].size())], block[p.second][rnd((int)block[p.second].size())]};

        for(int i = 0; i < n-1; i++)
            (*this)[i].first += index, (*this)[i].second += index;

        std::shuffle(this->begin(), this->end(), gen);
    }
private:
};

template <typename T = int, typename Randomizer = randomizer<T>>
class WeightedTree : public std::vector<std::pair<std::pair<int, int>, T>> {
public:
    template <typename Generator>
    void generate_prufer(int n, std::pair<T, T> const& range, Generator& gen, int index = 1) {
        if(n == 1) return;
        t.generate_prufer(n, gen, index);
        set(range, gen);
    }

    template <typename Generator>
    void generate_blocks(int n, int group_size, std::pair<T, T> const& range, Generator& gen, int index = 1) {
        if(n == 1) return;
        t.generate_blocks(n, group_size, gen, index);
        set(range, gen);
    }

private:
    Tree t;
    
    template <typename Generator>
    void set(std::pair<T, T> const& range, Generator& gen) {
        Randomizer rng(range.first, range.second);

        this->resize(t.size());

        for(std::size_t i = 0; i < t.size(); i++)
            (*this)[i] = {t[i], rng(gen)};

        t.clear();
    }
};

}

#endif
