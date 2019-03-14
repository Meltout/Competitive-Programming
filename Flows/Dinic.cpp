#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#define pb push_back
#define mp make_pair
#define ll long long
using namespace std;
const int N = 5e3 + 5;
const int INF = 1e9;

struct flow_edge{

    int u, v, cap, flow;
    flow_edge() {}
    flow_edge(int _u, int _v, int _cap, int _flow) {u = _u; v = _v; cap = _cap; flow = _flow;}
};

int s, t, ptr[N], q[N], d[N];
vector <flow_edge> e;
vector <int> g[N];

void add_edge(int u, int v, int cap, int flow = 0)
{
    g[u].pb((int)e.size());
    e.pb({u, v, cap, flow});

    g[v].pb((int)e.size());
    e.pb({v, u, 0, 0});
}

bool BFS()
{
    int qh = 0, qt = 0;
    q[qt++] = s;
    memset(d, -1, sizeof(d));
    d[s] = 0;
    while(qh < qt && d[t] == -1)
    {
        int v = q[qh++];
        for(auto id: g[v])
        {
            int to = e[id].v;
            if(d[to] == -1 && e[id].flow < e[id].cap)
            {
                d[to] = d[v] + 1;
                q[qt++] = to;
            }
        }
    }

    return (d[t] != -1);
}

int DFS(int v, int pushed)
{
    if(!pushed)
        return 0;
    if(v == t)
        return pushed;
    for(; ptr[v] < g[v].size(); ptr[v]++)
    {
        int id = g[v][ptr[v]];
        int to = e[id].v;
        if(d[to] != d[v] + 1 || e[id].flow >= e[id].cap)
            continue;

        int tried = DFS(to, min(pushed, e[id].cap - e[id].flow));
        if(tried)
        {
            e[id].flow += tried;
            e[id ^ 1].flow -= tried;
            return tried;
        }
    }

    return 0;
}

long long Dinic()
{
    long long flow = 0;
    while(BFS())
    {
        memset(ptr, 0, sizeof(ptr));
        while(int pushed = DFS(s, INF))
            flow += pushed;
    }
    return flow;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);





    return 0;
}
