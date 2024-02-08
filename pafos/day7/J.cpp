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

const int maxn=4e3+10;
int n;
vector<int>vect[maxn];
vector<pii>rez_edges;
int pos[maxn];

vector<int> ask(vector<int>v){

    printf("? %d ",v.size());
    for(int i=0;i<v.size();i++){
        printf("%d ",v[i]);
    }
    printf("\n");
    fflush(stdout);

    vector<int>ret;
    for(int i=0;i<v.size();i++){
        int a;
        scanf("%d",&a);
        ret.pb(a);
    }
    return ret;
}

vector<pii>get_degrees(vector<int>inds,vector<int>rest){

    vector<int>pom;
    for(int i=0;i<inds.size();i++)pom.pb(inds[i]);
    for(int i=0;i<rest.size();i++)pom.pb(rest[i]);

    pom=ask(pom);

    vector<pii>ret;
    for(int i=0;i<rest.size();i++)
        ret.pb({rest[i],pom[i+inds.size()]});

    return ret;
}

void go_dnc(vector<int>inds,vector<pii>qry,vector<pii>&edges){

    vector<pii>plp;
    for(int i=0;i<qry.size();i++)if(qry[i].ss>0)plp.pb(qry[i]);
    qry=plp;

    if(qry.size()==0)return;

    if(inds.size()==1){
        int x=inds[0];
        for(int i=0;i<qry.size();i++){
            int id=qry[i].ff;
            int v=qry[i].ss;
            for(int j=0;j<v;j++)
                edges.pb({x,id});
        }
        return;
    }

    int mid=(inds.size()-1)/2;
    vector<int>lb,rb;
    for(int i=0;i<inds.size();i++){
        if(i<=mid)lb.pb(inds[i]);
        else rb.pb(inds[i]);
    }

    vector<int>pom;
    vector<pii>qrylb,qryrb;
    for(int i=0;i<lb.size();i++)pom.pb(lb[i]);
    for(int i=0;i<qry.size();i++)pom.pb(qry[i].ff);

    pom=ask(pom);
    for(int i=0;i<qry.size();i++){
        int v=pom[i+lb.size()];
        int id=qry[i].ff;
        int deg=qry[i].ss;

        for(int j=0;j<vect[id].size();j++){
            int id2=vect[id][j];
            v-=pos[id2];
        }

        if(pom[i+lb.size()]==0)pos[id]=1;

        qrylb.pb({id,v});
        qryrb.pb({id,deg-v});

    }

    for(int i=0;i<qry.size();i++){
        int id=qry[i].ff;
        if(pom[i+lb.size()]==0)pos[id]=0;
    }

    go_dnc(lb,qrylb,edges);
    go_dnc(rb,qryrb,edges);

}
void partit(vector<int>v){

    vector<int>pom=ask(v);
    vector<int>inds,rest;

    for(int i=0;i<pom.size();i++){
        if(pom[i]==0)inds.pb(v[i]);
        else rest.pb(v[i]);
    }
    if(inds.size()==v.size())return;
    partit(rest);

    vector<pii>togo=get_degrees(inds,rest),phase_edges;
    go_dnc(inds,togo,phase_edges);

    for(int i=0;i<phase_edges.size();i++){
        int u=phase_edges[i].ff;
        int v=phase_edges[i].ss;
        vect[u].pb(v);
        vect[v].pb(u);
        rez_edges.pb({u,v});
    }

}
void dodaj_loops(){

    for(int i=1;i<=n;i++){
        vector<int>pom;
        pom.pb(i);pom.pb(i);
        pom=ask(pom);
        for(int j=0;j<pom[1];j++)rez_edges.pb({i,i});
    }

}

int main(){

    scanf("%d",&n);

    vector<int>v;
    for(int i=1;i<=n;i++)v.pb(i);
    partit(v);

    dodaj_loops();

    printf("! %d ",rez_edges.size());
    for(int i=0;i<rez_edges.size();i++)printf("%d %d ",rez_edges[i].ff,rez_edges[i].ss);
    fflush(stdout);

    return 0;
}
