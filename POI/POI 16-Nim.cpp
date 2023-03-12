/*

    idea: https://github.com/quangloc99/CompetitiveProgramming/blob/master/olympiad/POI/2016/nim.cpp


*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
int mod=1e9+7;
int dp[11][(1<<20)+10];
int n,d,a[500010];
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&d);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);

    sort(a+1,a+n+1);

    dp[0][0]=1;
    int xs=0;
    for(int i=1;i<=n;i++){
        xs^=a[i];

        int mx=min(2*a[i-1],(1<<20));

        for(int j=0;j<=mx;j++)dp[d][j]=dp[0][j];

        for(int k=d-1;k>0;k--){
            for(int j=0;j<=mx;j++){
                dp[(k+1)%d][j^a[i]]+=dp[k][j];
                if(dp[(k+1)%d][j^a[i]]>=mod)dp[(k+1)%d][j^a[i]]-=mod;
            }
        }

        for(int j=0;j<=mx;j++){
            dp[1%d][j^a[i]]+=dp[d][j];
            if(dp[1%d][j^a[i]]>=mod)dp[1%d][j^a[i]]-=mod;
        }
    }


    if(n%d==0)dp[0][xs]--;
    if(dp[0][xs]<0)dp[0][xs]+=mod;


    printf("%d\n",dp[0][xs]);

	return 0;
}
