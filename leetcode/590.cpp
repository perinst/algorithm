#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

void dfs(Node *node, vector<int> &a)
{
    if (node == nullptr)
        return;

    for (Node *childNode : node->children)
    {
        dfs(childNode, a);
    }

    a.push_back(node->val);
}

vector<int> postorder(Node *root)
{

    vector<int> a;
    if (!root)
        return a;

    Node *prevNode;

    std::stack<Node *> stack;
    stack.push(root);

    while (!stack.empty())
    {
        Node *node = stack.top();
        stack.pop();

        a.push_back(node->val);

        if (!node)
            continue;

        for (Node *n : node->children)
            stack.push(n);
    }

    reverse(a.begin(), a.end());

    return a;
}

int main()
{

    return 0;
}