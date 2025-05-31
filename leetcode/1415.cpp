#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
int targetIdx;

void generateHappyString(int &n, int &indexSorted, string &current, string &result)
{
    if (current.size() == n)
    {
        indexSorted++;

        if (indexSorted == targetIdx)
        {
            result = current;
        }

        return;
    }

    for (char currentChar = 'a'; currentChar <= 'c'; currentChar++)
    {
        if (current.size() > 0 && current.back() == currentChar)
        {
            continue;
        }
        current.push_back(currentChar);
        generateHappyString(n, indexSorted, current, result);
        if (result != "")
            return;

        current.pop_back();
    }
}

string getHappyString(int n, int k)
{
    int indexSorted = 0;

    stack<string> stack;

    stack.push("");

    while (!stack.empty())
    {

        string current = stack.top();
        stack.pop();

        if (current.size() == n)
        {

            indexSorted++;

            if (indexSorted == k)
            {
                return current;
            }

            continue;
        }

        for (char currentChar = 'c'; currentChar >= 'a'; currentChar--)
        {
            if (current.size() > 0 && current.back() == currentChar)
            {
                continue;
            }

            current.push_back(currentChar);
            stack.push(current);
        }
    }

    return "";
}

int main()
{
    int n = 3;
    int k = 9;
    getHappyString(n, k);
    return 0;
}