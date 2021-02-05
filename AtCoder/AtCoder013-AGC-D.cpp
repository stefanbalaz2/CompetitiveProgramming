/*

    idea:   https://img.atcoder.jp/agc013/editorial.pdf

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=3010;

int dp[maxn][2],mod=1e9+7,temp[maxn][2],n,m;
void regulate(int &x){
    if(x>=mod)x-=mod;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);

    dp[0][1]=1;
    for(int i=1;i<=n;i++)dp[i][0]=1;

    for(int i=1;i<=m;i++){

        for(int j=0;j<=n;j++){

            ///from k==0

                /// RR
                if(j>1)temp[j-1][0]+=dp[j][0],regulate(temp[j-1][0]);
                if(j==1)temp[j-1][1]+=dp[j][0],regulate(temp[j-1][1]);

                /// RB
                if(j>1)temp[j][0]+=dp[j][0],regulate(temp[j][0]);
                if(j==1)temp[j][1]+=dp[j][0],regulate(temp[j][1]);

                /// BB
                if(j<=n-1)temp[j+1][0]+=dp[j][0],regulate(temp[j+1][0]);

                /// BR
                if(j<=n-1)temp[j][0]+=dp[j][0],regulate(temp[j][0]);


            ///from k==1

                /// RR
                if(j>=1)temp[j-1][1]+=dp[j][1],regulate(temp[j-1][1]);

                /// RB
                if(j>=1)temp[j][1]+=dp[j][1],regulate(temp[j][1]);

                /// BB
                if(j<=n-1)temp[j+1][1]+=dp[j][1],regulate(temp[j+1][1]);

                /// BR
                if(j<=n-1)temp[j][1]+=dp[j][1],regulate(temp[j][1]);

        }

        memcpy(dp,temp,sizeof(dp));
        memset(temp,0,sizeof(temp));

    }


    int rez=0;
    for(int i=0;i<=n;i++){
        rez+=dp[i][1];
        regulate(rez);
    }

    printf("%d\n",rez);

    return 0;
}
