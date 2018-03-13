#include <iostream>
#include <string>
using namespace std;
const int N=1e3+5;

string s,T;

int P[N];

int main()
{
  int i;

  cin>>s;

  T+='#';
  for(i=0;i<s.size();i++)
  {
      T+=s[i];
      T+='#';
  }


  int C=0,R=-1,rad;

  for (i=0;i<T.length();i++)
  {
    if(i<=R)
        rad=min(P[2*C-i], R-i)+1;
    else
        rad=0;

    // Try to extend
    while (i+rad < T.length() && i-rad >= 0 && T[i-rad] == T[i+rad])
    {
        rad++;
    }

    P[i]=rad-1;
    if (i + rad - 1 > R)
    {
        C=i;
        R=i+rad-1;
    }
  }

  for(i=0;i<T.size();i++)
    cout<<T[i]<<" ";
  cout<<endl;
  for(i=0;i<T.size();i++)
    cout<<P[i]<<" ";


  return 0;
}
