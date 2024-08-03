#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>
#include <queue>
#include <set>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int INF = 1e9 + 7;

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define RFOR(i, a, b) for (int i = (a); i >= (b); i--)

#define CINARR(arr, n)      \
    FOR(i, 0, n)            \
    {                       \
        std::cin >> arr[i]; \
    }

#define COUTARR(arr)                \
    FOR(i, 0, arr.size())           \
    {                               \
        std::cout << arr[i] << " "; \
    }

#define ll long long

using namespace std;

const int MAX_TIME = 500000;
struct Candidate
{
    int index;
    int programmingSkill;
    int testingSkill;
    bool operator<(const Candidate &other) const
    {
        return index < other.index;
    }
};

class Solution
{
public:
    int minIncrementForUnique(vector<int> &nums)
    {
        const int n = nums.size();
        sort(nums.begin(), nums.end());
        int res = 0;
        for (int i = 1; i < n; i++)
        {
            if (nums[i] <= nums[i - 1])
            {

                res += (nums[i - 1] + 1 - nums[i]);
                nums[i] += (nums[i - 1] + 1 - nums[i]);

                for (const auto &i : nums)
                {
                    cout << i;
                }
            }
        }

        return res;
    }

    int minIncrementForUniqueFrequence(vector<int> &nums)
    {
        int maxVal = nums[0];
        int res = 0;
        for (int num : nums)
        {
            maxVal = max(num, maxVal);
        }

        vector<int> fre(nums.size() + maxVal + 1, 0);
        for (int num : nums)
        {
            fre[num]++;
        }

        for (int i = 0; i < fre.size(); i++)
        {
            if (fre[i] <= 1)
                continue;

            int duplicate = fre[i] - 1;
            res += duplicate;
            fre[i + 1] += duplicate;
        }
        return res;
    }

    int minIncrementForUniqueHashTable(vector<int> &nums)
    {
        unordered_map<int, int> fre;
        int res = 0;

        for (int num : nums)
        {
            fre[num]++;
        }

        for (auto &[num, count] : fre)
        {
            if (count == 1)
                continue;
            res += count - 1;
            fre[num + 1] = count - 1;
        }
        return res;
    }

    int monocarpInterview(int n, int m)
    {
        int totalCandidate = n + m + 1;

        vector<int> programingSkill(totalCandidate);
        vector<int> testingSkill(totalCandidate);

        //
        for (int i = 0; i < totalCandidate; ++i)
        {
            cin >> programingSkill[i] >> testingSkill[i];
        }
        //
        vector<long long> results(totalCandidate, 0);
        //
        FOR(excludedIndex, 0, totalCandidate)
        {
            //
            int programmers = 0;
            int testers = 0;
            //
            ll programingTeamSkill = 0;
            ll testetTeamSkill = 0;
            //
            vector<pair<int, int>> remainingCandidates;
            //
            FOR(i, 0, totalCandidate)
            {
                if (i != excludedIndex)
                    remainingCandidates.push_back({programingSkill[i], testingSkill[i]});
            }

            sort(remainingCandidates.begin(), remainingCandidates.end(), [](const pair<int, int> &a, const pair<int, int> &b)
                 {
                     return a.first > b.first; // Sort by programming skill in descending order
                 });

            long long programmingSkillSum = 0;
            for (int i = 0; i < n; ++i)
            {
                programmingSkillSum += remainingCandidates[i].first;
            }

            sort(remainingCandidates.begin(), remainingCandidates.end(), [](const pair<int, int> &a, const pair<int, int> &b)
                 {
                     return a.second > b.second; // Sort by testing skill in descending order
                 });

            long long testingSkillSum = 0;

            for (int i = 0; i < m; ++i)
            {
                testingSkillSum += remainingCandidates[i].second;
            }

            results[excludedIndex] = programmingSkillSum + testingSkillSum;
        }

        for (int i = 0; i < totalCandidate; ++i)
        {
            cout << "Excluding candidate " << i + 1 << ": " << results[i] << endl;
        }

        return 0;
    }
};

int maximizedCapBacktricking(int k, int w, int startIdx, vector<int> &memo, vector<int> &profits, vector<int> &capital)
{
    if (k == 0)
    {
        return w;
    }

    int maxCapital = w;

    for (int i = startIdx; i < profits.size(); i++)
    {
        if (w >= capital[i] && memo[i] == -1)
        {
            memo[i] = i;
            maxCapital = max(maxCapital, maximizedCapBacktricking(k - 1, w + profits[i], i, memo, profits, capital));
            memo[i] = -1;
        }
    }

    return maxCapital;
}

int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
{
    int maxCap = w;

    for (int i = 0; i < profits.size(); i++)
    {
        if (w >= capital[i])
        {
            vector<int> memo(profits.size(), -1);
            memo[i] = i;
            maxCap = max(maxCap, maximizedCapBacktricking(k - 1, w + profits[i], 0, memo, profits, capital));
        }
    }

    return maxCap;
}

int minPatches(vector<int> &nums, int n)
{
    int missing = 1;
    int idx = 0;
    int patch = 0;

    while (missing <= n)
    {

        if (idx < nums.size() && nums[idx] <= missing)
        {
            missing += nums[idx];
            idx++;
        }
        else
        {
            missing += missing;
            patch++;
        }
    }
    cout << patch;
    return patch;
}

void backTrackSubset(int start, vector<int> nums, int sub, int maxConsecutive, unordered_map<int, int> m)
{

    if (sub == maxConsecutive)
    {
        if (sub == 0)
            maxConsecutive++;
        else if (m.count(sub))
        {
            maxConsecutive++;
            return;
        }
    }
    else
    {
        m[sub] = sub;
    }

    for (int i = start; i < nums.size(); i++)
    {
        sub += nums[i];
        backTrackSubset(i + 1, nums, sub, maxConsecutive, m);
        sub -= nums[i];
    }
}

