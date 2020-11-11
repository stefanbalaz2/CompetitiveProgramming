/*

    idea:   https://codeforces.com/blog/entry/63099

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=1510;
int n,lcpref[maxn],rdp[maxn],temp[maxn],pref[maxn],a[maxn],m,s,k,rpref[maxn],inf=1e9;
vector<pii>p,cand;
vector<int>open[maxn],close[maxn];
pii dp[maxn][14];
bool srt(pii a,pii b){
    return (a.ss<b.ss)||(a.ss==b.ss && a.ff<b.ff);
}
void prek(){

    for(int i=1;i<=n;i++)dp[i][0]={inf,-1};
    for(int i=0;i<cand.size();i++)
        dp[cand[i].ss][0]=min(dp[cand[i].ss][0],{cand[i].ff,i});


    int h=log2(n);
    for(int i=1;i<=h;i++)
    for(int j=1;j<=n;j++){
        if(j+(1<<(i-1))<=n)dp[j][i]=min(dp[j][i-1],dp[j+(1<<(i-1))][i-1]);
        else dp[j][i]=dp[j][i-1];
    }


    memset(lcpref,-1,sizeof(lcpref));
    for(int i=0;i<cand.size();i++)lcpref[cand[i].ss]=i;

    int curr=-1;
    for(int i=1;i<=n;i++){
        if(lcpref[i]==-1)lcpref[i]=curr;
        else curr=lcpref[i];
    }
}
int query(int l,int r){
    if(l>r)return -1;
    int h=log2(r-l+1);
    return (min(dp[l][h],dp[r-(1<<h)+1][h])).ss;
}
bool check(int x){

    memset(pref,0,sizeof(pref));
    for(int i=1;i<=n;i++){
        pref[i]=pref[i-1]+(a[i]<=x);
    }

    int ret=0;
    for(int i=0;i<cand.size();i++){
        int l=cand[i].ff;
        int r=cand[i].ss;

        rdp[i+1]=pref[r]-pref[l-1];

        ret=max(ret,rdp[i+1]);
    }

    for(int i=2;i<=min(m,(int)cand.size());i++){
        for(int j=1;j<=cand.size();j++)rpref[j]=max(rpref[j-1],rdp[j]);

        for(int j=1;j<=cand.size();j++){
            int l=cand[j-1].ff;
            int r=cand[j-1].ss;

            temp[j]=0;


            int overlap=query(l,r-1);
            if(overlap!=-1){
                int olr=cand[overlap].ss;
                temp[j]=max(temp[j],pref[r]-pref[olr]+rdp[overlap+1]);
            }


            int pind=lcpref[l-1];
            if(pind!=-1)temp[j]=max(temp[j],pref[r]-pref[l-1]+rpref[pind+1]);

            ret=max(ret,temp[j]);
        }


        memcpy(rdp,temp,sizeof(temp));
    }



    return (ret>=k);
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d %d %d",&n,&s,&m,&k);

    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    set<pii>st;
    for(int i=1;i<=s;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if(st.find({l,r})!=st.end())continue;
        p.pb({l,r});
        open[l].pb(p.size()-1);
        close[r].pb(p.size()-1);
        st.insert({l,r});
    }

    multiset<int>minn;
    for(int i=1;i<=n;i++){

        for(int j=0;j<open[i].size();j++)minn.insert(i);

        for(int j=0;j<close[i].size();j++){
            int id=close[i][j];
            minn.erase(minn.find(p[id].ff));

            if(minn.size()==0 || (*minn.begin())>p[id].ff){
                cand.pb(p[id]);
            }

        }
    }
    sort(cand.begin(),cand.end(),srt);
    prek();


    int l=1;
    int r=1e9;
    int sr,ret=-1;
    while(l<=r){
        sr=(l+r)/2;
        if(check(sr)){
            r=sr-1;
            ret=sr;
        }
        else l=sr+1;
    }


    printf("%d\n",ret);

    return 0;
}
