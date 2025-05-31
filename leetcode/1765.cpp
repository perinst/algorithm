#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const vector<vector<int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
{
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    int rows = isWater.size();
    int columns = isWater[0].size();
    vector<vector<int>> cellHeight(rows, vector<int>(columns, -1));
    queue<pair<int, int>> queue;

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {
            if (isWater[x][y] == 1)
            {
                cellHeight[x][y] = 0;
                queue.push({x, y});
            }
        }
    }

    int heightOfNextLayer = 1;

    while (!queue.empty())
    {
        int layerSize = queue.size();

        for (int i = 0; i < layerSize; i++)
        {
            pair<int, int> cell = queue.front();
            queue.pop();
            for (int d = 0; d < 4; d++)
            {
                pair<int, int> neighborCell = {cell.first + dx[d],
                                               cell.second + dy[d]};

                if (isValidCell(neighborCell, rows, columns) && cellHeight[neighborCell.first][neighborCell.second] == -1)
                {
                    cellHeight[cell.first][cell.second] = heightOfNextLayer;
                    queue.push(neighborCell);
                }
            }
        }
        heightOfNextLayer++;
    }

    return cellHeight;
}

bool isValidCell(pair<int, int> &cell, int &rows, int &columns)
{
    return cell.first >= 0 && cell.second >= 0 && cell.first < rows &&
           cell.second < columns;
}

int main()
{
    return 0;
}