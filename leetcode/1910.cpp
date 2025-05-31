#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<int> buildPrefixTable(const string &pattern)
{
    int pSize = pattern.size();
    vector<int> prefixTable(m, 0);
    int j = 0;

    for (int i = 1; i < m; i++)
    {
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = prefixTable[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        prefixTable[i] = j;
    }

    return prefixTable;
}

int findPattern(const string &s, const string &pattern)
{
    int sSize = s.size();
    int pSize = pattern.size();

    for (int i = 0; i <= sSize - pSize; i++)
    {
        int j;
        for (j = 0; j < pSize; j++)
        {
            if (s[i + j] != pattern[j])
                break;
        }
        if (j == pSize)
            return i;
    }

    return -1;
}

int match(string s, string pattern)
{
    size_t pos = s.find(pattern);
    if (pos == string::npos)
        return -1;
    return pos;
}

string removeOccurrences(string s, string part)
{
    int index = 0;
    while (true)
    {
        index = match(s, part);
        if (index == -1)
            break;
        s.erase(index, part.size());
    }

    return s;
}

int main()
{
}