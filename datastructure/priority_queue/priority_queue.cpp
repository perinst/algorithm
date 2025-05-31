#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Node
{
    Node *left;
    Node *right;
    Node *parent;
    int data;

    Node(int value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {};
};

class priority_queue
{
private:
    Node *root;
    int size;
    int height;

    void heapfiyUp(Node *node)
    {
    }

public:
    priority_queue() : size(0), height(0) {};

    bool is_empty()
    {
        return size == 0;
    }

    void push(int value)
    {
        Node *newNode = new Node(value);
        if (is_empty())
        {
            root = newNode;
        }
        else
        {
            Node *node = root;
            while (node->left && node->right)
            {
            }
        }
    }
    Node findLeft(Node *node)
    {
        Node *temp = node;
        while (temp->left && temp->right)
        {
            temp = temp->left;
        }

    }

    void pop()
    {
    }

    int top()
    {
        return root->data;
    }
};

class PriorityQueueMaxHeap
{
    vector<int> heap;

private:
    void heapifyUp(int index)
    {
        while (index > 0 && heap[index] > heap[(index - 1) / 2])
        {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index)
    {
        stack<int> s;
        s.push(index);

        while (!s.empty())
        {

            int largest = s.top();
            s.pop();
            int leftChildIdx = 2 * index + 1;
            int rightChildIdx = 2 * index + 2;

            if (heap[leftChildIdx] > heap[largest])
            {
                largest = leftChildIdx;
            }

            if (heap[rightChildIdx] > heap[largest])
            {
                largest = rightChildIdx;
            }

            if (largest != index)
            {
                swap(heap[index], heap[largest]);
                s.push(largest);
            }
        }
    }

public:
    bool isEmpty()
    {
        return heap.empty();
    }

    void push(int val)
    {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    void pop()
    {
        if (isEmpty())
            return;
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        heapifyDown(0);
    }

    int top()
    {
        if (isEmpty())
            return -1;
        return heap[0];
    }
};

int main()
{
    
    return 0;
}