#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool areSentencesSimilar(string s1, string s2)
{
    if (s1.size() > s2.size())
        return areSentencesSimilar(s1, s2);

    int n = s1.size();

    vector<char> suffix;

    vector<char> prefix;

    for (int i = 0; i < n; i++)
    {
        if (s1[i] == s2[i])
            prefix.push_back(s1[i]);
        else
            break;
    }

    for (int i = 0; i < n; i++)
    {
        if (s1[n - 1 - i] == s2[n - 1 - i])
            suffix.push_back(s1[n - 1 - i]);
    }

    s2.erase(suffix.size(), prefix.size());

    return s1.size() < s2.size();
}

int main()
{
    return 0;
}