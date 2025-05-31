#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int leftChild, rightChild;
    long long maxValue;

    Node() : maxValue(0), leftChild(0), rightChild(0) {}
    Node(long long value, int left, int right) : maxValue(value), leftChild(left), rightChild(right) {}
};

const int MAX_NODES = 11000111;
Node segmentTree[MAX_NODES]; 
int totalNodes = 0;         

const int MAX_VERSIONS = 100005;
const int versionRoot[MAX_VERSIONS];

inline int updateMax(int nodeId)
{
    segmentTree[nodeId].maxValue = max(
        segmentTree[segmentTree[nodeId].leftChild].maxValue,
        segmentTree[segmentTree[nodeId].rightChild].maxValue);
}

int update(int left, int right, int updatePos, int newValue, int oldValue)
{
    if (left == right)
    {
        int newNodeIdx = ++totalNodes;
        segmentTree[newNodeIdx] = Node(newValue, 0, 0);
        return newNodeIdx;
    }

    int mid = (left + right) / 2;
    int newNode = ++totalNodes;

    if (updatePos <= mid)
    {
        segmentTree[newNode].leftChild = update(left, mid, updatePos, newValue, segmentTree[oldValue].leftChild);
        segmentTree[newNode].rightChild = segmentTree[oldValue].rightChild;
    }
    else
    {
        segmentTree[newNode].rightChild = update(left, mid, updatePos, newValue, segmentTree[oldValue].rightChild);
        segmentTree[newNode].leftChild = segmentTree[oldValue].leftChild;
    }
    updateMax(newNode);
    return newNode;
    
}

int main()
{

}
