#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <complex>
#define pb push_back
#define mp make_pair
using namespace std;
const int N=1e5+5;
const double PI=acos(-1);
const double INF=1e15;

int n;
struct point{

 double x,y;

 point() {}
 point(double _x, double _y) { x = _x; y = _y;}

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
}

double dabs(double x)
{
    if(x < 0)
        return -x;
    return x;
}

struct line{
  double a,b;
};

line angle_to_line(point pt,double ang)
{
     line res;

     res.a = tan(ang);
     res.b = pt.y - (pt.x * res.a);

     return res;
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
       if(ang == PI/2 || ang == 3*PI/2)
        return dabs(pt.x - other.pt.x);

       line l,l_other;

       l = angle_to_line(pt, ang);
       l_other = angle_to_line(other.pt, ang);

       double res;
       res = dabs(l_other.b - l.b) / sqrt(l.a * l.a + 1);

       return res;
   }

};

double point_dist(point pt1,point pt2)
{
    return (pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y);
}

double minimal_bounding_box()
{
   reverse(hull.begin()+1,hull.end());

   int a,b,c,d,hull_sz=hull.size();

   a=b=0;
   for(int i=0;i<hull_sz;i++)
   {
      if(hull[i].x < hull[a].x)
        a=i;
      if(hull[i].x > hull[b].x)
        b=i;
   }
   caliper A(hull[a],PI / 2), B(hull[b],3 * PI / 2);

   c=d=0;
   for(int i=0;i<hull_sz;i++)
   {
      if(hull[i].y < hull[c].y)
        c=i;
      if(hull[i].y > hull[d].y)
        d=i;
   }
   caliper C(hull[c],PI), D(hull[d],0);


   double area=INF;
   double done=0;
   while(done <= PI/2)
   {
      area=min(area, A.dist(B) * C.dist(D));

     // cerr<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
     // cerr<<A.dist(B)<<" "<<C.dist(D)<<endl;

      double theta = A.angle_to(hull[(a + 1) % hull_sz]);
      theta=min(theta, B.angle_to(hull[(b + 1) % hull_sz]));
      theta=min(theta, C.angle_to(hull[(c + 1) % hull_sz]));
      theta=min(theta, D.angle_to(hull[(d + 1) % hull_sz]));

      if(A.angle_to(hull[(a + 1) % hull_sz]) == theta)
      {
         A.move_to( hull[(a + 1) % hull_sz] );
         a = (a + 1) % hull_sz;
      }
      else if(B.angle_to(hull[(b + 1) % hull_sz]) == theta)
      {
         B.move_to( hull[(b + 1) % hull_sz] );
         b = (b + 1) % hull_sz;
      }
      else if(C.angle_to(hull[(c + 1) % hull_sz]) == theta)
      {
         C.move_to( hull[(c + 1) % hull_sz] );
         c = (c + 1) % hull_sz;
      }
      else if(D.angle_to(hull[(d + 1) % hull_sz]) == theta)
      {
         D.move_to( hull[(d + 1) % hull_sz] );
         d = (d + 1) % hull_sz;
      }

      A.rotate(theta);
      B.rotate(theta);
      C.rotate(theta);
      D.rotate(theta);

      done+=theta;
   }

   return area;
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

    double ans = minimal_bounding_box();

    cerr<<setprecision(11);
    cerr<<ans<<endl;

    return 0;
}

