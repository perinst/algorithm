#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;

class LC_1190
{
public:
    char open = '(';
    char close = ')';

    string reverseParentheses(string s)
    {

        std::stack<char> stack;
        std::string current;

        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != close)
            {
                stack.push(s[i]);
                continue;
            }

            while (!stack.empty())
            {
                char top = stack.top();
                stack.pop();
                if (top == open)
                {

                    for (char c : current)
                    {
                        stack.push(c);
                    }
                    current.clear();

                    break;
                }
                else
                {
                    current += top;
                }
            }
        }

        while (!stack.empty())
        {
            current = stack.top() + current;
            stack.pop();
        }

        return current;
    }

    std::string reverseParenthesesOn(std::string s)
    {
        std::stack<int> stack;
        std::vector<int> pair(s.size());

        // First pass: determine the positions of the pairs of parentheses
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(')
            {
                stack.push(i);
            }
            else if (s[i] == ')')
            {
                int j = stack.top();
                stack.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        // Second pass: construct the result string by iterating and reversing where necessary
        std::string result;
        for (int i = 0, d = 1; i < s.size(); i += d)
        {
            if (s[i] == '(' || s[i] == ')')
            {
                i = pair[i];
                d = -d;
            }
            else
            {
                result += s[i];
            }
        }

        return result;
    }

    void printStack(std::stack<std::string> s)
    {
        // Print elements in the stack from top to bottom
        while (!s.empty())
        {
            std::cout << s.top() << " ";
            s.pop();
        }
        std::cout << std::endl;
    }
    std::string generateLargeTestCase(int n)
    {
        std::string s;
        for (int i = 0; i < n; ++i)
        {
            s += '(';
        }
        for (int i = 0; i < n; ++i)
        {
            s += 'a';
        }
        for (int i = 0; i < n; ++i)
        {
            s += ')';
        }
        return s;
    }
    void runTest()
    {
        std::string testCase = generateLargeTestCase(1000);

        LC_1190 lc;

        auto start1 = std::chrono::high_resolution_clock::now();
        std::string result1 = lc.reverseParentheses(testCase);
        auto end1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration1 = end1 - start1;
        std::cout << "Solution 1 took " << duration1.count() << " seconds." << std::endl;

        auto start2 = std::chrono::high_resolution_clock::now();
        std::string result2 = lc.reverseParenthesesOn(testCase);
        auto end2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration2 = end2 - start2;
        std::cout << "Solution 2 took " << duration2.count() << " seconds." << std::endl;
    }
};

int main()
{

    LC_1190 lc;
    std::string s = "(u(love)i)";

    lc.runTest();

    return 0;
}