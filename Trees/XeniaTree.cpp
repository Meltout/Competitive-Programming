#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#define mp make_pair
#define pb push_back
using namespace std;
const int N = 1e5 + 5;
const int INF = 1e9;

int n, Q;
vector <int> nb[N];

bool vis[N];
int link[N], tree_sz[N], cnt_vert;

void pre_dfs(int v, int par = -1)
{
    cnt_vert++;
    tree_sz[v] = 1;
    for(int u: nb[v])
    {
        if(!vis[u] && u != par)
        {
            pre_dfs(u, v);
            tree_sz[v] += tree_sz[u];
        }
    }
}

int centroid(int v, int par = -1)
{
    for(int u: nb[v])
    {
        if(!vis[u] && u != par && tree_sz[u] > cnt_vert / 2)
            return centroid(u, v);
    }

    return v;
}

void decompose(int v, int par = -1)
{
    cnt_vert = 0;
    pre_dfs(v);

    int centr = centroid(v);
    link[centr] = par;

    vis[centr] = true;
    for(int u: nb[centr])
    {
        if(!vis[u])
            decompose(u, centr);
    }
    vis[centr] = false;
}


int from[N], to[N], timer;
int dep[N];
int sparse[N][30];

void DFS_LCA(int v, int par = -1)
{
    from[v] = to[v] = ++timer;
    sparse[v][0] = (par == -1) ? v : par;
    dep[v] = dep[par] + 1;

    for(int u: nb[v])
    {
        if(u != par)
        {
            DFS_LCA(u, v);
            to[v] = max(to[v], to[u]);
        }
    }
}

void calc_sparse()
{
    for(int i = 1; i < 30; i++)
        for(int j = 1; j <= n; j++)
            sparse[j][i] = sparse[sparse[j][i - 1]][i - 1];
}

bool in_subtree(int u, int v)
{
    return (from[u] <= from[v] && to[u] >= from[v]);
}

int LCA(int u, int v)
{
    if(dep[u] > dep[v])
        swap(u, v);

    if(in_subtree(u, v))
        return u;

    for(int i = 29; i >= 0; i--)
    {
        if(!in_subtree(sparse[u][i], v))
            u = sparse[u][i];
    }

    return sparse[u][0];
}

int dist(int u, int v)
{
    return dep[u] + dep[v] - 2 * dep[LCA(u, v)];
}

int ans[N];

void paint(int v)
{
    int u = v;
    while(u != -1)
    {
        ans[u] = min(ans[u], dist(u, v));
        u = link[u];
    }
}

int query(int v)
{
    int res = INF;

    int u = v;
    while(u != -1)
    {
        res = min(res, ans[u] + dist(u, v));
        u = link[u];
    }

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int i;
    int t, u, v;

    cin >> n >> Q;
    for(i = 1; i < n; i++)
    {
        cin >> u >> v;

        nb[u].pb(v);
        nb[v].pb(u);
    }

    DFS_LCA(1);
    calc_sparse();

    decompose(1);

    for(i = 1; i <= n; i++)
        ans[i] = INF;

    paint(1);
    while(Q--)
    {
        cin >> t >> v;

        if(t == 1)
        {
            paint(v);
        }
        if(t == 2)
        {
            cout << query(v) << endl;
        }
    }

    return 0;
}
