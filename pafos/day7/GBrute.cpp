#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int maxn=2e5+10;
const int maxb=18;
int n,q;
vector<int>vect[maxn];
int level[maxn],par[maxb][maxn],prek_pos[maxn],node_time,nstart[maxn],nend[maxn],hpar[maxn],ncolor[maxn];
int sz[maxn];
int globn,tn;
int tree_node_cnt=0;

vector<pair<pii,int>>real_queries;
vector<pii> path_queries[maxn*4];
vector<pair<int,pii>>node_add[3][maxn];
vector<int>dp[maxn],dp_pref[maxn],tpref[maxn],tlazy[maxn],root[maxn];
int tcnt[maxn],dpcnt,dp_id[maxn];
int rez[maxn];

struct tree_node{
    int l,r,val;
}tnds[maxn*50];
struct qr{

    int tip,u,v,d;

};
vector<qr>qs;

void prek_base(int x,int prv,int h){

    par[0][x]=prv;
    level[x]=h;
    nstart[x]=++node_time;
    sz[x]=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || prek_pos[id]==0)continue;
        prek_base(id,x,h+1);
        sz[x]=max(sz[x],sz[id]);
    }
    nend[x]=++node_time;
    sz[x]++;

}
void prek_base_nodes(vector<int>&v){

    for(int i=0;i<v.size();i++)prek_pos[v[i]]=1;

    prek_base(v[0],0,1);

    for(int i=0;i<v.size();i++)prek_pos[v[i]]=0;

    int h=maxb-1;
    for(int i=0;i<h;i++)
    for(int j=0;j<v.size();j++)
        par[i+1][v[j]]=par[i][ par[i][v[j]] ];

}

int lca(int x,int y){

    int h=maxb-1;

    if(level[x]<level[y])swap(x,y);

    for(int i=h;i>=0;i--){
        if(level[par[i][x]]<level[y])continue;
        x=par[i][x];
    }

    if(x==y)return x;

    for(int i=h;i>=0;i--){
        if(par[i][x]==par[i][y])continue;
        x=par[i][x];
        y=par[i][y];
    }
    return par[0][x];
}
int get_dist(int x,int y,int lc){
    if(lc==-1)lc=lca(x,y);
    return level[x]+level[y]-2*level[lc];
}



void add_qry(int x,int l,int r,int lp,int rp,pii path){

    if(l>rp || r<lp)return;
    if(l>=lp && r<=rp){
        path_queries[x].pb(path);
        return;
    }
    int mid=(l+r)/2;
    add_qry(x*2,l,mid,lp,rp,path);
    add_qry(x*2+1,mid+1,r,lp,rp,path);
}
void dodaj_qry(pii path,int l,int r){
    //printf("%d %d | %d %d PATH\n",l,r,path.ff,path.ss);
    add_qry(1,0,q-1,l,r,path);
}


bool in_subtree(int x,int y){
    /// x u y
    if(nstart[y]<=nstart[x] && nstart[x]<=nend[y])return true;
    return false;
}
int get_entry_point(int x,pii a){

    int h=maxb-1;
    if((in_subtree(x,a.ff)&&in_subtree(a.ss,x)))return x;
    for(int i=h;i>=0;i--){
        if(level[par[i][x]]<level[a.ff] || (in_subtree(par[i][x],a.ff)&&in_subtree(a.ss,par[i][x])) )continue;
        x=par[i][x];
    }
    return par[0][x];
}
pair<int,pii>line_dist(pii a,pii b){

    if(level[a.ff]>level[b.ff])swap(a,b);

   // printf("%d %d | %d %d LINE\n",a.ff,a.ss,b.ff,b.ss);
    if(!in_subtree(b.ff,a.ff))return {get_dist(a.ff,b.ff,-1),{a.ff,b.ff} };


    int pt=get_entry_point(b.ss,a);

    if(level[pt]<level[b.ff])return {get_dist(pt,b.ff,-1),{pt,b.ff}};
    return {0,{pt,pt}};
}
pair<int,pii>find_distance(pii a,pii b){

    int lcaa=lca(a.ff,a.ss);
    pii a1(lcaa,a.ff);
    pii a2(lcaa,a.ss);

    int lcab=lca(b.ff,b.ss);
    pii b1(lcab,b.ff);
    pii b2(lcab,b.ss);

    pair<int,pii>ret=line_dist(a1,b1);
    ret=min(ret,line_dist(a1,b2));
    ret=min(ret,line_dist(a2,b2));
    ret=min(ret,line_dist(a2,b1));

    return ret;
}

