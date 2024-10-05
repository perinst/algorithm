#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
// Overload the << operator for vector<int>
std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
int binarySearch(vector<pair<int, int>> &jobs, int target)
{
    int left = 0;
    int right = jobs.size() - 1;

    while (left <= right)
    {
        int mid = (right + left) / 2;

        if (jobs[mid].first == target)
            return mid;

        if (target > jobs[mid].first)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return right >= 0 ? jobs[right].second : 0;
}

int maxProfitAssignment(vector<int> &difficulty, vector<int> &profit, vector<int> &worker)
{

    int n = difficulty.size();
    // map for difficult -> profit

    vector<pair<int, int>> jobs(n);
    int p = 0;

    for (int i = 0; i < n; i++)
    {
        jobs[i] = {difficulty[i], profit[i]};
    }
    //
    sort(jobs.begin(), jobs.end());

    int maxProfit = INT_MIN;

    //
    for (int i = 0; i < n; i++)
    {
        maxProfit = max(maxProfit, jobs[i].second);
        jobs[i].second = maxProfit;
    }
    ///
    cout << difficulty << endl;

    for (int &w : worker)
    {
        p += binarySearch(jobs, w);
    }
    return p;
}

int maxProfitAssignmentN(vector<int> &difficulty, vector<int> &profit, vector<int> &worker)
{

    int ma = *max_element(difficulty.begin(), difficulty.end());

    vector<int> arr(ma + 1);

    for (int i = 0; i < difficulty.size(); i++)
    {
        arr[difficulty[i]] = max(arr[difficulty[i]], profit[i]);
    }

    cout << arr << endl;

    for (int i = 1; i < ma + 1; i++)
    {
        arr[i] = max(arr[i - 1], arr[i]);
    }

    cout << arr << endl;

    int res = 0;

    for (int i = 0; i < worker.size(); i++)
    {
        res += arr[min(worker[i], ma)];
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<int> d = {4, 6, 8, 10, 2};
    vector<int> p = {10, 80, 30, 40, 50};
    vector<int> workers = {4, 5, 6, 7};

    cout << maxProfitAssignmentN(d, p, workers) << endl;

    return 0;
}