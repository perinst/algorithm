#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <set>

#define ll long long
#define vi vector<int>
#define vii vector<vi>
#define pii pair<int, int>

#define pb push_back // Thêm phần tử vào vector
#define mp make_pair // Tạo cặp số

#define FOR(i, a, b) for (int i = (a); i < (b); i++)

#define RFOR(i, a, b) for (int i = (a); i >= (b); i--)

#define readArr(arr, n) FOR(i, 0, n) cin >> arr[i]

#define readMatrix(matrix, rows, cols) FOR(i, 0, rows) FOR(j, 0, cols) cin >> matrix[i][j]

#define read(...) \
    __VA_ARGS__;  \
    cin >> __VA_ARGS__;
#define write(...) cout << __VA_ARGS__ << endl;

#define all(x) (x).begin(), (x).end();

#define MOD 1000000007;

#define endl '\n';

#define DEGUG(x) cout << '>' << #x << ':' << x << endl;

const int INF = 1e9 + 7;

using namespace std;

void fastIO()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

class Solution
{

private:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> result;
        vector<int> subset;
        backtracking(0, nums, subset, result);
        return result;
    }

    void backtracking(int start, vector<int> &nums, vector<int> &subsets, vector<vector<int>> &result)
    {

        result.push_back(subsets);

        for (int i = start; i < nums.size(); ++i)
        {
            subsets.push_back(nums[i]);

            backtracking(i + 1, nums, subsets, result);

            subsets.pop_back();
        }
    }

    bool is_within_bounds(int x, int y, int n)
    {
        return x >= 0 && y >= 0 && x < n && y < n;
    }

    void bfs(vector<vector<int>> &m, int i, int j, int rs)
    {

        if (i == j == m.size())
        {
            rs++;
            return;
        }

        if (!is_within_bounds(i, j, m.size()))
            return;
    }

    int countTriplets(vector<int> &arr)
    {
        //
        int rs = 0;
        vector<vector<int>> result;

        //
        queue<pair<int, int>> q;
        //
        q.push({0, arr[0]});
        //
        while (!q.empty())
        {
            pair<int, int> e = q.front();

            q.pop();

            for (int i = 1; i <= 3; i++)
            {
            }
        }
        return rs;
    }
    int hipRecur(vector<int> &a, int &k)
    {

        vi dp(a.size(), INT_MAX);

        int min = hipDpRecurTopDown(a, k, 0, dp);

        return min;
    }

    int hipDpRecurTopDown(vi &a, int k, int idx, vi &dp)
    {

        if (idx >= a.size())
            return 0;

        if (dp[idx] != INT_MAX)
            return dp[idx];

        int minCost = INT_MAX;

        for (int i = idx + 1; i <= min((int)a.size(), idx + k); ++i)
        {

            int cost = (i == a.size() ? 0 : a[idx]) + hipDpRecurTopDown(a, k, i, dp);

            minCost = min(minCost, cost);
        }

        dp[idx] = minCost;

        return minCost;
    }

    int hopDpBottomUp(vector<int> &a, int &k)
    {

        int n = a.size();
        vi dp(n + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 0; i < n; i++)
        {

            if (dp[i] == INT_MAX)
                continue;

            for (int j = 1; j <= k; j++)
            {
                if (i + j > n)
                    continue;

                dp[i + j] = min(dp[i + j], dp[i] + (i + j == n ? 0 : a[i + j - 1]));

                cout << "a[" << i + j - 1 << "]: " << a[i + j - 1] << "   dp[" << i << "]: " << dp[i] << "  dp[" << i + j << "]: " << dp[i + j] << " | " << '\t';
            }
            cout << '\n';
        }

        return dp[n];
    }

    int hopQueue(vector<int> a, int k)
    {

        queue<pair<int, int>> q;
        q.push({0, a[0]});
        int minCost = INT_MAX;

        while (!q.empty())
        {
            auto [index, cost] = q.front();

            q.pop();

            for (int i = index; i < k; i++)
            {

                if (i < a.size())
                {
                    q.push({i, a[i]});
                }
            }
        }
    }
};
class SubsetTwoII
{

private:
    unordered_map<string, bool> memo;

public:
    // Helper function to generate a unique key for memoization
    string getKey(int n, int sum)
    {
        return to_string(n) + "|" + to_string(sum);
    };

    int countWays(int n, int sum)
    {
        // Base cases
        if (sum == 0)
            return 1; // Found a valid subset
        if (n == 0 || sum < 0)
            return 0; // No valid subset

        // Generate a unique key for memoization
        string key = getKey(n, sum);

        // If the result is already computed, return it
        if (memo.find(key) != memo.end())
            return memo[key];

        // Include the current number in the subset
        int include = countWays(n - 1, sum - n);
        // Exclude the current number from the subset
        int exclude = countWays(n - 1, sum);

        // Store the result in the memo table and return
        memo[key] = (include + exclude) % MOD;

        return memo[key];
    }
    void countPartitionTopDown(int n)
    {
        int sum_elem = n * (n + 1) / 2;

        // If the sum is odd, it cannot be split into two subsets with equal sum
        if (sum_elem % 2 != 0)
        {
            cout << 0 << endl;
            return;
        }

        // Each subset's sum needs to be half of the total sum
        int target = sum_elem / 2;

        // Clear memoization table
        memo.clear();

        // Find the number of ways to partition the set into two subsets with equal sum
        int result = countWays(n, target);

        // Since each valid partition is counted twice, divide the result by 2
        // result = (result * (MOD + 1) / 2) % MOD;

        cout << result << endl;
    }
    void countPartitionV2()
    {
        int n;
        cin >> n;

        int sum_elem = n * (n + 1) / 2;

        // can't split it up between two subsets evenly
        if (sum_elem & 1)
        {
            cout << 0 << endl;
            return;
        }

        // each subset's sum needs to be half of the total sum.
        sum_elem /= 2;

        // dp[i][j] = the number of ways to make sum j with the numbers from 1 to i
        vector<vector<int>> dp(n, vector<int>(sum_elem + 1));

        // base case: there is one way to make a sum of zero with zero elements.
        dp[0][0] = 1;
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= sum_elem; j++)
            {
                // there are dp[i - 1][j] possibilities if we don't include the ith
                // element
                dp[i][j] += dp[i - 1][j];

                // previous sum by including the current element
                int prev = j - i;

                if (prev >= 0)
                {
                    dp[i][j] += dp[i - 1][prev];
                }

                dp[i][j] %= MOD;
            }
        }

        cout << dp[n - 1][sum_elem] << '\n';
    }
};

class countTaxi
{

    int minimumTaxiForGroup(vector<int> a)
    {

        int n = a.size();
        int k = 4;
        queue<int> q;

        FOR(i, 0, n)
        {
            vi subset;
            subRecursion(i, a, subset, k);
        }
    }
    void subRecursion(int start, vi &a, vi &subset, int k)
    {

        if (k - a[start] < 0)
        {
                }

        subset.push_back(a[start]);
        subRecursion(start + 1, a, subset, k - a[start]);
        subet.pop();
    }

} int main()
{
    fastIO();
    int n = 7;
    SubsetTwoII sb;
    sb.countPartitionTopDown(n);

    return 0;
}