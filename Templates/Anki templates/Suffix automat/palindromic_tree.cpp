#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<iostream>
#include<assert.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=4e5+10;
const int maxalp=26;
int link[maxn],last,trans[maxn][maxalp],len[maxn],cnt;
string s;

void init(){

    memset(len,-1,sizeof(len));
    memset(trans,-1,sizeof(trans));
    last=1;
    cnt=2;
    link[0]=0;
    link[1]=0;
    len[0]=-1;
    len[1]=0;

}
int append(int pos){

    int curr=last;
    while(true){
        if(pos-1-len[curr]>=0 && s[pos]==s[pos-1-len[curr]])break;
        curr=link[curr];
    }

    int c=s[pos]-'a';

    if(trans[curr][c]!=-1){
        last=trans[curr][c];
        return 0;
    }

    int q=cnt++;
    trans[curr][c]=q;
    last=q;
    len[q]=len[curr]+2;

    curr=link[curr];
    while(true){
        if(pos-1-len[curr]>=0 && s[pos]==s[pos-1-len[curr]])break;
        curr=link[curr];
    }

    if(trans[curr][c]==q)link[q]=1;
    else link[q]=trans[curr][c];


    return 1;

}

int main(){

    ///freopen("test.txt","r",stdin);
    //freopen("moj.txt","w",stdout);

    init();
    cin>>s;
    int rez=0;
    for(int i=0;i<s.size();i++){
        rez+=append(i);
        printf("%d ",rez);
    }

    return 0;
}
