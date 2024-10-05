
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stack>
using namespace std;

void handleDozen(stack<string> &stack, std::unordered_map<int, string> &dic, int &num, int &d)
{

    int digitUnit = num % 10;
    int digitDozen = (num / 10) % 10;

    if (digitDozen == 0)
    {
        stack.push(dic[digitUnit]);
    }
    else if (digitDozen == 1)
    {
        int digit = 10 + digitUnit;
        stack.push(dic[digit]);
    }
    else
    {
        if (digitUnit != 0)
        {
            stack.push(dic[digitUnit]);
        }

        stack.push(dic[digitDozen * 10]);
    }

    d += 2;

    num /= 100;
}
string numberToWords(int num)
{

    std::string rs;
    std::unordered_map<int, string> unit;
    std::unordered_map<int, string> dic;
    std::stack<string> stack;

    unit[2] = "Hundred";
    unit[3] = "Thousand";
    unit[6] = "Million";
    unit[9] = "Billion";

    dic[1] = "One";
    dic[2] = "Two";
    dic[3] = "Three";
    dic[4] = "Four";
    dic[5] = "Five";
    dic[6] = "Six";
    dic[7] = "Seven";
    dic[8] = "Eight";
    dic[9] = "Nine";
    dic[10] = "Ten";
    dic[11] = "Eleven";
    dic[12] = "Twelve";
    dic[13] = "Thirteen";
    dic[14] = "Fourteen";
    dic[15] = "Fifteen";
    dic[16] = "Sixteen";
    dic[17] = "Seventeen";
    dic[18] = "Eighteen";
    dic[19] = "Nineteen";
    dic[20] = "Twenty";
    dic[30] = "Thirty";
    dic[40] = "Forty";
    dic[50] = "Fifty";
    dic[60] = "Sixty";
    dic[70] = "Seventy";
    dic[80] = "Eighty";
    dic[90] = "Ninety";

    int d = 0;

    while (num > 0)
    {

        int digitUnit = num % 10;
        int digitDozen = (num / 10) % 10;
        int digitHundred = (num / 100) % 10;

        if (digitUnit > 0 || digitDozen > 0 || digitHundred > 0)
        {
            if (d > 0 && d % 3 == 0)
            {
                stack.push(unit[d]);
            }

            if (digitDozen == 1)
            {
                int teen = digitDozen * 10 + digitUnit;
                stack.push(dic[teen]);
            }
            else
            {
                if (digitUnit > 0)
                {
                    stack.push(dic[digitUnit]);
                }
                if (digitDozen > 1)
                {
                    stack.push(dic[digitDozen * 10]);
                }
            }

            if (digitHundred > 0)
            {
                stack.push(unit[2]);
                stack.push(dic[digitHundred]);
            }
        }

        num /= 1000;
        d += 3;
    }

    while (!stack.empty())
    {
        rs.append(stack.top());
        stack.pop();
        if (!stack.empty())
        {
            rs.append(" ");
        }
    }

    return rs;
}

int main()
{
    int num = 103001;

    cout << numberToWords(num);

    return 0;
}