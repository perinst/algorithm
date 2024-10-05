#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// the solution is time limited
int n;
int m;

long long solve(vector<vector<int>> &points, int prevC, int r, vector<vector<long long>> &dp)
{

    if (r >= n)
        return 0;

    if (dp[r][prevC] != -1)
        return dp[r][prevC];

    long long maxScore = 0;

    for (int c = 0; c < m; c++)
    {
        long long nextPath = points[r][prevC] - abs(c - prevC) + solve(points, c, r + 1, dp);
        maxScore = max(maxScore, nextPath);
    }

    return dp[r][prevC] = maxScore;
}

long long maxPoints(vector<vector<int>> &points)
{

    long long s = 0;
    n = points.size();
    m = points[0].size();

    vector<vector<long long>> dp(n, vector<long long>(m, -1));

    long long maxScore = 0;

    for (int c = 0; c < m; ++c)
    {
        maxScore = std::max(maxScore, solve(points, c, 0, dp));
    }

    return maxScore;
}

long long iterative(vector<vector<int>> &points)
{
    int m = points.size(), n = points[0].size();

    vector<vector<long long>> dp(m, vector<long long>(n, 0));

    for (int j = 0; j < n; j++)
    {
        dp[0][j] = points[0][j];
    }

    for (int i = 1; i < m; i++)
    {
        vector<long long> leftSum(n, 0), rightSum(n, 0);
        leftSum[0] = dp[i - 1][0];
        rightSum[n - 1] = dp[i - 1][n - 1];

        for (int a = 1; a < n; a++)
        {
            leftSum[a] = max(leftSum[a - 1] - 1, dp[i - 1][a]);
            rightSum[n - a - 1] =
                max(rightSum[n - a] - 1, dp[i - 1][n - a - 1]);
        }

        for (int a = 0; a < n; a++)
        {
            if (a > 0 and a < n - 1)
            {
                dp[i][a] = points[i][a] +
                           max(leftSum[a],
                               max(leftSum[a - 1] - 1,
                                   max(rightSum[a], rightSum[a + 1] - 1)));
            }
            else if (a == 0)
            {
                dp[i][0] = points[i][0] + max(leftSum[0], rightSum[1] - 1);
            }
            else
            {
                dp[i][n - 1] = points[i][n - 1] +
                               max(rightSum[n - 1], leftSum[n - 2] - 1);
            }
        }
    }

    return *max_element(dp[m - 1].begin(), dp[m - 1].end());
}

long long maxPointsV1(vector<vector<int>> &points)
{
    if (points.size() == 1)
    {
        return *max_element(points[0].begin(), points[0].end());
    }
    else if (points[0].size() == 1)
    {
        long long sum = 0;
        for (int i = 0; i < points.size(); i++)
        {
            sum += points[i][0];
        }
        return sum;
    }
    return iterative(points);
}

long long maxPointsV2(vector<vector<int>> &points)
{
    const int m = points.size();
    const int n = points[0].size();
    vector<long long> dp(n, 0);
    long long ans = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[j] += points[i][j];
            ans = max(ans, dp[j]);
        }

        long long maxV = 0;

        for (int j = 0; j < n; j++)
        {
            maxV = dp[j] = max(maxV - 1, dp[j]);
        }

        maxV = 0;
        for (int j = n - 1; j >= 0; j--)
        {
            maxV = dp[j] = max(maxV - 1, dp[j]);
        }
    }

    return ans;
}

long long maxPointsV3(vector<vector<int>> &points)
{
    int rows = points.size(), cols = points[0].size();
    vector<long long> previousRow(cols);

    // Initialize the first row
    for (int col = 0; col < cols; ++col)
    {
        previousRow[col] = points[0][col];
    }

    // Process each row
    for (int row = 0; row < rows - 1; ++row)
    {
        vector<long long> leftMax(cols);
        vector<long long> rightMax(cols);
        vector<long long> currentRow(cols);

        // Calculate left-to-right maximum
        leftMax[0] = previousRow[0];
        for (int col = 1; col < cols; ++col)
        {
            leftMax[col] = max(leftMax[col - 1] - 1, previousRow[col]);
        }

        // Calculate right-to-left maximum
        rightMax[cols - 1] = previousRow[cols - 1];
        for (int col = cols - 2; col >= 0; --col)
        {
            rightMax[col] = max(rightMax[col + 1] - 1, previousRow[col]);
        }

        // Calculate the current row's maximum points
        for (int col = 0; col < cols; ++col)
        {
            currentRow[col] =
                points[row + 1][col] + max(leftMax[col], rightMax[col]);
        }

        // Update previousRow for the next iteration
        previousRow = currentRow;
    }

    // Find the maximum value in the last processed row
    long long maxPoints = 0;
    for (int col = 0; col < cols; ++col)
    {
        maxPoints = max(maxPoints, previousRow[col]);
    }

    return maxPoints;
}
int main()
{
    vector<vector<int>> points = {{1, 2, 3}, {1, 5, 1}, {3, 1, 1}};
    cout << maxPointsV3(points) << endl;
    return 0;
}
