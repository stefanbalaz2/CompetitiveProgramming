/*

    idea:

     - construct the dfstree
     - match the back edges and children edges
     - if we have 1 unmatched edge from the previous step we match it with the parent edge

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
const int maxn=1e5+10;
vector<int>vect[maxn];
int level[maxn],n,m,pos[maxn];
struct r{
    int a,b,c;
};
vector<r>rez;
int dfs(int x,int prv,int lvl){

    level[x]=lvl;
    pos[x]=1;

    vector<int>cand;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        if(pos[id] && level[id]>level[x])continue;

        if(pos[id] && level[id]<level[x])cand.pb(id);
        else if(!dfs(id,x,lvl+1))cand.pb(id);
    }

    int ret=0;

    ///printf("%d %d XXX\n",x,prv);
    ///for(int i=0;i<cand.size();i++)printf("%d ",cand[i]);
    ///printf("\n\n");

    for(int i=0;i<cand.size();i+=2){
        if(i==cand.size()-1){
            rez.pb({cand[i],x,prv}),ret=1;
            ///printf("%d XXJEBOTE\n",x);
        }
        else rez.pb({cand[i],x,cand[i+1]});
    }

    return ret;
}
int main(){

	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
	}

	if(m%2){
        printf("No solution\n");
        return 0;
	}

    dfs(1,0,0);

    for(int i=0;i<m/2;i++){printf("%d %d %d\n",rez[i].a,rez[i].b,rez[i].c);}

	return 0;
}
