#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Node
{
    int start;
    int end;
    vector<int> listsort;
    Node *left;
    Node *right;
};

const int MAX_N = 100000;
vector<int> arr(MAX_N);                 // Input array
vector<vector<int>> segTree(4 * MAX_N); // Segment tree

vector<int> merge(const vector<int> &left, const vector<int> &right)
{
    vector<int> result;
    int i = 0, j = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            result.push_back(left[i]);
            i++;
        }
        else
        {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size())
    {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size())
    {
        result.push_back(right[j]);
        j++;
    }
    return result;
}
// Build the segment tree with sorted subarrays

void build(int node, int start, int end)
{
    if (start == end)
    {
        segTree[node].push_back(arr[start]);
    }
    else
    {
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);

        segTree[node] = merge(segTree[2 * node], segTree[2 * node + 1]);
    }
}

// Query the segment tree to find the k-th smallest element in the range [L, R]

int query(int nodeIndex, int start, int end, int L, int R, int k)
{
    if (R < start || end < L)
        return -1;

    if ()
    {
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    // Reading input array
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    build(1, 0, n - 1);

    for (int i = 0; i < m; i++)
    {
        int L, R, k;
        cin >> L >> R >> k;
        L--;
        R--;
        cout << query(1, 0, n - 1, L, R, k) << endl;
    }

    return 0;
}