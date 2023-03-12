
/// https://codeforces.com/contest/863/problem/D

#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

const int maxn=2e5+10;

mt19937 gen(10);

struct node{

    int x,y,sz;
    int lazy;
    node *l,*r;

    node(int x){
        this->x=x;
        this->y=gen();
        this->sz=1;
        l=NULL;
        r=NULL;
    }

};
typedef node* pnode;
pnode root;

int sz(pnode x){
    if(x==NULL)return 0;
    return x->sz;
}
void upd(pnode x){
    if(x==NULL)return;
    x->sz=1+sz(x->l)+sz(x->r);
}
void push(pnode x){
    if(x==NULL)return;
    if(x->lazy){
        swap(x->l,x->r);
        x->lazy=0;
        if(x->l!=NULL)x->l->lazy^=1;
        if(x->r!=NULL)x->r->lazy^=1;
    }
}
void mrg(pnode l,pnode r,pnode &x){

    push(l);
    push(r);

    if(l==NULL && r==NULL){
        x=NULL;
    }
    else if(l==NULL){
        x=r;
    }
    else if(r==NULL){
        x=l;
    }
    else{

        if(l->y>=r->y){
            mrg(l->r,r,l->r);
            x=l;
        }
        else{
            mrg(l,r->l,r->l);
            x=r;
        }

    }

    upd(x);

}
void split(pnode x,pnode &l,pnode &r,int id,int c){

    push(x);

    if(x==NULL){
        l=r=NULL;
    }
    else{

        int cid=c+sz(x->l)+1;

        if(cid<=id){
            split(x->r,x->r,r,id,cid);
            l=x;
            upd(l);
        }
        else{
            split(x->l,l,x->l,id,c);
            r=x;
            upd(r);
        }

    }

}

vector<int>a;
void extr(pnode x){
    if(x==NULL)return;
    push(x);
    extr(x->l);
    a.pb(x->x);
    extr(x->r);
}

void ispis(pnode x){

    if(x==NULL)return;
    push(x);
    ispis(x->l);
    printf("%d ",x->x);
    ispis(x->r);
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int n,q,m;
    scanf("%d %d %d",&n,&q,&m);

    root=NULL;
    for(int i=1;i<=n;i++){

        int a;
        scanf("%d",&a);
        pnode p=new node(a);
        mrg(root,p,root);

    }

    while(q--){

        int tip,lp,rp;
        scanf("%d %d %d",&tip,&lp,&rp);

        if(tip==1){

            pnode l,r,mid;
            split(root,l,mid,lp-1,0);
            split(mid,mid,r,rp-lp+1,0);

            pnode p1,p2;
            split(mid,p1,p2,sz(mid)-1,0);
            mrg(p2,p1,mid);

            mrg(l,mid,root);
            mrg(root,r,root);

        }
        else{

            pnode l,r,mid;
            split(root,l,mid,lp-1,0);
            split(mid,mid,r,rp-lp+1,0);

            mid->lazy^=1;

            mrg(l,mid,root);
            mrg(root,r,root);


        }


    }

    extr(root);

    for(int i=1;i<=m;i++){

        int b;
        scanf("%d",&b);
        printf("%d ",a[b-1]);

    }

    return 0;
}

