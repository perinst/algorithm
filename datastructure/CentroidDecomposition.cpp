#include <iostream>
#include <vector>
#include <queue>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
using namespace std;

const int N = 20005;

struct Node
{
    vector<Node *> child;
    int val;

    Node(int v) : val(v), child(vector<Node *>(0)) {}
};

int findDecomposition(int t, Node *node)
{
    if (!node)
        return 0;

    if (t == node->val)
        return 0;

    int cnt = 0;

    for (Node *n : node->child)
    {
        cnt += (1 + findDecomposition(t, n));
    }

    return cnt;
}

int centroidDecomposition()
{
    Node *root;
    vector<int> decomposition;

    queue<Node *> q;

    q.push(root);

    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        int target = node->val;
        vector<Node *> listNodeChild = node->child;

        for (Node *n : listNodeChild)
        {
            int decoRoot = findDecomposition(target, root);
            int decoNode = findDecomposition(target, node);

            if (abs(decoRoot - decoNode) < 2)
                decomposition.push_back(target);

            q.push(n);
        }
    }

    cout << decomposition;

    return decomposition.size();
}

int main()
{
    return 0;
}