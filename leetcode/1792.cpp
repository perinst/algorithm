#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

using namespace std;

double maxAverageRatio(vector<vector<int>> &classes, int extraStudents)
{

    auto calculate = [](int pass, int total)
    {
        return (double)(pass + 1) / (total + 1) - (double)pass / total;
    };

    priority_queue<pair<double, pair<int, int>>>
        maxHeap;

    double sumRatio = 0.0;

    for (vector<int> &classData : classes)
    {
        maxHeap.push({calculate(classData[0], classData[1], {classData[0], classData[1]})});
    }

    while (extraStudents--)
    {
        auto [gain, class] = maxHeap.top();
        maxHeap.pop();

        int pass = class[0];
        int total = class[1];

        maxHeap.push({calculate(pass + 1, total + 1), {pass + 1, total + 1}});
    }

    double ratio = 0.0;

    while (!maxHeap.empty())
    {
        auto [_, class] = maxHeap.top();

        maxHeap.pop();
        ratio += (double)class[0] / class[1];
    }
    return ratio / classes.size();
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
        solve();
    }

    return 0;
}
