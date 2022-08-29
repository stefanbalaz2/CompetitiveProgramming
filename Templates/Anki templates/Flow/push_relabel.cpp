/**

    https://cses.fi/problemset/task/1694

    push relabel O(v*(v^2+e))

    implementacija:

        - za svaki node da bismo nasli sledece edge za pushovanje
        drzim pointer koji inkrementiram, koji kad dodje do kraja edgova
        onda jedino sto mogu sa tim cvorom uraditi je relabelovati, jer svaki
        edge koji probam da uradim ili sam ga popunio, ili je bio prenizak
        sto znaci da nismo imali edge ka njemu, sto znaci da ce taj drugi cvor morati
        da se poveca iznad nas da bismo dobili edge do njega, sto znaci da mora prvo
        bar jednom da se relabeluje nas trenutni cvor, tj bilo koji edge da smo probali
        i nismo mogli, moci cemo tek kad uradimo bar jedan relabel tog cvora,
        sto znaci da ce se nas pointer kretati O(v*e) puta

        - biranje najviseg cvora radimo tako sto drzimo kao counting sort i pomeramo pointer
        ka manjim brojevima, izmedju 2 relabela cemo imati maximalno O(v) pomeraja pointera
        zato sto kad nadjemo neki cvor, ili smo njega relabelovali, ili smo pushovali pa smo
        stvorili excess flow u cvoru koji je za jedan nizi od trenutnog, sto znaci da pointer pomeramo
        za jednu poziciju

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

ll inf=1e18;

struct edge{
    int u,v;
    ll f,c;
};
vector<edge>e;
const int maxn=510;
vector<int>vect[maxn],cnt[maxn];
int nep[maxn],h[maxn],cntpt,cntsz,s,t;
ll excess[maxn];

int n;

void add_edge(int u,int v,int cap){

    vect[u].pb(e.size());
    e.pb({u,v,0,cap});

    vect[v].pb(e.size());
    e.pb({v,u,cap,cap});
}

void push(int id){

    int u=e[id].u;
    int v=e[id].v;

    ll d=min(excess[u], e[id].c-e[id].f );
    if(d==0)return;
    e[id].f+=d;
    e[id^1].f-=d;

    if(excess[v]==0 && v!=t){
        cnt[h[v]].pb(v);
        cntsz++;
    }

    excess[u]-=d;
    excess[v]+=d;


    if(excess[u]==0){
        cnt[h[u]].pop_back();
        cntsz--;
    }


}
void relabel(int x){

    if(x==t)return;

    cnt[h[x]].pop_back();

    int nl=1e9;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(e[id].c-e[id].f==0)continue;
        nl=min(nl,h[e[id].v]);
    }

    if(nl==inf)return;
    h[x]=nl+1;
    cnt[h[x]].pb(x);
    cntpt=max(cntpt,nl+1);
}



ll get_flow(){

    s=1;
    t=n;
    memset(h,0,sizeof(h));
    memset(nep,0,sizeof(nep));
    memset(excess,0,sizeof(excess));
    h[s]=n;
    excess[s]=inf;
    for(int i=0;i<vect[s].size();i++)
        push(vect[s][i]);

    cntpt=n;

    while(cntsz){

        while(cnt[cntpt].size()==0)cntpt--;

        int id=cnt[cntpt].back();

        for(;nep[id]<vect[id].size() && excess[id]>0;nep[id]++){
            int id2=vect[id][nep[id]];
            if(e[id2].c-e[id2].f==0 || h[e[id2].u]!=h[e[id2].v]+1)continue;

            push(id2);
        }
        if(excess[id] && nep[id]==vect[id].size()){
            nep[id]=0;
            relabel(id);
        }

    }

    ll ret=0;
    for(int i=0;i<vect[t].size();i++){
        int id=vect[t][i];
        if(id&1)id^=1;
        else continue;

        ret+=e[id].f;
    }

    return ret;

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int m;
    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){

        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        add_edge(u,v,w);
    }

    printf("%lld\n",get_flow());


    return 0;
}
