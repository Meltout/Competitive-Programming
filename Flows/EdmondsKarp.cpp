#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
using namespace std;
vector <int> nb[101];
int c[101][101];
int f[101][101];
bool vis[101];
int pred[101];
int n,m,s,t;
int flow=0;
bool BFS(int s)
{
  int i,v;
  for(i=1;i<=n;i++)
  {
    vis[i]=false;
    pred[i]=0;
  }
  queue <int> q;
  q.push(s);
  vis[s]=true;
  while(!q.empty() && !vis[t])
  {
   v=q.front();
   q.pop();
   for(i=0;i<nb[v].size();i++)
   {
       if(c[v][nb[v][i]]-f[v][nb[v][i]]>0 && !vis[nb[v][i]])
       {
           vis[nb[v][i]]=true;
           pred[nb[v][i]]=v;
           q.push(nb[v][i]);
       }
   }
  }
  return vis[t];
}
void update_flow()
{
    int v=t,u,fmin=10000;
    while(v!=s)
    {
        u=pred[v];
        if(fmin>c[u][v]-f[u][v])
            fmin=c[u][v]-f[u][v];
        v=pred[v];
    }
    v=t;
    while(v!=s)
    {
        u=pred[v];
        f[u][v]=f[u][v]+fmin;
        f[v][u]=f[v][u]-fmin;
        v=pred[v];
    }
    flow=flow+fmin;
}
int main()
{
    int u,v,x;
    cin>>n>>m;
    int i;
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&x);
        c[u][v]=x;
        nb[u].push_back(v);
        nb[v].push_back(u);
    }
    cin>>s>>t;
    while(BFS(s))
    {
        update_flow();
        cout<<flow<<endl;
    }
    return 0;
}


/*

8 15
1 2 10
1 3 5
1 4 15
2 3 4
2 5 9
2 6 15
3 4 4
3 6 8
4 7 16
5 6 15
5 8 10
6 7 15
6 8 10
7 3 6
7 8 10
1 8

*/