pii path_intersect_single(pii a,pii b){

    if(level[a.ff]>level[b.ff])swap(a,b);

    if(!in_subtree(b.ff,a.ff))return {0,0};

    int pt=get_entry_point(b.ss,a);

    if(level[pt]<level[b.ff])return {0,0};
    return {b.ff,pt};

}
pii path_intersect(pii a,pii b){

    int lcaa=lca(a.ff,a.ss);
    pii a1(lcaa,a.ff);
    pii a2(lcaa,a.ss);

    int lcab=lca(b.ff,b.ss);
    pii b1(lcab,b.ff);
    pii b2(lcab,b.ss);

    pii pa11=path_intersect_single(a1,b1);
    pii pa12=path_intersect_single(a1,b2);
    pii pa21=path_intersect_single(a2,b1);
    pii pa22=path_intersect_single(a2,b2);

    if(level[pa11.ss]!=0 && level[pa11.ss]>level[pa12.ss])pa11=pa11;
    else{
        if(level[pa12.ss]!=0 && level[pa12.ss]>level[pa11.ss])pa11=pa12;
    }

    if(level[pa21.ss]!=0 && level[pa21.ss]>level[pa22.ss])pa21=pa21;
    else{
        if(level[pa22.ss]!=0 && level[pa22.ss]>level[pa21.ss])pa21=pa22;
    }

    if(pa11.ff==0)swap(pa11,pa21);
    if(pa21.ff==0)return pa11;

    return {pa11.ss,pa21.ss};
}

pii get_closer_points(int x,int y,int d){

    /// x priblizi y

    ///printf("%d %d | %d  priblizi\n",x,y,d);

    int lc=lca(x,y);

    int fd=get_dist(x,y,lc);
    if(fd<=d)return {x,d};
    assert((fd-d)%2==0);
    int c=(fd-d)/2;

    int ds=level[x]-level[lc];
    if(ds>=c){

        int goal=level[x]-c;
        int h=maxb-1;
        for(int i=h;i>=0;i--){
            if(level[par[i][x]]<goal)continue;
            x=par[i][x];
        }

        return {x,d+c};
    }
    else{
        d+=c;
        c-=ds;
        x=lc;

        int goal=level[y]-(level[y]-level[x]-c);
        int h=maxb-1;
        for(int i=h;i>=0;i--){
            if(level[par[i][y]]<goal)continue;
            y=par[i][y];
        }

        return {y,d};
    }

}
pair<pii,int>intersect(pii state,int d,pii path){

    if(state.ff==-1)return {path,0};

    /// nadjem dist
    pair<int,pii>dist=find_distance(state,path);

    //printf("%d %d %d AAAAAA\n",dist.ff,dist.ss.ff,dist.ss.ss);

    if(dist.ff==0){/// intersect
        state=path_intersect(state,path);
    }
    else{

        ///printf("%d | %d %d DISIT\n",dist.ff,dist.ss.ff,dist.ss.ss);

        pii pom;
        if(d==0)pom=get_closer_points(dist.ss.ff,dist.ss.ss,d);
        else{
            if(dist.ss.ff==state.ff)pom=get_closer_points(state.ff,dist.ss.ss,d);
            else pom=get_closer_points(state.ff,dist.ss.ff,d);
        }

        d=pom.ss;
        state={pom.ff,pom.ff};

    }

    return {state,d};
}


pair<pii,int> merge_vector(vector<pii>path,pii state,int state_d){

    for(int i=0;i<path.size();i++){
        //printf("%d %d | %d   - Merge -  %d %d\n",state.ff,state.ss,state_d,path_queries[x][i].ff,path_queries[x][i].ss);
        pair<pii,int>pom=intersect(state,state_d,path[i]);
        state=pom.ff;
        state_d=pom.ss;
        //printf("%d %d | %d   - Merge -  %d %d\n",state.ff,state.ss,state_d,path_queries[x][i].ff,path_queries[x][i].ss);
    }

}

