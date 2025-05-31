#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;

int nextNumber(int n)
{

    int nextNumber = 0;

    while (n)
    {
        nextNumber += pow(n % 10, 2);
        n /= 10;
    }

    return nextNumber;
}

bool isHappy(int n)
{

    int slow = n;
    int fast = nextNumber(n);

    while (fast != 1 && slow != fast)
    {

        slow = nextNumber(slow);
        fast = nextNumber(nextNumber(fast));
    }

    return fast == 1;
}

int main()
{
    cout << isHappy(19);
    return 0;
}