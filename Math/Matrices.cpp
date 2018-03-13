#include <iostream>
using namespace std;
const int N=15;

int helper[N][N];
void mul(int a[N][N],int b[N][N]) /// stores the result in helper
{
   int i,j,k;

   for(i=1;i<N;i++)
   {
       for(j=1;j<N;j++)
       {
           helper[i][j]=0;
           for(k=1;k<N;k++)
           {
               helper[i][j]+=a[i][k]*b[k][j];
           }
       }
   }
}

void transfer(int a[N][N]) /// transfers helper to a
{
    int i,j;
    for(i=1;i<N;i++)
    {
        for(j=1;j<N;j++)
        {
            a[i][j]=helper[i][j];
        }
    }
}



int main()
{



    return 0;
}
