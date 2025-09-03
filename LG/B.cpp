#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <climits>

/*

There are N S that consist only of uppercase English alphabets (denote these strings as S[1], S[2], ..., S[N]).

Reverse(T) is defined as the reversed string of an arbitrary string, T (clearly, for any string T, Reverse(Reverse(T)) = T).

For instance, Reverse("ABC") = "CBA".

For each of these N strings, you can decide whether to choose Reverse() to it or not -- and by doing so, you want to sort the N strings lexicographically (as there are N strings, you have 2N ways).

Let '1' denote the case where you apply Reverse() to each string and '0' the other case -- then we'll have a 0-1 string of length N. We call such strings "Reversal Strings".

For instance, suppose that N = 3 and S[1] = "ABC", S[2] = "XC", and S[3] = "DZ".

For the Reversal String "000": The three strings remain as-is ("ABC", "XC", and "DZ"), which is not lexicographically sorted. (S[3] comes before S[2].)
For the Reversal String "001": We apply Reverse() only to the third string, and we end up with "ABC", "XC", and "ZD" which is lexicographically sorted.
For the Reversal String "010": We apply Reverse() only to the second string, and we end up with "ABC", "CX", and "DZ" which is lexicographically sorted.
For the Reversal String "101": We apply Reverse() only to the first and third strings, and we end up with "CBA", "XC", and "ZD" which is lexicographically sorted.
There are other ways to sort these strings in lexicographic order.

Given N strings, find a Reversal String that sorts the strings in lexicographic order; if there are multiple such Reversal Strings, find the one that comes lexicographically first.

Input
The first line will contain the number of test cases, T.

For each test case, the first line will contain N, the number of strings.

In the next N lines, each line will contain one string that consists only of uppercase English alphabets.

Output
For each test case, output the Reversal String that sorts the given strings in lexicographic order; if there exist multiple such Reversal Strings, output the one that comes lexicographically first.

Limit
1 ≤ T ≤ 50
2 ≤ N ≤ 150
2 ≤ Length (S[i]) ≤ 20
For every i ≠ j, Reverse(S[i]) ≠ S[j] and S[i] ≠ S[j] always hold.
For each test case, there always exists at least one Reversal String that sorts the input strings in lexicographic order.
*/
using namespace std;

#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

class Solution
{
public:
    vector<string> S;
    vector<string> reversed_strings;
    int N;
    string rs;
    bool found;

    string reverse_string(const string &s)
    {
        string rev = s;
        reverse(rev.begin(), rev.end());
        return rev;
    }

    bool can_be_sorted(vector<string> &sequences)
    {

        for (size_t i = 1; i < sequences.size(); i++)
        {
            if (sequences[i - 1] > sequences[i])
                return false;
        }

        return true;
    }

    bool has_valid_continuation(const vector<string> &current_sequence, int pos)
    {
        if (pos >= N)
            return true;

        string last = current_sequence.empty() ? "" : current_sequence.back();

        return (current_sequence.empty() || last <= S[pos]) || (current_sequence.empty() || last <= reversed_strings[pos]);
    }

    void backtracking(int pos, string &reversal_bits, vector<string> &current_sequence)
    {
        if (found)
            return;

        if (pos == N)
        {
            if (can_be_sorted(current_sequence))
            {
                rs = reversal_bits;
                found = true;
            }
            return;
        }

        string last_str = current_sequence.empty() ? "" : current_sequence.back();

        // '0'
        if (current_sequence.empty() || last_str <= S[pos])
        {
            reversal_bits[pos] = '0';
            current_sequence.push_back(S[pos]);

            if (has_valid_continuation(current_sequence, pos + 1))
                backtracking(pos + 1, reversal_bits, current_sequence);

            current_sequence.pop_back();
        }

        if (found)
            return;

        // '1'
        if (current_sequence.empty() || last_str <= reversed_strings[pos])
        {
            reversal_bits[pos] = '1';
            current_sequence.push_back(reversed_strings[pos]);

            if (has_valid_continuation(current_sequence, pos + 1))
                backtracking(pos + 1, reversal_bits, current_sequence);

            current_sequence.pop_back();
        }
    }

    string solve()
    {
        cin >> N;
        rs = "";
        found = false;

        S.resize(N);
        reversed_strings.resize(N);

        for (int i = 0; i < N; i++)
        {
            cin >> S[i];
            reversed_strings[i] = reverse_string(S[i]);
        }

        string reversal_bits(N, '0');
        vector<string> current_sequence;

        backtracking(0, reversal_bits, current_sequence);

        return rs;
    }
};

int main()
{
    fast_io;

    int T = 1;
    cin >> T;

    while (T--)
    {
        Solution s;
        string rs = s.solve();

        cout << rs << endl;
    }

    return 0;
}