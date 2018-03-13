struct node{

  node* nxt[2];
  node* par;

  int cnt;

  node()
  {
      nxt[0]=NULL;
      nxt[1]=NULL;
      par=NULL;

      cnt=0;
  }

};
struct trie{

 node* root;

 void insert(int x,node* &v,int bit=BITS)
 {
    if(bit == 0)
    {
        v->cnt++;
        return;
    }

    if(x & (1 << (bit-1)))
    {
      if(v->nxt[1] == NULL)
      {
        v->nxt[1]=new node();
        v->nxt[1]->par=v;
      }

      insert(x,v->nxt[1],bit-1);
    }
    else
    {
      if(v->nxt[0] == NULL)
      {
        v->nxt[0]=new node();
        v->nxt[0]->par=v;
      }

      insert(x,v->nxt[0],bit-1);
    }
 }

 void erase(int x,node* &v,int bit=BITS)
 {
    if(bit == 0)
    {
        v->cnt--;
        if(!v->cnt)
            v=NULL;

        return;
    }

    if(x & (1 << (bit-1)))
        erase(x,v->nxt[1],bit-1);
    else
        erase(x,v->nxt[0],bit-1);

    if(v->nxt[1] == NULL && v->nxt[0] == NULL)
         v=NULL;
 }

 int minxor(int x,node *v,int bit=BITS)
 {
     if(bit == 0)
        return 0;

     int res=0,t;
     if(x & (1 << (bit-1)))
     {
         if(v->nxt[1] != NULL)
         {
             t=minxor(x,v->nxt[1],bit-1);
             res^=(1 << (bit-1));
         }
         else
         {
             t=minxor(x,v->nxt[0],bit-1);
         }
     }
     else
     {
         if(v->nxt[0] != NULL)
         {
             t=minxor(x,v->nxt[0],bit-1);
         }
         else
         {
             t=minxor(x,v->nxt[1],bit-1);
             res^=(1 << (bit-1));
         }
     }

     res^=t;

     return res;
 }

}trie;
