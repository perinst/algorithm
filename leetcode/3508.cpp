#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <deque>

using namespace std;

// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class Router
{
    int limit;
    unordered_map<string, vector<int>> mapExistPacket;
    deque<vector<int>> dq;
    unordered_map<int, vector<int>> mapDesTimestamp;

    int lowerBound(vector<int> arr, int target)
    {
        int left = 0;
        int right = arr.size();

        while (left < right)
        {
            int mid = right - ((right - left) / 2);

            if (arr[mid] == target)
                return left;

            if (target < arr[mid])
            {
                right = mid - 1;
            }
            else
            {
                left = mid;
            }
        }

        return left;
    }

public:
    Router(int memoryLimit)
    {
        limit = memoryLimit;
    }

    bool isLimit()
    {
        return dq.size() == limit;
    }

    bool addPacket(int source, int destination, int timestamp)
    {
        string key = std::to_string(source) + ":" +
                     std::to_string(destination) + ":" +
                     std::to_string(timestamp);

        if (mapExistPacket.count(key) > 0)
            return false;

        vector<int> packet = {source, destination, timestamp};

        if (isLimit())
        {
            auto oldestPacket = dq.front();
            dq.pop_front();

            // string oldKey = std::to_string(oldestPacket[0]) + ":" +
            //                 std::to_string(oldestPacket[1]) + ":" +
            //                 std::to_string(oldestPacket[2]);
            // mapExistPacket.erase(oldKey);
        }

        mapExistPacket[key] = packet;

        if (mapDesTimestamp[destination].size() == 0)
        {
            mapDesTimestamp[destination].push_back(timestamp);
        }
        else
        {
            int index = lowerBound(mapDesTimestamp[destination]);
        }

        dq.push_back(packet);

        return true;
    }

    vector<int> forwardPacket()
    {
        if (size <= 0)
            return {};

        vector<int> package = dq.front();

        string key = std::to_string(package[0]) + ":" +
                     std::to_string(package[1]) + ":" +
                     std::to_string(package[2]);

        mapExistPacket.erase(key);
        dq.pop_front();

        return package;
    }

    int getCount(int destination, int startTime, int endTime)
    {
        int count = 0;
        for (vector<int> &p : dq)
        {
            if (p[1] != destination)
                continue;
            if (p[2] <= endTime && p[2] >= startTime)
            {
                count++;
            }
        }
        return count;
    }
};

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // TODO: implement logic here
}

int main()
{
    // fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}