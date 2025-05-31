#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

string smallestNumber(string pattern)
{
    stack<int> stack;
    string rs = "";

    for (int number = 0; number <= pattern.size(); number++)
    {

        stack.push(number + 1);

        if (number == pattern.size() || pattern[number] == 'I')
        {
            while (!stack.empty())
            {
                rs += to_string(stack.top());
                stack.pop();
            }
        }
    }
    return rs;
};

int main()
{
    string pattern = "IIIDIDDD";
    smallestNumber(pattern);
    return 0;
}
