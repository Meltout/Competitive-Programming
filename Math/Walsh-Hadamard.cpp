#include <iostream>
using namespace std;
const int N=64;

void FWHT(int P[], bool inverse)
{
    for (int len = 1; 2 * len <= N; len <<= 1)
    {
        for (int i = 0; i < N; i += 2 * len)
        {
            for (int j = 0; j < len; j++)
            {
               int u = P[i + j];
               int v = P[i + len + j];
                P[i + j] = u + v;
                P[i + len + j] = u - v;
            }
        }
    }

    if (inverse)
    {
        for (int i = 0; i < N; i++)
            P[i] = P[i] / N;
    }
}

int main()
{


  return 0;
}
