#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

//  take 1 or L , K coin per time
// 1 < K < L < 10 => max take 9 coin per time
//  3 < N < 1000
//  1 <= N[i] <= 10^6

// print string include N characters A and B  when  A win although B process run then i'th character must A otherwise it  is B.

int K, L, N;
vector<int> coins;
unordered_map<int, bool> memoA;
unordered_map<int, bool> memoB;

bool isLastA(int remain);
bool isLastB(int remain);

bool isLastA(int remain)
{

    if (remain == 0)
        return false;

    if (memoA.find(remain) != memoA.end())
        return memoA[remain];

    bool result = (!isLastB(remain - 1) ||
                   (remain >= K ? !isLastB(remain - K) : true) ||
                   (remain >= L ? !isLastB(remain - L) : true));

    return memoA[remain] = result;
}

bool isLastB(int remain)
{
    if (remain == 0)
        return false;

    if (memoB.find(remain) != memoB.end())
        return memoB[remain];

    bool result = (isLastA(remain - 1) ||
                   (remain >= K ? isLastA(remain - K) : false) ||
                   (remain >= L ? isLastA(remain - L) : false));

    return memoA[remain] = result;
}

string solve(int coin)
{
    return isLastA(coin) ? "A" : "B";
}

int main()
{

    cin >> K >> L >> N;
    coins.resize(N);

    for (int i = 0; i < N; i++)
    {
        cin >> coins[i];
    }

    for (int i = 0; i < N; i++)
    {
        cout << solve(coins[i]) << "\t";
    }

    return 0;
}