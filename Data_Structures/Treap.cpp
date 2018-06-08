#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
using namespace std;

random_device rd;
mt19937 mt(rd());

struct node{

   node *l, *r;
   int key, prior, cnt;


   node() {};
   node(int _key) { key = _key; prior = mt(); cnt = 1; l = nullptr; r = nullptr;}

};

typedef node* pnode;

pnode root = nullptr;

int cnt(pnode t)
{
    if(t)
      return t->cnt;
    return 0;
}

void refresh(pnode &t)
{
    if(t)
        t->cnt = cnt(t->l) + cnt(t->r) + 1;
}

void split(pnode t, pnode &l, pnode &r, int key)
{
    if(!t) { l = nullptr; r = nullptr; return; }

    if(key < t->key)
      split(t->l, l, t->l, key), r = t;
    else
      split(t->r, t->r, r, key), l = t;

    refresh(t);
}

void merge(pnode &t, pnode l, pnode r)
{
    if(!l) { t = r; return; }
    if(!r) { t = l; return; }

    if(l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;

    refresh(t);
}

void insert(pnode &t, pnode x)
{
    if(!t) { t = x; return; }

    if(x->prior > t->prior)
        split(t, x->l, x->r, x->key), t = x;
    else
    {
        if(x->key < t->key)
            insert(t->l, x);
        else
            insert(t->r, x);
    }
}

void erase(pnode &t, int key)
{
    if(!t) return;
    if(t->key == key) { merge(t, t->l, t->r); return; }

    if(key < t->key)
        erase(t->l, key);
    else
        erase(t->r, key);
}

int main()
{



    return 0;
}
