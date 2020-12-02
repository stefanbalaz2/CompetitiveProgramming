/*

    idea:https://img.atcoder.jp/agc009/editorial.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll>pii;
const int maxn=1e5+10;
const int mb=20;
vector<int>vect[maxn];
int dp[maxn],inf=1e9,n;
void go(int x,int prv){

    int sum=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        go(id,x);
        sum^=dp[id];
    }

    /// poslednji konflikt
    int good=-1;
    for(int i=mb-1;i>0;i--){

        int cnt=0;
        for(int j=0;j<vect[x].size();j++){
            int id=vect[x][j];
            if(id==prv)continue;

            if(dp[id]&(1<<i))cnt++;
        }
        if(cnt<=1)good=i;
        else break;
    }

    for(int i=good;i<mb;i++){
        int cnt=0;
        for(int j=0;j<vect[x].size();j++){
            int id=vect[x][j];
            if(id==prv)continue;

            if(dp[id]&(1<<i))cnt++;
        }
        if(cnt==0){

            for(int j=i-1;j>0;j--)
                if(sum&(1<<j))sum^=(1<<j);

            sum^=(1<<i);

            dp[x]=sum;

            break;
        }
    }

}
int msb(int x){

    for(int i=mb-1;i>0;i--){
        if(x&(1<<i))return i;
    }

}
int main(){

    ///freopen("test2.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<n;i++){

        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    go(1,0);

    printf("%d\n",msb(dp[1])-1);


    return 0;
}
