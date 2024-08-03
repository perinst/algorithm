#include <vector>
#include <climits>

using namespace std;

bool isPerfectSquare(string number, long num)
{

    for (int num = 2; num * num <= c; num++)
    {

        int remain = c - num * num;

        int left = 0, right = remain;
        while (left < right)
        {
            int mid = (right + left) / 2;
            int sq = mid * mid;
            if (sq == remain)
                return true;

            if (sq < remain)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }
    return false;
}

int main()
{

    return 0;
}