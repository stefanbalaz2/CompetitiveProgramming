/*

    idea: https://img.atcoder.jp/arc087/editorial.pdf

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
const int maxn=1e5+10;
int cnt,nd[maxn][2],n,root,cnt1,cnt2;
ll l,rez;

void ins(int x,string &s,int dep){

    for(int i=0;i<s.size();i++){

        int c=s[i]-48;

        if(nd[x][c]==0){
            nd[x][c]=++cnt;
            x=cnt;
        }
        else{
            x=nd[x][c];
        }

    }

}

void dfs(int x,int lvl){

    if(nd[x][0]==0){}
    else dfs(nd[x][0],lvl+1);

    if(nd[x][1]==0){}
    else dfs(nd[x][1],lvl+1);

    if((nd[x][1]==0 && nd[x][0]!=0)||(nd[x][1]!=0 && nd[x][0]==0)){
        rez^=((l-lvl)&(-(l-lvl)));
    }
}

int main(){

    ///freopen("test.txt","r",stdin);

    cin>>n>>l;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        ins(root,s,0);
    }

    dfs(root,0);


    if(rez!=0)cout<<"Alice"<<endl;
    else cout<<"Bob"<<endl;

	return 0;
}
