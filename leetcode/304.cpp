#include <iostream>
#include <vector>
using namespace std;

class NumMatrix
{
public:
    vector<vector<int>> prefixMatrix;

    NumMatrix(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();

        prefixMatrix.resize(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
        {
            prefixMatrix[i][0] = matrix[i][0];

            for (int j = 1; j < m; j++)
            {
                prefixMatrix[i][j] = matrix[i][j] + prefixMatrix[i][j - 1];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {

        int s = 0;

        if (col1 < col2)
        {
            while (row1 <= row2)
            {
                s += prefixMatrix[row1][col2] - (col1 == 0 ? 0 : prefixMatrix[row1][col1 - 1]);
                row1++;
            }
        }
        else
        {
            while (row1 < row2)
            {
                s += prefixMatrix[row1][col1] - (col2 == 0 ? 0 : prefixMatrix[row1][col2 - 1]);
                row1++;
            }
        }
        return s;
    }
};

int main()
{

    return 0;
}