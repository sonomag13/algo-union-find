/*
    721. Accounts Merge
    Medium

    Given a list of accounts where each element accounts[i] is a list of strings, 
    where the first element accounts[i][0] is a name, and the rest of the elements 
    are emails representing emails of the account.

    Now, we would like to merge these accounts. Two accounts definitely belong to 
    the same person if there is some common email to both accounts. Note that even 
    if two accounts have the same name, they may belong to different people as people 
    could have the same name. A person can have any number of accounts initially, 
    but all of their accounts definitely have the same name.

    After merging the accounts, return the accounts in the following format: the 
    first element of each account is the name, and the rest of the elements are emails 
    in sorted order. The accounts themselves can be returned in any order.

    Example 1:

    Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
    Explanation:
    The first and third John's are the same person as they have the common email "johnsmith@mail.com".
    The second John and Mary are different people as none of their email addresses are used by other accounts.
    We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
    ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
    Example 2:

    Input: accounts = [["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]
    Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std; 
class UnionFind {
    
private:
    int* parent; 
    int* rank; 
    int count; 
    
public:
    UnionFind(const int count): count(count), parent(new int[count]), rank(new int[count]) {
        for (int i = 0; i < count; ++i) {
            // idex of these array represent the account ID
            // val of parent represent the root
            // val of rand represent the depth of children
            parent[i] = i;
            rank[i] = 1; 
        }
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int find(int p) {
        // path compression optimization
        while (p != parent[p]) {            
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p; 
    }

    void getUnion(int p, int q) {
        int root_p{find(p)}, root_q{find(q)};
        
        if (root_p == root_q) {
            // p and q have already been unified
            return; 
        }

        if (rank[root_p] > rank[root_q]) {
            parent[root_q] = root_p;
        }
        else if (rank[root_p] < rank[root_q]) {
            parent[root_p] = root_q;
        }
        else {
            parent[root_q] = root_p;
            rank[root_p]++; 
        }
    }
    
    void printParent() {
        for (int i = 0; i < count; ++i) {
            cout << i << ": " << parent[i] << endl; 
        }
    }
    
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        
        const int numAcc = accounts.size();

        /**
         * Build a map between Email and account ID 
         * Notice that a Email may have multiple accound ID
         **/ 
        map<string, vector<int>> mapEmailId; // use map to keep the Email account sorted    
        
        for (int id = 0; id < numAcc; ++id) {
            for (int im = 1; im < accounts[id].size(); ++im) {
                const string email{accounts[id][im]}; 
                mapEmailId[email].push_back(id);
            }
        }
        
        // connect the account id
        UnionFind uf(numAcc); 
        for (const auto& ele : mapEmailId) {
            vector<int> currId = ele.second;
            for (int i = 1; i < currId.size(); ++i) {
                uf.getUnion(currId[0], currId[i]);
            }
        }

        // regroup the email address
        vector<vector<string>> mergedAccount; 
        int newAccIdx = 0; 
        unordered_map<int, int> mapRootAccIdx; 

        for (const auto & ele : mapEmailId) {
            // just search for the root of the first accound id
            int root = uf.find(ele.second[0]); 

            if (mapRootAccIdx.find(root) == mapRootAccIdx.end()) {
                // the account has not been registered yet
                mapRootAccIdx.insert(make_pair(root, newAccIdx));
                newAccIdx++; 

                // insert the name
                vector<string> newAccount{accounts[root][0]};
                
                // insert the new account into the result
                mergedAccount.push_back(newAccount);

            }

            int currAccIdx = mapRootAccIdx[root]; 
            const string email = ele.first; 
            mergedAccount[currAccIdx].push_back(email);
        }
        
        return mergedAccount; 
    }
}; 