
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(int a, int b)
{
    return (1LL * a / gcd(a, b)) * b;
}

/**
 * @brief
 * complexity : n*m*k*log(k)
 * n : numbers of elements
 * m : number in stack : worse case: m == n
 * gcd: O(log(m))
 * merge element : worst case: n
 * total merge:  n^2
 * => total : O(n^2*log(m));
 * space: O(n+k) vs k<=n
 *
 * @brief
 *
 * @param nums
 * @return vector<int>
 */
vector<int> replaceNonCoprimes(vector<int> &nums)
{
    stack<int> st;
    int n = nums.size();

    st.push(nums[0]);

    for (int i = 1; i < n; i++)
    {
        int currentCombine = nums[i];

        while (!st.empty())
        {
            int top = st.top();

            if (gcd(top, currentCombine) <= 1)
            {
                break;
            }

            currentCombine = (int)lcm(currentCombine, top);
            st.pop();
        }

        st.push(currentCombine);
    }

    vector<int> rs;

    while (!st.empty())
    {
        rs.push_back(st.top());
        st.pop();
    }

    std::reverse(rs.begin(), rs.end());

    return rs;
}

int main()
{
    vector<int> nums = {6, 4, 3, 2, 7, 6, 2};
    replaceNonCoprimes(nums);
    return 0;
}