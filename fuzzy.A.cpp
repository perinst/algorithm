#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <unordered_map>
#include <sstream>

using namespace std;
class LevenshteinDistance
{
public:
    int minDistance(int x, int y, int z) { return min(min(x, y), z); }

    int editDistance(int m, int n, string &w1, string &w2, vector<vector<int>> &dp)
    {

        if (m == 0)
            return n;
        if (n == 0)
            return m;

        if (dp[m][n] != -1)
            return dp[m][n];

        if (w1[m - 1] == w2[n - 1])
        {
            dp[m][n] = editDistance(m - 1, n - 1, w1, w2, dp);
        }
        else
        {
            dp[m][n] = 1 + minDistance(
                               editDistance(m, n - 1, w1, w2, dp),    // Insert
                               editDistance(m - 1, n, w1, w2, dp),    // Remove
                               editDistance(m - 1, n - 1, w1, w2, dp) // Replace
                           );
        }

        return dp[m][n];
    }

    int levenshteinDistanceRecur(string word1, string word2)
    {

        int m = word1.size();
        int n = word2.size();

        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));

        return editDistance(m, n, word1, word2, dp);
    }
};

int main()
{

    LevenshteinDistance s;

    string word1 = "GEEXSFRGEEKKS";
    string word2 = "GEEKSFORGEEKS";

    cout << s.levenshteinDistanceRecur(word1, word2);

    return 0;
}