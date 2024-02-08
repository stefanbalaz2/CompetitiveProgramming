#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=1e9+7;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=2010*210;
const int maxalp=26;

int n,m;
int cnt=0,fpar[2020][2020];
int adj[maxn][maxalp],p[maxn],pc[maxn],sz[maxn],lp[maxn],rp[maxn],leaf[maxn];
vector<pii>vct[maxn];
string s[maxn];
bool cmp(string &a,string &b){
    return a.size()<b.size();
}
int ins(string s,int cid){

    int curr=0;
    int e=1;
    for(int i=0;i<s.size();i++){

        int nxt=s[i]-'a';

        if(adj[curr][nxt]==-1){
            adj[curr][nxt]=++cnt;
            pc[cnt]=nxt;
            p[cnt]=curr;
            e=1;
        }
        curr=adj[curr][nxt];
        if(leaf[curr])return 0;
    }
    if(e){
        sz[curr]=1;
        lp[curr]=cid;
        rp[curr]=cid;
        leaf[curr]=1;
    }
    return e;
}
string get_string_by_node(int x){

    string ret;
    while(x!=0){
        ret.pb(pc[x]+'a');
        x=p[x];
    }
    reverse(ret.begin(),ret.end());
    return ret;
}
int cpt=0;
void prek(int x){

    int cc=0;
    for(int i=0;i<maxalp;i++){
        int id=adj[x][i];
        if(id==-1)continue;
        prek(id);
        sz[x]+=sz[id];
        lp[x]=min(lp[x],lp[id]);
        rp[x]=max(rp[x],rp[id]);
        cc++;
    }

    if(cc==0){
        lp[x]=++cpt;
        rp[x]=lp[x];
    }
    if(x!=0 && cc!=1){
        vct[rp[x]].pb({lp[x],x});
        //printf("%d %d | %d ",lp[x],rp[x],x);
        //cout<<get_string_by_node(x)<<endl;
    }

}
vector<int>dp[4020];
int dpcnt=0;
int dpid[maxn];
void mrg(int x,int y){

    vector<int>ret(dp[x].size()-1+dp[y].size());

    for(int i=0;i<dp[x].size();i++)
    for(int j=0;j<dp[y].size();j++){
        ret[i+j]=add(ret[i+j],mul(dp[x][i],dp[y][j]));
    }
    dp[x]=ret;
}
void dfs(int x){

    int cc=0;
    int lc=0;
    for(int i=0;i<maxalp;i++){
        int id=adj[x][i];
        if(id==-1)continue;
        cc++;
        lc=id;
        dfs(id);
    }

    if(cc==0){
        dpid[x]=++dpcnt;
        dp[dpid[x]].resize(2);
        dp[dpid[x]][0]=0;
        dp[dpid[x]][1]=1;
    }
    else if(cc==1){
        dpid[x]=dpid[lc];
        if(x!=0)dp[dpid[x]][1]=add(dp[dpid[x]][1],1);
    }
    else{

        dpid[x]=-1;
        for(int i=0;i<maxalp;i++){
            int id=adj[x][i];
            if(id==-1)continue;
            if(dpid[x]==-1){
                dpid[x]=dpid[id];
                continue;
            }

            mrg(dpid[x],dpid[id]);

        }
        if(x!=0)dp[dpid[x]][1]=add(dp[dpid[x]][1],1);
    }

}
int go(){

    dfs(0);

    return dp[dpid[0]][m];
}

int main(){

    ///freopen("test.txt","r",stdin);

    memset(adj,-1,sizeof(adj));
    for(int i=0;i<maxn;i++){
        lp[i]=1e9;
        rp[i]=-1e9;
    }

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        cin>>s[i];
    }
    sort(s+1,s+n+1,cmp);

    /*if(n==2 && m==1){
        if(m==1)return 10;
    }*/

    int lst=0;
    for(int i=1;i<=n;i++){
        if(ins(s[i],lst+1)){lst++;s[lst]=s[i];}
    }
    n=lst;
    if(n<m){
        printf("0\n");
        return 0;
    }
    prek(0);

    memset(fpar,-1,sizeof(fpar));
    fpar[0][0]=0;
    for(int i=1;i<=n;i++){

        for(int j=0;j<vct[i].size();j++){
            int l=vct[i][j].ff;
            int x=vct[i][j].ss;

            //printf("%d %d %d AA ",l,i,x);
            //cout<<get_string_by_node(x)<<endl;

            for(int k=1;k<=m;k++){
                if(fpar[l-1][k-1]!=-1){
                    fpar[i][k]=x;
                }
            }
        }
    }

    if(fpar[n][m]==-1){
        printf("0\n");
        return 0;
    }
    //printf("OP\n");

    vector<string>rezset;
    pii curr={n,m};
    while(curr!=(pii){0,0}){
        rezset.pb(get_string_by_node(fpar[curr.ff][curr.ss]));
        ///printf("%d %d CCC\n",curr,fpar[curr]);
        curr.ff=lp[fpar[curr.ff][curr.ss]]-1;
        curr.ss--;
    }


    printf("%d\n",go());


    for(int i=0;i<rezset.size();i++){
        cout<<rezset[i]<<endl;
    }


    return 0;
}
