/*

    idea:   https://discuss.codechef.com/t/closefar-editorial/12807

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
typedef map<int,int>::iterator mit;
const int maxn=35000+10;
struct qv{
    int x,y,ind,ana;
    char type;
}q[maxn];
int in[maxn],niz[2*maxn],out[maxn],dp[maxn][20],level[maxn],tt,br,n,qbr,a[maxn],rh[maxn],val[maxn*4],treemax[maxn*4],treemin[maxn*4],pos[maxn];
int rez[maxn];
map<int,int>mapa;
int inf=1e9+2;
int bsize;
vector<int>vect[maxn];
void array_it(int x,int prv,int lvl){

    in[x]=++tt;
    niz[tt]=a[x];
    dp[x][0]=prv;
    level[x]=lvl;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;

        array_it(id,x,lvl+1);
    }

    out[x]=++tt;
    niz[tt]=a[x];
}
void prek(){
    int h=log2(n);
    for(int i=1;i<=h;i++)
        for(int j=1;j<=n;j++)
        dp[j][i]=dp[dp[j][i-1]][i-1];
}
int lca(int x,int y){

    int h=log2(n);

    if(level[y]>level[x])swap(x,y);
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
bool in_subtree(int x,int y){
    if(in[x]<=in[y] && out[y]<=out[x])return true;
    return false;
}
bool srt(qv a,qv b){
    return a.x/bsize<b.x/bsize || (a.x/bsize==b.x/bsize && a.y<b.y);
}
void sw(int x,int l,int r,int id){

    if(l>id || r<id)return;
    if(l==r){
        val[x]=inf;

        if(treemax[x]==-inf)treemax[x]=l;
        else treemax[x]=-inf;

        if(treemin[x]==inf)treemin[x]=l;
        else treemin[x]=inf;

        return ;
    }

    int mid=(l+r)/2;

    if(mid<id)sw(x*2+1,mid+1,r,id);
    else sw(x*2,l,mid,id);

    treemin[x]=min(treemin[x*2],treemin[x*2+1]);
    treemax[x]=max(treemax[x*2],treemax[x*2+1]);
    val[x]=min(val[x*2],val[x*2+1]);
}
void upval(int x,int l,int r,int id,int vl){

    if(l>id || r<id)return;
    if(l==r){
        val[x]=vl;
        return;
    }

    int mid=(l+r)/2;

    if(mid<id)upval(x*2+1,mid+1,r,id,vl);
    else upval(x*2,l,mid,id,vl);

    val[x]=min(val[x*2],val[x*2+1]);
}
int get_val(int x,int l,int r,int id){
    if(l>id || r<id)return inf;
    if(l==r)return val[x];
    int mid=(l+r)/2;
    if(mid<id)return get_val(x*2+1,mid+1,r,id);
    else return get_val(x*2,l,mid,id);
}
int get_min(int x,int l,int r,int ll,int rr){
    if(l>rr || r<ll)return inf;
    if(l>=ll && r<=rr)return treemin[x];
    int mid=(l+r)/2;
    return min(get_min(x*2,l,mid,ll,rr),get_min(x*2+1,mid+1,r,ll,rr));
}
int get_max(int x,int l,int r,int ll,int rr){
    if(l>rr || r<ll)return -inf;
    if(l>=ll && r<=rr)return treemax[x];
    int mid=(l+r)/2;
    return max(get_max(x*2,l,mid,ll,rr),get_max(x*2+1,mid+1,r,ll,rr));
}
void change(int x){
    pos[niz[x]]^=1;
    if(pos[niz[x]]==0){
        int pom=get_val(1,1,br,niz[x]);
        int desni=get_min(1,1,br,niz[x]+1,br);
        sw(1,1,br,niz[x]);

        upval(1,1,br,desni,min(pom+get_val(1,1,br,desni),inf));
    }
    else{
        int levi=get_max(1,1,br,1,niz[x]-1);
        int desni=get_min(1,1,br,niz[x]+1,br);
        sw(1,1,br,niz[x]);
        if(levi!=-inf)upval(1,1,br,niz[x],rh[niz[x]]-rh[levi]);
        if(desni!=inf)upval(1,1,br,desni,rh[desni]-rh[niz[x]]);
    }
}
int query1(){
    return val[1];
}
int query2(){
    return rh[get_max(1,1,br,1,br)]-rh[get_min(1,1,br,1,br)];
}
void build(int x,int l,int r){

    val[x]=inf;
    treemax[x]=-inf;
    treemin[x]=inf;

    if(l==r)return;

    int mid=(l+r)/2;

    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
}
void go(){

    build(1,1,br);

    ///for(int i=1;i<=tt;i++)printf("%d ",rh[niz[i]]);
    ///printf("AAA\n");

    int l=q[1].x;
    int r=l;
    change(l);

    for(int i=1;i<=qbr;i++){

        int ll=q[i].x;
        int rr=q[i].y;

        ///printf("%d %d %d QVQV\n",ll,rr,q[i].ind);

        while(r<rr){
            r++;
            change(r);
        }
        while(r>rr){
            change(r);
            r--;
        }

        while(l<ll){
            change(l);
            l++;
        }
        while(l>ll){
            l--;
            change(l);
        }

        if(q[i].ana!=-1)change(in[q[i].ana]);

        if(q[i].type=='F')rez[q[i].ind]=query2();
        else rez[q[i].ind]=query1();

        ///for(int i=1;i<=br;i++)printf("%d %d | ",pos[i],rh[i]);
        ///printf("\n\n");
        ///printf("%d");

        if(q[i].ana!=-1)change(in[q[i].ana]);
    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        mapa[a[i]]=0;
    }
    bsize=500;
    for(mit it=mapa.begin();it!=mapa.end();it++){
        it->ss=++br;
        rh[br]=it->ff;
    }
    for(int i=1;i<=n;i++)a[i]=mapa[a[i]];

    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    array_it(1,0,1);
    prek();

    scanf("%d",&qbr);
    for(int i=1;i<=qbr;i++){
        cin>>q[i].type>>q[i].x>>q[i].y;
        q[i].ind=i;

        q[i].ana=lca(q[i].x,q[i].y);
        if(lca(q[i].x,q[i].y)==q[i].x || lca(q[i].x,q[i].y)==q[i].y)q[i].ana=-1;

        if(in_subtree(q[i].x,q[i].y)){
            int x=q[i].x;
            int y=q[i].y;
            q[i].x=out[y];
            q[i].y=out[x];
        }
        else if(in_subtree(q[i].y,q[i].x)){
            int x=q[i].x;
            int y=q[i].y;
            q[i].x=out[x];
            q[i].y=out[y];
        }
        else{
            int x=q[i].x;
            int y=q[i].y;
            if(out[x]<in[y]){
                q[i].x=out[x];
                q[i].y=in[y];
            }
            else{
                q[i].x=out[y];
                q[i].y=in[x];
            }
        }
    }

    sort(q+1,q+qbr+1,srt);

    go();

    for(int i=1;i<=qbr;i++)printf("%d\n",rez[i]);

    return 0;
}
