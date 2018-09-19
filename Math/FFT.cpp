#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#define pb push_back
#define mp make_pair
using namespace std;

int rev(int x,int log)
{
   int res = 0;
   for(int i = 0; i < log; i++)
      if(x & (1 << i))
          res |= (1 << (log - 1 - i));

   return res;
}

void FFT(vector <base> &a, bool inverse)
{
   int n = (int)a.size();

   int logn = 0;
   while((1 << logn) < n)
    logn++;

   for(int i = 0; i < n; i++)
   {
       if(i < rev(i, logn))
        swap(a[i], a[rev(i, logn)]);
   }

   for(int len = 2; len <= n; len <<= 1)
   {
       double ang =  2.0 * PI / len;
       if(inverse)
        ang = -ang;

       base wlen(cos(ang), sin(ang));
       for(int i = 0; i < n; i += len)
       {
         base w(1);
         for(int j = 0; j < len / 2; j++)
         {
            base u, v;
            u = a[i + j];
            v = a[i + j + len / 2] * w  ;

            a[i + j] = u + v;
            a[i + j + len / 2]= u - v;

            w *= wlen;
         }
       }
   }

   if(inverse)
     for(int i = 0; i < n; i++)
       a[i] /= n;
}

void multiply (const vector<int> &a, const vector<int> &b, vector<int> &res)
{
	vector<base> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
	size_t n = 1;
	while (n < max (a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize (n),  fb.resize (n);

	FFT (fa, false),  FFT (fb, false);
	for (size_t i=0; i<n; ++i)
		fa[i] *= fb[i];
	FFT (fa, true);

	res.resize (n);
	for (size_t i=0; i<n; ++i)
		res[i] = int (fa[i].real() + 0.5);

    for(int i = 0; i < n; i++)
        cout << res[i] << " ";
    cout << endl;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);




    return 0;
}

