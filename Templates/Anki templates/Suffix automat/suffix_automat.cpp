/**

    https://www.spoj.com/problems/SUBLEX/

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

const int maxn=1e5+10;
const int maxalp=30;
int trans[maxn*2][maxalp],len[maxn*2],link[maxn*2],last,cnt;

void append(int c){

    int curr=last;
    len[cnt]=len[last]+1;
    while(curr!=-1 && trans[curr][c]==-1){
        trans[curr][c]=cnt;
        curr=link[curr];
    }
    last=cnt;
    cnt++;
    if(curr==-1){
        link[last]=0;
        return;
    }
    int q=trans[curr][c];
    if(len[curr]+1==len[q]){
        link[last]=q;
        return;
    }

    int clone=cnt++;
    for(int i=0;i<maxalp;i++)trans[clone][i]=trans[q][i];
    link[clone]=link[q];
    link[q]=clone;
    link[last]=clone;
    len[clone]=len[curr]+1;

    while(curr!=-1 && trans[curr][c]==q){
        trans[curr][c]=clone;
        curr=link[curr];
    }

}
void build(string &s){

    cnt=1;
    memset(trans,-1,sizeof(trans));
    memset(len,-1,sizeof(len));
    memset(link,-1,sizeof(link));
    last=0;
    len[last]=0;

    for(int i=0;i<s.size();i++)
        append(s[i]-'a');
}

ll inf=1e10;
ll dp[maxn*2];
ll go(int x){

    if(dp[x]!=-1)return dp[x];
    dp[x]=1;
    for(int i=0;i<maxalp;i++)
        if(trans[x][i]!=-1)
            dp[x]=dp[x]+go(trans[x][i]);

    dp[x]=min(dp[x],inf);
    return dp[x];
}

void go2(int x,ll k){

    if(k==0)return;

    for(int i=0;i<maxalp;i++){
        if(trans[x][i]==-1)continue;
        int id=trans[x][i];

        if(go(id)>=k){
            printf("%c",'a'+i);
            go2(id,k-1);
            return;
        }
        k-=go(id);
    }

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    string s;
    cin>>s;
    build(s);
    memset(dp,-1,sizeof(dp));

    int t;
    scanf("%d",&t);
    while(t--){

        ll k;
        scanf("%lld",&k);

        go2(0,k);
        printf("\n");
    }

    return 0;
}
