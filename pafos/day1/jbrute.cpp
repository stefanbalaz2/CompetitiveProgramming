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

int proot=step(3,7*17*8);
const int maxn=(1<<20);
int prekw[maxn],fact[maxn],inv[maxn];
void prek(){
    fact[0]=1;
    prekw[0]=1;
    for(int i=1;i<maxn;i++){
        prekw[i]=mul(prekw[i-1],proot);
        fact[i]=mul(fact[i-1],i);
    }
    inv[maxn-1]=invv(fact[maxn-1]);
    for(int i=maxn-1;i>0;i--)
        inv[i-1]=mul(inv[i],i);
}
void fft(vector<int>&a,bool invert){

    int n=a.size();
    int j=0;
    for(int i=1;i<n;i++){
        int bit=n>>1;
        for(;bit&j;bit>>=1)j^=bit;
        j^=bit;
        if(i<j)swap(a[i],a[j]);
    }

    for(int len=2;len<=n;len<<=1){
        int hlen=(len/2);
        for(int i=0;i<n;i+=len){
            int curr=0;
            int d=maxn/len;
            if(invert)d=maxn-d;
            for(int j=0;j<hlen;j++){

                int pom1=a[i+j];
                int pom2=mul(a[i+hlen+j],prekw[curr]);

                a[i+j]=add(pom1,pom2);
                a[i+j+hlen]=sub(pom1,pom2);

                curr+=d;
                if(curr>=maxn)curr-=maxn;
            }
        }
    }

    if(invert){
        int invn=invv(n);
        for(int i=0;i<n;i++)a[i]=mul(a[i],invn);
    }

}
vector<int>pmul(vector<int>a,vector<int>b){

    int n=1;
    a.resize(max((int)a.size(),2));
    b.resize(max((int)b.size(),2));
    while(n<a.size()+b.size()-1)n<<=1;
    if(n>=maxn)while(1){}
    a.resize(n);
    b.resize(n);
    fft(a,0);
    fft(b,0);
    for(int i=0;i<n;i++)a[i]=mul(a[i],b[i]);
    fft(a,1);
    return a;
}

vector<int>b[maxn],a[maxn],g[maxn],gp[maxn];
int sz[maxn],p[maxn],q[maxn];
void calc_b(int x){
    b[x].clear();
    b[x].resize(a[x].size());
    for(int i=a[x].size()-2;i>=0;i--)
        b[x][i]=add(b[x][i+1],a[x][i+1]);
}
vector<int> calc_half_a(int x,int y){
    vector<int>poma,pomb;
    poma=a[x];
    pomb=b[y];
    for(int i=1;i<poma.size();i++)
        poma[i]=mul(poma[i], mul(inv[i-1],inv[sz[x]-i]) );
    for(int i=0;i<pomb.size();i++)
        pomb[i]=mul(pomb[i], mul(inv[i],inv[sz[y]-i]) );

    poma=pmul(poma,pomb);
    poma.resize(sz[x]+sz[y]+1);
    for(int i=1;i<poma.size();i++)
        poma[i]=mul(poma[i],mul( fact[i-1],fact[sz[x]+sz[y]-i] ));


    return poma;
}
void go_f(int x,int l,int r){

    ///printf("%d %d LR\n",l,r);

    if(l==r){
        a[x].resize(p[l]+1);
        a[x][q[l]]=fact[p[l]];
        sz[x]=p[l];
        return;
    }
    int mid=(l+r)/2;
    go_f(x*2,l,mid);
    go_f(x*2+1,mid+1,r);

    calc_b(x*2);
    calc_b(x*2+1);
    sz[x]=sz[x*2]+sz[x*2+1];

    a[x].resize(sz[x]+1);
    vector<int>pom1=calc_half_a(x*2,x*2+1);
    for(int i=0;i<=sz[x];i++)a[x][i]=pom1[i];
    pom1=calc_half_a(x*2+1,x*2);
    for(int i=0;i<=sz[x];i++)a[x][i]=add(a[x][i],pom1[i]);
    a[x].resize(sz[x]+1);

}
int rez[maxn];
int cc[maxn*4];
void push_g(int x,int y,int z){

    gp[x].resize(sz[x]+1);
    for(int i=0;i<=sz[x];i++)gp[x][i]=mul(g[x][i],invv(a[x][i]));

    vector<int>pomg=gp[x];
    vector<int>pomb=b[y];

    for(int i=1;i<=sz[x];i++)
        pomg[i]=mul(pomg[i],mul( fact[i-1] , fact[sz[x]-i] ) );

    for(int i=0;i<=sz[y];i++)
        pomb[i]=mul(pomb[i],mul( inv[i] , inv[sz[y]-i] ) );


    if(pomb.size()-1!=sz[y])while(1){}
    reverse(pomb.begin(),pomb.end());

    pomg=pmul(pomg,pomb);

    g[z].resize(sz[z]+1);
    for(int i=1;i<=sz[z];i++){
        g[z][i]=mul( mul( a[z][i] ,mul(inv[i-1],inv[sz[z]-i])  ), pomg[i+sz[y]] );
    }

}

void go_g(int x,int l,int r){

    if(l==r){
        for(int i=0;i<g[x].size();i++){
            rez[l]=add(rez[l],g[x][i]);
        }
        return;
    }

    push_g(x,x*2,x*2+1);
    push_g(x,x*2+1,x*2);

    int mid=(l+r)/2;
    go_g(x*2,l,mid);
    go_g(x*2+1,mid+1,r);

    ///if(cc[x]!=0)while(1){}

}


int ind[maxn];
int bn[maxn];
int n;
void dodaj(vector<int>&niz){
    for(int i=1;i<=n;i++)bn[i]=q[i];
    for(int j=0;j<niz.size();j++){
        bn[ind[niz[j]]]--;
        if(bn[ind[niz[j]]]==0){
            rez[ind[niz[j]]]++;
            return;
        }
    }
}
void go(){

    int m;
    scanf("%d %d",&n,&m);
    int cnt=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i]);
        for(int j=0;j<p[i];j++)ind[++cnt]=i;
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&q[i]);
    }

    vector<int>niz;
    for(int i=1;i<=m;i++)niz.pb(i);
    for(int i=1;i<=n;i++)rez[i]=0;
    dodaj(niz);
    while(next_permutation(niz.begin(),niz.end())){
        dodaj(niz);
    }

    for(int i=1;i<=n;i++){
        printf("%d ",rez[i]);
    }
    printf("\n");

}

int main(){

    freopen("test.txt","r",stdin);
    freopen("brute.txt","w",stdout);

    prek();

    int t;
    scanf("%d",&t);
    while(t--){
        go();
    }



    return 0;
}
