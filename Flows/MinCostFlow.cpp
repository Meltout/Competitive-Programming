#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define ll long long
using namespace std;
const int N = 305;
const int INF = 1e9;

struct edge{

    int from, to;
    int cap, flow, cost;

    edge() {}
    edge(int _from, int _to, int _cap, int _cost) {from = _from; to = _to; cap = _cap; flow = 0; cost = _cost;}
};
vector <edge> e;

vector <int> g[N];
void add_edge(int u, int v, int cap, int cost)
{
    g[u].pb((int)e.size());
    e.pb(edge(u, v, cap, cost));
    g[v].pb((int)e.size());
    e.pb(edge(v, u, 0, -cost));
}

int nodes = N - 1, s = N - 1, t = N - 2;
int pred[N], is_inside[N], dist[N];
queue <int> Q;
bool SPFA()
{
    for(int i = 1; i <= nodes; i++)
        dist[i] = INF;
    dist[t] = INF;
    dist[s] = 0;

    Q.push(s);
    is_inside[s] = true;
    while(!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        is_inside[u] = false;

        for(int id: g[u])
        {
            int v = e[id].to;
            if(e[id].cap > e[id].flow && dist[u] + e[id].cost < dist[v])
            {
                dist[v] = dist[u] + e[id].cost;
                pred[v] = id;

                if(!is_inside[v])
                {
                    Q.push(v);
                    is_inside[v] = true;
                }
            }
        }
    }

    return (dist[t] != INF);
}

pair <int, ll> min_cost_flow(int F = INF)
{
    int flow = 0;
    ll cost = 0;
    while(SPFA() && flow < F)
    {
        int mn_flow = F - flow;

        int u = t;
        while(u != s)
        {
            mn_flow = min(mn_flow, e[pred[u]].cap - e[pred[u]].flow);
            u = e[pred[u]].from;
        }

        u = t;
        while(u != s)
        {
            e[pred[u]].flow += mn_flow;
            cost += 1LL * mn_flow * e[pred[u]].cost;
            e[pred[u] ^ 1].flow -= mn_flow;
            u = e[pred[u]].from;
        }
        flow += mn_flow;

    }

    return {flow, cost};
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);





    return 0;
}
