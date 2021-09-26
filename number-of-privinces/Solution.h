// 547. Number of Provinces
// Medium

#include <vector>

using namespace std; 

class UnionFind {
public:
    UnionFind(const int n): counter(n) {    
        for (int i = 0; i < n; ++i) {
            parent.push_back(i);
            rank.push_back(1);
        }
    }

    ~UnionFind() = default; 

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
        
        if (rank[p_root] > rank[q_root]) {
            parent[p_root] = q_root;
        }
        else if (rank[p_root] < rank[q_root]) {
            parent[q_root] = p_root;
        }   
        else {
            parent[q_root] = p_root;
            rank[q_root]++;
        }
        
        counter--; 
    }
    
    int get_num() const {
        return counter;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int counter; 
    
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        // use union find to connect the cities
        int n = isConnected.size();
        
        UnionFind uf(n); 
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j] == 1) {
                    uf.unionize(i, j);    
                }
            }
        }
        
        return uf.get_num(); 
        
    }    
};