void construct_queries(int x,int l,int r,pii state,int state_d){

    for(int i=0;i<path_queries[x].size();i++){
        //printf("%d %d | %d   - Merge -  %d %d\n",state.ff,state.ss,state_d,path_queries[x][i].ff,path_queries[x][i].ss);
        pair<pii,int>pom=intersect(state,state_d,path_queries[x][i]);
        state=pom.ff;
        state_d=pom.ss;
        //printf("%d %d | %d   - Merge -  %d %d\n",state.ff,state.ss,state_d,path_queries[x][i].ff,path_queries[x][i].ss);
    }

    if(l==r){
        if(qs[l].tip==3){
            real_queries.pb({state,qs[l].d-state_d});
        }
        return;
    }

    int mid=(l+r)/2;

    construct_queries(x*2,l,mid,state,state_d);
    construct_queries(x*2+1,mid+1,r,state,state_d);
}


int dfs_centroid(int x,int prv,int n,int &c){

    int sz=1;

    int e=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || !prek_pos[id])continue;

        int pom=dfs_centroid(id,x,n,c);
        if(c!=-1)return 0;

        if(pom>n/2)e=0;
        sz+=pom;
    }
    if(n-sz>n/2)e=0;

    if(e)c=x;

    return sz;
}
int get_centroid(vector<int>&nodes){

    for(int i=0;i<nodes.size();i++)prek_pos[nodes[i]]=1;

    int ret=-1;
    dfs_centroid(nodes[0],0,nodes.size(),ret);

    for(int i=0;i<nodes.size();i++)prek_pos[nodes[i]]=0;

    return ret;
}

void dfs_hld(int x,int prv,int hld_par){

    int idx=-1;
    hpar[x]=hld_par;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || !prek_pos[id])continue;
        if(idx==-1)idx=i;
        else{
            if(sz[vect[x][idx]]<sz[id])idx=i;
        }
    }

    if(idx==-1)return;

    swap(vect[x][0],vect[x][idx]);

    dfs_hld(vect[x][0],x,hld_par);
    for(int i=1;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || !prek_pos[id])continue;
        dfs_hld(id,x,id);
    }

}
void prek_hld_nodes(vector<int>&nodes){

    for(int i=0;i<nodes.size();i++)prek_pos[nodes[i]]=1;

    dfs_hld(nodes[0],0,nodes[0]);

    for(int i=0;i<nodes.size();i++)prek_pos[nodes[i]]=0;

}
void dfs_color(int x,int prv,int color){

    ncolor[x]=color;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || !prek_pos[id])continue;
        dfs_color(id,x,color);
    }

}
int prek_color_nodes(vector<int>&nodes){

    for(int i=0;i<nodes.size();i++)prek_pos[nodes[i]]=1;

    int x=nodes[0];
    int color=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(!prek_pos[id]){color++;continue;}
        dfs_color(id,x,color++);
    }

    for(int i=0;i<nodes.size();i++)prek_pos[nodes[i]]=0;

    return color;

}

void dodaj_offline_path(int id,int c){

    pii path=real_queries[id].ff;
    int d=real_queries[id].ss;

    int lc=c;

    int curr=path.ff;
    while(curr!=0){

        int p=hpar[curr];

        node_add[1][p].pb({d,{id,1}});
        node_add[1][curr].pb({d,{id,-1}});
        node_add[0][curr].pb({d,{id,1} });

        curr=par[0][p];
    }

    curr=path.ss;
    while(curr!=0){

        int p=hpar[curr];

        node_add[1][p].pb({d,{id,1}});
        node_add[1][curr].pb({d,{id,-1}});
        node_add[0][curr].pb({d,{id,1} });

        curr=par[0][p];
    }
    node_add[0][c].pb({d,{id,-1}});

    node_add[2][c].pb({d-1,{id,1} });

}

