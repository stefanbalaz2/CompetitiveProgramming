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
int last,len[maxn*2],frpos[maxn*2],isnclone[maxn*2],link[maxn*2],trans[maxn*2][maxalp],cnt;



void append(int c){

    int cur=last;
    last=cnt++;
    len[last]=len[cur]+1;
    frpos[last]=len[last]-1;
    isnclone[last]=1;
    while(cur!=-1 && trans[cur][c]==-1){
        trans[cur][c]=last;
        cur=link[cur];
    }

    if(cur==-1){
        link[last]=0;
        return;
    }
    int q=trans[cur][c];
    if(len[q]==len[cur]+1){
        link[last]=q;
        return;
    }

    int clone=cnt++;
    frpos[clone]=frpos[q];
    link[clone]=link[q];
    link[q]=clone;
    link[last]=clone;
    len[clone]=len[cur]+1;
    for(int i=0;i<maxalp;i++)trans[clone][i]=trans[q][i];

    while(cur!=-1 && trans[cur][c]==q){
        trans[cur][c]=clone;
        cur=link[cur];
    }

}

void build(string &s){

    len[0]=0;
    cnt=1;
    link[0]=-1;
    memset(trans,-1,sizeof(trans));

    for(int i=0;i<s.size();i++)
        append(s[i]-'a');


}
vector<int>vect[maxn*2];
int cntt[maxn*2];
void go(int x){

    cntt[x]=isnclone[x];
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        go(id);
        cntt[x]+=cntt[id];
    }

}


int main() {


    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);


    string s;
    cin>>s;

    build(s);

    for(int i=1;i<cnt;i++)
        vect[link[i]].pb(i);

    go(0);

    while(1){

        cin>>s;

        int curr=0;
        int e=0;
        for(int i=0;i<s.size();i++){
            int c=s[i]-'a';

            printf("%d %d AA\n",c,trans[curr][c]);
            if(trans[curr][c]==-1){
                printf("0 no\n");
                e=1;
                break;
            }
            curr=trans[curr][c];
        }
        if(!e)printf("%d\n",cntt[curr]);

    }

    return 0;
}
