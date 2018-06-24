#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;

int n;
vector <int> nb[N];

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
