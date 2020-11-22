/*

    idea:https://codeforces.com/blog/entry/65487

    mine little different

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int>pii;
const int maxn=250010;
const int maxm=1e7+10;

pii stek[maxm];
int stek2[maxm];
int n,m,k[maxn],ah[maxm],br,sbr,sbr2;
ll ac[maxm],dp[maxm][2],inf=1e18;
vector<int>cost[maxn],h[maxn];

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){

        scanf("%d",&k[i]);
        for(int j=0;j<k[i];j++){
            int a;
            scanf("%d",&a);
            h[i].pb(a);
        }
        for(int j=0;j<k[i];j++){
            int a;
            scanf("%d",&a);
            cost[i].pb(a);
        }
    }

    ///construt
    int q;
    scanf("%d",&q);
    while(q--){

        int id,mul;
        scanf("%d %d",&id,&mul);

        for(int j=0;j<h[id].size();j++){
            ah[++br]=h[id][j];
            ac[br]=((ll)cost[id][j]*(ll)mul);
        }
    }


    stek[++sbr]={br,br};/// rightmost, curr pos
    stek2[++sbr2]=br;
    dp[br][0]=ac[br];
    if(ah[br]>1)dp[br][1]=ac[br];
    else dp[br][1]=inf;
    for(int i=br-1;i>=1;i--){


        while(sbr2){
            int id=stek2[sbr2];
            if(id-ah[id]+1<i+1)break;

            sbr2--;
        }


        /// 1
        if(ah[i]==1){

            if(sbr2==0)dp[i][1]=inf;
            else{
                int pos=stek2[sbr2];
                if(pos-ah[pos]+1>=i){
                    pos=stek2[sbr2-1];



                    if(sbr2>1)dp[i][1]=dp[pos][1];
                    else dp[i][1]=inf;
                }
                else dp[i][1]=dp[pos][1];
            }

        }
        else{
            dp[i][1]=min(dp[i+1][0]+ac[i],dp[i+1][1]);
        }


        /// 0
        int l=1;
        int r=sbr;
        int sr,ret=min(br,i+ah[i]-1);

        while(l<=r){
            sr=(l+r)/2;

            if(stek[sr].ss<=i+ah[i]-1){
                ret=max(ret,stek[sr].ff);
                r=sr-1;
            }
            else l=sr+1;
        }

        dp[i][0]=ac[i]+dp[ret+1][0];
        if(sbr2>0)dp[i][0]=min(dp[i][0],dp[stek2[sbr2]][1]);



        while(sbr && stek[sbr].ff<=ret){
            sbr--;
        }
        stek[++sbr]={ret,i};


        while(sbr2 && stek2[sbr2]-ah[stek2[sbr2]]+1>=i-ah[i]+1)sbr2--;
        stek2[++sbr2]=i;


    }

    printf("%lld\n",min(dp[1][0],dp[1][1]));

return 0;
}
