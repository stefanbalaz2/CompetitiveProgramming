/*

    we can split query range in the middle, and those which are not satisfied go right in the tree
    others go left, and we solve recursively for both halves

    we maintain a segtree which we update by queries as we move our boundaries

    complexity: O(nlog^2n)
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
lld tree[4*maxn];
int curr,m,n,q,lq[maxn],rq[maxn],p[maxn],color[maxn],rez[maxn];
lld a[maxn];
vector<int>vect[maxn],tree2[maxn*4];
void push(int x){
    if(tree[x]==0)return;

    tree[x*2]+=tree[x];
    tree[x*2+1]+=tree[x];

    tree[x]=0;
}
void update(int x,int l,int r,int ll,int rr,lld val){

    if(l>rr || r<ll)return;
    if(l>=ll && r<=rr){
        tree[x]+=val;
        return;
    }
    int mid=(l+r)/2;

    push(x);

    update(x*2,l,mid,ll,rr,val);
    update(x*2+1,mid+1,r,ll,rr,val);
}
lld query(int x,int l,int r,int id){
    if(l>id || r<id)return 0;
    if(l==r)return tree[x];
    push(x);
    int mid=(l+r)/2;
    return query(x*2,l,mid,id)+query(x*2+1,mid+1,r,id);
}
void move_to_pt(int x){

    while(curr<x){
        curr++;
        if(lq[curr]<=rq[curr])update(1,1,m,lq[curr],rq[curr],(lld)a[curr]);
        else{
            update(1,1,m,lq[curr],m,(lld)a[curr]);
            update(1,1,m,1,rq[curr],(lld)a[curr]);
        }
    }

    while(curr>x){
        if(lq[curr]<=rq[curr])update(1,1,m,lq[curr],rq[curr],(lld)-a[curr]);
        else{
            update(1,1,m,lq[curr],m,(lld)-a[curr]);
            update(1,1,m,1,rq[curr],(lld)-a[curr]);
        }
        --curr;
    }
}
void go(int x,int l,int r){

    if(l==r){
        move_to_pt(l);
        for(int i=0;i<tree2[x].size();i++){
            ull ret=0;
            for(int j=0;j<vect[tree2[x][i]].size();j++)
                ret+=(ull)query(1,1,m,vect[tree2[x][i]][j]);

            if(ret>=(ull)p[tree2[x][i]])rez[tree2[x][i]]=l;
        }

        tree2[x].clear();
        return;
    }

    int mid=(l+r)/2;

    move_to_pt(mid);

    for(int i=0;i<tree2[x].size();i++){
        ull ret=0;
        for(int j=0;j<vect[tree2[x][i]].size();j++)
            ret+=(ull)query(1,1,m,vect[tree2[x][i]][j]);

        if(ret>=(ull)p[tree2[x][i]])tree2[x*2].pb(tree2[x][i]);
        else tree2[x*2+1].pb(tree2[x][i]);
    }

    tree2[x].clear();

    go(x*2,l,mid);
    go(x*2+1,mid+1,r);

}
int main(){

    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){
        scanf("%d",&color[i]);
        vect[color[i]].pb(i);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        tree2[1].pb(i);
    }

    scanf("%d",&q);
    for(int i=1;i<=q;i++)
        scanf("%d %d %lld",&lq[i],&rq[i],&a[i]);

    go(1,1,q);

    for(int i=1;i<=n;i++){
        if(rez[i]==0)printf("NIE\n");
        else printf("%d\n",rez[i]);
    }

return 0;
}
