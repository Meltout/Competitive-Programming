#include <iostream>
#include <random>
using namespace std;

random_device rd;
mt19937 mt(rd());

struct node{

  int key,prior;
  int cnt;

  node* l;
  node* r;

  node() {}

  node(int _key,int _prior)
  {
      key=_key;
      prior=_prior;
      l=NULL;
      r=NULL;

      cnt=1;
  }

};
typedef node* node_ptr;

struct treap{

    node_ptr root;

    int cnt(node_ptr t)
    {
        if(t == NULL)
            return 0;
        else
            return t->cnt;
    }

    void update_cnt(node_ptr t)
    {
        t->cnt=1+cnt(t->l)+cnt(t->r);
    }

    void split(node_ptr t,int key,node_ptr &l,node_ptr &r)
    {
        if(t == NULL)
        {
            l=r=NULL;

            return;
        }

        if(key < t->key)
        {
            split(t->l,key,l,t->l);

            r=t;
        }
        else
        {
            split(t->r,key,t->r,r);

            l=t;
        }

        update_cnt(t);
    }

    void insert(node_ptr &t,node_ptr x)
    {
        if(t == NULL)
        {
            t=x;

            return;
        }

        if(x->prior > t->prior)
        {
        split(t,x->key,x->l,x->r);

        t=x;
        }
        else
            if(x->key < t->key)
                insert(t->l,x);
            else
                insert(t->r,x);

        update_cnt(t);
    }

    void merge(node_ptr &t,node_ptr l,node_ptr r)
    {
        if(l == NULL || r == NULL)
        {
            if(r == NULL)
                t=l;
            else
                t=r;
            return;
        }

        if(l->prior > r->prior)
        {
            merge(l->r,l->r,r);

            t=l;
        }
        else
        {
            merge(r->l,l,r->l);

            t=r;
        }

        update_cnt(t);
    }

    void erase(node_ptr &t,int key)
    {
        if(t->key == key)
        {
            merge(t,t->l,t->r);
            return;
        }

        if(key < t->key)
            erase(t->l,key);
        else
            erase(t->r,key);

        update_cnt(t);
    }

    node_ptr find(node_ptr t,int key)
    {
        if(t == NULL || t->key == key)
            return t;

        if(key < t->key)
            find(t->l,key);
        else
            find(t->r,key);
    }

    node_ptr kth_element(node_ptr t,int k,int add=0)
    {
       if(cnt(t->l) + add == k-1)
        return t;

       if(cnt(t->l) + add >= k)
           kth_element(t->l,k,add);
       else
           kth_element(t->r,k,add+cnt(t->l)+1);
    }

    int count_less(node_ptr t,int x)
    {
        if(t == NULL)
            return 0;

        if(t->key < x)
            return cnt(t->l)+1+count_less(t->r,x);
        else
            return count_less(t->l,x);
    }

};

