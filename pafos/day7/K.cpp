#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=110;
int n,sn,m;
int adj[maxn][maxn];
int ind[maxn][maxn];
vector<pii>edges;

struct pt{
    int x,y;

    pt(int x,int y){
        this->x=x;
        this->y=y;
    }

    ll cross(pt b){
        return (ll)x*b.y-(ll)y*b.x;
    }

    pt operator -(pt b){
        return pt(x-b.x,y-b.y);
    }
    pt operator +(pt b){
        return pt(x+b.x,y+b.y);
    }

    bool operator ==(pt b){
        return x==b.x && y==b.y;
    }

    void ispis(){
        printf("%d %d POINTS\n",x,y);
    }

};

vector<pt>points,sources;

bool is_strict_on_line(pt a,pt b,pt c){

    if(a==b || a==c)return false;

    a=a-c;
    b=b-c;

    if(a.cross(b)==0){
        a=a+c;
        b=b+c;
        if(a.x>=min(b.x,c.x) && a.x<=max(b.x,c.x))return true;
    }
    return false;
}
bool check_edge_strict_intersect(pt a1,pt a2,pt b1,pt b2){

    a1=a1-a2;
    b1=b1-a2;
    b2=b2-a2;

    ll pom1=a1.cross(b1);
    ll pom2=a1.cross(b2);

    ///printf("%lld %lld POMMM\n",pom1,pom2);

    if(pom1<0 && pom2>0)return true;
    if(pom1>0 && pom2<0)return true;
    return false;
}
bool check(int u,int v){

    for(int i=0;i<points.size();i++)
        if(is_strict_on_line(points[i],points[u],points[v])){
            ///printf("PUKO POINT\n");
            return false;
        }


    for(int i=0;i<edges.size();i++){
        if(check_edge_strict_intersect(points[u],points[v],points[edges[i].ff],points[edges[i].ss]) &&
           check_edge_strict_intersect(points[edges[i].ff],points[edges[i].ss],points[u],points[v])){
            /*printf("PUKO edge 1 %d %d \n",edges[i].ff,edges[i].ss);
            points[edges[i].ff].ispis();
            points[edges[i].ss].ispis();
            points[u].ispis();
            points[v].ispis();*/
            return false;
        }
    }

    return true;
}
void make_edges(){

    for(int i=0;i<points.size();i++){
        for(int j=i+1;j<points.size();j++){
            if(adj[i][j]!=-1)continue;


            if(!check(i,j)){
                //printf("%d %d PUKAO\n",i,j);
                continue;
            }
           // printf("PROSAO %d %d\n",i,j);

            adj[i][j]=0;
            adj[j][i]=0;

            edges.pb({i,j});
        }
    }

}

ll surface(pt a,pt b,pt c){
    a=a-c;
    b=b-c;
    return abs(a.cross(b));
}
struct triangle{
    int a[3];

    bool pt_inside(pt x){
        if(surface(x,points[a[0]],points[a[1]])+surface(x,points[a[2]],points[a[1]])+surface(x,points[a[0]],points[a[2]])==surface(points[a[2]],points[a[0]],points[a[1]]))
            return true;
        return false;
    }

};
vector<triangle>trivect;
void make_triangles(){

    /// ubaci proveru da ne sme ni jedna tacka biti u trouglu
    for(int i=0;i<points.size();i++){
        for(int j=i+1;j<points.size();j++){
            for(int k=j+1;k<points.size();k++){
                if(adj[i][j]!=-1 && adj[i][k]!=-1 && adj[j][k]!=-1){

                    triangle t;
                    t.a[0]=i;
                    t.a[1]=j;
                    t.a[2]=k;
                    int e=1;
                    for(int p=0;p<points.size();p++){
                        if(p==i || p==j || p==k)continue;
                        if(t.pt_inside(points[p])){
                            e=0;
                            break;
                        }
                    }
                    if(!e)continue;

                    trivect.pb({i,j,k});
                }
            }
        }
    }

}

vector<vector<int>>cand;
int par[maxn*maxn],flag[maxn*maxn];
int root(int x){
    if(par[x]==x)return x;
    return par[x]=root(par[x]);
}
void join(int x,int y){
    x=root(x);
    y=root(y);
    if(x==y)return;
    flag[x]|=flag[y];
    par[y]=x;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d %d",&n,&sn,&m);

    for(int i=0;i<n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        points.pb({x,y});
    }
    int inf=1e9+20;
    points.pb({(int)-inf,(int)-inf});
    points.pb({(int)-inf,(int)inf});
    points.pb({(int)inf,(int)-inf});
    points.pb({(int)inf,(int)inf});
    n+=4;

    for(int i=0;i<sn;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        sources.pb({x,y});
    }

    memset(adj,-1,sizeof(adj));
    for(int i=0;i<m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        u--;
        v--;
        adj[u][v]=1;
        adj[v][u]=1;
        edges.pb({u,v});
    }

    make_edges();
    make_triangles();

    int ndsu=edges.size()+trivect.size();
    for(int i=0;i<ndsu;i++){
        par[i]=i;
        flag[i]=0;
    }

    for(int i=0;i<sources.size();i++)
        for(int j=0;j<trivect.size();j++)
            if(trivect[j].pt_inside(sources[i]))flag[j]=1;

    for(int i=0;i<edges.size();i++){
        ///printf("%d %d EDGE\n",edges[i].ff,edges[i].ss);
        ind[edges[i].ff][edges[i].ss]=i;
        ind[edges[i].ss][edges[i].ff]=i;
    }

    cand.resize(edges.size());
    for(int i=0;i<trivect.size();i++){

        int u,v,z;
        u=trivect[i].a[0];
        v=trivect[i].a[1];
        z=trivect[i].a[2];

       /// printf("%d %d %d TRI\n",u,v,z);

        if(adj[u][v]==0)join(i,ind[u][v]+trivect.size());
        else if(adj[u][v]==1) cand[ind[u][v]].pb(i);
        if(adj[z][v]==0)join(i,ind[z][v]+trivect.size());
        else if(adj[z][v]==1) cand[ind[z][v]].pb(i);
        if(adj[z][u]==0)join(i,ind[z][u]+trivect.size());
        else if(adj[z][u]==1) cand[ind[z][u]].pb(i);

    }

    for(int i=0;i<m;i++){
        int rez=0;
        for(int j=0;j<cand[i].size();j++){
            int x=root(cand[i][j]);
            rez=max(rez,flag[x]);
        }
        printf("%d",rez);
    }


    return 0;
}
