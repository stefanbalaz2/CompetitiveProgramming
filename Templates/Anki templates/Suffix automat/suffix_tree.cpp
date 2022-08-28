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
int trans[maxn*2][maxalp],len[maxn*2],link[maxn*2],last,cnt,frpos[maxn*2];

string s;

void append(int c){

    int curr=last;
    len[cnt]=len[last]+1;
    frpos[cnt]=len[cnt]-1;
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

vector<int>vect[maxn];
int stt[maxn][maxalp],lps[maxn],rps[maxn];
void go(int x){

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        int tc=s[frpos[id]-len[x]]-'a';
        int lpos=frpos[id]-len[x];
        int rpos=frpos[id]-len[id]+1;

        ///printf("%d %d | %d %d %d %d AA\n",x,id,tc,lpos,rpos,frpos[id]);

        stt[x][tc]=id;
        lps[id]=lpos;
        rps[id]=rpos;

        printf("%d |",x);
        for(int j=lpos;j>=rpos;j--)printf("%c",s[j]);
        printf("| %d\n",id);

        go(id);

    }

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    cin>>s;
    s+=(char)(26+'a');
    reverse(s.begin(),s.end());
    build(s);

    for(int i=1;i<cnt;i++)
        vect[link[i]].pb(i);

    go(0);

    return 0;
}
