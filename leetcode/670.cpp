#include <iostream>
#include <vector>
#include <string>

using namespace std;

int maximumSwap(int num)
{

    string strNum = to_string(num);
    int n = strNum.size();
    char maxV = strNum[n - 1];
    int idx = n - 1;

    vector<int> last(10, -1);

    for (int i = 0; i < n; i++)
    {
        last[strNum[i] - '0'] = i;
    }

    for (int i = 0; i < n; i++)
    {
        for (int d = 9; d > strNum[i] - '0'; d--)
        {
                }
    }

    cout << maxV << endl
         << idx << endl;
    swap(strNum[0], strNum[idx]);

    return stoi(strNum);
}

int main()
{
}