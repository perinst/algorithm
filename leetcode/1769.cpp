#include <iostream>
#include <vector>
using namespace std;

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ",";
        }
    }
    os << "]";
    return os;
}

vector<int> minOperations(string boxes)
{
    vector<int> answer(boxes.size(), 0);

    for (int i = 0; i < boxes.size(); i++)
    {
        int step = 0;
        for (int j = 0; j < boxes.size(); j++)
        {
            char value = boxes[j];
            if (value == '0' || j == i)
            {
                continue;
            }
            step += abs(j - i);
        }
        answer[i] = step;
    }

    return answer;
}

vector<int> minOperations2(string boxes)
{
    int n = boxes.size();
    vector<int> answer(n, 0);

    int ballsToLeft = 0, movesToLeft = 0;
    int ballsToRight = 0, movesToRight = 0;

    for (int i = 0; i < n; i++)
    {
        answer[i] += movesToLeft;
        ballsToLeft += boxes[i] - '0';
        movesToLeft += ballsToLeft;

        int j = n - 1 - i;
        answer[j] += movesToRight;
        ballsToRight += boxes[j] - '0';
        movesToRight += ballsToRight;
    }

    return answer;
}

void solve()
{
    string boxes;
    cin >> boxes;
    cout << minOperations2(boxes);
}

int main()
{
    solve();

    return 0;
}