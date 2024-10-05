#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
// Overload the << operator for vector<int>
std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

// Overload the << operator for vector<vector<int>>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<int>> &vec)
{
    os << "[\n";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << "  " << vec[i];
        if (i != vec.size() - 1)
        {
            os << ",\n";
        }
    }
    os << "\n]";
    return os;
}

using namespace std;

int rowSize;
int colSize;

bool boundOfRange(int &ur, int &lc, int &br, int &rc)
{
    if (ur > br || lc > rc)
        return true;

    if (br < 0 || rc < 0 || ur >= rowSize || lc >= colSize)
        return true;

    return false;
}

int maxSumRectangle(vector<vector<int>> &m, int &k, int ur, int lc, int br, int rc)
{
    if (boundOfRange(ur, lc, br, rc))
        return 0;

    int sum = m[br][rc] - (ur != 0 ? m[ur - 1][rc] : 0) - (lc != 0 ? m[br][lc - 1] : 0) + (ur != 0 && lc != 0 ? m[ur - 1][lc - 1] : 0);

    if (sum <= k)
        return sum;

    int ur_1 = maxSumRectangle(m, k, ur + 1, lc, br, rc);
    int lc_1 = maxSumRectangle(m, k, ur, lc + 1, br, rc);
    int br_1 = maxSumRectangle(m, k, ur, lc, br - 1, rc);
    int rc_1 = maxSumRectangle(m, k, ur, lc, br, rc - 1);

    return max(ur_1, max(lc_1, max(br_1, rc_1)));
}

int maxSumSubMatrix(vector<vector<int>> &matrix, int k)
{

    rowSize = matrix.size();
    colSize = matrix[0].size();

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 1; j < colSize; j++)
        {
            matrix[i][j] += matrix[i][j - 1];
        }
    }

    for (int i = 0; i < colSize; i++)
    {
        for (int j = 1; j < rowSize; j++)
        {
            matrix[j][i] += matrix[j - 1][i];
        }
    }

    cout << matrix << endl;

    if (matrix[rowSize - 1][colSize - 1] <= k)
        return matrix[rowSize - 1][colSize - 1];

    return maxSumRectangle(matrix, k, 0, 0, rowSize - 1, colSize - 1);
}

int solve(vector<vector<int>> &matrix, int k)
{

    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    int maxSum = INT_MIN;

    for (int left = 0; left < colSize; left++)
    {
        vector<int> rowSum(rowSize, 0);
        for (int right = 0; right < colSize; right++)
        {
            for (int i = 0; i < rowSize; i++)
            {
                rowSum[i] += matrix[i][right];
                        }
        }
    }
}

int main()
{
    vector<vector<int>> m = {{1, 0, 1}, {0, -2, 3}};
    int k = 2;
    cout << maxSumSubMatrix(m, k);
    return 0;
}