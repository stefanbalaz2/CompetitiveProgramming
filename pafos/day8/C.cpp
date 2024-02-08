#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}


const int maxn=1e6+10;
int n;
int a[maxn],b[maxn],d[maxn],c[maxn];

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    vector<int>ind;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        ind.pb(i);
    }
    for(int i=1;i<=n;i++){
        scanf("%d",&b[i]);
    }

    vector<int>pomsrt[2];
    ll inf=2e18;
    ll rez=inf;
    for(int i=0;i<=30;i++){

        /// spremno sortirano

        for(int j=0;j<n;j++){
            d[ind[j]]=b[ind[j]]-(a[ind[j]]>>i);
            c[ind[j]]=(a[ind[j]]&((1<<i)-1));
            ///printf("%d ",d[ind[j]]);
        }
        ///printf(" | %d D\n",i);
        int e=1;
        for(int j=1;j<n;j++){
            if(d[ind[j]]>=d[ind[j-1]]){}
            else e=0;
        }
        if(e==0)goto ende;

        if(d[ind[0]]<0)goto ende;

        if(d[ind[0]]==d[ind[n-1]]){
            rez=min(rez,(ll)i+d[1]);
            goto ende;
        }
        if(abs(d[ind[0]]-d[ind[n-1]])>1)goto ende;

        {
        int id=-1;
        for(int j=1;j<n;j++){
            if(d[ind[j]]!=d[ind[j-1]]){
                id=j;
                break;
            }
        }

        if(c[ind[id]]==c[ind[id-1]])goto ende;


        int pom0=c[ind[id-1]];
        int pom1=c[ind[id]];
        ll prez=0;
        for(int j=0;j<i;j++){
            if((pom0>>1)==(pom1>>1)){
                pom0++;
                pom1++;
                prez++;
            }
            assert(pom0!=pom1);
            pom0>>=1;
            pom1>>=1;
        }
        prez+=i;
        prez+=d[ind[0]];
        rez=min(rez,prez);
        ///printf("%d %lld AAA\n",i,prez);
        }


        ///sortnext/
        ende:
        for(int j=n-1;j>=0;j--)
            pomsrt[(a[ind[j]]&(1<<i))>0].pb(ind[j]);

        int pt=0;
        while(pomsrt[0].size()){
            ind[pt++]=pomsrt[0].back();
            pomsrt[0].pop_back();
        }
        while(pomsrt[1].size()){
            ind[pt++]=pomsrt[1].back();
            pomsrt[1].pop_back();
        }

    }
    if(rez==inf)rez=-1;
    printf("%lld\n",rez);

    return 0;
}
