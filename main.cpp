#include <iostream>

#include "utils.h"
#include "UnionFind0.h"
#include "UnionFind1.h"
#include "UnionFind2.h"

using namespace std;

int main() {
    int n{10};

    {
        cout << "union find with size optimization" << endl;
        UF0::UnionFind uf(n);
        uf.unionElements(4, 3);
        uf.unionElements(3, 8);
        uf.unionElements(6, 5);
        uf.unionElements(9, 4);
        uf.unionElements(5, 0);
        uf.unionElements(2, 1);
        uf.unionElements(7, 2);
        uf.unionElements(6, 2);
        printArray(uf.getParent(), n);
    }

    {
        cout << "union find with rank optimization" << endl;
        UF1::UnionFind uf(n);
        uf.unionElements(4, 3);
        uf.unionElements(3, 8);
        uf.unionElements(6, 5);
        uf.unionElements(9, 4);
        uf.unionElements(5, 0);
        uf.unionElements(2, 1);
        uf.unionElements(7, 2);
        uf.unionElements(6, 2);
        printArray(uf.getParent(), n);
    }

    {
        cout << "union find with rand optimization & path compression" << endl;
        UF2::UnionFind uf(n);

        uf.unionElements(4, 3);
        uf.unionElements(3, 8);
        uf.unionElements(6, 5);
        uf.unionElements(9, 4);
        uf.unionElements(5, 0);
        uf.unionElements(2, 1);
        uf.unionElements(7, 2);
        uf.unionElements(6, 2);

        cout << "before path compression" << endl;
        printArray(uf.getParent(), n);

        // using find to compress the path
        cout << "root of 6: " << uf.find(6) << endl;
        cout << "root of 0: " << uf.find(0) << endl;

        cout << "after path compression" << endl;
        printArray(uf.getParent(), n);
    }


    return 0;
}