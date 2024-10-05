#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
                                                       right(right) {}
};

vector<int> postorderTraversal(TreeNode *root)
{
    if (!root)
        return vector<int>(0);

    vector<int> postorder;

    std::stack<TreeNode *> stack;

    stack.push(root);
    TreeNode *prevNode = nullptr;

    while (root || !stack.empty())
    {

        if (root)
        {
            stack.push(root->left);
            root = root->left;
        }
        else
        {
            root = stack.top();
            if (!root->right || root->right == prevNode)
            {
                postorder.push_back(root->val);
                stack.pop();
                prevNode = root;
                root = nullptr;
            }
            else
            {
                root = root->right;
            }
        }
    }

    return postorder;
}
int main()
{
    return 0;
}