/**
    https://acm.timus.ru/problem.aspx?space=1&num=1960

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;


const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=1e5+10;
const int maxalp=26;
string s;
int cnt,link[maxn],len[maxn],trans[maxn][maxalp],last;
void prep(){

    last=1;
    cnt=2;
    link[0]=0;
    link[1]=0;
    len[0]=-1;
    len[1]=0;
    memset(trans,-1,sizeof(trans));

}
int append(int pos,int c){

    int curr=last;
    while(pos-len[curr]-1<0 || s[pos-len[curr]-1]!=s[pos]){curr=link[curr];}

    if(trans[curr][c]!=-1){
        last=trans[curr][c];
        return 0;
    }

    last=cnt;
    len[last]=len[curr]+2;
    trans[curr][c]=cnt++;

    curr=link[curr];
    while(pos-len[curr]-1<0 || s[pos-len[curr]-1]!=s[pos]){curr=link[curr];}
    link[last]=trans[curr][c];
    if(trans[curr][c]==last)link[last]=1;

    return 1;
}

int main(){

    ///freopen("test.txt","r",stdin);

    cin>>s;

    prep();

    int rez=0;
    for(int i=0;i<s.size();i++){
        rez+=append(i,s[i]-'a');
        printf("%d ",rez);
    }
    printf("\n");

    return 0;
}
