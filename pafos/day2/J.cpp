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

int n;
int inf=1e9;
map<pii,vector<pair< pair<pii,pii>,int >>>mapa;
set<pii>st;
const int maxn=510;
vector<int>vect[maxn];
int col[maxn],pos[maxn],pos2[maxn],deg[maxn];

void add_slope(pii a,pii b,int id){

    if(a.ff>b.ff || (a.ff==b.ff && a.ss>b.ss) )swap(a,b);

    if(a.ff==b.ff){
        mapa[{inf,inf}].pb( { {a,b}, id} );
    }
    else{
        int g=abs(__gcd((b.ff-a.ff),(b.ss-a.ss)));
        mapa[ { (b.ff-a.ff)/g , (b.ss-a.ss)/g } ].pb({ {a,b} , id });
    }

}
int cross(pii a,pii c,pii b){
    a.ff-=c.ff;
    a.ss-=c.ss;
    b.ff-=c.ff;
    b.ss-=c.ss;
    return a.ff*b.ss-a.ss*b.ff;
}
bool intersect(pii pl,pii pr,pii ql,pii qr){

    if(cross(pl,pr,ql)!=0)return false;

    if(pl.ff==pr.ff){

        if(pl.ss>ql.ss || (pl.ss==ql.ss && pr.ss>qr.ss)){
            swap(pl,ql);
            swap(pr,qr);
        }

        if(pr.ss>ql.ss)return true;
        return false;
    }

    if(pl.ff>ql.ff || (pl.ff==ql.ff && pr.ff>qr.ff) ){
        swap(pl,ql);
        swap(pr,qr);
    }

    if(pr.ff>ql.ff)return true;
    return false;

}
void add_edge(int a,int b){
    st.insert({a,b});
    st.insert({b,a});

   // printf("%d %d EDGE\n",a,b);
}
void process_vector(vector<pair<pair<pii,pii>,int>> v){

    for(int i=0;i<v.size();i++){
        for(int j=i+1;j<v.size();j++){
            if(intersect(v[i].ff.ff,v[i].ff.ss,v[j].ff.ff,v[j].ff.ss)){
                add_edge(v[i].ss,v[j].ss);
                //printf("%d %d -> %d %d | %d %d -> %d %d \n",v[i].ff.ff.ff,v[i].ff.ff.ss,v[i].ff.ss.ff,v[i].ff.ss.ss,
                       //v[j].ff.ff.ff,v[j].ff.ff.ss,v[j].ff.ss.ff,v[j].ff.ss.ss);
            }
        }
    }


}
void process_slopes(){

    for(map<pii,vector<pair<pair<pii,pii>,int>>>::iterator it=mapa.begin();it!=mapa.end();it++){
        process_vector(it->ss);
    }

}

int find_min(){
    int ret=-1;
    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        if(ret==-1)ret=i;
        else{
            if(deg[i]<deg[ret])ret=i;
        }
    }
    return ret;
}
void dfs(int x,int c,int *p){

    pos2[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id] || pos2[x] || col[id]!=p[c^1])continue;
        dfs(id,c^1,p);
    }

}
void dfs_invert(int x,int c,int *p){

    pos2[x]=1;
    col[x]=p[c^1];
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id] || pos2[id] || col[id]!=p[c^1])continue;
        dfs_invert(id,c^1,p);
    }
}
int probaj(int x,int y){

    int p[2]={col[x],col[y]};

    memset(pos2,0,sizeof(pos));
    dfs(x,0,p);

    if(pos2[y])return false;

    memset(pos2,0,sizeof(pos));
    dfs_invert(x,0,p);

    return true;
}
void go(){

    int x=find_min();

    if(x==-1)return;
    if(deg[x]>5)while(1){}
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        deg[id]--;
    }
    pos[x]=1;

    /*printf("%d X\n",x);
    for(int i=1;i<=n;i++){
        printf("%d ",deg[i]);
    }
    printf("\n");*/

    go();


    set<int>clrs;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        clrs.insert(col[id]);
    }

    if(clrs.size()<5){
        for(int i=1;i<=5;i++){
            if(clrs.find(i)==clrs.end()){
                col[x]=i;
                break;
            }
        }
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(pos[id])continue;
            deg[id]++;
        }
        pos[x]=0;
        return;
    }


    int e=0;
    for(int i=0;i<vect[x].size();i++){
        for(int j=i+1;j<vect[x].size();j++){
            if(pos[vect[x][i]] || pos[vect[x][j]])continue;
            if(probaj(vect[x][i],vect[x][j])){
                col[x]=col[vect[x][i]];
                e=1;
                break;
            }
        }
        if(e)break;
    }

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        deg[id]++;
    }
    pos[x]=0;

}
int cp[6]={'a','G','R','M','P','S'};
int main(){

    ///freopen("test.txt","r",stdin);

    ///printf("%d AA\n",__gcd(-4,2));

    scanf("%d",&n);

    for(int i=1;i<=n;i++){

        string s;
        cin>>s;

        int k;
        scanf("%d",&k);
        vector<pii>vect;
        for(int j=0;j<k;j++){
            int x,y;
            scanf("%d %d",&x,&y);
            vect.pb({x,y});
        }

        int prv=k-1;
        for(int j=0;j<k;j++){
            add_slope(vect[prv],vect[j],i);
            prv=j;
        }

    }

    process_slopes();

    for(set<pii>::iterator it=st.begin();it!=st.end();it++){
        vect[(*it).ff].pb((*it).ss);
        deg[(*it).ff]++;
    }


    go();

    for(int i=1;i<=n;i++){
        printf("%c",cp[col[i]]);
    }

    return 0;
}
