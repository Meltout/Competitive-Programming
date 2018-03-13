#include <iostream>
using namespace std;
const int N=1e2+5;

int n,m;

struct fenwick_2D{

   int val[N][N];

   void update(int x,int y,int d) /// adds d to tab[x][y]
   {
       int i,j;

       for(i=x;i<=n;i+=(i & (-i)))
        for(j=y;j<=m;j+=(j & (-j)))
         val[i][j]+=d;

   }

   int query(int x,int y)  /// returns sum of tab[1][1] to tab[x][y]
   {
       int i,j;

       int res=0;

       for(i=x;i>0;i-=(i & (-i)))
        for(j=y;j>0;j-=(j & (-j)))
         res+=val[i][j];

       return res;
   }


   int range_query(int r1,int c1,int r2,int c2) /// lower left and upper right corners of the rectangle we query
   {

       return query(r2,c2) - query(r1-1,c2) - query(r2,c1-1) + query(r1-1,c1-1);

   }



}fen;


int main()
{
    n=m=N;

    fen.update(1,1,5);

    fen.update(2,3,3);

    cout<<fen.query(3,5);




}
