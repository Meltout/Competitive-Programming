#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#define pb push_back
#define mp make_pair
using namespace std;
const int N=1e5+5;
const double PI=acos(-1);

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

   for(i=1;i<=min(3,n);i++)
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

 /*  cerr<<endl;
   for(i=0;i<hull.size();i++)
   {
       cerr<<hull[i].x<<" "<<hull[i].y<<endl;
   } */
}

struct caliper{

   point pt; /// the point on which the caliper hangs
   double ang; /// angle of counter-clockwise rotation

   caliper() {}
   caliper(point _pt, double _ang) {pt = _pt; ang = _ang;}

   double angle_to(point pt2)
   {
      double x = ang - atan2(pt2.y - pt.y, pt2.x - pt.x);

      while(x >= PI) x -= 2 * PI;
      while(x <= -PI) x += 2 * PI;

      return x;
   }

   void rotate(double by)
   {
      ang -= by;
      while(ang < 0) ang += 2 * PI;
   }

   void move_to(point pt2)
   {
       pt=pt2;
   }

   double dist(const caliper &other)
   {
       double res=(pt.x - other.pt.x) * (pt.x - other.pt.x) + (pt.y - other.pt.y) * (pt.y - other.pt.y);

       return sqrt(res);
   }

};

double diameter_hull()
{
   int a,b,hull_sz=hull.size();
   double theta;

   reverse(hull.begin()+1,hull.end());

   a=b=0;
   for(int i=0;i<hull_sz;i++)
   {
      if(hull[i].x < hull[a].x)
        a=i;
      if(hull[i].x > hull[b].x)
        b=i;
   }

   caliper A(hull[a],PI / 2), B(hull[b],3 * PI / 2);

   if(hull_sz == 2)
   {
       return A.dist(B);
   }

   double diam=0;
   double done=0;
   while(done <= PI)
   {
      diam=max(diam,A.dist(B));

      if(A.angle_to(hull[(a + 1) % hull_sz]) <= B.angle_to( hull[(b + 1) % hull_sz] ))
      {
         theta = A.angle_to( hull[(a + 1) % hull_sz] );
         A.move_to( hull[(a + 1) % hull_sz] );
         a = (a + 1) % hull_sz;
      }
      else
      {
         theta = B.angle_to( hull[(b + 1) % hull_sz] );
         B.move_to( hull[(b + 1) % hull_sz] );
         b = (b + 1) % hull_sz;
      }

      A.rotate(theta);
      B.rotate(theta);

      done+=theta;
   }

   return diam;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int i;

    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>p[i].x>>p[i].y;
    }

    convex_hull();

    double ans = diameter_hull();

    cout<<setprecision(11);
    cout<<ans<<endl;

    return 0;
}


/*

6
0 0
1 0
2 1
1 2
0 2
-1 1

*/
