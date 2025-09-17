#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_map>
#include <string>

using namespace std;

// Example 1:

// Input: s = "(()"
// Output: 2
// Explanation: The longest valid parentheses substring is "()".
// Example 2:

// Input: s = ")()())"
// Output: 4
// Explanation: The longest valid parentheses substring is "()()".

bool isValidParentheses(int left, int right, string &s)
{

    stack<char> st;

    for (int i = left; i <= right; i++)
    {
        char c = s[i];

        if (c == '(')
        {
            st.push(c);
            continue;
        }

        if (st.empty())
            return false;

        st.pop();
    }

    return st.empty();
}

int longestValidParentheses(string s)
{
    // int longestP = 0;
    // int n = s.size();

    // Older Solution: O(n^3) vs space: n^2 or 1 => TLE vs MLE
    // vector<vector<int>> dp(n + 1, vector<int>(n + 1));

    // for (int left = 0; left < n; left++)
    // {
    //     for (int right = left + 1; right < n; right++)
    //     {

    //         if (s[left] != '(' || s[right] != ')')
    //             continue;

    //         if (dp[left][right])
    //             continue;

    //         if (!isValidParentheses(left, right, s))
    //             continue;

    //         longestP = std::max(longestP, right - left + 1);

    //         dp[left][right] = longestP;
    //     }
    // }

    // Optimize using only tow pointer left and right  and keep moving from left to right then using stack to keep untrack "("
    // when find ')' , we pop from the stack and compute the length valid substing end here.

    // int longestP = 0;
    // int n = s.size();
    // stack<int> st;

    // st.push(-1);

    // for (int right = 0; right < n; right++)
    // {
    //     if (s[right] == '(')
    //     {
    //         st.push(right);
    //         continue;
    //     }

    //     st.pop();

    //     if (st.empty())
    //     {
    //         st.push(right);
    //     }
    //     else
    //     {
    //         longestP = max(longestP, right - st.top());
    //     }
    // }

    int longestP = 0;
    int n = s.size();
    vector<int> dp(n, 0);

    // dp[i] is length of longest valid paretheres end at index i.

    for (int i = 1; i < n; i++)
    {
        if (s[i] == '(')
            continue;

        if (s[i - 1] == '(')
        {
            dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
        }
        else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(')
        {
            dp[i] = dp[i - 1] + 2;
            if (i - dp[i - 1] - 2 >= 0)
            {
                dp[i] += dp[i - dp[i - 1] - 2];
            }
        }

        longestP = max(longestP, dp[i]);
    }

    return longestP;
}

int main()
{
    string s = "((()))";

    longestValidParentheses(s);

    return 0;
}
