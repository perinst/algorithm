#include <iostream>
#include <vector>
#include <unordered_map>

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

// Overload the << operator for vector<vector<int>>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<int>> &vec)
{
    os << "[\n";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << "  " << vec[i];
        if (i != vec.size() - 1)
        {
            os << ",\n";
        }
    }
    os << "\n]";
    return os;
}

using namespace std;
int T;
vector<vector<int>> ans;

void backtracking(vector<int> &candidates, vector<int> &subset, int sum, int idx)
{
    cout << subset << "\t" << sum << endl;

    if (sum == T)
    {
        cout << subset << endl;
        ans.push_back(subset);
        return;
    }

    for (int i = idx; i < candidates.size(); i++)
    {
        if (sum + candidates[i] > T)
            continue;

        subset.push_back(candidates[i]);

        backtracking(candidates, subset, sum + candidates[i], i);

        subset.pop_back();
    }
}

vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    T = target;
    ans.clear();
    vector<int> subset;

    backtracking(candidates, subset, 0, 0);

    return ans;
}

vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
{
    vector<vector<int>> rs(0);
    return rs;
}

int main()
{

    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    cout << combinationSum(candidates, target) << endl;

    return 0;
}