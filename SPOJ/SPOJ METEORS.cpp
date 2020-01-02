/*
    idea: create a persistent segtree for every query
    and binary search over the queries for every color to get the answer

    complexity: O(nlog^2n)
    nlogn for making persistent segtree
    nlog^2n for querying, because for every color we have logk*logm*number_of_positions_with_this_color
    so logk*logn*(color1+color2...)=logk*logn*m
*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define lld long long
#define ull unsigned long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=3e5+10;
struct ss{
    lld sum;
    int l,r;
}tree[100*maxn];
int cnt,n,m,p[maxn],color[maxn],root[maxn],q,lastroot;
vector<int>vect[maxn];
void update_node(int &x,lld val){

    tree[cnt+1]=tree[x];
    x=++cnt;
    tree[x].sum+=val;
}
void push(int x){

    if(tree[x].sum==0)return;

    update_node(tree[x].l,tree[x].sum);
    update_node(tree[x].r,tree[x].sum);

    tree[x].sum=0;
}
void update(int &x,int prv,int l,int r,int ll,int rr,lld val){

    if(l>rr || r<ll)return;

    tree[cnt+1]=tree[x];
    x=++cnt;

    if(l>=ll && r<=rr){
        tree[x].sum+=val;
        return;
    }
    push(x);
    int mid=(l+r)/2;
    update(tree[x].l,tree[prv].l,l,mid,ll,rr,val);
    update(tree[x].r,tree[prv].r,mid+1,r,ll,rr,val);
}
lld query(int x,int l,int r,int id){
    if(l==r)return tree[x].sum;
    push(x);
    int mid=(l+r)/2;
    if(id<=mid)return query(tree[x].l,l,mid,id);
    else return query(tree[x].r,mid+1,r,id);
}
bool check(int boja,int vreme){

    ull ret=0;
    for(int i=0;i<vect[boja].size();i++)
        ret+=(ull)query(root[vreme],1,m,vect[boja][i]);

    if(ret>=(ull)p[boja])return 1;
    return 0;
}
int main(){

    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){
        scanf("%d",&color[i]);
        vect[color[i]].pb(i);
    }
    for(int i=1;i<=n;i++)scanf("%d",&p[i]);

    scanf("%d",&q);
    for(int i=1;i<=q;i++){

        int l,r;
        lld a;

        scanf("%d %d %lld",&l,&r,&a);

        if(l<=r){
            root[i]=lastroot;
            update(root[i],lastroot,1,m,l,r,a);
            lastroot=root[i];
        }
        else{
            root[i]=lastroot;
            update(root[i],lastroot,1,m,l,m,a);
            lastroot=root[i];

            root[i]=lastroot;
            update(root[i],lastroot,1,m,1,r,a);
            lastroot=root[i];
        }
    }

    for(int i=1;i<=n;i++){

        int l=1;
        int r=q;
        int sr;
        int ret=-1;
        while(l<=r){
            sr=(l+r)/2;
            if(check(i,sr)){
                ret=sr;
                r=sr-1;
            }
            else l=sr+1;
        }

        if(ret==-1)printf("NIE\n");
        else printf("%d\n",ret);
    }

return 0;
}
