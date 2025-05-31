#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string_view>
using namespace std;

bool starts_with(string &str, string &pref)
{
    for (int i = 0; i < pref.length(); i++)
    {
        if (pref[i] != str[i])
            return false;
    }
    return true;
}
int prefixCount(vector<string> &words, string pref)
{
    int count = 0;
    for (string &str : words)
    {
        if (starts_with(str, pref))
        {
            count++;
        }
    }
    return count;
}
int main()
{
    return 0;
}