void mrg_dp(int x,int y){

    for(int i=0;i<dp[y].size();i++)
        dp[x][dp[x].size()-i-1]+=dp[y][dp[y].size()-i-1];

}
void bit_upd(int idx,int x,int val){

    if(x<0)return;
    ///printf("UPDATE %d %d\n",x,val);
    while(x+1<=tpref[idx].size()){
        tpref[idx][x]+=val;
       /// printf("%d ",x);
        int pom=x+1;
        pom+=(pom&(-pom));
        x=pom-1;
    }
    tcnt[idx]+=val;
   /// printf("\n");

}
int bit_get(int idx,int x){

    x--;
    int val=0;
    if(x>=0){
        while(x+1>0){
            val+=tpref[idx][x];
            int pom=x+1;
            pom-=(pom&(-pom));
            x=pom-1;
        }
    }


    return tcnt[idx]-val;

}
int bit_get_real(int idx,int x){

    ///x--;
    int val=0;
    //printf("GET %d\n",x);
    if(x>=0){
        while(x+1>0){
            //printf("|%d ",x);
            val+=tpref[idx][x];
            int pom=x+1;
            pom-=(pom&(-pom));
            x=pom-1;
        }
    }
   // printf("\n");

    return val;

}
void bit_upd_lazy_single(int idx,int x,int val){

    if(x<0 || tlazy[idx].size()<=x)return;
    while(x+1<=tlazy[idx].size()){
        tlazy[idx][x]+=val;
        int pom=x+1;
        pom+=(pom&(-pom));
        x=pom-1;
    }

}
void bit_upd_lazy(int idx,int l,int r,int val){
    bit_upd_lazy_single(idx,l,val);
    bit_upd_lazy_single(idx,r,-val);
    dp_pref[idx][r]+=val;
}
int bit_get_lazy(int idx,int x){

    int val=0;
    if(x>=0){
        while(x+1>0){
            val+=tlazy[idx][x];
            int pom=x+1;
            pom-=(pom&(-pom));
            x=pom-1;
        }
    }

    return val;

}

int get_new_node(){
    tree_node_cnt++;
    tnds[tree_node_cnt].l=0;
    tnds[tree_node_cnt].r=0;
    tnds[tree_node_cnt].val=0;
    return tree_node_cnt;
}
inline int get_val(int x){
    if(x==0)return 0;
    return tnds[x].val;
}
void update_tree(int &x,int l,int r,int id,int val){

    if(l>id || r<id)return;

    x=get_new_node();

    if(l==r){
        tnds[x].val+=val;
        return;
    }
    int mid=(l+r)/2;
    update_tree(tnds[x].l,l,mid,id,val);
    update_tree(tnds[x].r,mid+1,r,id,val);

    tnds[x].val=get_val(tnds[x].l)+get_val(tnds[x].r);
}
int query_tree(int x,int l,int r,int lp,int rp){
    if(l>rp || r<lp || x==0)return 0;
    if(l>=lp && r<=rp)return tnds[x].val;
    int mid=(l+r)/2;
    return query_tree(tnds[x].l,l,mid,lp,rp)+query_tree(tnds[x].r,mid+1,r,lp,rp);
}

