/*
    idea: 
*/
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=190;
const int maxc=19;
int a[maxn][maxn],dp[maxn][maxn][maxn][20],pref[maxn][maxn];
int get(int u,int d,int l,int r){
    return pref[d][r]-pref[u-1][r]-pref[d][l-1]+pref[u-1][l-1];
}
bool monotone(int u,int l,int d,int r){
    int pom=get(u,d,l,r);
    int surface=(d-u+1)*(r-l+1);

    if(pom==0 || pom==surface)return true;
    else return false;
}
int main(){

    scanf("%d %d",&n,&m);

    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=1;j<=m;j++){
            a[i][j]=s[j-1]=='#'?1:0;
            pref[i][j]=pref[i-1][j]+pref[i][j-1]-pref[i-1][j-1]+a[i][j];
        }
    }
    for(int i=0;i<=n+1;i++){
        a[i][0]=2;
        a[i][m+1]=2;
    }
    for(int i=0;i<=m+1;i++){
        a[0][i]=2;
        a[n+1][i]=2;
    }

    for(int i=n;i>=1;i--){
        for(int l=1;l<=m;l++){
            for(int r=l;r<=m;r++){

                if(i==n){
                    if(monotone(i,l,i,r))dp[l][r][i][0]=i;
                    else dp[l][r][i][0]=i-1;
                }
                else if(monotone(i,l,i+1,r)){
                    dp[l][r][i][0]=dp[l][r][i+1][0];
                }
                else if(monotone(i,l,i,r))dp[l][r][i][0]=i;
                else dp[l][r][i][0]=i-1;

            }
        }
    }


    if(dp[1][m][1][0]==n){
        printf("0\n");
        return 0;
    }

    for(int c=1;c<=maxc;c++){

        for(int l=1;l<=m;l++){
            for(int r=l;r<=m;r++){

                for(int i=1;i<=n;i++){

                    int pom=dp[l][r][i][c-1]+1;
                    if(pom>n)dp[l][r][i][c]=n;
                    else dp[l][r][i][c]=dp[l][r][pom][c-1];

                }
            }
        }


        for(int i=1;i<=n;i++){

            for(int l=1;l<=m;l++){
                int ptr=l;
                int ptr2=l;

                for(int r=l+1;r<=m;r++){

                    while(ptr<r-1 && dp[l][ptr][i][c-1]>dp[ptr+1][r][i][c-1])ptr++;
                    while(ptr2<r-1 && dp[l][ptr2][i][c-1]>=dp[ptr2+1][r][i][c-1])ptr2++;

                    dp[l][r][i][c]=max(dp[l][r][i][c],min(dp[l][ptr][i][c-1],dp[ptr+1][r][i][c-1]));
                    if(ptr>l)dp[l][r][i][c]=max(dp[l][r][i][c],min(dp[l][ptr-1][i][c-1],dp[ptr][r][i][c-1]));
                    if(ptr<r-1)dp[l][r][i][c]=max(dp[l][r][i][c],min(dp[l][ptr+1][i][c-1],dp[ptr+2][r][i][c-1]));

                    dp[l][r][i][c]=max(dp[l][r][i][c],min(dp[l][ptr2][i][c-1],dp[ptr2+1][r][i][c-1]));
                    if(ptr2>l)dp[l][r][i][c]=max(dp[l][r][i][c],min(dp[l][ptr2-1][i][c-1],dp[ptr2][r][i][c-1]));
                    if(ptr2<r-1)dp[l][r][i][c]=max(dp[l][r][i][c],min(dp[l][ptr2+1][i][c-1],dp[ptr2+2][r][i][c-1]));

                }

            }

        }

        if(dp[1][m][1][c]==n){
            printf("%d\n",c);
            break;
        }
    }


return 0;
}
