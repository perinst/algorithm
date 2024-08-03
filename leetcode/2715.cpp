#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <stack>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int maxS(vector<int> &arr)
    {
        int n = sizeof(arr) / sizeof(arr[0]);

        int max = arr[0];

        for (int i = 1; i < n; ++i)
        {
            if (arr[i] > max)
            {
                max = arr[i];
            }
        }
        return max;
    }
    vector<int> survivedRobotsHealths(vector<int> &positions, vector<int> &healths, std::string directions)
    {
        std::unordered_map<int, int> hashmapP;
        std::stack<int> stack;

        int size_road = maxS(positions);
        int amount_e = positions.size();

        for (int i = 1; i <= positions.size(); i++)
        {
            hashmapP[positions[i - 1]] = i;
        }

        while (amount_e > 0)
        {
        }

        for (int p : positions)
        {
            int i = hashmapP[p] - 1;
            int h = healths[i];
            char d = directions[i];

            if (d == 'R' && i + 1 < amount_e && directions[i + 1] == 'L')
            {
                int idx_opponent = hashmapP[i + 1];

                if (idx_opponent > 0)
                {
                    if (healths[idx_opponent - 1] > healths[i])
                    {
                        hashmapP[i + 1] = 0;
                        amount_e--;
                    }
                    else if (healths[idx_opponent - 1] < healths[i])
                    {
                        hashmap[idx_opponent] = 0;
                        amount_e--;
                    }
                    else
                    {
                        hashmapP[i + 1] = 0;
                        hashmap[idx_opponent] = 0;
                        amount_e -= 2;
                    }
                }
            }
            else if (d == 'L' && i - 1 > 0 && directions[i - 1] == 'R')
            {
                int idx_opponent = hashmapP[i - 1];

                if (idx_opponent > 0)
                {
                    if (healths[idx_opponent - 1] > healths[i])
                    {
                        hashmapP[i + 1] = 0;
                        amount_e--;
                    }
                    else if (healths[idx_opponent - 1] < healths[i])
                    {
                        hashmap[idx_opponent] = 0;
                        amount_e--;
                    }
                    else
                    {
                        hashmapP[i + 1] = 0;
                        hashmap[idx_opponent] = 0;
                        amount_e -= 2;
                    }
                }
            }

            if (d == 'R' && i + 2 < amount_e)
            {
                int idx_opponent = hashmapP[i + 2];

                if (idx_opponent > 0)
                {
                    if (healths[idx_opponent - 1] > healths[i])
                    {
                        hashmapP[i + 1] = 0;
                        amount_e--;
                    }
                    else if (healths[idx_opponent - 1] < healths[i])
                    {
                        hashmap[idx_opponent] = 0;
                        amount_e--;
                    }
                    else
                    {
                        hashmapP[i + 1] = 0;
                        hashmap[idx_opponent] = 0;
                        amount_e -= 2;
                    }
                }
            }
            else if (d == 'L' && i - 2 > 0)
            {

                int idx_opponent = hashmapP[i - 2];
                if (idx_opponent > 0)
                {
                    if (healths[idx_opponent - 1] > healths[i])
                    {
                        hashmapP[i + 1] = 0;
                        amount_e--;
                    }
                    else if (healths[idx_opponent - 1] < healths[i])
                    {
                        hashmap[idx_opponent] = 0;
                        amount_e--;
                    }
                    else
                    {
                        hashmapP[i + 1] = 0;
                        hashmap[idx_opponent] = 0;
                        amount_e -= 2;
                    }
                }
            }
        }
    };
    vector<int> survivedRobotsHealthsStack(vector<int> &positions, vector<int> &healths, std::string directions)
    {
        std::stack<int> stack;
        std::unordered_map<int, int> hashmapP;
        vector<int> rs;

        int amount_e = positions.size();

        for (int i = 0; i < amount_e; i++)
        {
            hashmapP[positions[i]] = i;
        }

        int i = 0;
        for (int i = 0; i < amount_e; i++)
        {

            int idx = hashmapP[positions[i]];

            if (directions[idx] == 'R')
            {
                stack.push(idx);
            }
            else
            {

                while (!stack.empty())
                {
                    int idxR = stack.top();
                    // idx for L robot ->
                    if (healths[idxR] > healths[idx])
                    {
                        healths[idxR]--;
                        healths[idx] = 0;
                        break;
                    }
                    else if (healths[idxR] < healths[idx])
                    {
                        healths[idx]--;
                        healths[idxR] = 0;
                        stack.pop();
                    }
                    else
                    {
                        healths[idx] = healths[idxR] = 0;
                        stack.pop();
                    }
                }
            }
        }

        for (int h : healths)
        {
            if (h > 0)
                rs.push_back(h);
        }

        return rs;
    }
};

int main()
{
    std::unordered_map<std::string, int> hashmap;

    // Inserting some key-value pairs into the hashmap
    hashmap["apple"] = 1;
    hashmap["banana"] = 2;
    hashmap["orange"] = 3;

    std::cout << hashmap["a"];

    // Get value by key using at()
    std::string key = "banana";
    return 0;
}