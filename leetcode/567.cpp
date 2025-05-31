#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;
bool checkInclusion(string s1, string s2)
{
    unordered_map<char, int> setS1;
    unordered_map<char, int> checked;
   

    for (char &c : s1)
    {
        setS1[c]++;
    }

    for (char &c : s2)
    {

        if (!setS1.count(c))
        {
            checked.clear();
            continue;
        }

        if (checked[c] < setS1[c])
        {
            checked[c]++;
        }
        else
        {
            checked.clear();
        }
    }

    if (checked.size() != setS1.size())
        return false;

    for (auto &[k, d] : checked)
    {
        if (setS1[k] != d)
            return false;
    }

    return true;
}

int main()
{

    string s1 = "abcdxabcde";
    string s2 = "abcdeabcdx";

    cout << checkInclusion(s1, s2);

    return 0;
}