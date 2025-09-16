#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

#define FOR(i, a, b)                \
    for (int i = (a); i < (b); i++) \
        ;

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    void flatten(TreeNode *root)
    {
        if (root == nullptr)
            return;

        stack<TreeNode *> st;

        TreeNode *dumb = new TreeNode();

        st.push(root);

        while (!st.empty())
        {
            TreeNode *node = st.top();
            st.pop();

            dumb->right = new TreeNode(node->val);

            if (node->right)
            {
                st.push(node->right);
            }

            if (node->left)
            {
                st.push(node->left);
            }
        }

        root = &dumb;
    }
};