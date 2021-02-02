/*

    idea: kuhn from biggest to lowest
        and compressing the paths with dsu


*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=4e5+10;

int n,m,match[maxn],pos[maxn],dp[maxn],par[maxn];
vector<int>vect[maxn],p;
vector<pii>niz;

int root(int x){
    if(par[x]==x)return x;
    else return par[x]=root(par[x]);
}
int join(int x,int y){
    x=root(x);
    y=root(y);
    par[y]=x;
}
void init_dsu(){
    for(int i=1;i<=m;i++){
        par[i]=i;
    }
}

void add_edge(int a,int b){

    vect[a].pb(b);
    vect[b].pb(a);

}

int kuhn(int x){

    ///printf("%d XX\n",x);

    if(dp[x])return 0;

    pos[x]=1;
    p.pb(x);

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(match[id]==-1){
            match[id]=x;
            return 1;
        }
    }

    random_shuffle(vect[x].begin(),vect[x].end());
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        int id2=root(match[id]);
        ///printf("%d  %d IDID\n",match[id],pos[match[id]]);
        if(pos[id2])continue;
        ///if(match[])

        if(kuhn(id2)){
            match[id]=x;
            join(x,id2);
            return 1;
        }

    }

    dp[x]=1;

    return 0;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    init_dsu();

    memset(match,-1,sizeof(match));
    for(int i=1;i<=m;i++){
        int a,b,w;
        scanf("%d %d %d",&a,&b,&w);
        add_edge(i,a+m);
        add_edge(i,b+m);
        niz.pb({w,i});
    }

    sort(niz.begin(),niz.end());

    int rez=0;
    for(int i=niz.size()-1;i>=0;i--){
        int id=niz[i].ss;

       /// printf("%d AAA\n",i);
        if(kuhn(id)){
            rez+=niz[i].ff;
            ///printf("YESYESYES\n");
        }

        for(int j=0;j<p.size();j++)pos[p[j]]=0;
        p.clear();
    }

    printf("%d\n",rez);

    return 0;
}
