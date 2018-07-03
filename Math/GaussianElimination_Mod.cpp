#include <iostream>
#include <vector>
using namespace std;

long long fast_pow(long long base, int e, long long MOD)
{
    if(e == 1)
        return base % MOD;

    long long ans = fast_pow(base, e / 2, MOD);
    ans = (ans * ans) % MOD;

    if(e & 1)
        ans = (ans * base) % MOD;

    return ans;
}

long long inv(long long x, long long MOD)
{
    return fast_pow(x, MOD - 2, MOD);
}

vector <long long> Gauss_Mod(vector< vector <long long> > &a, long long MOD) /// returns empty vector if no solution
{
    int n = a.size(), m = (int)a[0].size() - 1;

    for(int i = 0; i < n; i++)
        for(int j = 0; j <= m; j++)
            a[i][j] = ((a[i][j] % MOD) + MOD) % MOD;


    vector <int> where(m, -1);
    for(int col = 0, row = 0; col < m && row < n; col++)
    {
        int sel = row;
        for(int i = row; i < n; i++)
        {
            if(a[i][col] > a[sel][col])
                 sel = i;
        }

        if(a[sel][col] == 0)
            continue;

        for(int i = col; i <= m; i++)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for(int i = 0; i < n; i++)
        {
            long long c_inv = inv(a[row][col], MOD);
            if(i != row)
            {
                if(a[i][col] == 0)
                    continue;

                long long c = (a[i][col] * c_inv) % MOD;
                for(int j = col; j <= m; j++)
                    a[i][j] = ((a[i][j] - ((a[row][j] * c) % MOD) % MOD) + MOD) % MOD;
            }
        }

        row++;
    }

    vector <long long> ans(m, 0);

    for(int i = 0; i < m; i++)
       if(where[i] != -1)
          ans[i] = (a[where[i]][m] * inv(a[where[i]][i], MOD)) % MOD;


    for(int i = 0; i < n; i++)
    {
        long long sum = a[i][m] % MOD;
        for(int j = 0; j < m; j++)
            sum = (sum - ((a[i][j] * ans[j]) % MOD) + MOD) % MOD;

        if(sum != 0)
            return vector <long long>();
    }


    return ans;
}


