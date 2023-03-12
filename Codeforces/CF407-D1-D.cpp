/*

    idea: https://codeforces.com/blog/entry/11333

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=410;
int a[maxn][maxn],maxl[maxn][maxn],cm2[maxn*maxn],cm[maxn*maxn],niz[maxn],n,m,rez[maxn],ans,minr[maxn][maxn];
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
        }
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)minr[i][j]=m+1;

    for(int i=1;i<maxn*maxn;i++)cm2[i]=m+1;


    for(int i=n;i>=1;i--){/// row

        /// update
        for(int j=1;j<=m;j++){
            int col=a[i][j];

            maxl[i][j]=cm[col];
            cm[col]=j;

            for(int k=i+1;k<=n;k++)
                maxl[k][j]=max(maxl[k][j],cm[a[k][j]]);

        }
        for(int j=1;j<=m;j++){
            int col=a[i][j];
            cm[col]=0;
        }

        for(int j=m;j>=1;j--){
            int col=a[i][j];

            minr[i][j]=cm2[col];
            cm2[col]=j;

            for(int k=i+1;k<=n;k++)
                minr[k][j]=min(minr[k][j],cm2[a[k][j]]);

        }
        for(int j=1;j<=m;j++){
            int col=a[i][j];
            cm2[col]=m+1;
        }



        /// go
        for(int j=1;j<=m;j++)rez[j]=m+1;
        for(int j=i;j<=n;j++){

            for(int k=1;k<=m;k++)niz[k]=m+1;
            for(int k=1;k<=m;k++)niz[maxl[j][k]]=min(k-1,niz[maxl[j][k]]);
            for(int k=1;k<=m;k++)niz[k]=min(minr[j][k]-1,niz[k]);

            int curr=m+1;
            for(int k=m;k>=1;k--){
                curr=min(curr,niz[k]);
                rez[k]=min(rez[k],curr);

                /// update rez
                ans=max(ans,(rez[k]-k+1)*(j-i+1));
            }
        }

    }


    printf("%d\n",ans);

    return 0;
}
