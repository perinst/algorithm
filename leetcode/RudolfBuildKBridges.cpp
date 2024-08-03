#include <iostream>
#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class RudolfBuildKBridges
{
public:
    int t;
    int n;
    int m;
    int k;
    int d;

    vector<vector<int>> grid;
    vector<int> minCostRow;

    void cinInput()
    {
        cin >> n >> m >> k >> d;

        grid.resize(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> grid[i][j];
            }
        }
    }

    int minCost(vector<vector<int>> &grid, int i, int start, vector<int> &dp)
    {

        if (start == m - 1)
            return 1;

        if (start >= m)
            return 0;

        if (dp[start] != -1)
            return dp[start];

        int minCostRS = INT_MAX;

        for (int j = start + 1; j < m && (j - start) - 1 <= d; j++)
        {
            minCostRS = min(minCostRS, grid[i][start] + 1 + minCost(grid, i, j, dp));
        }

        return dp[start] = minCostRS;
    }

    int solve()
    {
        minCostRow.resize(n, 0);

        for (int i = 0; i < n; i++)
        {
            vector<int> dp(m, -1);
            minCostRow[i] = minCost(grid, i, 0, dp);
        }
        for (int cost : minCostRow)
        {
            cout << cost << "\t";
        }

        int slide = 0;
        int minC = 0;

        if (k > minCostRow.size())
            return 0;

        for (slide = 0; slide < k; slide++)
        {
            minC += minCostRow[slide];
        }

        cout << endl;

        while (slide < minCostRow.size())
        {
            cout << "l:" << slide << "\t";

            int newSlideCost = (minC - minCostRow[slide - k]) + minCostRow[slide];

            if (newSlideCost < minC)
            {
                minC = newSlideCost;
            }

            slide++;
        }
        cout << endl;
        cout << minC;

        return minC;
    }
};

int main()
{
    RudolfBuildKBridges s;
    s.cinInput();
    s.solve();

    return 0;
}
