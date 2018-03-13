#include <iostream>
#include <string>
using namespace std;
int t[101];
void make_table(string a) // precompute
{
 t[0]=-1;
 t[1]=0;
 int pos=2;// the current t that we are calculating
 int cnd=0;// on what position we are in the string a
 while(pos<a.size())
 {
     if(a[pos-1]==a[cnd])
     {
         t[pos]=cnd+1;
         cnd++;
         pos++;
     }
     else
     {
         if(cnd>0)
             cnd=t[cnd];
         else
         {
          t[pos]=0;
          pos++;
         }
     }
 }
}
int main()
{
    int m=0,i=0;  // m=beginning of current "pattern-w" in s
    string s,w;   // searching for w in s;
    getline(cin,s);
    getline(cin,w);
    make_table(w);
  /*  for(i=0;i<w.size();i++)
        cout<<t[i]<<" ";
    cout<<endl;*/
    i=0;
    while(m+i<s.size())   // KMP
    {

        if(s[m+i]==w[i])
        {
         if(i==w.size()-1)
         {
             cout<<m<<endl;
             break;
         }
         i++;
        }
        else
        {
         if(t[i]>-1)
         {
           m=m+i-t[i];
           i=t[i];
         }
         else
         {
           m=m+1;
           i=0;
         }
        }
    }
    return 0;
}


/*

ABC ABCDAB ABCDABCDABDE
ABCDABD

KAPKAPPAPAKAPPA
KAPPA

DDDBCEB
DDB

*/
