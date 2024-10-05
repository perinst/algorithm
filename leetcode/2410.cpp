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
// this solution Memory Limit Exceeded but complexity : O(n)
int matchPlayersAndTrainers(vector<int> &players, vector<int> &trainers)
{
    unordered_map<int, int> map;

    int maxA = *max_element(trainers.begin(), trainers.end());
    vector<int> prefix(maxA + 1);
    int cnt = 0;
    for (int &t : trainers)
    {
        map[t]++;
        prefix[t] = t;
    }

    int assign = maxA;
    for (int i = maxA; i >= 0; i--)
    {
        if (prefix[i] != maxA && prefix[i] > 0)
        {
            assign = prefix[i];
        }
        prefix[i] = assign;
    }

    cout << prefix << endl;

    for (int i = 0; i < players.size() && i < trainers.size(); i++)
    {

        if (players[i] > maxA)
            continue;

        int trainer = prefix[players[i]];

        if (map[trainer]-- >= 0)
        {
            cnt++;
        }
    }

    return cnt;
}

// this take O(n*log(n))

int matchPlayersAndTrainersV2(vector<int> &players, vector<int> &trainers)
{
    sort(players.begin(), players.end());
    sort(trainers.begin(), trainers.end());

    int p1 = 0;
    int p2 = 0;
    int cnt = 0;

    while (p1 < players.size() && p2 < trainers.size())
    {
        if (players[p1] <= trainers[p2])
        {
            cnt++;
            p1++;
            p2++;
        }
        else
        {
            p2++;
        }
    }
    return cnt;
}

int main()
{
    vector<int> p = {4, 7, 9};
    vector<int> t = {8, 2, 5, 8};

    cout << matchPlayersAndTrainers(p, t);

    return 0;
}