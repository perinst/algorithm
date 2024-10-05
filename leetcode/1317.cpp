#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int findTheLongestSubstring(string s)
{

    std::unordered_set<char> set = {'a', 'e', 'i', 'o', 'u'};
    vector<int> vowels(5, 0);
    int len = s.size();
    // count amount vowel in string
    for (char &c : s)
    {
        if (c == 'a')
            vowels[0]++;

        if (c == 'e')
            vowels[1]++;

        if (c == 'i')
            vowels[2]++;

        if (c == 'o')
            vowels[3]++;

        if (c == 'u')
            vowels[4]++;
    }
    //

    //
}

int main()
{

    return 0;
}