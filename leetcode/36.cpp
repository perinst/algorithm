
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool isValidSudoku(vector<vector<char>> &board)
{
    const int N = 9;

    vector<vector<bool>> hashRow(N, vector<bool>(N));
    vector<vector<bool>> hashCol(N, vector<bool>(N));
    vector<vector<bool>> blocks(N, vector<bool>(N));

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            int num = board[i][j] - '1';

            int indexBlock = (i / 3) * 3 + (j / 3);

            // range 3X3
            if (hasRow[i][num] || hashCol[j][num] || blocks[indexBlock][num])
            {
                return false;
            }

            hasRow[i][num] = true;
            hashCol[j][num] = true;
            blocks[indexBlock][num] = true
        }
    }

    return true;
}

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
}

int main()
{
    fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}