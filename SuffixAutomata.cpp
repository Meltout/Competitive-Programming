#include <map>
#include <iostream>
using namespace std;
const int N=1e5+5;

struct state{

   map <char,int> next;

   int link,len;

};

state st[2*N];
int sz,last;

void sa_init()
{
    sz=0;
    last=0;

    st[0].link=-1;
    st[0].len=0;
    sz++;

    /*
    in case of multiple tests problem

    for(int i=0;i<N*2;i++)
        st[i].next.clear();
    */
}


void sa_extend(char c)
{
    int cur;
    int p,q;
    int clone;

    cur=sz;
    sz++;

    st[cur].len = st[last].len +1;

    p=last;
    while(!st[p].next.count(c))
    {
        st[p].next[c]=cur;

        p=st[p].link;

        if(p==-1)
            break;
    }

    if(p==-1)
        st[cur].link=0;
    else
    {
        q=st[p].next[c];

        if(st[p].len + 1 == st[q].len)
            st[cur].link=q;
        else
        {
            clone=sz;
            sz++;

            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;

            while(st[p].next[c] == q)
            {
                st[p].next[c]=clone;

                p=st[p].link;

                if(p==-1)
                    break;
            }

            st[q].link = clone;
            st[cur].link = clone;

        }

    }

    last=cur;

}

int main()
{
    string s;
    cin>>s;

    sa_init();
    for(int i=0;i<s.size();i++)
    {
        sa_extend(s[i]);
    }
    cerr<<sz<<endl;
}
