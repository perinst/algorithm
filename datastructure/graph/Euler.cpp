#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 1000;

vector<int> adj[MAXN];
vector<vector<bool>> used;
vector<int> eulerianCycle;

void euler_walk(int u)
{
    stack<int> st;
    st.push(u);

    while (!st.empty())
    {
        int v = st.top();
        bool found = false;

        int adj_size = adj[v].size();

        for (size_t i = 0; i < adj_size; i++)
        {
            int w = adj[v][i];
            // Nếu cạnh (v, w) chưa dùng thì sử dụng nó

            if (used[v][i])
                continue;

            used[v][i] = true;

            for (int j = 0; j < adj[w].size(); j++)
            {
                if (adj[w][j] == v && !used[w][j])
                {
                    used[w][j] = true;
                    break;
                }
            }

            st.push(w);
            found = true;
            break;
        }

        if (!found)
        {
            // Nếu không còn cạnh nào chưa sử dụng thì thêm đỉnh này vào chu trình
            eulerianCycle.push_back(v);
            st.pop();
        }
    }
}

int main()
{
    int m, n;
    cin >> n >> m;

    used.assign(n, vector<bool>());
    for (int i = 0; i < n; i++)
    {
        adj[i].clear();
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        // Đồ thị vô hướng
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
    {
        used[i].assign(adj[i].size(), false);
    }

    // Chọn đỉnh bắt đầu:  0
    euler_walk(0);

    if (eulerianCycle.size() == m + 1)
    {
        cout << "Chu trinh Euler la: ";
        reverse(eulerianCycle.begin(), eulerianCycle.end());
        for (int v : eulerianCycle)
        {
            cout << v << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Khong ton tai chu trinh Euler." << endl;
    }

    return 0;
}