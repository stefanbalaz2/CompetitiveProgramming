/*

    idea:

        -construct a trie
        -do a dp on the trie -> dp[i][j] max solution for subtree of i if we take j string from that subtree
        -dont visit unnecessary states while updating dp

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
const int maxn=2010;
const int maxlen=510;
const int mxnode=maxlen*maxn;
vector<int>dp[maxn*maxlen];
int cnt,val[maxn*maxlen],sz[mxnode],n,k,pos[mxnode];
vector<int>vect[maxn*maxlen];
string s[maxn];
int rek(int lvl,int l,int r){

    ++cnt;
    int node=cnt;

    while(l<=r && lvl==s[l].size()){l++;val[node]++;}

    if(l>r)return node;

    int l2=l,r2=l;

    while(1){

        while(r2+1<=r && s[r2+1][lvl]==s[r2][lvl])r2++;

        vect[node].pb(rek(lvl+1,l2,r2));

        l2=r2+1;
        r2=l2;

        if(l2>r)break;
    }

    return node;
}
void getsz(int x){

    sz[x]=val[x];
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        getsz(id);
        sz[x]+=sz[id];
    }
}
void build_tree(){
    rek(0,1,n);
    getsz(1);
}
int go(int x,int k){

    if(pos[x]){
        if(k>sz[x])return 0;
        return dp[x][k];
    }

    pos[x]=1;
    dp[x].resize(sz[x]+1);
    for(int i=1;i<dp[x].size();i++)dp[x][i]=-1;

    int up;
    for(int j=0;j<dp[x].size();j++){
        if(dp[x][j]!=-1)up=j;
        else break;
    }

    for(int j=up;j>=0;j--){

        int pom=dp[x][j];
        for(int i=1;i<=val[x];i++){
            int sum=pom+j*i+(i*(i-1))/2;

            dp[x][j+i]=max(dp[x][j+i],sum);
        }
    }

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        int up;
        for(int j=0;j<dp[x].size();j++){
            if(dp[x][j]!=-1)up=j;
            else break;
        }

        for(int j=up;j>=0;j--){
            if(dp[x][j]==-1)break;

            int pom=dp[x][j];
            for(int p=1;p<=sz[id];p++){
                int sum=pom+j*p+(p*(p-1))/2+go(id,p);

                dp[x][j+p]=max(dp[x][j+p],sum);
            }
        }

    }


    return dp[x][k];
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);

    for(int i=1;i<=n;i++)cin>>s[i];
    sort(s+1,s+n+1);

    build_tree();

    printf("%d\n",go(1,k)-(k*(k-1))/2);

	return 0;
}
