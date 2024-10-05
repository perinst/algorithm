#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool comparable(int n1, int n2)
{
    string s1 = to_string(n1);
    string s2 = to_string(n2);

    int l1 = s1.length();
    int l2 = s2.length();

    if (l1 < l2)
        return comparable(l2, l1);

    for (int i = 0; i < l1; i++)
    {
        if (s1[i] > s2[i])
            return false;
    }
    return true;
}

string largestNumber(vector<int> &nums)
{

    std::sort(nums.begin(), nums.end());
}

int main()
{

    return 0;
}