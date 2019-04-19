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
#define ll long long
using namespace std;


const double PI = acos(-1);
typedef complex<double> base;

int rev(int x, int log_n)
{
    int res = 0;
    for(int j = 0; j < log_n; j++)
        if(x & (1 << j))
            res |= (1 << (log_n - 1 - j));
    return res;
}

void fft(vector <base> &a, bool invert)
{
    int n = (int)a.size(), log_n = 0;
    while((1 << log_n) < n)
        log_n++;

    for(int i = 0; i < n; i++)
        if(i < rev(i, log_n))
            swap(a[i], a[rev(i, log_n)]);

    for(int len = 2; len <= n; len *= 2)
    {
        double ang = (2 * PI / len) * (invert ? -1 : 1);
        base wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len)
        {
            base w(1, 0);
            for(int j = 0; j < len / 2; j++)
            {
                base u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if(invert)
        for(int i = 0; i < n; i++)
            a[i] /= n;
}

vector <ll> multiply(const vector <int> &a, const vector <int> &b)
{
    vector <base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < max((int)a.size(), (int)b.size()))
        n *= 2;
    n *= 2;

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for(int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector <ll> res(n);
    for(int i = 0; i < n; i++)
        res[i] = (ll)(fa[i].real() + 0.5);

    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int tests;
    int n;
    vector <int> a, b;

    cin >> tests;
    while(tests--)
    {
        cin >> n;
        a.resize(n + 1), b.resize(n + 1);
        for(int i = 0; i <= n; i++)
            cin >> a[i];
        for(int i = 0; i <= n; i++)
            cin >> b[i];

        vector <ll> res = multiply(a, b);
        for(int i = 0; i <= 2 * n; i++)
            cout << res[i] << " ";
        cout << endl;
    }


    return 0;
}
