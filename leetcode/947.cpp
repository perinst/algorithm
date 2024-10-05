#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<pair<int, int>>> col;
unordered_map<int, vector<pair<int, int>>> row;

// status == 1  is row
// status ==0  is col;

int bfs(vector<vector<int>> &stones, unordered_set<int, bool> &visitedRows, unordered_set<int, bool> &visitedCols, int status, int k)
{
    if (status == 1 && visitedRows.count(k))
        return;
    if (status == 0 && visitedCols.count(k))
        return;

    if (status == 1)
        visitedRows.insert(k);
    else
        visitedCols.insert(k);

    vector<pair<int, int>> pairs = status == 1 ? row[k] : col[k];

    for (auto &p : pairs)
    {
        int r = p.first;
        int c = p.second;

        bfs(stones, visitedRows, visitedCols, 1, r);
        bfs(stones, visitedRows, visitedCols, 0, c);
    }
}

int removeStones(vector<vector<int>> &stones)
{

    for (vector<int> &stone : stones)
    {
        row[stone[0]].push_back({stone[0], stone[1]});
        col[stone[1]].push_back({stone[0], stone[1]});
    }

    int amountConnectedComponent = 0;
    unordered_set<int, bool> visitedRow;
    unordered_set<int, bool> visitedCol;

    for (vector<int> s : stones)
    {

        if (!visitedRow.count(s[0]) && !visitedCol.count(s[1]))
        {
            bfs(stones, visitedRow, visitedCol, 1, s[0]);
            amountConnectedComponent++;
        }
    }

    return stones.size() - amountConnectedComponent;
}

int main()
{
}