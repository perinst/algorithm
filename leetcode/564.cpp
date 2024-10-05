#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Solution
{
public:
    // Convert to palindrome keeping first half constant.
    long long convert(long long &num)
    {
        string s = to_string(num);
        int n = s.length();
        int l = (n - 1) / 2, r = n / 2;
        while (l >= 0)
            s[r++] = s[l--];
        return stoll(s);
    }
    // Find the previous palindrome, just smaller than n.
    long long previousPalindrome(long long num)
    {
        long long left = 0, right = num;
        long long ans = INT_MIN;
        while (left <= right)
        {
            long long mid = (right - left) / 2 + left;
            long long palin = convert(mid);
            if (palin < num)
            {
                ans = palin;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return ans;
    }
    // Find the next palindrome, just greater than n.
    long long nextPalindrome(long long num)
    {
        long long left = num, right = 1e18;
        long long ans = INT_MIN;
        while (left <= right)
        {
            long long mid = (right - left) / 2 + left;
            long long palin = convert(mid);
            if (palin > num)
            {
                ans = palin;
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        return ans;
    }
    string nearestPalindromic(string n)
    {

        long long num = stoll(n);
        long long a = previousPalindrome(num);
        long long b = nextPalindrome(num);

        cout << a << " " << b << endl;

        if (abs(a - num) <= abs(b - num))
            return to_string(a);
        return to_string(b);
    }
};

// Convert to palindrome keeping first half constant.
long long convert(long long &num)
{
    string s = to_string(num);
    int n = s.size();

    int l = (n - 1) / 2;
    int r = n / 2;

    while (l >= 0)
    {
        s[r++] = s[l--];
    }

    return stoll(s);
}

// binary for
long long smallerPalindrome(long long num)
{
    long long left = 0;
    long long right = num;

    long long ans = INT_MIN;

    while (left <= right)
    {

        long long mid = (right + left) / 2;
        long long p = convert(mid);

        if (p < num)
        {
            ans = p;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return ans;
}
long long largerPalindrome(long long num)
{
    long long left = num, right = 1e18;

    long long ans = -1;

    while (left <= right)
    {
        long long mid = (right + left) / 2;
        long long p = convert(mid);

        if (p > num)
        {
            ans = p;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return ans;
}
string nearestPalindromic(string n)
{
    if (n.size() == 1)
        return to_string(n[0] - '0' - 1);

    long long num = stoll(n);

    long long smaller = smallerPalindrome(num);
    long long larger = largerPalindrome(num);

    cout << smaller << "  " << larger << endl;

    if (abs(smaller - num) <= abs(larger - num))
        return to_string(smaller);

    return to_string(larger);
}

int main()
{
    Solution s;

    string n = "202";

    cout << nearestPalindromic(n);

    return 0;
}