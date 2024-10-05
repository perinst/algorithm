#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class FenWickTree
{
private:
    vector<int> fenwick;
    vector<int> prefixS;

    // calculate range for responsibility value of an index i. ex: value 12 -> 8-bit form is (0000 1100)2 => -12 = (1111 0100 )2
    // 12 & (-12) == (0000 1100)2 & (1111 0100) = (0000 0100)2 = 4;
    // range for responsibility of 12 =  4;

    int rsb(int num)
    {
        return num & (-num);
    }

    int prefixSum(int i)
    {
        // INPUT
        //    i = an index
        //    fenwick = the Fenwick tree of array A
        // OUTPUT
        //    The prefix sum of A ending at index i

        int rs = 0;
        while (i--)
        {
            rs += fenwick[i];
            i -= rsb(i);
        }

        return rs;
    }

public:
    FenWickTree(vector<int> nums)
    {
        this->fenwick = nums;
    }
    vector<int> build()
    {
        int n = fenwick.size();
        for (int i = 0; i < n; i++)
        {
            int parent = i + this->rsb(i);

            if (parent <= n)
            {
                fenwick[parent] += fenwick[i];
            }
        }

        return fenwick;
    }
};

int main()
{

    return 0;
}