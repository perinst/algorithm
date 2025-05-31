#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
using namespace std;

// bool backtracking(int num, int curr)
// {

// }

bool isValidPartition(int num, int target)
{
    string s = to_string(num);
    std::queue<pair<int, int>> q;

    q.push({0, 0});

    while (!q.empty())
    {
        auto [sum, pos] = q.front();
        q.pop();

        if (pos == s.length() && sum == target)
        {
            return true;
        }

        for (int len = 1; pos + len <= s.length(); len++)
        {
            string part = s.substr(pos, len);
            if (part.length() > 9)
                break;
            long long val = stoll(part);
            if (val > INT_MAX)
                break;
            if (sum + val <= sum)
            {
                q.push({sum + (int)val, pos + len});
            }
        }
    }

    return false;
}

class Solution
{
public:
    bool backtrack(const string &s, int start, long long currSum, int target)
    {
        // Base case: if we've used all digits and sum equals target
        if (start == s.length())
        {
            return currSum == target;
        }

        // Try all possible partitions from current position
        for (int len = 1; start + len <= s.length(); len++)
        {
            string part = s.substr(start, len);

            // Skip if number is too large
            if (part.length() > 9)
                break;

            // Convert partition to number
            long long val = stoll(part);
            if (val > INT_MAX)
                break;

            // Skip if sum would exceed target
            if (currSum + val > target)
                break;

            // Recursively try this partition
            if (backtrack(s, start + len, currSum + val, target))
            {
                return true;
            }
        }

        return false;
    }

    bool isValidPartition(int num, int target)
    {
        return backtrack(to_string(num), 0, 0, target);
    }

    int punishmentNumber(int n)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            int square = i * i;
            if (isValidPartition(square, i))
            {
                sum += square;
            }
        }
        return sum;
    }
};
int punishmentNumber(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int square = i * i;
        if (isValidPartition(square, i))
        {
            sum += square;
        }
    }
    return sum;
}

int main()
{
    return 0;
}