
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

#define FOR(i, a, b)                \
    for (int i = (a); i < (b); i++) \
        ;

using namespace std;

struct Node
{
    int val;
    Node *next;
    Node *prev;
    int min;
};

class LinkedList
{
public:
    Node *head;
    Node *tail;
    int size;

    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void insert(int val, int min)
    {
        Node *newNode = new Node{val, nullptr, nullptr, min};

        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        size++;
    }

    void pop()
    {

        if (size == 0)
            return;

        if (size == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
            return;
        }

        Node *temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        delete temp;

        size--;
    }
};

class MinStack
{

private:
    LinkedList *dbLinkedList;

public:
    MinStack()
    {
        dbLinkedList = new LinkedList();
    }

    void push(int val)
    {
        dbLinkedList->insert(val, min(this->getLinkedListTopMin(), val));
    }

    void pop()
    {
        if (dbLinkedList->size == 0)
            return;

        dbLinkedList->pop();
    }

    int getLinkedListTopMin()
    {
        if (dbLinkedList->size == 0)
            return INT_MAX;

        return dbLinkedList->tail->min;
    }

    int top()
    {
        if (dbLinkedList->size == 0)
            return INT_MAX;

        return dbLinkedList->tail->val;
    }

    int getMin()
    {
        return dbLinkedList->tail->min;
    }
};

int main()
{
    return 0;
}