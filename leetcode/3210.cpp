#include <iostream>
#include <vector>

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

int maximumLength(vector<int> &nums)
{

    int firstIndexOlder = 0;
    int firstIndexEven = 0;

    while (firstIndexEven + 1 < nums.size() && ((nums[firstIndexEven] + nums[firstIndexEven + 1]) % 2 != 0))
    {
        firstIndexEven++;
    }

    while (firstIndexOlder + 1 < nums.size() && ((nums[firstIndexOlder] + nums[firstIndexOlder + 1]) % 2 == 0))
    {
        firstIndexOlder++;
    }

    int longestSubValidEven = 0;

    int indexEven = firstIndexEven;

    while (indexEven < nums.size())
    {

        int j = indexEven + 1;

        while (j < nums.size() && (nums[indexEven] + nums[j]) % 2 != 0)
        {
            j++;
        }

        longestSubValidEven++;

        indexEven = j + 1;
    }

    int longestSubValidOld = 0;
    int indexOld = 0;

    while (indexOld < nums.size())
    {

        int j = indexOld + 1;

        while (j < nums.size() && (nums[indexOld] + nums[j]) % 2 == 0)
        {
            j++;
        }

        longestSubValidOld++;

        indexOld = j + 1;
    }

    return max(longestSubValidEven, longestSubValidOld);
}

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }
}

int main()
{
    fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        cout << solve() << endl;
    }

    return 0;
}