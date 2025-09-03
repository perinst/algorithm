/*

Albert loves hiking.

There are two nearby mountains (Mt. East and Mt. West), and there are hiking trails of various lengths.

Mt. East has n trails (whose lengths are A[1], ..., A[n]). Mt. West has m trails (whose lengths are B[1], ..., B[m]).

Every trail in Mt. East begins and ends at the same place (the entrance of Mt. East), and likewise every trail in Mt. West begins and ends at the same location (the entrance of Mt. West).

The entrances of the two mountains are connected by the East-West bridge of length x. In the image below, the square represents the entrance of Mt. East and the circle the entrance of Mt. West, where the East-West bridge has length x = 10. The two trails of Mt. East has lengths 40 and 45 whereas the two trails of Mt. West has the same length of 42.



Albert wants to plan a hiking route whose total length is at least C and at most D, according to the rules below. (A hiking route is to describe which trails are used in what order.)

The same trail cannot be used more than once.
Two trails of the same mountain cannot be used back-to-back (hence, each mountain's trail must be used alternatively).
When moving from one mountain to the other, the East-West bridge (of length x) must be used -- this is the only way. The bridge can be used multiple times.
The bridge cannot be used as the first or the last trail, and the bridge cannot be used consecutively. Hence, when the bridge is used, it must be before and after using a trail from either of the mountains.
In the example above, we have  n = m = 2, x = 10, A = [40, 45] and B = [42, 42]. Suppose C = 1 and D = 100. There are 12 hiking routes Albert can use whose net length is between 1 and 100, inclusive:

4 hiking routes whose length is between 40 and 45, inclusive (Albert can use one of the four trails alone).
8 hiking routes whose length is between 92 and 97, inclusive (Albert can use one trail from each mountain, and then decide the order in which he'll use them).
Given n, m, x, C, D, A, and B, help Albert figure out how many hiking routes he can come up with.

Input
The first line of the input will contain an integer T, the number of test cases.

Each test case will consist of three lines. The first line will contain n, m, x, C, and D, separated by whitespace. The second line will contain n integers (the lengths of the trails in Mt. East), separated by whitespace. The third line will contain m integers (the lengths of the trails in Mt. West), separated by whitespace.

Output
Output the answer in a single line for each test case.

Since the answer can be very large, output the answer modulo 109+7.

Limit
1 ≤ T ≤ 5
1 ≤ n, m ≤ 18
1 ≤ x ≤ 108
​1 ​≤ C ≤ D ≤ 109
1 ​​≤ the length of each trail ≤ 108
*/