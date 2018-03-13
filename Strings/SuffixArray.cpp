#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const int N=1e5+5;

int n;
string s;

int suff_rank[20][N];

struct myTuple{

   int ind;
   int first_half;
   int second_half;

   bool operator <(myTuple other) const
   {
       if(first_half != other.first_half)
        return first_half < other.first_half;

       return second_half < other.second_half;
   }

}sa[N];

int lcp[N],inv_sa[N];
void kasai()
{
   int i,j;

   for(i=0;i<n;i++)
     inv_sa[sa[i].ind]=i;

   int k=0;
   for(i=0;i<n;i++)
   {
      if(inv_sa[i] == n-1)
      {
          k=0;
          continue;
      }

      j=sa[inv_sa[i]+1].ind;

      while(i+k<n && j+k<n && s[i+k] == s[j+k])
        k++;

      lcp[inv_sa[i]]=k;

      if(k)
        k--;
   }

   for(i=0;i<n;i++)
   {
       cerr<<lcp[i]<<" ";
   }
   cerr<<endl;
}

pair <int,int> in_segment(string t)
{
   int low,high,mid;
   pair <int,int> res=mp(-1,-1);

   low=0;
   high=n-1;
   while(low <= high)
   {
       mid=(low+high)/2;
       int j=sa[mid].ind;

       int bigger=0;
       for(int i=0;i<t.size();i++)
       {
           if(j+i >= n)
           {
               bigger=1;
               break;
           }

           if(t[i] > s[j+i])
           {
            bigger=1;
            break;
           }
           if(t[i] < s[j+i])
           {
            bigger=-1;
            break;
           }
       }

       if(bigger == 0)
       {
           res.first=mid;
           high=mid-1;
       }

       if(bigger == -1)
           high=mid-1;

       if(bigger == 1)
           low=mid+1;
   }

   low=0;
   high=n-1;
   while(low <= high)
   {
       mid=(low+high)/2;
       int j=sa[mid].ind;

       int bigger=0;
       for(int i=0;i<t.size();i++)
       {
           if(j+i >= n)
           {
               bigger=1;
               break;
           }

           if(t[i] > s[j+i])
           {
            bigger=1;
            break;
           }
           if(t[i] < s[j+i])
           {
            bigger=-1;
            break;
           }
       }

       if(bigger == 0)
       {
           res.second=mid;
           low=mid+1;
       }

       if(bigger == -1)
           high=mid-1;

       if(bigger == 1)
           low=mid+1;
   }

   return res;
}

int main()
{
   int i,cnt,step;

   cin>>s;
   n=s.size();

   for(i=0;i<n;i++)
       suff_rank[0][i]=s[i]-'$';

   for(cnt=1,step=1;cnt<n;cnt*=2,step++)
   {
      for(i=0;i<n;i++)
      {
          sa[i].ind=i;
          sa[i].first_half=suff_rank[step-1][i];

          if(i + cnt < n)
            sa[i].second_half=suff_rank[step-1][i+cnt];
          else
            sa[i].second_half=-1;
      }

      sort(sa,sa+n);

      suff_rank[step][sa[0].ind]=0;

      int cur=0;
      for(i=1;i<n;i++)
      {
          if(sa[i].first_half != sa[i-1].first_half || sa[i].second_half != sa[i-1].second_half)
            cur++;

          suff_rank[step][sa[i].ind]=cur;
      }
   }

   for(i=0;i<n;i++)
   {
       cerr<<sa[i].ind<<" ";
   }
   cerr<<endl;

   kasai();


   return 0;
}