int getMaximumConsecutive(vector<int> &coins)
{

    unordered_map<int, int> m;

    int sub = 0;
    int maxConsecutive = 0;

    backTrackSubset(0, coins, sub, maxConsecutive, m);
    cout << maxConsecutive;
    return maxConsecutive;
}

int getMaximumConsecutiveSort(vector<int> &coins)
{
    int maxCon = 1;
    sort(coins.begin(), coins.end());

    for (int c : coins)
    {
        if (c < maxCon + 1)
            maxCon += c;
        else
            break;
    }

    return maxCon;
}

void backTracking4Sum(vector<int> &nums, vector<vector<int>> &rs, vector<int> &sub4, int start, int target)
{
    if (sub4.size() == 4 && target == 0)
    {
        rs.push_back(sub4);
        return;
    }

    for (int i = start; i < nums.size(); ++i)
    {
        if (i > start && nums[i] == nums[i - 1])
            continue;
        // Skip duplicates

        sub4.push_back(nums[i]);
        backTracking4Sum(nums, rs, sub4, i + 1, target - nums[i]);
        sub4.pop_back();
    }
}

vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    vector<vector<int>> rs;
    vector<int> sub4;

    // sort(nums.begin(), nums.end()); // Sort the array to handle duplicates
    backTracking4Sum(nums, rs, sub4, 0, target);

    return rs;
};

vector<vector<int>> fourSumV2(vector<int> nums, int &target)
{
    vector<vector<int>> rs;
    vector<int> sub4;

    queue<pair<vector<int>, pair<int, int>>> q;
    q.push({{}, {0, target}});
    int n = nums.size();

    while (!q.empty())
    {
        auto current = q.front();
        q.pop();
        vector<int> combination = current.first;
        int startIdx = current.second.first;
        int remanningTarget = current.second.second;

        if (combination.size() == 4 && remanningTarget == 0)
        {
            rs.push_back(combination);
            continue;
        }

        for (int i = startIdx; i < n; i++)
        {

            // if (i > start && nums[i] == nums[i - 1])
            //     continue;

            vector<int> newCombination = combination;
            newCombination.push_back(nums[i]);
            q.push({newCombination, {i + 1, remanningTarget - nums[i]}});
        }
    }

    return rs;
}

vector<vector<int>> fourSumV3(vector<int> &num, int target)
{
}

int monoFindMostTeamInterview(int n, int m)
{
    int total = n + m;
    vector<int> programers;
    vector<int> testers;
    vector<pair<int, int>> pairSkils;
    int maxTotalSkill = 0;

    for (int i = 0; i < total; i++)
    {
        cin >> programers[i] >> testers[i];
        pairSkils.push_back({programers[i], testers[i]});
    }

    queue<pair<vector<int>, int>> q;

    q.push({{programers[0]}, 0});

    vector<int> subIdx;

    while (!q.empty())
    {

        auto current = q.front();
        q.pop();
        vector<int> subIdx = current.first;
        int start = current.second;
        if (subIdx.size() == n)
        {
            int total = 0;
            int idx = 0;
            for (int i = 0; i < n + m; i++)
            {

                if (subIdx[idx] == i)
                {
                    idx++;
                    total += programers[i];
                }
                else
                {
                    total += testers[i];
                }
            }
            if (total > maxTotalSkill)
                maxTotalSkill = total;
        }

        for (int i = start; i < n; i++)
        {
            subIdx.push_back(i);
            q.push({subIdx, i + 1});
        }
    }

    return maxTotalSkill;
}

class UniPaths
{
    int uniquePathsDPTab(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++)
        {
            dp[i][0] = 1;
        }

        for (int j = 0; j < n; j++)
        {
            dp[0][j] = 1;
        }

        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    int uniquePathsDPMemo(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return bfs(0, 0, m, n, dp);
    }

    int bfs(int i, int j, int &m, int &n, vector<vector<int>> &dp)
    {
        if (i >= m || j >= n)
            return 0;

        if (i == m - 1 && j == n - 1)
            return 1;

        if (dp[i][j] != -1)
            return dp[i][j];

        dp[i][j] = bfs(i + 1, j, m, n, dp) + bfs(i, j + 1, m, n, dp);

        return dp[i][j];
    }

    int nCr(int n, int r)
    {
        if (r > n)
            return 0;
        if (r == 0 || n == r)
            return 1;

        double res = 0;
        for (int i = 0; i < r; i++)
        {
            res += log(n - i) - log(i + 1);
        }
        return (int)round(exp(res));
    }

    int uniquePaths(int m, int n)
    {
        return nCr(n + m - 2, n - 1);
    }
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

class Tree
{

    TreeNode *removeLeafNodes(TreeNode *root, int &target)
    {

        if (root == nullptr)
            return root;

        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);

        if (root->val == target && root->left == nullptr && root->right == nullptr)
            return nullptr;

        return root;
    }
};
int strStr(string haystack, string needle)
{

    int count = 0;
    for (int i = 0; i < haystack.size(); i++)
    {

        if (haystack[i] == needle[count])
        {
            if (count == needle.size() - 1)
            {
                cout << i;
                return i - count;
            }

            else
            {
                count++;
            }
        }
        else if (count > 0)
        {
            count = 0;
        }
    }
    return -1;
}

int main()
{

    Solution s;
    int n, m;
    string haystack = "mississippi";
    string neeedle = "issip";

    cout << strStr(haystack, neeedle);
    return 0;
}