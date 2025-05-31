#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
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

int minGroups(vector<vector<int>> &intervals)
{
    int n = intervals.size();
    std::sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int> &b)
              { return a[1] - a[0] < b[1] - b[0]; });

    std::cout << intervals << std::endl;

    return 1;
}

int main()
{
    std::vector<std::vector<int>> intervals = {{5, 10}, {6, 8}, {1, 10}, {1, 5}, {2, 3}};

    minGroups(intervals);

    return 0;
}