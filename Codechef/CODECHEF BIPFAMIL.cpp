/*

    idea:  first we calculate dp[i][j][k], number of ways of constructing
    a set of distinct intervals with i nodes on the left side, j on the right, and k last nodes on the right
    are not connected to the ones before

    after that we have to include repetitions of the same interval, u can do that
    by calculating perm[i][j], number of ways to construct a permutation with i distinct
    elements of size j, where ith element appears before i+1th
    multipljy  every perm[i][j] with fact[i] in order to get number of ways to construct a permutation with i distinct
    elements of size j

    use perm to fix up dp[i][j][k], to get ur result

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=2510;
ll mod=1e9+7;
vector<ll>dp[maxn],temp[maxn];
ll ans[maxn][maxn],rez[maxn][maxn],perm[maxn][maxn],fact[maxn],inv[maxn];
void add(ll &x,ll y){
    x=(x+y)%mod;
}
ll sub(ll x,ll y){
    x-=y;
    if(x<0)x+=mod;
    return x;
}
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }
return ret;
}
ll c(int n,int k){
    if(k>n)return 0;

    ll ret=fact[n];
    ret=(ret*inv[k])%mod;
    ret=(ret*inv[n-k])%mod;
    return ret;
}
void prek(){

    dp[0].pb(1);
    dp[0].pb(1);
    rez[1][1]=1;
    for(int i=2;i<=maxn-10;i++){/// number of right done

        int left_bound=maxn/i;

        for(int j=0;j<maxn;j++){
            temp[j].clear();
            temp[j].resize(left_bound+1);
        }


        for(int j=0;j<maxn-10;j++){


            for(int k=0;k<dp[j].size();k++){

                if(dp[j][k]==0)continue;

                /// place nothing
                add(temp[j+1][k],dp[j][k]);


                /// place smth
                if(j==0){

                    for(int p=1;p+k<=min(left_bound,i+k);p++){
                        if(p==1){
                            temp[1][p+k]=(temp[1][p+k]+dp[j][k]);
                            if(temp[1][p+k]>=mod)temp[1][p+k]-=mod;

                            temp[0][p+k]=(temp[0][p+k]+c(i-1,p)*dp[j][k])%mod;
                        }
                        else {
                            temp[0][p+k]=(temp[0][p+k]+c(i,p)*dp[j][k])%mod;
                        }

                    }

                }
                else{

                    for(int p=1;p+k<=min(left_bound,i+k);p++){
                        temp[j+1][p+k]=(temp[j+1][p+k]+c(j+1,p)*dp[j][k])%mod;
                    }

                    for(int p=1;p+k<=min(left_bound,i+k);p++){
                        temp[0][p+k]=(temp[0][p+k]+sub(c(i,p),c(j+1,p))*dp[j][k])%mod;
                    }

                }

            }

        }


        for(int j=1;j<=left_bound;j++){
            rez[i][j]=temp[0][j];
        }


        for(int j=0;j<maxn;j++){
            dp[j]=temp[j];
        }

    }


    /// calc permutations of x distinct and y elements
    perm[0][0]=1;
    for(int i=0;i<maxn-10;i++){
        for(int j=0;j<maxn-10;j++){
            perm[i][j+1]=(perm[i][j+1]+perm[i][j]*i)%mod;
            perm[i+1][j+1]=(perm[i+1][j+1]+perm[i][j])%mod;
        }
    }

    for(int i=1;i<=maxn-10;i++){
        for(int j=1;j<=maxn-10;j++){
            perm[i][j]=(perm[i][j]*fact[i])%mod;
        }
    }



    for(int i=1;i<=maxn-10;i++){

        int left_bound=(maxn-10)/i;

        for(int j=1;j<=left_bound;j++){

            for(int k=j;k<=left_bound;k++){
                ans[i][k]=(ans[i][k]+rez[i][j]*perm[j][k])%mod;
            }

        }

    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    fact[0]=1;
    inv[0]=1;
    for(int i=1;i<maxn;i++){
        fact[i]=(fact[i-1]*(ll)i)%mod;
        inv[i]=step(fact[i],mod-2);
    }

    prek();


    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d %d",&n,&m);
        printf("%lld\n",ans[m][n]);
    }


    return 0;
}

