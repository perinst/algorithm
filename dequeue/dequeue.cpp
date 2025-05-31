#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int data;
    Node *prev;
    Node *next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class Deque
{
private:
private:
    Node *front;
    Node *rear;
    int size;

public:
    Deque() : front(nullptr), rear(nullptr), size(0) {}
    int size()
    {
        return size;
    }
    bool isEmpty()
    {
        return size == 0;
    }

    void pushFront(int value)
    {
        Node *newNode = new Node(value);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        size++;
    }

    void pushBack(int value)
    {
        Node *newNode = new Node(value);
        if (isEmpty())
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
        }
        size++;
    }

    void popFront()
    {
        if (isEmpty())
            return;

        Node *temp = front;
        if (front == rear)
        {
            front = rear = nullptr;
        }
        else
        {
            front = front->next;
            front->prev = nullptr;
        }
        delete temp;
        size--;
    }

    void popBack()
    {
        if (isEmpty())
            return;

        Node *temp = rear;
        if (front == rear)
        {
            front = rear = nullptr;
        }
        else
        {
            rear = rear->prev;
            rear->prev = nullptr;
        }
        delete rear;
        size--;
    }

    int getFront()
    {
        return isEmpty() ? -1 : front->data;
    }

    int getBack()
    {
        if (isEmpty())
        {
            return -1;
        }
        return rear->data;
    }
    
    void printDeque()
    {
        if (isEmpty())
        {
            cout << "Deque is empty!" << endl;
            return;
        }
        Node *node = front;

        while (node != nullptr)
        {
            cout << node->data << " ";
            node = node->next;
        }
        cout << endl;
    }

    // Destructor to free memory
    ~Deque()
    {
        while (!isEmpty())
        {
            popFront();
        }
    }

};

int main()
{
    int n, k;
    cin >> n, k;
    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int t = n - k + 1;

    return 0;
}