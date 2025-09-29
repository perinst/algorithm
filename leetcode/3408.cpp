#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <set>
#include <utility>

using namespace std;

// Utility macros
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define FOR(i, a, b)                \
    for (int i = (a); i < (b); i++) \
        ;

#define RFOR(i, a, b)                \
    for (int i = (a); i >= (b); i--) \
        ;

#define CINARR(arr) \
    FOR(i, 0, arr.size()) { std::cin >> arr[i]; }

#define COUTARR(arr) \
    FOR(i, 0, arr.size()) { std::cout << arr[i] << " "; }
// Fast I/O
#define fast_io                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

// class PriorityQueue<T>
// {

// }

struct Node
{
    int priority;
    int id;
};
class IndexPriorityQueue
{

private:
    vector<Node> heap;
    unordered_map<int, int> pos;

    void swapNodes(int i, int j)
    {
        swap(heap[i], heap[j]);

        pos[heap[i].id] = i;
        pos[heap[j].id] = j;
    }

    void bubbleUp(int i)
    {
        while (i > 0)
        {
            int p = (i - 1) / 2;
            if (heap[i].priority <= heap[p].priority)
                break;
            swapNodes(i, p);
            i = p;
        }
    }

    void bubbleDown(int i)
    {
        int n = heap.size();
        while (true)
        {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int largest = i;

            if (l < n && heap[l].priority < heap[largest].priority)
                largest = l;
            if (r < n && heap[r].priority < heap[largest].priority)
                largest = r;

            if (largest == i)
                break;

            swapNodes(i largest);
            i = largest;
        }
    }

public:
    bool empty() const { return heap.empty() };
    int size() const { return heap.size() };

    void insert(int id, int priority)
    {
        if (pos.count(id))
        {
            this->update(id, priority);
            return;
        }

        this->heap.push_back({priority, id});

        pos[id] = heap.size() - 1;
        bubbleUp(heap.size() - 1);
    }

    void update(int id, int newPriority)
    {
        if (!pos.count(id))
            return;

        int index = pos[id];
        int oldP = heap[index].priority;
        heap[index].priority = newPriority;

        if (newPriority > oldP)
        {
            bubbleUp(index);
        }
        else
        {
            bubbleDown(index);
        }
    }

    void erase(int taskId)
    {
        if (!pos.count(taskId))
            return;

        int index = pos[taskId];

        swapNodes(index, heap.size() - 1);

        heap.pop_back();
        pos.erase(taskId);

        // TODO: optimize this code
        bubbleUp(i);
        bubbleDown(i);
    }

    pair<int, int> top() const
    {

        if (heap.empty())
            return {-1, -1};

        return { heap[0].id, heap[0].priority }
    }

    void pop()
    {
        auto [id, p] = this->top();
        this->erase(id);
    }
};

struct Task
{
    int taskId;
    int priority;
    int userId;
};

struct TaskCmp
{
    bool operator()(const Task &a, const Task &b) const
    {
        if (a.priority != b.priority)
            return a.priority < b.priority;

        return a.taskId < b.taskId;
    }
};

class TaskManager
{
    set<Task, TaskCmp> pq;
    unordered_map<int, Task> mapTaskUser;

public:
    TaskManager(vector<vector<int>> &tasks)
    {

        for (vector<int> &task : tasks)
        {
            int userId = task[0];
            int taskId = task[1];
            int priority = task[2];
            this->add(userId, taskId, priority);
        }
    }

    void add(int userId, int taskId, int priority)
    {

        auto it = mapTaskUser.find(taskId);
        if (it != mapTaskUser.end())
        {
            pq.erase(it->second);
        }
        Task task{taskId, priority, userId};

        mapTaskUser[taskId] = task;

        pq.insert(task);
    }

    void edit(int taskId, int newPriority)
    {
        auto it = mapTaskUser.find(taskId);
        if (it == mapTaskUser.end())
            return;

        pq.erase(it->second);
        it->second.priority = newPriority;
        pq.insert(it->second);
    }

    void rmv(int taskId)
    {
        Task task = mapTaskUser[taskId];
        pq.erase(task);
    }

    int execTop()
    {
        if (pq.empty())
            return -1;

        auto it = pq.begin();
        Task task = *it;
        pq.erase(it);

        mapTaskUser.erase(task.taskId);
        return task.userId;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */

void solve()
{
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int i = 0; i < N; i++)
    {
        cin >> nums[i];
    }

    // TODO: implement logic here
}

int main()
{
    // fast_io;

    int T = 1;
    // cin >> T;

    while (T--)
    {
        solve();
    }

    return 0;
}