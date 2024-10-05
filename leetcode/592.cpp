#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b)
{
    if (a == 0)
        return b;
    return gcd(a % b, a);
}

int lcm(int a, int b) { return (a / gcd(a, b)) * b; }

void getNumAndDe(string s, int &i, int &num, int &de)
{
}

string fractionAddition(string e)
{
    char currSign;
    int numerator;
    int denominator;
    int i = 0;

    if (e[0] == '-')
    {
        currSign = '-';
        i++;

        while (e[i] != '/')
        {
            numerator = numerator * 10 + e[i];
            i++;
        }

        i++;

        denominator = e[i++] - '0';
    }
    else
    {
        currSign = '+';
        numerator = e[0] - '0';
        denominator = e[2] - '0';
        i = 3;
    }

    while (i < e.size())
    {
        char sign = e[i];
        int num = e[i + 1] - '0';
        int de = e[i + 3] - '0';

        cout << currSign << numerator << " /" << denominator << endl;
        cout << sign << num << " /" << de << endl;

        if (numerator == 0)
        {
            numerator = num;
            denominator = de;
            i += 4;
            continue;
        }

        if (num == 0)
        {
            i += 4;
            continue;
        }

        if (de != denominator)
        {
            if (sign == currSign)
            {
                numerator = numerator * de + num * denominator;
            }
            else
            {
                numerator = abs(numerator * de - num * denominator);
                currSign = numerator * de < num * denominator ? currSign : sign;
            }

            denominator = denominator * de;
        }
        else
        {
            if (sign == currSign)
            {
                numerator += num;
            }
            else
            {
                numerator = abs(numerator * de - num * denominator);
                currSign = numerator > num ? currSign : sign;
            }
        }

        cout << currSign << " " << numerator << " / " << denominator << endl;

        int GCD = gcd(numerator, denominator);
        cout << "gcd: " << gcd << endl;

        numerator /= GCD;
        denominator /= GCD;

        i += 4;
        cout << "-------------------------------------" << endl;
    }
    string ans = "";

    if (currSign == '-')
        ans.append(1, currSign);

    ans.append(std::to_string(numerator));
    ans.append("/");
    ans.append(std::to_string(denominator));

    return ans;
}

int main()
{
    string e = "-5/2+10/3+7/9";
    cout << fractionAddition(e) << endl;
    return 0;
}