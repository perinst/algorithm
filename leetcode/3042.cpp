#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool isPrefixAndSuffix(string word1, string word2)
{
    int n = word1.size();

    for (int i = 0; i < n; i++)
    {
        if (word1[i] != word2[i] || word1[word1.length() - i - 1] != word2[word2.length() - i - 1])
        {
            return false;
        }
    }
    return true;
}

int countPrefixSuffixPairs(vector<string> &words)
{
    std::sort(words.begin(), words.end(), [](const string &a, const string &b)
              { return a.size() < b.size(); });

    int count = 0;

    for (int i = 0; i < words.size(); i++)
    {
        for (int j = i + 1; j < words.size(); j++)
        {
            if (isPrefixAndSuffix(words[i], words[j]))
                count++;
        }
    }
    return count;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);

    return 0;
}