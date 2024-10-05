#include <iostream>
#include <vector>

using namespace std;

int maxScoreSightseeingPair(vector<int> &v)
{
    int n = v.size();
    int maxVi = 0;
    int maxVj = 0;
    for (int i = 0; i < n; i++)
    {
        maxVi = max(maxVi, v[i] + i);
        maxVj = max(maxVj, v[i] - i);
    }
    return maxVi + maxVj;
}

int main()
{
    return 0;
}