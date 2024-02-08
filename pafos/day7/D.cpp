#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define mid (left+right)/2
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=1e6+10;
int n,b[maxn];
mt19937 gen(10);

struct node{

    pii x;
    int y,sz;
    int lazy,lazy2;
    node *l,*r;

    node(pii x){
        this->x=x;
        this->y=gen();
        this->sz=1;
        this->lazy=0;
        this->lazy2=0;
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
    if(x->lazy || x->lazy2){
        if(x->l!=NULL){
            x->l->lazy+=x->lazy;
            x->l->x.ff+=x->lazy;
            x->l->lazy2+=x->lazy2;
            x->l->x.ss+=x->lazy2;
        }
        if(x->r!=NULL){
            x->r->lazy+=x->lazy;
            x->r->x.ff+=x->lazy;
            x->r->lazy2+=x->lazy2;
            x->r->x.ss+=x->lazy2;
        }
        x->lazy=0;
        x->lazy2=0;
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
void split(pnode x,pnode &l,pnode &r,pii id,int c){

    push(x);

    if(x==NULL){
        l=r=NULL;
    }
    else{

        int cid=c+sz(x->l)+1;

        if(x->x<=id){
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
bool find_slope(pnode x,int val,int &pos,pnode &ret){

    if(x==NULL)return false;
    push(x);
    if(x->x.ff<=val)ret=x;
    if(x->x.ff==val){pos=x->x.ss;ret=x;return true;}
    if(x->x.ff<val)return find_slope(x->r,val,pos,ret);
    return find_slope(x->l,val,pos,ret);
}
bool find_pos(pnode x,int val,pnode &ret){

    if(x==NULL)return false;
    push(x);
    if(x->x.ss<=val)ret=x;
    if(x->x.ss==val){ret=x;return true;}
    if(x->x.ss<val)return find_pos(x->r,val,ret);
    return find_pos(x->l,val,ret);
}
bool find_pos2(pnode x,int val,pnode &ret){

    if(x==NULL)return false;
    push(x);
    if(x->x.ss>=val)ret=x;
    if(x->x.ss==val){ret=x;return true;}
    if(x->x.ss<val)return find_pos2(x->r,val,ret);
    return find_pos2(x->l,val,ret);
}
void delete_node(pnode &root,pii val){

    pnode p1,p2,p3;

    split(root,p1,p2,{val.ff-1,val.ss},0);
    split(p2,p2,p3,{val.ff,val.ss},0);

    mrg(p1,p3,root);
}
void insert_node(pnode &root,pii val){

    pnode p1,p2,nn=new node(val);

    split(root,p1,p2,val,0);
    mrg(p1,nn,root);
    mrg(root,p2,root);

}
void ispis(pnode x){

    if(x==NULL)return;
    push(x);
    ispis(x->l);
    printf("%d %d |",x->x.ff,x->x.ss);
    ispis(x->r);
}
void go1(int a,pnode &root,int ci){

    pnode pom0=NULL;
    int pos=-1;
    if(!find_slope(root,0,pos,pom0)){
        insert_node(root,{0,pom0->x.ss});
    }

    pnode p1,p2;
    split(root,p1,p2,{-1,1000000000},0);
    if(p2!=NULL){
        p2->lazy2++;
        p2->x.ss++;
    }
    mrg(p1,p2,root);


}
void go2(int a,pnode &root,int ci){

    pnode pom=NULL;
    if(!find_pos2(root,a,pom)){
        if(a<=ci)insert_node(root,{pom->x.ff,a});
    }

    pnode p1,p2;
    split(root,p1,p2,{pom->x.ff,a},0);
    if(p1!=NULL){
        p1->lazy--;
        p1->x.ff--;
    }
    if(p2!=NULL){
        p2->lazy++;
        p2->x.ff++;
    }

    mrg(p1,p2,root);
}
void tovector(pnode x,vector<pii>&vect){

    if(x==NULL)return;
    push(x);
    tovector(x->l,vect);
    vect.pb(x->x);
    tovector(x->r,vect);
}


int main(){


    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    pnode root=new node({0,0});
    insert_node(root,{100000000,2000000});
    ll curr=0;

    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        int a=b[i];

        go1(a,root,i);
        go2(a,root,i);

        curr+=(ll)a-1;

    }

    vector<pii>vect;
    tovector(root,vect);

    int prv=0;
    curr-=vect[0].ff;
    ll rez=1e18;
    int cnt=0;
    for(int i=0;i<vect.size();i++){

        int id=vect[i].ss;

        for(int j=prv+1;j<=id;j++){
            cnt++;
            if(cnt>n)break;
            curr+=vect[i].ff;
            rez=min(rez,curr);
            prv=cnt;
        }

    }

    printf("%lld\n",rez);

    return 0;
}
