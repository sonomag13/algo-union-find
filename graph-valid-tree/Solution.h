// 261. Graph Valid Tree
// Medium

#include <vector>

using namespace std; 

class UnionFind {    
public:
    UnionFind(const int n): parent(new int[n]), rank(new int[n]), counter(n) {        
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
    bool validTree(int n, vector<vector<int>>& edges) {
        
        UnionFind uf(n); 
        
        for (auto & edge : edges) {
            
            int root1 = uf.find(edge[0]);
            int root2 = uf.find(edge[1]);
            
            if (root1 == root2) {
                // Important
                // edge[0] and edge[1] have been visited, and they point to 
                // the same root. However, edge[0] and edge[1] also suggests
                // edge[1] points to edge[0], which violate the tree structure
                return false; 
            }
            else {
                uf.unionize(root1, root2);
            }
        }
        
        return uf.getCounter() == 1; 
        
    }
};