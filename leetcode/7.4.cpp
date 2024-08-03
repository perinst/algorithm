#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int bfs(vector<vector<int>> &grid, int x, int y, int island_id)
{
    int n = grid.size();
    queue<pair<int, int>> q;

    q.push({x, y});
    grid[x][y] = island_id;
    int area = 0;

    vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (!q.empty())
    {
        auto [cx, cy] = q.front();
    }

    return area;
}
int minDifference(vector<int> &nums)
{
    if (nums.size() <= 4)
    {
        return 0;
    }
    sort(nums.begin(), nums.end());
    int ans = nums.back() - nums[0];
    for (int i = 0; i <= 3; i++)
    {
        ans = min(ans, nums[nums.size() - (3 - i) - 1] - nums[i]);
    }
    return ans;
}

struct ListNode
{
    int val;
    ListNode next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode next) : val(x), next(next) {}
};

ListNode *mergeKLists(vector<ListNode *> &lists)
{
    int n = lists.size();

    while (n > 0)
    {

        for (int i = 0; i < n / 2; i + 2)
        {
            lists[i] = merge(lists[i], lists[i + 1]);
        }

        n /= 2;
    }
}

ListNode *merge(ListNode *n1, ListNode *n2)
{

    ListNode dumb(0);
    ListNode *head = &dumb;

    while (n1 != nullptr && n2 != nullptr)
    {
        if (n1->val > n2->val)
        {
            head->next = n2;
            n2 = n2->next;
        }
        else
        {
            head->next = n1;
            n1 = n1->next;
        }
        head = head->next;
    }

    while (n1 != nullptr)
    {
        head = n1->val;
        n1 = n1->next;
    }
    while (n2 != nullptr)
    {
        head = n2->val;
        n2 = n2->next;
    }

    return dumb->next;
}
void bfs(int start, int idx, string sub, string pattern)
{

    if (sub[idx] != pattern[idx])
        return;

    if (sub.size() == pattern.size())
    {
        return sub.size();
    }
}
int lcsRecur(string &word1, string &word2, int m, int n, vector<vector<int>> &dp)
{
    if (m == 0 || n == 0)
        return 0;

    if (dp[m][n] != -1)
    {
        return dp[m][n]
    }

    if (word1[m - 1] == word2[n - 1])
        return 1 + lcsRecur(word1, word2, m - 1, n - 1);

    int lcsW1 = lcsRecur(word1, word2, m - 1, n, dp);
    int lcsW2 = lcsRecur(word1, word2, m, n - 1, dp);

    dp[m][n] = max(lcsW1, lcsW2);

    return dp[m][n];
}

int longestCommonSubsequence(string text1, string text2)
{
    int m = text1.size();
    int n = text2.size();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < = m; i++)
    {
        for (int j = 0; j <= n; j++)
        {

            if (i == 0 || j == 0)
            {
                continue;
            }

            if (text1[i - 1] == text2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

class Solution
{
    static int[] maxDeque;
    static int[] minDeque;
    static int maxHead;
    static int maxTail;
    static int minHead;
    static int minTail;

public:
    int longestSubarray(int[] nums, int limit)
    {
        int n = nums.length;
        maxDeque = new int[n];
        minDeque = new int[n];
        maxHead = 0;
        maxTail = 0;
        minHead = 0;
        minTail = 0;

        int res = 0;
        int r = 0;
        for (int l = 0; l < n; l++)
        {
            while (r < n && withinLimit(nums, nums[r], limit))
            {
                addToLast(nums, r);
                r++;
            }
            res = Math.max(res, r - l);
            removeExpired(l);
        }
        return res;
    }

    boolean withinLimit(int[] nums, int num, int limit)
    {
        int max = maxHead < maxTail ? Math.max(nums[maxDeque[maxHead]], num) : num;
        int min = minHead < minTail ? Math.min(nums[minDeque[minHead]], num) : num;
        return max - min <= limit;
    }

    void addToLast(int[] nums, int r)
    {
        while (maxHead < maxTail && nums[maxDeque[maxTail - 1]] <= nums[r])
        {
            maxTail--;
        }

        maxDeque[maxTail++] = r;

        while (minHead < minTail && nums[minDeque[minTail - 1]] >= nums[r])
        {
            minTail--;
        }

        minDeque[minTail++] = r;
    }

    void removeExpired(int l)
    {
        if (maxDeque[maxHead] == l)
        {
            maxHead++;
        }
        if (minDeque[minHead] == l)
        {
            minHead++;
        }
    }
}

int
main()
{

    return 0;
}