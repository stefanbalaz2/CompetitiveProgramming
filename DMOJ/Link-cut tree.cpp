#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
typedef pair<int,int> pii;
typedef set<int>::iterator usit;
typedef pair<bool,int> pbi;
const int maxq=1e5+10;
const int maxn=1e5+10;
vector<int>vect[maxn],q_edges[maxn];
int deg[maxn],disc[maxn],low[maxn],globpos[maxn],pos[maxn],tim,rebuild_nodes[maxn],brstek,brcomp,n,q,qsum[maxn],rt[maxn],rez[maxn],br,parent[maxn];
int level[maxn],dp[maxn][20];
vector<int>vc[maxn];
set<int>validni;
pii stek[maxn*5];
struct query{
    int u,v,w;
}kveri[maxq];
struct bicomp{

    set<int>nodes;
    vector<int>kveri;

    void ubaci_node(int x){
        nodes.insert(x);
    }

    void ubaci_kveri(int x){
        kveri.pb(x);
    }

}bc[4*maxn];
struct node{
    set<int>bcs;

    void ubaci_bc(int x){
        bcs.insert(x);
    }
    void izbaci(int x){
        bcs.erase(x);
    }
    void ispis(){
        printf("ISPIS KOMPONENTI\n");
        for(usit it=bcs.begin();it!=bcs.end();it++)printf("%d ",*it);
        printf("\n");
    }
}nd[maxn];
void leveluj(int x,int lvl){

    level[x]=lvl;
    for(int i=0;i<vc[x].size();i++){
        int id=vc[x][i];
        leveluj(id,lvl+1);
    }

}
int lca(int x,int y){

    int h=log2(n);

    if(level[x]<level[y])swap(x,y);

    for(int i=h;i>=0;i--){
        if(level[dp[x][i]]<level[y])continue;
        x=dp[x][i];
    }
    if(x==y)return x;

    for(int i=h;i>=0;i--){
        if(dp[x][i]==dp[y][i])continue;
        x=dp[x][i];
        y=dp[y][i];
    }

    return dp[x][0];
}
bool check(){

    for(int i=2;i<=n;i++){
        vc[parent[i]].pb(i);
        dp[i][0]=parent[i];
    }

    int h=log2(n);
    for(int i=1;i<=h;i++)for(int j=1;j<=n;j++)dp[j][i]=dp[dp[j][i-1]][i-1];
    leveluj(1,1);

    for(int i=1;i<=q;i++){
        if(lca(kveri[i].u,kveri[i].v)!=kveri[i].w)return false;
    }
    return true;
}
int root(int x){
    if(rt[x]==x)return x;
    else return rt[x]=root(rt[x]);
}
void join(int x,int y){
    y=root(y);
    if(y==x)return;
    rt[y]=x;
}
pbi u_istoj_bc(int x,int y){

    if(nd[x].bcs.size()>nd[y].bcs.size())swap(x,y);

    for(usit it=nd[x].bcs.begin();it!=nd[x].bcs.end();it++){
        if(nd[y].bcs.find(*it)!=nd[y].bcs.end())return {1,*it};
    }

return {0,-1};
}
void add_edge(int x,int y){

    q_edges[x].pb(y);
    deg[y]++;

    vect[x].pb(y);
    vect[y].pb(x);
}
void dfs_bicomps(int x,int prv,int root,vector<vector<int> > &ret){

    disc[x]=++tim;
    low[x]=disc[x];
    int child=0;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(globpos[id])continue;
        if(rebuild_nodes[id]==0)continue;

        if(id==prv)continue;
        else if(disc[id]==0){

            stek[++brstek]=(pii){x,id};

            child++;
            dfs_bicomps(id,x,root,ret);

            low[x]=min(low[x],low[id]);

            if((low[id]>=disc[x] && x!=root)||(x==root && child>1)){

                vector<int>pom;
                while(stek[brstek]!=(pii){x,id}){
                    pom.pb(stek[brstek].ff);
                    pom.pb(stek[brstek].ss);
                    brstek--;
                }
                pom.pb(stek[brstek].ff);
                pom.pb(stek[brstek].ss);
                brstek--;

                ret.pb(pom);
            }

        }
        else if(disc[id]<low[x]){
            low[x]=disc[id];
            stek[++brstek]={x,id};
        }

    }

}
void find_bicomps(int x,vector<vector<int> > &ret){/// mogu se ponavljati cvorovi u ret

    brstek=0;
    dfs_bicomps(x,0,x,ret);

    vector<int>pom;
    while(brstek){
        pom.pb(stek[brstek].ff);
        pom.pb(stek[brstek].ss);
        brstek--;
    }
    ret.pb(pom);
}
void init(){

    for(int i=1;i<=n;i++)rebuild_nodes[i]=1;
    /// izdvoj bc
    for(int i=1;i<=n;i++){
        if(pos[i])continue;

        vector<vector<int> >pom_comps;
        find_bicomps(i,pom_comps);

        for(int j=0;j<pom_comps.size();j++){
            brcomp++;

            for(int k=0;k<pom_comps[j].size();k++){
                int id=pom_comps[j][k];
                pos[id]=1;

                bc[brcomp].ubaci_node(id);
                nd[id].ubaci_bc(brcomp);
            }

        }
    }

    /// pogledaj kverije
    for(int i=1;i<=q;i++){

        int idu=kveri[i].u;
        int idv=kveri[i].v;
        int idw=kveri[i].w;

        if(idu==idw || idv==idw)continue;

        pbi pom=u_istoj_bc(idu,idv);

        if(!pom.ff)qsum[idw]--;
        else bc[pom.ss].ubaci_kveri(i);
    }

    for(int i=1;i<=n;i++)
        if(deg[i]==0 && qsum[i]==0)validni.insert(i);

    memset(pos,0,sizeof(pos));
    memset(disc,0,sizeof(disc));
    memset(low,0,sizeof(low));

    for(int i=1;i<=n;i++)rebuild_nodes[i]=0;
}
void go(){

    vector<int>vld;

    for(usit it=validni.begin();it!=validni.end();it++)vld.pb((*it));
    validni.clear();

    ///printf("%d AA\n",x);

    for(int i=0;i<vld.size();i++){
        int x=vld[i];

        rez[++br]=x;
        globpos[x]=1;
        for(int i=0;i<q_edges[x].size();i++){
            int id=q_edges[x][i];
            deg[id]--;

            if(qsum[id]==0 && deg[id]==0)validni.insert(id);
        }
    }

    set<int>bcs;
    for(int i=0;i<vld.size();i++){
        int x=vld[i];

        for(usit it=nd[x].bcs.begin();it!=nd[x].bcs.end();it++)bcs.insert(*it);
    }


    /// izbrisi bc iz nodova i obelezi za rebuild
    for(usit it=bcs.begin();it!=bcs.end();it++){
        int id=(*it);

        for(usit it2=bc[id].nodes.begin();it2!=bc[id].nodes.end();it2++){
            int id2=(*it2);
            if(globpos[id2])continue;

            rebuild_nodes[id2]=1;
            nd[id2].izbaci(id);
        }
    }

    /// nadji bc
    for(usit it=bcs.begin();it!=bcs.end();it++){
        int id=(*it);

        for(usit it2=bc[id].nodes.begin();it2!=bc[id].nodes.end();it2++){
            int id2=(*it2);
            if(pos[id2])continue;
            if(globpos[id2])continue;

            vector<vector<int> >pom;
            find_bicomps(id2,pom);
            for(int i=0;i<pom.size();i++){
                brcomp++;

                for(int j=0;j<pom[i].size();j++){
                    int pid=pom[i][j];
                    pos[pid]=1;

                    bc[brcomp].ubaci_node(pid);
                    nd[pid].ubaci_bc(brcomp);
                }
            }
        }
    }

    /// reset pos
    for(usit it=bcs.begin();it!=bcs.end();it++){
        int id=(*it);

        for(usit it2=bc[id].nodes.begin();it2!=bc[id].nodes.end();it2++){
            int id2=(*it2);
            pos[id2]=0;
            disc[id2]=0;
            low[id2]=0;
            rebuild_nodes[id2]=0;
        }
    }

    /// raspodeli kverije
    for(usit it=bcs.begin();it!=bcs.end();it++){
        int id=(*it);

        for(int j=0;j<bc[id].kveri.size();j++){
            int i=bc[id].kveri[j];

            int idu=kveri[i].u;
            int idv=kveri[i].v;
            int idw=kveri[i].w;

            if(idu==idw || idv==idw)continue;

            pbi pom=u_istoj_bc(idu,idv);

            if(!pom.ff)qsum[idw]--;
            else bc[pom.ss].ubaci_kveri(i);

            if(qsum[idw]==0 && deg[idw]==0)validni.insert(idw);
        }
    }

    /// clear memory
    for(usit it=bcs.begin();it!=bcs.end();it++){
        int id=(*it);
        bc[id].nodes.clear();
        bc[id].kveri.clear();
    }
    for(int i=0;i<vld.size();i++){
        int x=vld[i];
        nd[x].bcs.clear();
    }

    ///printf("%d GOTOV\n",x);

    /*for(int i=1;i<=n;i++){
        printf("\n%d  CVORRRRRRRRR\n",i);
        nd[i].ispis();
    }*/

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&q);
    for(int i=1;i<=q;i++){
        scanf("%d %d %d",&kveri[i].u,&kveri[i].v,&kveri[i].w);

        if(kveri[i].u!=kveri[i].w && kveri[i].v!=kveri[i].w)qsum[kveri[i].w]++;

        if(kveri[i].u!=kveri[i].w)add_edge(kveri[i].w,kveri[i].u);
        if(kveri[i].v!=kveri[i].w)add_edge(kveri[i].w,kveri[i].v);
    }

    init();

    for(int i=1;i<=n;i++)go();

    for(int i=1;i<=n;i++)rt[i]=i;
    while(br){
        int id=rez[br];

        for(int i=0;i<q_edges[id].size();i++){
            int id2=q_edges[id][i];

            parent[root(id2)]=id;
        }

        for(int i=0;i<q_edges[id].size();i++){
            int id2=q_edges[id][i];

            join(id,id2);
        }

        br--;
    }

    for(int i=1;i<=n;i++){
        if(parent[i]==0 && i!=1)parent[i]=1;
    }

    ///printf("%d CHECK\n",check());

    for(int i=1;i<=n;i++){
        printf("%d ",parent[i]);
    }

return 0;
}
