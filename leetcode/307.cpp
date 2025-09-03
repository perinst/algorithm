#include <iostream>
#include <vector>

using namespace std;

class NumArray
{
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    void buildSegment(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }

        int mid = (start + end) / 2;

        buildSegment(2 * node, start, mid);
        buildSegment(2 * node + 1, mid + 1, end);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void updateHelper(int node, int start, int end, int index, int val)
    {

        if (start == end)
        {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;

        if (index <= mid)
        {
            updateHelper(2 * node, start, mid, index, val);
        }
        else
        {
            updateHelper(2 * node + 1, mid + 1, end, index, val);
        }

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

public:
    NumArray(vector<int> &nums)
    {
        n = nums.size();
        arr = nums;
        tree.resize(4 * n);
        build();
    }

    void build()
    {
        buildSegment(1, 0, n - 1);
    }

    void update(int index, int val)
    {
        arr[index] = val;
        updateHelper(1, 0, n - 1, index, val);
    }

    int sumRangeHelper(int node, int start, int end, int left, int right)
    {
        if (right < start || left > end)
            return 0;

        if (start <= left && right <= end)
        {
            return tree[node];
        }

        int mid = (start + end) / 2;

        if (mid >= left && mid <= right)
        {
            return sumRangeHelper(2 * node, start, mid, left, mid) + sumRangeHelper(2 * node + 1, mid + 1, end, mid + 1, right);
        }

        return sumRangeHelper(2 * node, start, mid, left, right) + sumRangeHelper(2 * node + 1, mid + 1, end, left, right);
    }

    int sumRange(int left, int right)
    {
        return sumRangeHelper(1, 0, n - 1, left, right);
    }
};

int main()
{
    return 0;
}