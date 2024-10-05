#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

string solve()
{

    int A, B, C, M;
    cin >> A >> B >> C >> M;

    if (abs(A - B) <= M || abs(B - C) <= M || abs(A - C) <= M)
        return "YES";

    return "NO";
}

void runTest(int T)
{

    while (T--)
    {
        cout << solve() << endl;
    }
}

int main()
{

    int T;
    cin >> T;
    runTest(T);
    return 0;
}
