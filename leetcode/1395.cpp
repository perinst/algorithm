#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cnt = 0;

void backtrackMore(vector<int> &rating, vector<int> &subset, int start)
{
    if (subset.size() == 3)
    {

        cnt++;

        return;
    }

    for (int i = start; i < rating.size(); i++)
    {
        if (subset.empty() || rating[i] > subset.back())
        {
            subset.push_back(rating[i]);
            backtrackMore(rating, subset, i + 1);
            subset.pop_back();
        }
    }
}

void backtrackLess(vector<int> &rating, vector<int> &subset, int start)
{
    if (subset.size() == 3)
    {

        cnt++;

        return;
    }

    for (int i = start; i < rating.size(); i++)
    {
        if (subset.empty() || rating[i] < subset.back())
        {
            subset.push_back(rating[i]);
            backtrackLess(rating, subset, i + 1);
            subset.pop_back();
        }
    }
}

int numTeams(vector<int> &rating)
{
    cnt = 0;
    vector<int> subsetMore;
    vector<int> subsetLess;

    backtrackMore(rating, subsetMore, 0);

    backtrackLess(rating, subsetLess, 0);

    cout << "rs: " << cnt;

    return cnt;
}

int numTeamsCountTwoSide(vector<int> &rating)
{

    int n = rating.size();
    int count = 0;
    for (int i = 1; i < n - 1; ++i)
    {

        int less_left = 0, greater_left = 0;
        int less_right = 0, greater_right = 0;

        // Count less and greater elements to the left of i
        for (int j = 0; j < i; ++j)
        {
            if (rating[j] < rating[i])
            {
                ++less_left;
            }
            else if (rating[j] > rating[i])
            {
                ++greater_left;
            }
        }

        // Count less and greater elements to the right of i
        for (int j = i + 1; j < n; ++j)
        {
            if (rating[j] < rating[i])
            {
                ++less_right;
            }
            else if (rating[j] > rating[i])
            {
                ++greater_right;
            }
        }

        // Calculate the number of teams with i as the middle element
        count += less_left * greater_right + greater_left * less_right;
    }

    return count;
}
int numTeamsDP(vector<int> &rating)
{
    int n = rating.size();
    vector<int> left_smaller(n, 0), right_larger(n, 0);
    vector<int> left_larger(n, 0), right_smaller(n, 0);

    // Fill left_smaller and left_larger
    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (rating[j] < rating[i])
            {
                left_smaller[i]++;
            }
            else if (rating[j] > rating[i])
            {
                left_larger[i]++;
            }
        }
    }

    // Fill right_larger and right_smaller
    for (int i = n - 2; i >= 0; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (rating[j] > rating[i])
            {
                right_larger[i]++;
            }
            else if (rating[j] < rating[i])
            {
                right_smaller[i]++;
            }
        }
    }

    // Calculate the number of valid teams
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        count += left_smaller[i] * right_larger[i] + left_larger[i] * right_smaller[i];
    }

    return count;
}

// Binary Indexed Tree (BIT) or Fenwick Tree
class BIT
{
public:
    BIT(int size) : bit(size + 1, 0) {}

    void update(int index, int value)
    {
        for (; index < bit.size(); index += index & -index)
        {
            bit[index] += value;
        }
    }

    int query(int index)
    {
        int sum = 0;
        for (; index > 0; index -= index & -index)
        {
            sum += bit[index];
        }
        return sum;
    }

private:
    vector<int> bit;
};

int numTeamsBIT(vector<int> &rating)
{
    int n = rating.size();
    if (n < 3)
        return 0;

    int max_rating = *max_element(rating.begin(), rating.end());

    BIT leftBIT(max_rating), rightBIT(max_rating);

    vector<int> left_smaller(n, 0), right_larger(n, 0);
    vector<int> left_larger(n, 0), right_smaller(n, 0);

    // Count smaller elements to the left
    for (int i = 0; i < n; ++i)
    {
        left_smaller[i] = leftBIT.query(rating[i] - 1);
        left_larger[i] = i - left_smaller[i];
        leftBIT.update(rating[i], 1);
    }

    // Count larger elements to the right
    for (int i = n - 1; i >= 0; --i)
    {
        right_larger[i] = rightBIT.query(max_rating) - rightBIT.query(rating[i]);
        right_smaller[i] = (n - 1 - i) - right_larger[i];
        rightBIT.update(rating[i], 1);
    }

    // Calculate the number of valid teams
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        count += left_smaller[i] * right_larger[i] + left_larger[i] * right_smaller[i];
    }

    return count;
}

int main()
{
    vector<int> rating = {2, 5, 3, 4, 1};
    numTeams(rating);
    return 0;
}