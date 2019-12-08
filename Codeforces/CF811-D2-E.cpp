#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef pair< int,int> pii;
struct ss{
    int l,r,rez,lc[20],rc[20];
}tree[400010];
int p[50],n,niz[50],a[20][100010],q,m;
ss get_new(){
    ss ret;
    ret.l=ret.r=ret.rez=0;
    memset(ret.lc,0,sizeof(ret.lc));
    memset(ret.rc,0,sizeof(ret.rc));
    return ret;
}
int root(int x){
    if(x==p[x])return x;
    p[x]=root(p[x]);
    return p[x];
}
ss mrg(ss aa,ss bb){

    if(aa.rez==-1)return bb;
    if(bb.rez==-1)return aa;

    ss ret=get_new();
    ret.rez=aa.rez+bb.rez;
    ret.l=aa.l;
    ret.r=bb.r;

    for(int i=1;i<=n;i++){
        p[i]=aa.lc[i];
        p[i+n]=aa.rc[i];
        p[i+2*n]=bb.lc[i]+2*n;
        p[i+3*n]=bb.rc[i]+2*n;
    }

    for(int i=1;i<=n;i++){

        if(a[i][aa.r]==a[i][bb.l]){
            if(root(i+n)!=root(i+2*n)){
                p[root(i+2*n)]=root(i+n);
                ret.rez--;
            }
        }
    }

    memset(niz,0,sizeof(niz));
    for(int i=1;i<=n;i++){
        ret.lc[i]=root(i);
        if(!niz[ret.lc[i]])niz[ret.lc[i]]=i;
        ret.lc[i]=niz[ret.lc[i]];

        ret.rc[i]=root(i+3*n);
        if(!niz[ret.rc[i]])niz[ret.rc[i]]=i+n;
        ret.rc[i]=niz[ret.rc[i]];
    }

    return ret;
}
void build(int x,int l,int r){

    if(l==r){

        tree[x].l=l;
        tree[x].r=r;

        int col=0;
        for(int i=1;i<=n;i++){
            if(a[i][l]!=a[i-1][l]){
                tree[x].rez++;
                col=i;
            }
            tree[x].lc[i]=tree[x].rc[i]=col;
        }
        return;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);

    tree[x]=mrg(tree[x*2],tree[x*2+1]);
}
ss query(int x,int l,int r,int ll,int rr){

    if(l>rr || r<ll){
        ss p;
        p.rez=-1;
        return p;
    }
    if(l>=ll && r<=rr)return tree[x];
    int mid=(l+r)/2;

    return mrg(query(x*2,l,mid,ll,rr),query(x*2+1,mid+1,r,ll,rr));
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d %d",&n,&m,&q);
    int in=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }
    build(1,1,m);

    for(int i=1;i<=q;i++){

        int l,r;
        scanf("%d %d",&l,&r);

        printf("%d\n",query(1,1,m,l,r).rez);
    }

    return 0;
}
