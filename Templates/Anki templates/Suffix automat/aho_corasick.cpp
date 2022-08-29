/**

    https://codeforces.com/problemset/problem/963/D

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
int link[maxn],nxt[maxn][maxalp],isleaf[maxn],cnt=1,root=0;
int par[maxn],cpar[maxn],nxt_leaf[maxn],k[maxn],msz[maxn];

void ins(int x,string &s,int c,int id){


    while(1){

        if(c==s.size()){
            isleaf[x]=id;
            return;
        }

        int sc=s[c]-'a';

        if(nxt[x][sc]==-1){
            par[cnt]=x;
            cpar[cnt]=sc;
            nxt[x][sc]=cnt++;
        }

        x=nxt[x][sc];
        c=c+1;
    }
}
int get_link(int x);
int get_nxt(int x,int c){
    if(nxt[x][c]!=-1)return nxt[x][c];
    if(x==0)return 0;
    return nxt[x][c]= get_nxt(get_link(x),c);
}
int get_link(int x){
    if(link[x]!=-1)return link[x];
    if(x==0)return -1;
    if(par[x]==0)return 0;
    return link[x]=  get_nxt(get_link(par[x]),cpar[x]);
}
int get_leaf(int x){

    if(nxt_leaf[x]!=-1)return nxt_leaf[x];
    if(x==0)return 0;

    if(isleaf[x])nxt_leaf[x]=x;
    else nxt_leaf[x]=get_leaf(get_link(x));

    return nxt_leaf[x];

}
vector<int>vect[maxn];

int e=0;
void chk(string &s,string p){

    if(s.size()<p.size())return;

    for(int i=0;i<p.size();i++){
        if(p[i]!=s[i])return;
    }

    e=1;
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    string s;
    cin>>s;

    chk(s,"abaaaaaabbbbbaaa");

    memset(link,-1,sizeof(link));
    memset(nxt_leaf,-1,sizeof(nxt_leaf));
    memset(nxt,-1,sizeof(nxt));

    int q;
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d",&k[i]);
        string m;
        cin>>m;
        msz[i]=m.size();
        ins(root,m,0,i);
    }


    int curr=root;
    for(int i=0;i<s.size();i++){

        int c=s[i]-'a';
        curr=get_nxt(curr,c);


        int pom=get_leaf(curr);
        while(pom!=0){
            vect[isleaf[pom]].pb(i+1);
            pom=get_leaf(get_link(pom));
        }

    }

    for(int i=1;i<=q;i++){
        if(vect[i].size()<k[i]){
            printf("-1\n");
            continue;
        }
        int rez=1e9;
        for(int j=k[i]-1;j<vect[i].size();j++)
            rez=min(rez,vect[i][j]- (vect[i][j-k[i]+1]-msz[i]+1) +1 );

        printf("%d\n",rez);
    }

    return 0;
}
