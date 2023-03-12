/*

    idea: fix a node X which will be in all of yourpaths u will manipulate, so that node has to have
    enough paths so we could construct a solution just from that node
    pick some subtrees that will have the weight distance from X to their nodes from 1 to sum of sizes of those subtrees
    other subtree weight distances will be consecutive multiples of (sum of sizes of the previous subtrees)
    construct the weigths with dfs

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxn=1010;
int sz[maxn],n,lim,root,sum[maxn],curr1,curr2,diff,pos[maxn];
vector<int>vect[maxn];
vector<pair<pii,int> >rez;
void prek(int x,int prv){

    sz[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        prek(id,x);
        sz[x]+=sz[id];
    }
}
void go(int x,int prv){

    int dp[n+1];
    memset(dp,-1,sizeof(dp));
    dp[0]=0;
    dp[n-sz[x]]=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        go(id,x);

        for(int j=n-1;j>=0;j--){
            if(j+sz[id]>n)continue;
            if(dp[j]!=-1)dp[j+sz[id]]=sz[id];
        }
    }

    for(int i=0;i<=n;i++){
        if(i*(n-1-i)+i>=lim && dp[i]!=-1){
            root=x;
        }
    }

}
void go3(int x,int prv){

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        rez.pb({{x,id},curr1-sum[x]});
        sum[id]=curr1;
        curr1++;

        go3(id,x);
    }

}
void go4(int x,int prv){

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        rez.pb({{x,id},curr2-sum[x]});
        sum[id]=curr2;
        curr2+=diff;

        go4(id,x);
    }

}
void go2(int x){

    int dp[n+1];
    memset(dp,-1,sizeof(dp));
    dp[0]=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        for(int j=n-1;j>=0;j--){
            if(j+sz[id]>n)continue;
            if(dp[j]!=-1){
                if(dp[j+sz[id]]==-1)dp[j+sz[id]]=id;
            }
        }
    }


    int ind=-1;
    for(int i=0;i<=n;i++)
        if(i*(n-1-i)+i>=lim && dp[i]!=-1)ind=i;


    diff=ind;
    curr1=1;
    curr2=diff;

    while(ind!=0){
        pos[dp[ind]]=1;
        ind-=sz[dp[ind]];
    }

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];

        if(pos[id]){
            rez.pb( {{x,id},curr1++} );
            sum[id]=sum[x]+curr1-1;
            go3(id,x);
        }
        else{
            rez.pb( {{x,id},curr2} );
            sum[id]=sum[x]+curr2;
            curr2+=diff;
            go4(id,x);
        }

    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d",&n);
    lim=(2*n*n)/9;
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    prek(1,0);
    root=-1;
    go(1,0);

    if(root==-1)return 10;


    prek(root,0);
    go2(root);

    for(int i=0;i<rez.size();i++)printf("%d %d %d\n",rez[i].ff.ff,rez[i].ff.ss,rez[i].ss);

    return 0;
}
