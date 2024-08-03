#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    int T;
    cin >> T;

    while (T--)
    {

        int N;
        cin >> N;

        vector<int> arrivals(N);
        vector<int> departures(N);

        for (int i = 0; i < N; ++i)
        {
            cin >> arrivals[i];
        }

        for (int i = 0; i < N; ++i)
        {
            cin >> departures[i];
        }

        vector<pair<int, char>> events;

        for (int i = 0; i < N; ++i)
        {
            events.push_back({arrivals[i], 'A'});
            events.push_back({departures[i], 'D'});
        }

        // Sort events: first by time; in case of tie, 'D' should come before 'A'
        sort(events.begin(), events.end(), [](const pair<int, char> &a, const pair<int, char> &b)
             {
            if (a.first == b.first) return a.second < b.second;
            return a.first < b.first; });

        int current_guests = 0;
        int max_guests = 0;

        for (const auto &event : events)
        {
            if (event.second == 'A')
            {
                current_guests++;
                max_guests = max(max_guests, current_guests);
            }
            else
            {
                current_guests--;
            }
        }

        cout << max_guests << endl;
    }

    return 0;
}
