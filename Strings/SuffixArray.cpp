#include <iostream>
#include <algorithm>
#include <string>
#define pb push_back
#define mp make_pair
using namespace std;
const int N=1e5+5;

int n;
string s;

struct SArray{

   int ind;
   int first_half,second_half;

   bool operator <(SArray other) const
   {
       if(first_half != other.first_half)
        return first_half < other.first_half;

       return second_half < other.second_half;
   }
}sa[N],sa_conc[N];

int suff_rank[20][N];

void construct(string _s,SArray _sa[],int _rank[20][N])
{
   int i;

   for(i=0;i<_s.size();i++)
       _rank[0][i]=_s[i]-'$';

   int step,cnt;
   for(step=1,cnt=1;cnt<_s.size();cnt*=2,step++)
   {
       for(i=0;i<_s.size();i++)
       {
          _sa[i].ind=i;
          _sa[i].first_half=_rank[step-1][i];

          if(i + cnt < _s.size())
           _sa[i].second_half=_rank[step-1][i+cnt];
          else
           _sa[i].second_half=-1;

       }

       sort(_sa,_sa+(int)_s.size());

       int cur=0;
       _rank[step][_sa[0].ind]=0;
       for(i=1;i<_s.size();i++)
       {
          if(_sa[i].first_half != _sa[i-1].first_half || _sa[i].second_half != _sa[i-1].second_half)
              cur++;

          _rank[step][_sa[i].ind]=cur;
       }
   }
}

int lcp[N];

int inv_sa[N];
void kasai(string _s,SArray _sa[], int _lcp[])
{
    int i,j;
    int _n=_s.size();

    for(i=0;i<_n;i++)
        inv_sa[_sa[i].ind]=i;


    int k=0;
    for(i=0;i<_n;i++)
    {
       if(inv_sa[i] == _n-1)
       {
          k=0;
          continue;
       }

       j=_sa[inv_sa[i]+1].ind;
       while(i+k<_n && j+k<_n && _s[i+k] == _s[j+k])
           k++;


       _lcp[inv_sa[i]]=k;

       if(k)
        k--;
    }
    _lcp[_n-1]=0;

   /* for(i=0;i<_s.size();i++)
    {
        cerr<<_lcp[i]<<" ";
    }
    cerr<<endl; */
}




int main()
{
   int i,cnt,step;

   cin>>s;

   construct(s,sa,suff_rank);

   kasai(s,sa,lcp);


   return 0;
}

