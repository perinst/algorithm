#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_set>

using namespace std;

#define ll long long;

long long maxWeight(vector<int> &pizzas)
{
    long long weight = 0;
    int days = pizzas.size() / 4;
    int n = pizzas.size() - 1;
    sort(pizzas.begin(), pizzas.end());

    for (int i = 1; i <= days; i += 2)
    {
        weight += pizzas[n];
        n--;
    }

    n--;
    for (int i = 2; i <= days; i += 2)
    {
        weight += pizzas[n];
        n -= 2;
    }

    return weight;
}

int main()
{
    vector<int> days = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    cout << maxWeight(days);
    return 0;
}