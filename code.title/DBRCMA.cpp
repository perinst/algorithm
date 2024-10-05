#include <iostream>
#include <vector>

using namespace std;

// constraint : 0 < N <= 2000,  0 < v[i] < 1000

int solve(vector<int> &v)
{
    int left = 0;
    int right = v.size() - 1;
    int sold = 0;
    int i = 1;

    while (left <= right)
    {

        if (v[left] < v[right])
        {
            sold += i * v[left];
            left++;
        }
        else
        {
            sold += i * v[right];
            right--;
        }

        i++;
    }

    return sold;
}

int main()
{
    int N;
    cin >> N;
    vector<int> v(N);

    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }

    cout << solve(v) << endl;

    return 0;
}