#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

private:
    vector<TreeNode *> nodes;

    void getListNodeStart(int &valStart, TreeNode *node)
    {
        if (!node)
            return;

        if (node->val == valStart)
        {
            nodes.emplace_back(node);
        }

        getListNodeStart(valStart, node->left);
        getListNodeStart(valStart, node->right);
    };

    bool isDownWardPath(ListNode *head, TreeNode *node)
    {
        if (!head)
            return true;

        if (!node || head->val != node->val)
            return false;

        return isDownWardPath(head->next, node->left) || isDownWardPath(head->next, node->right);
    }

public:
    bool isSubPath(ListNode *head, TreeNode *root)
    {
        this->getListNodeStart(head->val, root);

        for (TreeNode *node : nodes)
        {
            if (isDownWardPath(head, node))
                return true;
        }

        return false;
    }
};
int main()
{

    return 0;
}