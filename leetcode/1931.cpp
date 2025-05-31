#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;
const int MOD = 1e9 + 7;

template <typename T>

std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

bool isValidRowMask(const string &mask)
{
    for (size_t k = 0; k < mask.size() - 1; k++)
    {
        if (mask[k] == mask[k + 1])
            return false;
    }
    return true;
}

vector<string> getAllValidRowMask(int m)
{
    vector<string> valid_masks;
    const int total_mask = static_cast<int>(pow(3, m));

    for (int mask = 0; mask < total_mask; mask++)
    {
        int num = mask;
        string ternary = "";

        while (num > 0)
        {
            ternary = to_string(num % 3) + ternary;
            num /= 3;
        }

        while (ternary.length() < m)
        {
            ternary = "0" + ternary;
        }

        if (isValidRowMask(ternary))
        {
            valid_masks.push_back(ternary);
        }
    }
    return valid_masks;
}

bool areMasksCompatible(const std::string &mask1, const std::string &mask2)
{

    if (mask1.length() != mask2.length())
    {
        return false;
    }

    for (size_t k = 0; k < mask1.length(); k++)
    {
        if (mask1[k] == mask2[k])
        {
            return false;
        }
    }

    return true;
}

int colorTheGrid(int m, int n)
{
    vector<string> valid_row_masks = getAllValidRowMask(m);

    int num_valid_masks = valid_row_masks.size();

    if (num_valid_masks == 0)
    {
        return 0;
    }

    // vector<vector<int>> dp(m, vector<int>(n + 1, 1));

    vector<long long> dp_prev(num_valid_masks, 0);

    for (int j = 0; j < num_valid_masks; j++)
    {
        dp_prev[j] = 1;
    }

    for (int i = 1; i < n; i++)
    {
        vector<long long> dp_curr(num_valid_masks, 0);

        for (int j_curr = 0; j_curr < num_valid_masks; j_curr++)
        {
            string &mask_curr = valid_row_masks[j_curr];

            for (int j_prev = 0; j_prev < num_valid_masks; j_prev++)
            {
                string &mask_prev = valid_row_masks[j_prev];

                if (areMasksCompatible(mask_curr, mask_prev))
                {
                    dp_curr[j_curr] = (dp_curr[j_curr] + dp_prev[j_prev]) % MOD;
                }
            }
        }
        dp_prev = dp_curr;
    }
    long long total_ways = 0;

    for (long long ways : dp_prev)
    {
        total_ways = (total_ways + ways) % MOD;
    }

    return static_cast<int>(total_ways);
}

int main()
{
    colorTheGrid(1, 2);
    return 0;
}