#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#define pb push_back
#define mp make_pair
using namespace std;
const int N = 1e2 + 5;
const int INF = 1e9;

int n;

struct edge{

    int u, v, cap, flow;

    edge() {}
    edge(int _u, int _v, int _cap, int _flow) {u = _u; v = _v; cap = _cap; flow = _flow;}
};

int s, t, ptr[N], q[N], d[N];
vector <edge> e;
vector <int> g[N];

void add_edge(int u, int v, int cap)
{
    edge e1 = {u, v, cap, 0};
    edge e2 = {v, u, 0, 0};

    g[u].pb((int)e.size());
    e.pb(e1);
    g[v].pb((int)e.size());
    e.pb(e2);
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
        for(int i = 0; i < g[v].size(); i++)
        {
            int id = g[v][i];
            int to = e[id].v;

            if(d[to] == -1 && e[id].flow < e[id].cap)
            {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }

    return (d[t] != -1);
}

int DFS(int v, int flow)
{
    if(!flow)   return 0;
    if(v == t)  return flow;
    for(; ptr[v] < g[v].size(); ptr[v]++)
    {
        int id = g[v][ptr[v]];
        int to = e[id].v;
        if(d[to] != d[v] + 1)
            continue;

        int pushed = DFS(to, min(flow, e[id].cap - e[id].flow));
        if(pushed)
        {
            e[id].flow += pushed;
            e[id ^ 1].flow -= pushed;
            return pushed;
        }
    }

    return 0;
}

int flow;
int Dinitz()
{
    while(BFS())
    {
        memset(ptr, 0, sizeof(ptr));
        while(1)
        {
            int pushed = DFS(s, INF);
            if(pushed == 0)
                break;

            flow += pushed;
        }
    }

    return flow;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);




    return 0;
}
