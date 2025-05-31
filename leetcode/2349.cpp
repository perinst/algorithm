#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

class NumberContainers
{
private:
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>>
        numberToIndices;
    std::unordered_map<int, int> indexToNumbers;

public:
    NumberContainers() {}

    void change(int index, int number)
    {
        numberToIndices[number].push(index);
        indexToNumbers[index] = number;
    }

    int find(int number)
    {
        if (numberToIndices.find(number) == numberToIndices.end())
        {
            return -1;
        }

        auto &minHeap = numberToIndices[number];

        while (!minHeap.empty())
        {
            int index = minHeap.top();
            if (indexToNumbers[index] == number)
            {
                return index;
            }
            minHeap.pop();
        }

        return -1;
    }
};

class NumberContainers2
{
public:
    unordered_map<int, unordered_set<int>> numberToIndices;
    unordered_map<int, int> indexToNumbers;

    NumberContainers() {}

    void change(int index, int number)
    {
        if (indexToNumbers.find(index) != indexToNumbers.end())
        {
            int prevNumber = indexToNumbers[index];
            numberToIndices[prevNumber].erase(index);
            if (numberToIndices[prevNumber].empty())
            {
                numberToIndices.erase(prevNumber);
            }
        }

        numberToIndices[number].insert(index);
        indexToNumbers[index] = number;
    }

    int find(int number)
    {
        return numberToIndices[number].empty() ? -1 : *numberToIndices[number].begin();
    }
};

int main()
{
    return 0;
}