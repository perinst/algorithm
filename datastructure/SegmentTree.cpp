#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Node
{
public:
    Node *leftNode;
    Node *rightNode;
    int leftRange;
    int rightRange;
    int minRange; // Stores the index of the minimum value

    Node(int left, int right, int val) : leftNode(nullptr), rightNode(nullptr), leftRange(left), rightRange(right), minRange(val) {}
    Node() : leftNode(nullptr), rightNode(nullptr), leftRange(0), rightRange(0), minRange(-1) {}
};

class SegmentTree
{
private:
    vector<int> nums;
    Node *root;

public:
    SegmentTree(vector<int> &inputNums)
    {
        nums = inputNums;
        root = build(0, nums.size() - 1);
    }

    Node *build(int left, int right)
    {
        if (left == right)
            return new Node(left, right, left); // Store the index of the minimum element

        Node *newNode = new Node();

        newNode->leftRange = left;
        newNode->rightRange = right;

        int mid = (right + left) / 2;

        newNode->leftNode = build(left, mid);
        newNode->rightNode = build(mid + 1, right);

        // Compare the minimum values at the indices stored in left and right nodes
        if (nums[newNode->leftNode->minRange] < nums[newNode->rightNode->minRange])
            newNode->minRange = newNode->leftNode->minRange;
        else
            newNode->minRange = newNode->rightNode->minRange;

        return newNode;
    }

    int queryMin(int left, int right)
    {
        return queryMin(root, left, right);
    }

    int queryMin(Node *node, int left, int right)
    {
        if (!node || left > node->rightRange || right < node->leftRange)
        {
            return -1; // Invalid case
        }

        if (left <= node->leftRange && node->rightRange <= right)
        {
            return node->minRange; // Return the index of the minimum value in the range
        }

        // Query the left and right children
        int leftMin = queryMin(node->leftNode, left, right);
        int rightMin = queryMin(node->rightNode, left, right);

        // Handle cases where one side is out of range
        if (leftMin == -1)
            return rightMin;
        if (rightMin == -1)
            return leftMin;

        // Return the index with the minimum value
        return nums[leftMin] < nums[rightMin] ? leftMin : rightMin;
    }
};

int main()
{
    vector<int> nums = {2, 4, 1, 5, 6, 3};
    SegmentTree st(nums);

    // Query for the minimum index in range [1, 4]
    int minIndex = st.queryMin(1, 4);
    cout << "Minimum value in range [1, 4]: " << nums[minIndex] << endl;

    return 0;
}