int get_single_pref(int idx,int d,int n){

    int sz=dp_pref[idx].size();
    int lazy=bit_get_lazy(idx,d);
    int ret=lazy;
    if(d>=dp_pref[idx].size()){}
    else ret+=dp_pref[idx][d];

    ///ret+=query_tree(root[idx][sz-d-1],0,n,sz-d-1,n);

    return ret;
}
void push_pref_lazy(int idx,int mx,int x){

    int ct=0;

    for(int i=dp[idx].size()-1;i>=max(0,(int)dp[idx].size()-mx);i--){
        int tt=bit_get(idx,i);/// getuje kolko T affectuje ovu poziciju

        bit_upd_lazy(idx, (int)dp[idx].size()-(i)-1-tt+1 ,(int)dp[idx].size()-(i)-1,dp[idx][i] );
        ///printf("%d | %d %d %d %d %d UPD LAZY\n",x, (int)dp[idx].size()-(i)-1-tt+1 ,(int)dp[idx].size()-(i)-1,dp[idx][i],tt,i);

        tt=bit_get_real(idx,i)-bit_get_real(idx,i-1);
        ct+=tt;
    }
    for(int i=dp[idx].size()-1;i>=max(0,(int)dp[idx].size()-mx);i--){
        int tt=bit_get_real(idx,i)-bit_get_real(idx,i-1);
        bit_upd(idx,i,-tt);
    }
   // printf("US2 %d %d\n");
    bit_upd(idx,(int)tpref[idx].size()-mx-1,ct);


    /*int prvroot=0;
    if((int)dp[idx].size()-mx-1>=0)prvroot=root[idx][(int)dp[idx].size()-mx-1];
    for(int i=max(0,(int)dp[idx].size()-mx);i<dp[idx].size();i++)
        root[idx][i]=prvroot;*/


}
void go_dp(int x,int prv,int n){

    sort(node_add[2][x].begin(),node_add[2][x].end());
    dpcnt++;
    dp_id[x]=dpcnt;
    int mx=-1;
    int child=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || !prek_pos[id])continue;

        child++;
        go_dp(id,x,n);
        if(i==0){
            dp_id[x]=dp_id[id];
            continue;
        }

        mx=max(mx,(int)dp[dp_id[id]].size());
    }

    int idx=dp_id[x];

    if(mx!=-1){

        push_pref_lazy(idx,mx,x);

        /*int vll=-1;
        vll=vect[x][0];
        printf("PREKK %d -> %d\n",x,vll);
        for(int i=0;i<dp[idx].size();i++){
            printf("%d %d %d \n",dp[idx][i],bit_get(idx,i),get_single_pref(idx,dp[idx].size()-i-1,n ));
        }
        printf("\n");*/
    }

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv || !prek_pos[id])continue;
        if(i==0)continue;

        mrg_dp(dp_id[x],dp_id[id]);
    }


    //printf("%d %d AAA\n",x,n);
    dp[dp_id[x]].pb(x<=globn);
    dp_pref[dp_id[x]].pb(0);

    int nrv=0;
    if(root[idx].size()>0)nrv=root[idx].back();
    root[idx].pb(nrv);

    int nsz=tpref[idx].size()+1;
    int lb=(nsz&(-nsz));

    tpref[idx].pb(bit_get_real(idx,(int)tpref[idx].size()-1)-
                  bit_get_real(idx,(int)tpref[idx].size()-lb ));

    tlazy[idx].pb(bit_get_lazy(idx,(int)tlazy[idx].size()-1)-
                  bit_get_lazy(idx,(int)tlazy[idx].size()-lb ));


    if(mx!=-1){
        if((int)tpref[idx].size()-mx-2>=0){
            bit_upd(idx,(int)tpref[idx].size()-mx-2,1);
        }

        int sz=dp[idx].size();
        for(int i=sz-1;i>(int)tpref[idx].size()-mx-2;i--)
            dp_pref[idx][sz-i-1]+=dp[idx][i];

        /*int prvroot=0;
        for(int i=(int)tpref[idx].size()-mx-1;i<dp[idx].size();i++){
            if(i-1<0)prvroot=0;
            else prvroot=root[idx][i-1];

            update_tree(root[idx][i],0,n,i,dp[idx][i]);
        }*/
    }
    else{
        bit_upd(idx,(int)tpref[idx].size()-1,1);
        ///update_tree(root[idx][tpref[idx].size()-1],0,n,tpref[idx].size()-1,dp[idx].back());
    }

    /// OPA
    push_pref_lazy(idx,dp[idx].size(),x);
    /// OPA



    /*int vll=-1;
    vll=vect[x][0];
    printf("DPS %d -> %d\n",x,vll);
    for(int i=0;i<dp[idx].size();i++){
        printf("%d %d %d \n",dp[idx][i],bit_get(idx,i),get_single_pref(idx,dp[idx].size()-i-1,n ));
    }
    printf("\n");*/

    /// izracunaj kverije


    for(int i=0;i<node_add[0][x].size();i++){
        int d=node_add[0][x][i].ff;
        int id=node_add[0][x][i].ss.ff;
        int coef=node_add[0][x][i].ss.ss;

       // printf("%d %d  AAA0\n",id,d);

        int val;
        if(d>=dp[idx].size())val=0;
        else val=dp[idx][(int)dp[idx].size()-1-d];

        rez[id]+=val*coef;
    }

    for(int i=0;i<node_add[1][x].size();i++){
        int d=node_add[1][x][i].ff;
        int id=node_add[1][x][i].ss.ff;
        int coef=node_add[1][x][i].ss.ss;

        //printf("%d %d  AAA1\n",id,d);

        int val;
        if(d>=dp[idx].size())val=0;
        else val=get_single_pref(idx,d,n);

        rez[id]+=val*coef;
    }

    if(node_add[2][x].size()==0)return;


    int prefix=0;
    int cid=dp[idx].size();
    for(int i=0;i<node_add[2][x].size();i++){
        int d=node_add[2][x][i].ff;
        int id=node_add[2][x][i].ss.ff;
        int coef=node_add[2][x][i].ss.ss;

        ///printf("%d %d  AAA2\n",id,d);

        while(cid>0 && (int)dp[idx].size()-cid-1<d){
            cid--;
            prefix+=dp[idx][cid];
        }

        rez[id]+=prefix*coef;
    }


}


