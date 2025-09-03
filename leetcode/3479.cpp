#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class SegmentTree
{
private:
    vector<int> tree;
    vector<int> arr;
    int n;

    void build(int node, int start, int end)
    {
        if (start == end)
            tree[node] = arr[start];
        else
        {
            int mid = (start + end) / 2;

            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);

            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void updateHelper(int node, int start, int end, int idx, int val)
    {
        if (start == end)
        {
            arr[idx] = val;
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;

        if (idx <= mid)
        {
            updateHelper(2 * node, start, mid, idx, val);
        }
        else
        {
            updateHelper(2 * node + 1, mid + 1, end, idx, val);
        }

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int queryHelper(int node, int start, int end, int l, int r)
    {
        if (r < start || l > end)
            return -1;

        if (l <= start && end <= r)
            return tree[node];

        int mid = (start + end) / 2;

        int p1 = queryHelper(tree[node * 2], start, mid, l, r);
        int p2 = queryHelper(tree[node * 2 + 1], mid + 1, end, l, r);

        return max(p1, p2);
    }

    int findLeftMostBasket(int node, int start, int end, int fruit, int searchStart, int searchEnd)
    {
        if (start > searchEnd || end < searchStart)
        {
            return -1;
        }

        if (tree[node] < fruit)
            return -1;

        if (start == end)
        {
            if (arr[start] >= fruit)
                return start;
            else
                return -1;
        }

        int mid = (start + end) / 2;
        int leftResult = findLeftMostBasket(2 * node, start, mid, fruit, searchStart, searchEnd);

        if (leftResult != -1)
            return leftResult;

        return findLeftMostBasket(2 * node + 1, mid + 1, end, fruit, searchStart, searchEnd);
    }

public:
    SegmentTree(vector<int> &baskets)
    {
        n = baskets.size();
        arr = baskets;
        tree.resize(n * 4);
        build(1, 0, n - 1);
    }

    void update(int idx, int val)
    {
        updateHelper(1, 0, n - 1, idx, val);
    }

    int query(int l, int r)
    {
        return queryHelper(1, 0, n - 1, l, r);
    }

    int findLeftmostSuitableBasket(int fruit)
    {
        return findLeftMostBasket(1, 0, n - 1, fruit, 0, n - 1);
    }
};

// complexity: O(n * (n - k) * (n-k)) => suitable for n <= 1000

int lower_bound_c(vector<int> &arr, int &target)
{

    int left = 0;
    int right = arr.size();

    while (left < right)
    {
        int mid = (left + right) / 2;

        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;
}

int numOfUnplacedFruits(vector<int> &fruits, vector<int> &baskets)
{
    SegmentTree segTree(baskets);
    int unplacedCount = 0;

    for (int &fruit : fruits)
    {
        int basketIndex = segTree.findLeftmostSuitableBasket(fruit);

        if (basketIndex != -1)
        {
            segTree.update(basketIndex, 0);
        }
        else
        {
            unplacedCount++;
        }
    }
    return unplacedCount;
}

void solve()
{
    int N;
    cin >> N;
    vector<int> fruits(N);
    vector<int> baskets(N);
    for (int i = 0; i < N; i++)
    {
        cin >> fruits[i];
    }

    for (int i = 0; i < N; i++)
    {
        cin >> baskets[i];
    }

    cout << numOfUnplacedFruits(fruits, baskets) << endl;
}

int main()
{

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}