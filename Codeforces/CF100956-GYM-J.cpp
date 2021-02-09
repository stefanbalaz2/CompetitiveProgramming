/*

    idea: find number of increasing sequences of length i
            multiply that by factorial[i] and number of ways to make a partition of n objects into i sets

*/
#include<bits/stdc++.h>
#define lld long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;

const int maxn=2020;

lld dp[maxn],fact[maxn*2],inv[maxn*2],mod=1e9+7,p[maxn][maxn];
int tree[maxn][maxn*4],n;

void regulate(int &x){
    if(x>=mod)x-=mod;
}


void update(int x,int l,int r,int i,int id,int val){

    if(l>id || r<id)return;
    if(l==r){
        tree[i][x]+=val;
        regulate(tree[i][x]);
        return;
    }
    int mid=(l+r)/2;

    update(x*2,l,mid,i,id,val);
    update(x*2+1,mid+1,r,i,id,val);

    tree[i][x]=tree[i][x*2]+tree[i][x*2+1];
    regulate(tree[i][x]);

}
int query(int x,int l,int r,int ll,int rr,int i){

    if(l>rr || r<ll)return 0;
    if(l>=ll && r<=rr)return tree[i][x];
    int mid=(l+r)/2;

    int pom=query(x*2,l,mid,ll,rr,i)+query(x*2+1,mid+1,r,ll,rr,i);
    regulate(pom);

    return pom;
}

void go(int x){

    for(int i=n;i>=1;i--){
        update(1,1,n,i,x,query(1,1,n,1,x,i-1));

        ///printf("%d %d %d KK\n",i,query(1,1,n,1,x,i-1),x);
    }

}

lld step(lld base,lld pw){


    lld ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }

    return ret;
}

lld c(int n,int k){

    lld ret=fact[n];
    ret=(ret*inv[k])%mod;
    ret=(ret*inv[n-k])%mod;

    return ret;
}

void prek(){

    for(int i=1;i<=n;i++)
        dp[i]=tree[i][1];


    fact[0]=1;
    inv[0]=1;
    for(int i=1;i<=2*n;i++){
        fact[i]=(fact[i-1]*i)%mod;
        inv[i]=step(fact[i],mod-2);
    }

    p[0][0]=1;
    for(int i=1;i<=n;i++){

        for(int j=1;j<=n;j++){

            p[i][j]=(p[i-1][j]*j+p[i-1][j-1])%mod;

        }

    }

}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    update(1,1,n,0,1,1);
    ///printf("%d AAAA\n",query(1,1,n,1,2,0));
    for(int i=1;i<=n;i++){
        int a;
        scanf("%d",&a);

        go(a);
    }

    prek();


    lld rez=0;

    for(int i=1;i<=n;i++){

        ///printf("%lld %d\n",dp[i],i);

        rez=(rez+((dp[i]*p[n][i])%mod)*fact[i] )%mod;

    }

    printf("%lld\n",rez);

    return 0;
}
