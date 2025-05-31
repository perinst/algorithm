#include <iostream>
#include <string>
#include <queue>
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

// class Solution
// {
// public:
//     TreeNode *recoverFromPreorder(string traversal)
//     {
//         int i = 0;
//         int val = 0;

//         while (i < traversal.length() && isdigit(traversal[i]))
//         {
//             val = val * 10 + (traversal[i] - '0');
//             i++;
//         }

//         TreeNode *root = new TreeNode(val);

//         int depth = 0;

//         while (i < traversal.size())
//         {

//             depth = 0;
//             while (i < traversal.size() && traversal[i] == '-')
//             {
//                 depth++;
//                 i++;
//             }
//             cout << depth << "\n";
//             int val = 0;
//             while (i < traversal.length() && isdigit(traversal[i]))
//             {
//                 val = val * 10 + (traversal[i] - '0');
//                 i++;
//             }

//             TreeNode *node = findNodeDepth(root, depth - 1);
//             cout << "left: " << node->left << "  right:  " << node->right << "\n";
//             if (node->left == nullptr)
//             {
//                 node->left = new TreeNode(val);
//             }
//             else
//             {
//                 node->right = new TreeNode(val);
//             }
//         }

//         return root;
//     }

//     TreeNode *findNodeDepth(TreeNode *node, int depth)
//     {
//         if (depth == 0)
//         {
//             if (node->left == nullptr)
//                 return node;

//             if (node->right == nullptr)
//                 return node;

//             return nullptr;
//         }

//         TreeNode *left = findNodeDepth(node->left, depth - 1);
//         TreeNode *right = findNodeDepth(node->right, depth - 1);

//         if (left != nullptr)
//             return left;

//         return right;
//     }
// };

class Solution
{
public:
    TreeNode *recoverFromPreorder(string traversal)
    {
        int i = 0;
        return dfs(traversal, i, 0);
    }

    TreeNode *dfs(string &s, int &i, int level)
    {
        int depth = 0;

        while (i + depth < s.size() && s[i + depth] == '-')
        {
            depth++;
        }

        if (depth != level)
            return nullptr;

        i += depth;

        int val = 0;
        while (i < s.size() && isdigit(s[i]))
        {
            val = val * 10 + (s[i] - '0');
            i++;
        }

        TreeNode *node = new TreeNode(val);

        node->left = dfs(s, i, level + 1);
        node->right = dfs(s, i, level + 1);

        return node;
    }
};

int main()
{
    string traversal = "1-2--3--4-5--6--7";
    Solution s;

    s.recoverFromPreorder(traversal);

    return 0;
}