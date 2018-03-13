#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
const int N=5e4+5;

int n,m,p;
vector <int> nb[2*N];

int match[2*N];
int vis[2*N];

int timestamp;

bool kuhn(int v)
{
    int i;

    if(vis[v]==timestamp)
        return false;
    vis[v]=timestamp;

    for(i=0;i<nb[v].size();i++)
    {
        int to=match[nb[v][i]];

        if(to==-1)
        {
            match[nb[v][i]]=v;

            return true;
        }
        else
        {
            if(kuhn(to))
            {
                match[nb[v][i]]=v;

                return true;
            }
        }

    }

    return false;

}


int main()
{
    int i;
    int u,v;
    int matches=0;

    cin>>n>>m>>p;
    for(i=1;i<=p;i++)
    {
        scanf("%d%d",&u,&v);
        v+=n;

        nb[u].push_back(v);
        nb[v].push_back(u);

    }


    memset(match,-1,sizeof(match));
    for(i=1;i<=n;i++)
    {
        timestamp++;

        if(kuhn(i))
            matches++;
    }


    printf("%d\n",matches);


    return 0;
}

/*

5 4 6
5 2
1 2
4 3
3 1
2 2
4 4

*/
