#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <unordered_map>

using namespace std;

string reverseStr(string str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
    {
        std::swap(str[i], str[n - i - 1]);
    }
    return str;
}

int longestPalindrome(vector<string> &words)
{

    unordered_map<string, int> freq;

    for (auto &word : words)
    {
        freq[word]++;
    }

    int length = 0;
    bool hasCenter = false;

    for (auto &[word, count] : freq)
    {
        string rev = string{word[1], word[0]};
        if (word == rev)
        {
            length += (count / 2) * 4;
            if (count % 2 == 1)
                hasCenter = true;
        }
        else if (freq.count(rev))
        {
            int pairs = min(count, freq[rev]);
            length += (pairs * 4);
            freq[rev] = 0;
        }
    }
    if (hasCenter)
        length += 2;
    return length;
}

int main()
{
    // vector<string> words = {"dd", "aa", "bb", "dd", "aa", "dd", "bb", "dd", "aa", "cc", "bb", "cc", "dd", "cc"};
    vector<string> words = {"xx", "aa"};
    cout << longestPalindrome(words);
}