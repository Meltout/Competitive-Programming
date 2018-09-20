#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <complex>
#include <cmath>
#define pb push_back
#define mp make_pair
using namespace std;
const double PI = acos(-1);
typedef complex<double> base;


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
            v = a[i + j + len / 2] * w;

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


template <class T>
struct Polynomial{

    vector <T> a;
    int degree; /// a.size() + 1

    Polynomial() {a = vector <T>(); degree = 0; }
    Polynomial(int D) { a = vector <T>(D + 1, 0); degree = D; }

    Polynomial& operator = (const Polynomial &P)
    {
        this->a.clear();
        this->degree = 0;

        this->a = P.a;
        this->degree = P.degree;

        return *this;
    }

    void resize(const int D)
    {
        this->a.clear();
        this->degree = 0;

        this->a = vector <T>(D + 1, 0);
        this->degree = D;
    }

    T& operator [] (const int p)
    {
        return this->a[p];
    }
    T operator [] (const int p) const
    {
        return this->a[p];
    }

    Polynomial& operator *= (const Polynomial &P) /// FFT, no MOD
    {
        vector <base> A(this->a.begin(), this->a.end()), B(P.a.begin(), P.a.end());
        int n = 1;

        while(n < max(A.size(), B.size()))
            n *= 2;
        n *= 2;

        A.resize(n); B.resize(n);

        FFT(A, false);
        FFT(B, false);

        for(int i = 0; i < n; i++)
            A[i] *= B[i];

        FFT(A, true);

        Polynomial <int> solution(this->degree + P.degree);
        for(int i = 0; i <= solution.degree; i++)
            solution[i] = (int)(A[i].real() + 0.5);

        *this = solution;

        return *this;
    }

    friend ostream& operator <<(ostream &stream, const Polynomial &P)
    {
        stream << P.degree << endl;
        for(int i = 0; i <= P.degree; i++)
        {
            stream << P[i];
            if(i < P.degree)
                stream << " ";
        }
       // stream << endl;
        return stream;
    }
};



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);





    return 0;
}
