#pragma once

#include <cassert>
#include <iostream>
#include <vector>

namespace UF1 {

    class UnionFind {
    private:
        int* parent;
        int* rank;
        int count;

    public:
        UnionFind(int count): parent(new int[count]), rank(new int[count]), count(count) {
            for (int i = 0; i < count; ++i) {
                // generate a member that has no connection
                parent[i] = i;
            }
        }
        ~UnionFind() {
            delete[] parent;
            delete[] rank;
        }

        int find(int p) {
            // return the root of the p
            assert(p >= 0 && p < count);
            while (p != parent[p]) {
                // keep tracing back until find the root of p
                p = parent[p];
            }
            return p;
        }

        bool isConnected(int p, int q) {
            return find(p) == find(q);
        }

        void unionElements(int p, int q) {
            int root_p{find(p)};
            int root_q{find(q)};
            if (root_p == root_q) {
                return;
            }

            if (rank[root_p] < rank[root_q]) {
                parent[root_p] = root_q;
            }
            else if (rank[root_p] > rank[root_q]) {
                parent[root_q] = root_p;
            }
            else {
                // rank[root_p] > rank[root_q]
                parent[root_p] = root_q;
                rank[root_q]++;
            }
        }

        int* getParent() {
            return parent;
        }

    };

} // UF1