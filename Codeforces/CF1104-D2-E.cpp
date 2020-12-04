/*

    idea:   https://codeforces.com/blog/entry/64722

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll>pii;
const int maxn=3e5+10;
int p[maxn],level[maxn],plen,n,m,k,pos[maxn];
vector<int>vect[maxn],leaf;
void go(int x,int prv,int lvl,int &ret){


    p[x]=prv;
    level[x]=lvl;
    pos[x]=1;

    if(lvl==plen)ret=x;


    int child=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        child++;

        go(id,x,lvl+1,ret);
    }

    if(child==0)leaf.pb(x);
}
void solve_path(){

    int ret=-1;
    go(1,0,1,ret);

    if(ret!=-1){

        printf("PATH\n");
        printf("%d\n",level[ret]);
        while(ret!=0){
            printf("%d ",ret);
            ret=p[ret];
        }
        printf("\n");
        return ;
    }

    printf("CYCLES\n");
    for(int i=0;i<min((int)leaf.size(),k);i++){
        int x=leaf[i];

        vector<int>cand;
        for(int j=0;j<vect[x].size();j++){
            int id=vect[x][j];
            if(id==p[x])continue;
            cand.pb(id);
            if(cand.size()==2)break;
        }

        int id1=cand[0];
        int id2=cand[1];
        if((level[x]-level[id1]+1)%3!=0){
            printf("%d\n",level[x]-level[id1]+1);
            while(1){
                printf("%d ",x);
                if(x==id1)break;
                x=p[x];
            }
            printf("\n");
        }
        else if((level[x]-level[id2]+1)%3!=0){
            printf("%d\n",level[x]-level[id2]+1);
            while(1){
                printf("%d ",x);
                if(x==id2)break;
                x=p[x];
            }
            printf("\n");
        }
        else{
            if(level[id1]>level[id2])swap(id1,id2);

            printf("%d\n",level[id2]-level[id1]+2);
            printf("%d ",x);
            while(1){
                printf("%d ",id2);
                if(id2==id1)break;
                id2=p[id2];
            }
            printf("\n");
        }

    }
}
int main(){

    ///freopen("test2.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d %d",&n,&m,&k);
    plen=n/k+(n%k>0);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);

        vect[u].pb(v);
        vect[v].pb(u);
    }

    solve_path();


    return 0;
}
