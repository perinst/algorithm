#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

int strStr(string haystack, string needle)
{

    int count = 0;
    for (int i = 0; i < haystack.size(); i++)
    {

        if (haystack[i] == needle[count])
        {
            cout << i << "\t";

            cout << count << "\n";
            if (count == needle.size() - 1)
            {
                return i - count;
            }
            else
            {
                count++;
            }
        }
        else if (count > 0)
        {
            count = 0;
        }
    }
    return -1;
}

int main()
{
    string haystack = "mississippi";
    string neeedle = "issip";

    cout << strStr(haystack, neeedle);
    return 0;
}