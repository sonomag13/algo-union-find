// LeetCode 1101. The Earliest Moment When Everyone Become Friends
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
    int earliestAcq(vector<vector<int>>& logs, int n) {
        
        auto comp = [] (const logtype& log1, const logtype& log2) {
            return log1[0] < log2[0];
        };        
        sort(logs.begin(), logs.end(), comp); 
        
        UnionFind uf(n);         
        for (auto& log : logs) {            
            uf.unionize(log[1], log[2]);            
            if (uf.getCounter() == 1) {
                // when all the people become friend, there will be 
                // only one group
                return log[0]; 
            }            
        }
        
        return -1; 
        
    }
    
private:
    typedef vector<int> logtype;
};