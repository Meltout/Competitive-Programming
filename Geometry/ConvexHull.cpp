#include <iostream>
#include <algorithm>
#include <vector>
#define pb push_back
using namespace std;
const int N=1e5+5;

int n;
struct point{

 double x,y;

}p[N];


int orientation(point a,point b,point c)
{
    double res=(b.y-a.y)*(c.x-b.x) - (c.y-b.y)*(b.x-a.x);

    if(res > 0) /// clockwise
        return 1;
    if(res < 0)
        return -1;
    if(res == 0)
        return 0;
}

bool angle_sort(point s,point t)
{
    if(orientation(p[1],s,t) == 0)
        return s.x < t.x;

    if(orientation(p[1],s,t) == -1)
        return true;
    return false;
}

vector <point> hull;
void convex_hull()
{
   int i;

   for(i=2;i<=n;i++)
   {
      if(p[i].y < p[1].y)
         swap(p[i],p[1]);
      if(p[i].y == p[1].y)
        if(p[i].x < p[1].x)
          swap(p[1],p[i]);
   }

   sort(p+2,p+n+1,angle_sort);

   for(i=1;i<=3;i++)
    hull.pb(p[i]);

   for(i=4;i<=n;i++)
   {
       int sz=hull.size();
       while(hull.size() > 1 && orientation(hull[sz-2],hull[sz-1],p[i]) != -1)
       {
           hull.pop_back();
           sz--;
       }
       hull.pb(p[i]);
   }
}
