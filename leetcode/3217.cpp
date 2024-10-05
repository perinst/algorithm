#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

// Definition for singly-linked list.

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *modifiedList(vector<int> &nums, ListNode *head)
    {
        unordered_set<int> set(nums.begin(), nums.end());

        while (set.find(head->val) != set.end() && head)
        {
            ListNode *temp = head;
            head = head->next;
            delete temp;
        }

        if (!head)
        {
            return nullptr;
        }

        ListNode *node = head;

        while (node->next)
        {
            if (set.find(node->next->val) != set.end())
            {
                ListNode *temp = node->next;
                node->next = node->next->next;
                delete temp;
            }
            else
            {
                node = node->next;
            }
        }

        return head;
    }
};
int main()
{

    return 0;
}