#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;
int maxN = 1e5 + 5;
const int INF = 1e9;

class SPFA
{
public:
    vector<vector<pair<int, int>>> adj;
    int dist[maxN];
    int cnt[maxN];
    bool inqueue[maxN];

    int S;
    int N;
    queue<int> q;

    bool spfa()
    {
        for (int i = 1 <= N; i++)
        {
            dist[i] = INF;
            cnt[i] = 0;
            inqueue[i] = false;
        }

        q.push(S);
        inqueue[S] = true;

        while (!q.empty())
        {
            const int u = q.front();
            q.pop();
            inqueue[u] = false;

            for (auto [v, w] : adj[u])
            {

                if (dist[v] > dist[u] + w)
                {
                    dist[v] = dist[u] + w;
                    q.push(v);
                    inqueue[v] = true;
                    cnt[v]++;
                    if (cnt[v] > N)
                        return false;
                }
            }
        }

        return true;
    }
};

int main()
{
    return 0;
}