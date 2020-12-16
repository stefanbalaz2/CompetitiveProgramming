#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
const int maxn=110;
ll dp[3][maxn][maxn],niz[maxn],mod=1e9+7,a[maxn];
int n;
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }

    return ret;
}
ll go1(int l,int r){

    for(int i=l-1;i<=r+1;i++)niz[i]=0;


    ll curr=a[l-1];
    if(l==1)curr=0;
    else if(a[l-2]<=a[l-1])curr=a[l-2];
    if(curr==1)curr=0;
    for(int i=max(1,l-1);i<=min(n,r+1);i++){

        if(curr>=a[i]){
            curr=a[i];
            niz[i]=a[i];
        }
        else{
            niz[i]=max(niz[i],curr);
        }
    }



    curr=a[r+1];
    if(r==n)curr=0;
    else if(a[r+2]<=a[r+1])curr=a[r+2];
    if(curr==1)curr=0;
    for(int i=min(r+1,n);i>=max(1,l-1);i--){

        if(curr>=a[i]){
            curr=a[i];
            niz[i]=a[i];
        }
        else{
            niz[i]=max(niz[i],curr);
        }
    }




    curr=-1;
    ll h=0;
    ll ret=1;
    for(int i=max(1,l-1);i<=min(n,r+1);i++){

        if(niz[i]!=curr){
            curr=niz[i];
            h=a[i]-niz[i];

            ret=(ret*step(2,h))%mod;
        }
        else{

            if(h>=a[i]-niz[i]){
                h=a[i]-niz[i];
            }
            else{
                ret=(ret*step(2,a[i]-niz[i]-h))%mod;
                h=a[i]-niz[i];
            }

        }

    }

    return ret;
}
ll go3(int l,int r){

    ll ret=1;
    for(int i=l+1;i<=r-1;i++){
        if(a[i]>=a[i-1] && a[i]>=a[i+1])ret=(ret*step(2,a[i]-max(a[i-1],a[i+1])) )%mod;
    }

    return max(ret,1ll);
}
void prek(){

    for(int i=1;i<=n+1;i++){
        for(int j=i-1;j<=n;j++){
            dp[0][i][j]=go1(i,j);
            dp[2][i][j]=go3(i,j);
        }
    }

}
ll go2(int l,int r){

    if(l>r){
        return dp[0][l][r];
    }
    if(dp[1][l][r]!=-1)return dp[1][l][r];

    dp[1][l][r]=1;

    int f1=-1;
    for(int i=l;i<=r;i++){
        if(a[i]==0){
            f1=i;
            break;
        }
    }
    if(f1!=-1){
        dp[1][l][r]=(go2(l,f1-1)*2*go2(f1+1,r))%mod;
        return dp[1][l][r];
    }

    ll ret=0;

    if(a[l-1]==0){

        for(int i=l;i<=r-1;i++)
            for(int j=i+1;j<=n;j++)
                ret=(ret+2*((((dp[0][l][i-1]*dp[2][i][j])%mod)*go2(j+1,r))%mod))%mod;


    }
    else{

        for(int i=l;i<=r-1;i++)
            for(int j=i+1;j<=n;j++)
                ret=(ret+((dp[0][l][i-1]*dp[2][i][j])%mod)*go2(j+1,r))%mod;



    }

    ret=(ret+dp[0][l][r])%mod;

    dp[1][l][r]=ret;
    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
        if(a[i]==1)a[i]=0;
    }


    prek();
    memset(dp[1],-1,sizeof(dp[1]));

    printf("%lld\n",go2(1,n));


return 0;
}
