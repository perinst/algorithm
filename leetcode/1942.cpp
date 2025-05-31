
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Overload the << operator for vector<vector<int>>
// std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<int>> &vec)
// {
//     os << "[\n";
//     for (size_t i = 0; i < vec.size(); ++i)
//     {
//         os << "  " << vec[i];
//         if (i != vec.size() - 1)
//         {
//             os << ",\n";
//         }
//     }
//     os << "\n]";
//     return os;
// }

int smallestChair(vector<vector<int>> &times, int targetFriend)
{

    int targetArrive = times[targetFriend][0];

    std::sort(times.begin(), times.end(), [](const std::vector<int> &a, const std::vector<int> &b)
              { return a[0] < b[0]; });

    // first : time leave , second: position seat
    std::priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> leave_seat;

    // min heap for index seat
    std::priority_queue<int, vector<int>, greater<vector<int>>> available_seats;

    int nextChair = 0;

    for (vector<int> &time : times)
    {

        int arrive = time[0];
        int leave = time[1];
        // free space for all seat has left
        while (!leave_seat.empty() && leave_seat.top().first <= arrive)
        {
            available_seats.push(leave_seat.top().second);
            leave_seat.pop();
        }

        int sat;
        if (!available_seats.empty())
        {
            sat = available_seats.top();
            available_seats.pop();
        }
        else
        {
            sat = nextChair++;
        }

        leave_seat.push({time[1], nextChair});

        if (targetArrive == arrive)
            return sat;
    }

    return -1;
}
int main() {

};
