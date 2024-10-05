
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

void turn_left(int &r, int &c)
{
    c -= 1;
}

void turn_right(int &r, int &c)
{
    c += 1;
}

void turn_up(int &r, int &c)
{
    r -= 1;
}

void turn_down(int &r, int &c)
{
    r += 1;
}

bool isOutSide(int &row, int &col, int &r, int &c)
{
    if (r >= row || c >= col || r <= 0 || c <= 0)
    {
        return true;
    }
    return false;
}

void next_turn(char &previous_direction, int &r, int &c)
{
    if (previous_direction == 'u')
    {
        turn_right(r, c);
        previous_direction = 'r';
    }
    else if (previous_direction == 'r')
    {
        turn_down(r, c);
        previous_direction = 'd';
    }
    else if (previous_direction == 'd')
    {
        turn_left(r, c);
        previous_direction = 'l';
    }
    else if (previous_direction == 'l')
    {
        turn_up(r, c);
        previous_direction = 'u';
    }
}

void move_in_same_direction(char previous_direction, int &r, int &c)
{
    if (previous_direction == 'r')
        c++;
    else if (previous_direction == 'u')
        r--;
    else if (previous_direction == 'd')
        r++;
    else if (previous_direction == 'l')
        c--;
}

vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
{

    const int limit = rows * cols;
    vector<vector<int>> rs(limit, vector<int>(2, 0));

    rs[0] = {rStart, cStart};

    int i = 1;
    int step = 1;

    while (i < limit)
    {

        // do for right movement
        // for (int k = 0; k < step; k++)
        // {
        //     if (cStart + 1 < cols)
        //     {
        //         ++cStart;
        //         rs[i++] = {rStart, cStart};
        //     }
        // }

        while (cStart + 1 < cols && i < limit)
        {
            if (rs[rStart][cStart + 1] != 0)
            {
                ++cStart;
                rs[i++] = {rStart, cStart};
            }

            if (rStart + 1 == rows)
                break;
            if (rs[rStart + 1][cStart] == 0)
                break;
        }

        // for go down
        while (rStart + 1 < rows && i < limit)
        {
            if (rs[rStart + 1][cStart] != 0)
            {
                ++rStart;
                rs[i++] = {rStart, cStart};
            }

            if (cStart == 0)
                break;
            if (rs[rStart][cStart - 1] == 0)
                break;
        }

        // for left movement
        while (cStart - 1 >= 0 && i < limit)
        {
            if (rs[rStart + 1][cStart] != 0)
            {
                --cStart;
                rs[i++] = {rStart, cStart};
            }

            if (rStart == 0)
                break;
            if (rs[rStart - 1][cStart] == 0)
                break;
        }

        // for move up
        while (rStart - 1 >= 0 && i < limit)
        {
            if (rs[rStart - 1][cStart] != 0)
            {
                --rStart;
                rs[i++] = {rStart, cStart};
            }

            if (cStart + 1 == cols)
                break;
            if (rs[rStart][cStart + 1] == 0)
                break;
        }
    }

    return rs;
}

vector<vector<int>> spiralMatrixIIIV2(int rows, int cols, int rStart, int cStart)
{
    const int limit = rows * cols;
    vector<vector<int>> rs(limit, vector<int>(2));

    rs[0] = {rStart, cStart};

    int i = 1;
    int step = 1;

    while (i < limit)
    {
        // Move right
        for (int k = 1; k <= step && i < limit; ++k)
        {
            if (cStart + 1 < cols)
            {
                ++cStart;
                rs[i++] = {rStart, cStart};
            }
        }

        // Move down
        for (int k = 1; k <= step && i < limit; ++k)
        {
            if (rStart + 1 < rows)
            {
                ++rStart;
                rs[i++] = {rStart, cStart};
            }
        }

        ++step;

        // Move left
        for (int k = 1; k <= step && i < limit; ++k)
        {
            if (cStart - 1 >= 0)
            {
                --cStart;
                rs[i++] = {rStart, cStart};
            }
        }

        // Move up
        for (int k = 1; k <= step && i < limit; ++k)
        {
            if (rStart - 1 >= 0)
            {
                --rStart;
                rs[i++] = {rStart, cStart};
            }
        }

        ++step;
    }

    return rs;
}
int main()
{
    int rows = 5, cols = 6, rStart = 1, cStart = 4;
    vector<vector<int>> rs = spiralMatrixIII(rows, cols, rStart, cStart);

    for (vector<int> &sub : rs)
    {
        cout << "[ " << sub[0] << ", " << sub[1] << " ]" << endl;
    }
    return 0;
}