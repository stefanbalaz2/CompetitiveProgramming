/*

observation: the constructed string is always of length n+m-1
we can build it from the both ends at the same time, adding 2 matching letters
one diagonal means one letter in the string
we do a dp on the diagonals meaning dp[i][j]
number of palindroms starting at (1,1) and ending in ith position on the diagonal
which match with paths that start at (n,m) and end at jth position on the other diagonal

O(N^3)

*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair< int,int> pii;
const int maxn=510;
int ind[maxn][maxn],n,m,l,r;
ll dp[maxn][maxn],temp[maxn][maxn],mod=1e9+7,rez;
char a[maxn][maxn];
vector<pii>d[maxn*2];
int get_ind(pii x){
    return ind[x.ff][x.ss];
}
void update(pii x,pii y){

    int idx=get_ind(x);
    int idy=get_ind(y);

    if(a[x.ff][x.ss]!=a[y.ff][y.ss]){
        temp[idx][idy]=0;
        return;
    }

    int id=get_ind({x.ff-1,x.ss});
    ///printf("%d %d %d %lld FWA\n",idx,idy,id,temp[idx][idy]);
    if(id!=-1){

        int id2=get_ind({y.ff+1,y.ss});
       /// printf("%d %lld AAAAAA\n",id2,dp[id][id2]);
        if(id2!=-1)temp[idx][idy]+=dp[id][id2];

        id2=get_ind({y.ff,y.ss+1});
         ///printf("%d %lld AAAAAA\n",id2,dp[id][id2]);
        if(id2!=-1)temp[idx][idy]+=dp[id][id2];
    }

    id=get_ind({x.ff,x.ss-1});
   /// printf("%d %d %d %d %d  %lld FWA\n",idx,idy,id,x.ff,x.ss,temp[idx][idy]);
    if(id!=-1){

        int id2=get_ind({y.ff+1,y.ss});
        ///printf("%d %d %d %lld AAAAAA\n",id2,y.ff,y.ss,dp[id][id2]);
        if(id2!=-1)temp[idx][idy]+=dp[id][id2];

        id2=get_ind({y.ff,y.ss+1});
        if(id2!=-1)temp[idx][idy]+=dp[id][id2];
    }

    ///printf("%lld TEMP\n",temp[idx][idy]);

    temp[idx][idy]%=mod;
}
void go(){

    l=2+1;
    r=m+n-1;

    while(l<=r){


        /// calculate dp[i][j]
        for(int i=0;i<d[l].size();i++)
            for(int j=0;j<d[r].size();j++)
                update(d[l][i],d[r][j]);

       /* for(int i=0;i<d[l].size();i++){
            for(int j=0;j<d[r].size();j++)
                printf("%lld ",temp[i][j]);
            printf("\n");
        }*/

        for(int i=0;i<=500;i++)
            for(int j=0;j<=500;j++)dp[i][j]=temp[i][j];

        memset(temp,0,sizeof(temp));

        l++;
        r--;
    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    memset(ind,-1,sizeof(ind));
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        for(int j=1;j<=m;j++){

            a[i][j]=s[j-1];
            d[i+j].pb({i,j});
            ind[i][j]=d[i+j].size()-1;

        }
    }

    if(a[1][1]==a[n][m])dp[0][0]=1;
    else dp[0][0]=0;

    go();

    if((n+m-1)%2){
        l--;
        for(int i=0;i<d[l].size();i++){
            int id=get_ind(d[l][i]);
            rez+=dp[id][id];
        }
        rez%=mod;
    }
    else{
        l--;
        r++;

        for(int i=0;i<d[l].size();i++){
            int xx=get_ind(d[l][i]);

            int id=get_ind({d[l][i].ff+1,d[l][i].ss});
            if(id!=-1)rez+=dp[xx][id];

            id=get_ind({d[l][i].ff,d[l][i].ss+1});
            if(id!=-1)rez+=dp[xx][id];

            rez%=mod;
        }
    }

    printf("%lld\n",rez);

    return 0;
}