int get_rez(pii path,int d){

    vector<int>nodes;
    int lc=lca(path.ff,path.ss);

    int x=path.ff;
    while(x!=lc){
        nodes.pb(x);
        x=par[0][x];
    }
    x=path.ss;
    while(x!=lc){
        nodes.pb(x);
        x=par[0][x];
    }
    nodes.pb(lc);

    queue<int>q;
    int inf=1e9;
    vector<int>dist(tn+1,inf);
    for(int i=0;i<nodes.size();i++){
        q.push(nodes[i]);
        dist[nodes[i]]=0;
    }

    while(q.size()){

        x=q.front();
        q.pop();

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(dist[id]<=dist[x]+1)continue;

            dist[id]=dist[x]+1;
            q.push(id);
        }

    }

    int ret=0;
    for(int i=1;i<=globn;i++){
        if(dist[i]<=d)ret++;
    }
    return ret;
}
void go(vector<int>nodes,vector<int>qind){

    for(int i=0;i<qind.size();i++){
        int id=qind[i];
        rez[id]=get_rez(real_queries[id].ff,real_queries[id].ss);
    }

}

int main(){

    freopen("test.txt","r",stdin);
    freopen("fullbrute.txt","w",stdout);

    int t;
    scanf("%d",&t);
    ///t=3;
    while(t--){

        scanf("%d %d",&n,&q);

        globn=n;
        real_queries.clear();
        qs.clear();
        for(int i=0;i<=2*n;i++){
            vect[i].clear();
        }
        for(int i=0;i<=q*4;i++){
            if(i<=q)rez[i]=0;
            path_queries[i].clear();
        }

        for(int i=1;i<n;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            vect[u].pb(n+i);
            vect[n+i].pb(u);
            vect[v].pb(n+i);
            vect[n+i].pb(v);
        }
        tn=2*n-1;
        vector<int>v;
        for(int i=1;i<=tn;i++)v.pb(i);
        prek_base_nodes(v);

        map<pii,int>mapa,prevpat;

        /*pii state={-1,-1};
        int state_d=0;

        state={25,25};
        state_d=1;
        pair<pii,int> ppp=intersect(state,state_d,{1,7});
        state=ppp.ff;
        state_d=ppp.ss;

        printf("%d %d | %d STATE SSS\n",state.ff,state.ss,state_d);
        return 0;*/


        for(int i=0;i<q;i++){
            qr pom;
            scanf("%d",&pom.tip);
            if(pom.tip==1){
                pii pat;
                scanf("%d %d",&pat.ff,&pat.ss);
                if(mapa[pat]==0){
                    prevpat[pat]=i;
                }
                mapa[pat]++;

                /*pair<pii,int> ppp=intersect(state,state_d,pat);
                state=ppp.ff;
                state_d=ppp.ss;

                printf("%d %d | %d STATE\n",state.ff,state.ss,state_d);*/

            }
            else if(pom.tip==2){
                pii pat;
                scanf("%d %d",&pat.ff,&pat.ss);
                mapa[pat]--;
                if(mapa[pat]==0){
                    dodaj_qry(pat,prevpat[pat],i);
                }
            }
            else{
                scanf("%d",&pom.d);
                pom.d*=2;
            }
            qs.pb(pom);
        }
        for(auto it=mapa.begin();it!=mapa.end();it++){
            if(it->ss>0)
                dodaj_qry(it->ff,prevpat[it->ff],q-1);
        }

        construct_queries(1,0,q-1,{-1,-1},0);

        ///printf("%d %d | %d STATE\n",state.ff,state.ss,state_d);

        /*for(auto x:real_queries){
           /// printf("%d %d | %d QRY\n",x.ff.ff,x.ff.ss,x.ss);
        }*/
        /*int qid=0;
        printf("%d %d %d QQQ\n",real_queries[qid].ff.ff,real_queries[qid].ff.ss,real_queries[qid].ss);*/

        vector<int>qrs,nodes;
        for(int i=0;i<real_queries.size();i++){
            if(real_queries[i].ff.ff==-1){
                continue;
            }
            qrs.pb(i);
        }
        for(int i=1;i<=tn;i++)nodes.pb(i);

        go(nodes,qrs);


        for(int i=0;i<real_queries.size();i++){
            printf("%d\n",rez[i]);
        }

    }

    return 0;
}
