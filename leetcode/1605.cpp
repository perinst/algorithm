#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum)
{
    int n = rowSum.size();
    int m = colSum.size();

    vector<vector<int>> origin(n, vector<int>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            origin[i][j] = min(rowSum[i], colSum[j]);
            rowSum[i] -= origin[i][j];
            colSum[j] -= origin[i][j];
        }
    }
    return origin;
}

int main()
{

    return 0;
}