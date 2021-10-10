// LeetCode 1971. Find if Path Exists in Graph
// Easy

#include <vector>

using namespace std; 

class UnionFind {
    
public:
    UnionFind(int n) {
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
            rank.push_back(0);
        }
    }
    
    ~UnionFind() = default; 
    
    int find (int p) {
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
        
    }        

private: 
    vector<int> parent; 
    vector<int> rank; 
};


class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        
        UnionFind uf(n); 
        
        for (auto & edge : edges) {
            uf.unionize(edge[0], edge[1]);
        }
        
        return uf.find(start) == uf.find(end);
        
    }
};