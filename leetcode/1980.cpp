#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_set>

using namespace std;

string findDifferentBinaryString(vector<string> &nums)
{
    int n = nums[0].size();
    stack<string> stack;
    string init = "";
    stack.push(init);
    std::unordered_set<string> set;

    for (string num : nums)
    {
        set.insert(num);
    }

    while (!stack.empty())
    {
        string current = stack.top();
        stack.pop();

        if (current.size() == n && set.find(current) == set.end())
            return current;

        if (current.size() == n)
        {
            continue;
        }

        stack.push(current + "0");
        stack.push(current + "1");
    }
    return "";
}

int main()
{
    vector<string> nums = {"01", "10"};
    cout << findDifferentBinaryString(nums);

    return 0;
}