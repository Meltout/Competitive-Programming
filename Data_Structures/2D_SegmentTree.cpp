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

struct SegmentTree_2D{

    int val[4 * N][4 * N];
    int arr[N][N];
    int n, m;
    int nothing;

    int combine(int x, int y)
    {
        return x + y;
    }

    void build_y(int posx, int lowx, int highx, int posy, int lowy, int highy)
    {
        if(lowy == highy)
        {
            if(lowx == highx)
                val[posx][posy] = arr[lowx][lowy];
            else
                val[posx][posy] = combine(val[posx * 2][posy], val[posx * 2 + 1][posy]);

            return;
        }

        int midy = (lowy + highy) / 2;

        build_y(posx, lowx, highx, posy * 2, lowy, midy);
        build_y(posx, lowx, highx, posy * 2 + 1, midy + 1, highy);

        val[posx][posy] = combine(val[posx][posy * 2], val[posx][posy * 2 + 1]);
    }

    void build_x(int posx, int lowx, int highx)
    {
        if(lowx != highx)
        {
            int midx = (lowx + highx) / 2;
            build_x(posx * 2, lowx, midx);
            build_x(posx * 2 + 1, midx + 1, highx);
        }

        build_y(posx, lowx, highx, 1, 1, m);
    }

    int query_y(int posx, int posy, int lowy, int highy, int ly, int ry)
    {
        if(ly > highy || ry < lowy)
            return nothing;
        if(ly <= lowy && ry >= highy)
            return val[posx][posy];

        int midy = (lowy + highy) / 2;
        return combine(query_y(posx, posy * 2, lowy, midy, ly, ry),
                 query_y(posx, posy * 2 + 1, midy + 1, highy, ly, ry));
    }

    int query_x(int posx, int lowx, int highx, int lx, int rx, int ly, int ry)
    {
        if(lx > highx || rx < lowx)
            return nothing;
        if(lx <= lowx && rx >= highx)
            return query_y(posx, 1, 1, m, ly, ry);

        int midx = (lowx + highx) / 2;
        return combine(query_x(posx * 2, lowx, midx, lx, rx, ly, ry),
                 query_x(posx * 2 + 1, midx + 1, highx, lx, rx, ly, ry));
    }

    void update_y(int posx, int lowx, int highx, int posy, int lowy, int highy, int x, int y, int new_val)
    {
        if(lowy > y || highy < y)
            return;
        if(lowy == highy)
        {
            if(lowx == highx)
                val[posx][posy] = new_val;
            else
                val[posx][posy] = combine(val[posx * 2][posy], val[posx * 2 + 1][posy]);

            return;
        }

        int midy = (lowy + highy) / 2;

        update_y(posx, lowx, highx, posy * 2, lowy, midy, x, y, new_val);
        update_y(posx, lowx, highx, posy * 2 + 1, midy + 1, highy, x, y, new_val);

        val[posx][posy] = combine(val[posx][posy * 2], val[posx][posy * 2 + 1]);
    }

    void update_x(int posx, int lowx, int highx, int x, int y, int new_val)
    {
        if(lowx > x || highx < x)
            return;
        if(lowx != highx)
        {
            int midx = (lowx + highx) / 2;

            update_x(posx * 2, lowx, midx, x, y, new_val);
            update_x(posx * 2 + 1, midx + 1, highx, x, y, new_val);
        }

        update_y(posx, lowx, highx, 1, 1, m, x, y, new_val);
    }


}seg;

void build_tree(int arr[N][N], int n, int m)
{
    seg.n = n;
    seg.m = m;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            seg.arr[i][j] = arr[i][j];

    seg.nothing = 0;
    seg.build_x(1, 1, n);
}

int Query(int lx, int rx, int ly, int ry)
{
    return seg.query_x(1, 1, seg.n, lx, rx, ly, ry);
}

void Update(int x, int y, int new_val)
{
    seg.update_x(1, 1, seg.n, x, y, new_val);
}

int n, m;
int q;
int a[N][N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> n >> m;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
        }
    }

    build_tree(a, n, m);

    cin >> q;
    while(q--)
    {
        int type, new_val;
        int lx, rx, ly, ry;

        cin >> type;

        if(type == 1)
        {
          cin >> lx >> ly >> rx >> ry;
          cout << Query(lx, rx, ly, ry) << endl;
        }
        else
        {
          cin >> lx >> ly >> new_val;
          Update(lx, ly, new_val);
        }

    }

    return 0;
}

