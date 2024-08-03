#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;

    Node(int value)
    {
        key = value;
        left = nullptr;
        right = nullptr;
    }
};

Node *insert(Node *root, int key)
{
    if (root == nullptr)
    {
        return new Node(key);
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    return root;
}

Node *findLCA(Node *root, int n1, int n2)
{
    if (root == nullptr)
        return nullptr;
    if (root->key > n1 && root->key > n2)
    {
        return findLCA(root->left, n1, n2);
    }
    if (root->key < n1 && root->key < n2)
    {
        return findLCA(root->right, n1, n2);
    }
    return root;
}

void findMinMaxAB(Node *root, int key, int &minV, int &maxV)
{
    while (root != nullptr)
    {
        minV = min(minV, root->key);
        maxV = max(maxV, root->key);

        if (root->key > key)
        {
            root = root->left;
        }
        else if (root->key < key)
        {
            root = root->right;
        }
        else
        {
            break;
        }
    }
}
//
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

    Node *root = nullptr;
    for (int i = 0; i < N; ++i)
    {
        root = insert(root, values[i]);
    }

    Node *lca = findLCA(root, A, B);

    int minV = INT_MAX, maxV = INT_MIN;
    findMinMaxAB(lca, A, minV, maxV);
    findMinMaxAB(lca, B, minV, maxV);

    cout << minV << " " << maxV << endl;

    return 0;
}
