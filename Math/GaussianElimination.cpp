#include <iostream>
#include <vector>
using namespace std;
const int N = 105;
const double EPS = 1e-9;

double abs(double x)
{
    if(x < 0)
        return -x;
    return x;
}

vector <double> Gauss(vector< vector <double> > &a) /// returns empty vector if no solution
{
    int n = a.size(), m = (int)a[0].size() - 1;

    vector <int> where(m, -1);

    for(int col = 0, row = 0; col < m && row < n; col++)
    {
        int sel = row;
        for(int i = row; i < n; i++)
        {
            if(abs(a[i][col]) > abs(a[sel][col]))
                 sel = i;
        }

        if(abs(a[sel][col]) < EPS)
            continue;

        for(int i = col; i <= m; i++)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for(int i = 0; i < n; i++)
        {
            if(i != row)
            {
                if(abs(a[i][col]) < EPS)
                    continue;

                double c = a[i][col] / a[row][col];
                for(int j = col; j <= m; j++)
                    a[i][j] -= a[row][j] * c;
            }
        }

        row++;
    }

    vector <double> ans(m, 0);

    for(int i = 0; i < m; i++)
       if(where[i] != -1)
          ans[i] = a[where[i]][m] / a[where[i]][i];


    for(int i = 0; i < n; i++)
    {
        double sum = a[i][m];
        for(int j = 0; j < m; j++)
            sum -= a[i][j] * ans[j];

        if(abs(sum) > EPS)
            return vector <double>();
    }

    return ans;
}

