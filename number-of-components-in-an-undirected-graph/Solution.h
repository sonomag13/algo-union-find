// LeetCode 323. Number of Connected Components in an Undirected Graph
// Medium

#include <vector>

using namespace std; 

class UnionFind {
public:
    UnionFind(const int n): counter(n), parent(new int[n]), rank(new int[n]) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 1; 
        }
    }
    
    ~UnionFind() {
        delete[] parent;
        delete[] rank; 
    }
    
    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p; 
    }
    
    void unionize(int p, int q) {
        
        int p_root = find(p);
        int q_root = find(q); 
        
        if (p_root == q_root) {
            return; 
        }
        
        if (rank[p_root] < rank[q_root]) {
            parent[q_root] = p_root; 
        }
        else if (rank[p_root] > rank[q_root]) {
            parent[p_root] = q_root;
        }
        else {
            parent[p_root] = q_root;
            rank[p_root]++; 
        }
        counter--; 
    }
    
    int getCounter() const {
        return counter; 
    }
    
private:
    int* parent; 
    int* rank; 
    int counter; 
};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        
        UnionFind uf(n);
        
        for (auto & edge : edges) {
            uf.unionize(edge[0], edge[1]);
        }
        
        return uf.getCounter();
        
    }
};