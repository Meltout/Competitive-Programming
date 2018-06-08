#include <iostream>
#include <vector>
using namespace std;
const int N = 1e5 + 5;

vector <int> nb[N];

int link[N];
int tree_sz[N], cnt_vert;
bool vis[N];

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
