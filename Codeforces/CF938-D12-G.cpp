/*



*/
#include<bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=2e5+10;
const int maxbit=30;
struct edge{
    int u,v,w,type;
};
vector<edge>tree[maxn*4];
vector<int>vect[30];
vector<pair<int*,int> >changes;
int br,start[30],n,q,m,sz[maxn],p[maxn],len[maxn],rez[maxn];
map<pii,pii>mapa;
pii get_edge(int x,int y){
    if(x<y)return {x,y};
    return {y,x};
}
void update(int x,int l,int r,int ll,int rr,edge val){
    if(l>rr || r<ll)return;
    if(l>=ll && r<=rr){
        tree[x].pb(val);
        return;
    }
    int mid=(l+r)/2;
    update(x*2,l,mid,ll,rr,val);
    update(x*2+1,mid+1,r,ll,rr,val);
}
void init_dsu(){

    for(int i=1;i<=n;i++){
        sz[i]=1;
        p[i]=i;
        len[i]=0;
    }
}
int get_root(int x){
    if(x==p[x])return x;
    return get_root(p[x]);
}
int get_len(int x){
    if(x==p[x])return len[x];
    return (len[x]^get_len(p[x]));
}
bool join(int x,int y,int w){

    int w1=get_len(x);
    int w2=get_len(y);

    x=get_root(x);
    y=get_root(y);

    if(x==y)return false;

    if(sz[x]<sz[y])swap(x,y);

    changes.pb({&sz[x],sz[x]});
    changes.pb({&p[y],p[y]});
    changes.pb({&len[y],len[y]});


    sz[x]+=sz[y];
    p[y]=x;
    len[y]^=w^w1^w2;

    return true;
}
void gauss_and_resize(vector<int> &vect){

    int index=0;
    for(int i=maxbit;i>=0;i--){

        int id=-1;
        for(int j=index;j<vect.size();j++)
            if(vect[j]&(1<<i)){
                id=j;
                break;
            }

        if(id==-1)continue;

        swap(vect[index],vect[id]);

        for(int j=0;j<vect.size();j++){
            if(j==index)continue;
            if(vect[j]&(1<<i))vect[j]^=vect[index];
        }

        index++;
    }

    while(vect.size() && vect[vect.size()-1]==0)vect.pop_back();
}
int msb(int x){
    if(x==0)return 0;
    for(int i=maxbit;i>=0;i--)
        if(x&(1<<i))return i;
}
int get_ans(vector<int> &vect,int x){

    for(int i=0;i<vect.size();i++)
        if(x&(1<<msb(vect[i])))x^=vect[i];


    return x;
}
void revert_changes(int x){

    while(changes.size()>start[x]){
        *(changes[changes.size()-1].ff)=changes[changes.size()-1].ss;
        changes.pop_back();
    }
}
void go(int x,int l,int r){

    br++;
    for(int i=0;i<vect[br-1].size();i++)vect[br].pb(vect[br-1][i]);


    start[br]=changes.size();
    for(int i=0;i<tree[x].size();i++){
        int u,v,w;
        u=tree[x][i].u;
        v=tree[x][i].v;
        w=tree[x][i].w;
        if(tree[x][i].type)continue;

        if(!join(u,v,w))vect[br].pb(get_len(u)^get_len(v)^w);
    }

    gauss_and_resize(vect[br]);

    for(int i=0;i<tree[x].size();i++){
        int u,v,id;
        u=tree[x][i].u;
        v=tree[x][i].v;
        id=tree[x][i].w;
        if(!tree[x][i].type)continue;

        rez[id]=get_ans(vect[br],get_len(u)^get_len(v));
    }

    if(l!=r){
        int mid=(l+r)/2;
        go(x*2,l,mid);
        go(x*2+1,mid+1,r);
    }

    revert_changes(br);
    vect[br].clear();
    br--;

}
int main(){

	///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        mapa[get_edge(u,v)]={0,w};
    }

    scanf("%d",&q);
    for(int i=1;i<=q;i++){

        int tip;
        scanf("%d",&tip);

        if(tip==1){
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            mapa[get_edge(u,v)]={i,w};
        }
        else if(tip==2){
            int u,v;
            scanf("%d %d",&u,&v);

            int l=mapa[get_edge(u,v)].ff;
            int w=mapa[get_edge(u,v)].ss;
            int r=i;

            update(1,0,q,l,r,{u,v,w,0});

            mapa.erase(get_edge(u,v));
        }
        else if(tip==3){
            int u,v;
            scanf("%d %d",&u,&v);
            update(1,0,q,i,i,{u,v,i,1});
        }

    }

    for(map<pii,pii>::iterator it=mapa.begin();it!=mapa.end();it++)
        update(1,0,q,it->ss.ff,q,{it->ff.ff,it->ff.ss,it->ss.ss,0});


    memset(rez,-1,sizeof(rez));
    init_dsu();
    go(1,0,q);

    for(int i=1;i<=q;i++){
        if(rez[i]==-1)continue;
        printf("%d\n",rez[i]);
    }

	return 0;
}
