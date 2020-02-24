/*

    idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2004/editorial/jas.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
const int maxn=5e4;
vector<int>val[maxn],vect[maxn];
int dp[maxn],n;
void go(int x,int prv){

    for(int i=1;i<=25;i++)val[x].pb(0);

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        if(id==prv)continue;

        go(id,x);

        for(int j=0;j<val[x].size();j++)val[x][j]+=val[id][j];
    }

    int p=val[x].size()-1;
    while(p>=0 && val[x][p]<2)p--;
    p++;

    while(val[x][p]>0)p++;

    dp[x]=p;

    val[x][p]=1;
    p--;
    while(p>=0)val[x][p--]=0;
}
int main(){

    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    go(1,0);

    int rez=0;
    for(int i=1;i<=n;i++)
        rez=max(rez,dp[i]);

    printf("%d\n",rez);

return 0;
}
