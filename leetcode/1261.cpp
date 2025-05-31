#include <iostream>
#include <algorithm>
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

// ["FindElements","find","find","find","find"]
// [[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]

class FindElements
{
public:
    TreeNode *root;
    FindElements(TreeNode *root)
    {
        this->root = root;
        rebuild(root, 0);
    }

    void rebuild(TreeNode *node, int x)
    {
        if (node == nullptr)
            return;

        node->val = x;

        rebuild(node->left, 2 * x + 1);

        rebuild(node->right, 2 * x + 2);
    }

    bool find(int target)
    {
        if (target == 0)
            return true;
        int parent = target % 2 == 0 ? (target - 2) / 2 ? (target - 1) / 2;
        do
        {
            if (parent == 0)
                return true;
            parent = parent % 2 == 0 ? (parent - 2) / 2 ? (parent - 1) / 2;

        } while (parent >= 0);

        return false;
    }

    bool findValue(TreeNode *node, int &target)
    {
        if (node == nullptr)
            return false;
        if (node->val == target)
            return true;

        return findValue(node->left, target) || findValue(node->right, target);
    }
};

int main()
{
    return 0;
}