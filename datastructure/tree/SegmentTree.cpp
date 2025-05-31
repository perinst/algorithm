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
    // Stores the index of the minimum value
    int minRangeIdx;

    Node(int left, int right, int val) : leftNode(nullptr), rightNode(nullptr), leftRange(left), rightRange(right), minRangeIdx(val) {}
    Node() : leftNode(nullptr), rightNode(nullptr), leftRange(0), rightRange(0), minRangeIdx(-1) {}
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
            return new Node(left, right, left);

        Node *newNode = new Node();

        newNode->leftRange = left;
        newNode->rightRange = right;

        int mid = (right + left) / 2;

        newNode->leftNode = build(left, mid);
        newNode->rightNode = build(mid + 1, right);

        if (nums[newNode->leftNode->minRangeIdx] < nums[newNode->rightNode->minRangeIdx])
            newNode->minRangeIdx = newNode->leftNode->minRangeIdx;
        else
            newNode->minRangeIdx = newNode->rightNode->minRangeIdx;

        return newNode;
    }

    Node *insertLast(int val)
    {
        this->nums.push_back(val);
        Node *node = this->root;

        while (node->rightNode != nullptr)
        {
            int idx = node->minRangeIdx;
            if (num[idx] < val)
            {
                node->minRangeIdx = this->nums.size() - 1;
            }

            node = node->rightNode;
            node->rightRange = this->nums.size() - 1;
        }
    }

    void updateSingle(int val, int index)
    {
        this->nums[index] = val;
        int updateFromIdx = (this->nums.size() - 1) / 2;

        updateSingle(this->root, value, 0, this.nums.size() - 1, index);
    }

    Node *updateSingle(Node *node, int &value, int left, int right, int &index)
    {
        if (left == right && left == index)
        {
            return node;
        }

        int mid = (right + left) / 2;

        if (index <= mid)
        {
            Node *leftNode = updateSingle(node->leftNode, value, left, mid, index);
        }
        else
        {
            Node *rightNode = updateSingle(node->rightNode, value, mid + 1, right, index);
        }
    }

    Node *plusRange(int valuePlus, int fromIdx, int toIdx)
    {
    }

    int queryMin(int left, int right)
    {
        return queryMin(root, left, right);
    }

    int queryMin(Node *node, int left, int right)
    {
        if (!node || left > node->rightNode->rightRange || right < node->leftNode->leftRange)
        {
            return -1;
        }

        if (left <= node->leftRange && node->rightRange <= right)
            return node->minRangeIdx;

        int minLeftIdx = queryMin(node->leftNode, left, right);
        int minRightIdx = queryMin(node->rightNode, left, right);

        if (minLeftIdx == -1)
            return minRightIdx;
        if (minRightIdx == -1)
            return minLeftIdx;

        return nums[minLeftIdx] < nums[minRightIdx] ? minLeftIdx : minRightIdx;
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
