#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

class BST
{
public:
    vector<int> tree;
    int capacity;

    int left(int index)
    {
        return 2 * index + 1;
    }

    int right(int index)
    {
        return 2 * index + 2;
    }

public:
    BST(int size) : capacity(size)
    {
        tree.resize(size, INT_MAX);
    }

    void insert(int key)
    {
        int index = 0;

        while (index < capacity && tree[index] != INT_MAX)
        {
            if (key < tree[index])
            {
                index = left(index);
            }
            else
            {
                index = right(index);
            }
        }

        if (index < capacity)
        {
            tree[index] = key;
        }
    }

    int findLCA(int A, int B)
    {
        int index = 0;
        while (index < capacity && tree[index] != INT_MAX)
        {
            if (tree[index] > A && tree[index] > B)
            {
                index = left(index);
            }
            else if (tree[index] < A && tree[index] < B)
            {
                index = right(index);
            }
            else
            {
                return index;
            }
        }
        return -1; // LCA not found
    }

    void findMinMax(int startIndex, int key, int &minVal, int &maxVal)
    {
        int index = startIndex;
        while (index < capacity && tree[index] != INT_MAX)
        {
            while (tree[index] != key)
            {
                minVal = min(minVal, tree[index]);
                maxVal = max(maxVal, tree[index]);
                if (tree[index] > key)
                {
                    index = left(index);
                }
                else if (tree[index] < key)
                {
                    index = right(index);
                }
            }
            minVal = min(minVal, tree[index]);
            maxVal = max(maxVal, tree[index]);
            break;
        }
    }
    void printfTree()
    {
        cout << "Tree: ";
        for (int i = 0; i < tree.size(); ++i)
        {
            if (tree[i] != INT_MAX)
            {
                cout << tree[i] << " ";
            }
            else
            {
                cout << "NULL ";
            }
        }
        cout << endl;
    }
};

int main()
{
    int N;
    cin >> N;

    vector<int> values(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> values[i];
    }

    int A, B;
    cin >> A >> B;

    int maxHeight = log2(N + 1);
    int maxSize = pow(2, maxHeight + 1);
    BST bst(maxSize);

    for (int i = 0; i < N; ++i)
    {
        bst.insert(values[i]);
    }
    bst.printfTree();

    int lcaIndex;

    lcaIndex = bst.findLCA(A, B);

    int minVal = INT_MAX, maxVal = INT_MIN;

    cout << "start index" << lcaIndex;

    // bst.findMinMax(lcaIndex, A, minVal, maxVal);
    // bst.findMinMax(lcaIndex, B, minVal, maxVal);

    cout << minVal << " " << maxVal << endl;

    return 0;
}
