#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution
{
public:
    Node *connect(Node *root)
    {
        if (!root)
            return root;

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {

            int amountNodes = q.size();
            Node *prev = nullptr;

            for (int i = 0; i < amountNodes; i++)
            {
                Node *node = q.front();
                q.pop();

                if (prev)
                {
                    prev->next = node;
                }

                prev = node;
                q.push(node->left);
                q.push(node->right);
            }
        }

        return root;
    }
};

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // TODO: implement logic here
}

int main()
{
    // fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}