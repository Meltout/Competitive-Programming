#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
using namespace std;
const double PI=acos(-1);

typedef complex<double> base;

int rev(int x,int log)
{
   int res=0;
   for(int i=0;i<log;i++)
      if(x&(1 << i))
          res|=(1<<(log - 1 - i));

   return res;
}

void FFT(vector <base> &a, bool inverse)
{
   int n=a.size();

   int logn=0;
   while((1 << logn) < n)
    logn++;

   for(int i=0;i<n;i++)
   {
       if(i < rev(i,logn))
        swap(a[i],a[rev(i,logn)]);
   }

   for(int len=2;len<=n;len<<=1)
   {
       double ang=2*PI/len;
       if(inverse)
        ang=-ang;

       base wlen=(cos(ang),sin(ang));
       for(int i=0;i<n;i+=len)
       {
         base w=(1,0);
         for(int j=0;j<len/2;j++)
         {
            base u,v;
            u=a[i+j];
            v=w*a[i+j+len/2];

            a[i+j]=u+v;
            a[i+j+len/2]=u-v;

            w*=wlen;
         }
       }
   }

   if(inverse)
     for(int i=0;i<n;i++)
       a[i]/=n;
}


int main()
{



    return 0;
}
