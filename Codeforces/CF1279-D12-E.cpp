/*

    editorial: https://codeforces.com/blog/entry/72577

*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int maxn=50+10;
int cc,p[maxn],last[maxn],first[maxn];
ll dp_cycles[maxn],dp_ways[maxn],factorial[maxn],inf=1e18+5;
ll mul(ll x,ll y){

    ll ret=inf;
    ret/=x;
    ret/=y;
    if(ret==0)return inf;

return x*y;
}
ll add(ll x,ll y){

    if(x+y>inf)return inf;
    return x+y;
}
ll fact(int x){

    if(x<=1)return 1;
    return factorial[x]=mul(fact(x-1),x);
}
ll cycles(int x){

    if(x<=3)return 1;
    if(dp_cycles[x]!=-1)return dp_cycles[x];

    return dp_cycles[x]=mul(cycles(x-1),(x-2));
}
ll ways(int x){

    if(x==0)return 1;
    if(dp_ways[x]!=-1)return dp_ways[x];

    dp_ways[x]=0;
    for(int i=1;i<=x;i++)
        dp_ways[x]=add(dp_ways[x],mul(cycles(i),ways(x-i)));

    return dp_ways[x];
}
void reset_dsu(int n){

    cc=n;
    for(int i=1;i<=n;i++){
        p[i]=i;
        first[i]=1;
        last[i]=1;
    }

}
int root(int x){
    if(p[x]==x)return x;
    return root(p[x]);
}
void join(int x,int y){

    p[x]=y;
    last[y]=0;
    first[x]=0;
    cc--;
}
ll check_join(int x,int y){

    if(first[x]==0 || last[y]==0)return 0;

    if(root(x)==root(y))return 0;

    return fact(cc-2);
}
void construct_cycle(ll k,int n,vector<int> &vect){

    reset_dsu(n);

    vect.resize(n);
    vect[0]=n;

    join(1,n);

    for(int i=1;i<n;i++){


        if(i==n-1){

            for(int j=1;j<=n;j++)
            if(last[j]){
                vect[i]=j;
                break;
            }

            break;
        }

        for(int j=1;j<=n;j++){

            ll pom=check_join(i+1,j);

            if(pom<k)k-=pom;
            else{
                vect[i]=j;
                join(i+1,j);
                break;
            }
        }

    }
}
void go(int start,int n,ll k,vector<int> &rez){

    if(n==0)return;

    int block_size=-1;
    for(int i=1;i<=n;i++){

        if(mul(ways(n-i),cycles(i))<k)k-=ways(n-i)*cycles(i);
        else{
            block_size=i;
            break;
        }
    }
    if(block_size==-1){
        rez.pb(-1);
        return;
    }

    ll which_cycle=k/ways(n-block_size)+1-(k%ways(n-block_size)==0);

    k%=ways(n-block_size);
    if(k==0)k=ways(n-block_size);


    vector<int>vect;
    construct_cycle(which_cycle,block_size,vect);

    for(int i=0;i<vect.size();i++){
        vect[i]+=start-1;
        rez.pb(vect[i]);
    }

    go(start+block_size,n-block_size,k,rez);
}
int main(){

    ///freopen("test.txt","r",stdin);

    memset(factorial,-1,sizeof(factorial));
    memset(dp_ways,-1,sizeof(dp_ways));
    memset(dp_cycles,-1,sizeof(dp_cycles));

    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        ll k;
        scanf("%d %lld",&n,&k);

        vector<int>rez;
        go(1,n,k,rez);

        for(int i=0;i<rez.size();i++)printf("%d ",rez[i]);
        printf("\n");
    }

return 0;
}
