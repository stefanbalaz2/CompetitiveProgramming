/**


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
int trans[maxn*2][maxalp],len[maxn*2],link[maxn*2],last,cnt,frpos[maxn*2];

void append(int c){

    int curr=last;
    len[cnt]=len[last]+1;
    frpos[cnt]=len[cnt];
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
    frpos[clone]=frpos[q];
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

int dp[maxn*2],n1,n2;
vector<int>vect[maxn*2];
void go(int x){

    dp[x]=0;
    if(frpos[x]<=n1)dp[x]=1;
    else dp[x]=2;

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        go(id);

        dp[x]|=dp[id];
    }

}

void go2(int x,string p){

    if(dp[x]!=3)return;
    cout<<p<<endl;
    for(int i=0;i<26;i++){
        int id=trans[x][i];
        go2(id,p+( (char)('a'+i) ));
    }

}

int main() {

    freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    string s1,s2,s;
    cin>>s1>>s2;

    n1=s1.size();
    n2=s2.size();

    s=s1;
    s.pb(26+'a');
    s+=s2;

    build(s);

    for(int i=0;i<cnt;i++){
        if(link[i]==-1)continue;
        vect[link[i]].pb(i);
    }

    go(0);

    string p;
    go2(0,p);

    return 0;
}
