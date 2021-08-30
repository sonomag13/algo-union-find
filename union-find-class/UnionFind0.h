#pragma once

#include <cassert>
#include <iostream>
#include <vector>

namespace UF0 {

    class UnionFind {
    private:
        int* parent; // index: node; value: root
        int* size;   // number of the node points to node parent[i]
        int count;   // number of the nodes

    public:
        UnionFind(int count): parent(new int[count]), size(new int[count]), count(count) {
            for (int i = 0; i < count; ++i) {
                parent[i] = i;  // generate a member that has no connection
                size[i] = 1;    // every node is its own root
            }
        }
        ~UnionFind() {
            delete[] parent;
            delete[] size;
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

            /**
             * size optimization
             * make the length of the tree as short as possible
             **/
            if (size[root_p] <  size[root_q]) {
                parent[root_p] = root_q;
                size[root_q] += size[root_p];
            }
            else {
                parent[root_q] = root_p;
                size[root_p] += size[root_q];
            }
        }

        int* getParent() {
            return parent;
        }

    };

} // UF0