/*

    idea: https://codeforces.com/blog/entry/65295

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
int q,st,tcnt,jeste,tip2c;
ll inf=3e18;
mt19937 gen(500);
map<ll,ll> mapa;
struct node{
    ll mn,t,val,rval,lazy,s;
    node *l,*r;
    node(){}
    node(ll mn,ll t,ll s,ll val,node *l,node *r){
        this->mn=mn;
        this->t=t;
        this->val=val;
        this->l=l;
        this->r=r;
        this->rval=gen();
        this->lazy=0;
        this->s=s;
    }
};
typedef node* pnode;
int sq;
pnode root;
ll get_val(pnode x){
    if(x==NULL)return inf;
    return x->val;
}
void push(pnode x){

    if(x==NULL)return;

    pnode l=x->l;
    if(l!=NULL){
        l->lazy+=x->lazy;
        l->val+=x->lazy;
        l->mn+=x->lazy;
    }

    l=x->r;
    if(l!=NULL){
        l->lazy+=x->lazy;
        l->val+=x->lazy;
        l->mn+=x->lazy;
    }

    x->lazy=0;
}
ll get_mn(pnode x){
    if(x==NULL)return inf;
    return x->mn;
}
void upd(pnode x){
    if(x==NULL)return;
    x->mn=min(x->val,min(get_mn(x->l),get_mn(x->r)));
}
void split(pnode x,pnode &l,pnode &r,ll val){

    if(x==NULL){
        l=r=NULL;
        return;
    }

    push(x);

    if(x->t<=val){
        split(x->r,x->r,r,val);
        l=x;
    }
    else{
        split(x->l,l,x->l,val);
        r=x;
    }

    upd(x);
}
void mrg(pnode &x,pnode l,pnode r){

    push(l);
    push(r);

    if(l==NULL){
        x=r;
        return;
    }
    if(r==NULL){
        x=l;
        return;
    }

    if(l->rval>r->rval){
        mrg(l->r,l->r,r);
        x=l;
    }
    else{
        mrg(r->l,l,r->l);
        x=r;
    }

    upd(x);
}
void last_node(pnode x,pnode &ret){

    push(x);

    if(x==NULL)return;

    if(x->r==NULL){
        ret=x;
        return;
    }
    else{
        last_node(x->r,ret);
    }
}
void first_node(pnode x,pnode &ret){

    push(x);

    if(x==NULL)return;

    if(x->l==NULL){
        ret=x;
        return;
    }
    else{
        first_node(x->l,ret);
    }
}
void ins(ll t,ll s){

    if(root==NULL){
        root=new node(0,t,s,0,NULL,NULL);
        return;
    }

    pnode ltree,rtree;
    split(root,ltree,rtree,t);


    pnode last=NULL;
    last_node(ltree,last);

    ll val;
    if(last==NULL)val=0;
    else val=last->val+(t-last->t)*last->s;
    pnode pom=new node(val,t,s,val,NULL,NULL);

    last=NULL;
    first_node(rtree,last);
    if(last!=NULL){
        ll upval=(val+(last->t-t)*s)-last->val;
        rtree->lazy+=upval;
        rtree->val+=upval;
        rtree->mn+=upval;
    }

    mrg(root,ltree,pom);
    mrg(root,root,rtree);
}
void del(ll t){

    pnode l,mid,r;

    split(root,l,r,t);
    split(l,l,mid,t-1);

    pnode fst=NULL;
    ll val,s,tt;
    last_node(l,fst);
    if(fst==NULL){val=0;s=0;tt=0;}
    else{val=fst->val;s=fst->s;tt=fst->t;}

    pnode snd=NULL;
    first_node(r,snd);
    if(snd!=NULL){
        ll upval=(val+(snd->t-tt)*s)-snd->val;
        r->lazy+=upval;
        r->val+=upval;
        r->mn+=upval;
    }

    mrg(root,l,r);
}
void qry(pnode x,ll val,int &tm){

    push(x);

    if(get_mn(x->l)<=val)qry(x->l,val,tm);
    else if(x->val<=val){
        tm=x->t;
        return;
    }
    else qry(x->r,val,tm);
}
double query(int l,int r,ll v){

    pnode ltree,midtree,rtree;
    double ret=-2;

    split(root,ltree,rtree,r-1);
    split(ltree,ltree,midtree,l-1);

    if(midtree==NULL){ret=-1;}
    else{

        pnode fst=NULL;
        first_node(midtree,fst);
        ll zero=fst->val-v;

        int tm=0;
        if(midtree->mn>zero){
            pnode lst=NULL;

            last_node(midtree,lst);
            ret=((double)zero-(double)lst->val)/(double)lst->s+(double)lst->t;
            if(ret>r || ret<lst->t)ret=-1;
        }
        else{
            qry(midtree,zero,tm);
            pnode pom1,pom2;
            split(midtree,pom1,pom2,tm-1);

            pnode lst=NULL;
            last_node(pom1,lst);
            ret=((double)zero-(double)lst->val)/(double)lst->s+(double)lst->t;

            mrg(midtree,pom1,pom2);
        }
    }

    mrg(root,ltree,midtree);
    mrg(root,root,rtree);

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d",&q);
    sq=q;
    int cnt=0;
    st=0;
    int inscnt=0;
    while(q--){

        cnt++;
        int tip;
        scanf("%d",&tip);

        if(tip==1){
            int t,s;
            scanf("%d %d",&t,&s);
            ins(t,s);
        }
        else if(tip==2){
            int t;
            scanf("%d",&t);
            del(t);
        }
        else{
            int l,r,v;
            tcnt++;
            scanf("%d %d %d",&l,&r,&v);
            if(v==0){
                printf("%d\n",l);
                continue;
            }

            cout<<fixed;
            cout<<setprecision(6);
            cout<<query(l,r,v)<<endl;
        }

    }

    return 0;
}
