/**

    https://www.spoj.com/problems/FACT0/

    obavezno moraju oba da krenu iz istog broja inace mozda se uopste ne nalaze u istom ciklusu

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<ll,int> pii;

using i128=__int128_t;

mt19937_64 gen(10);

void advance2(ll &x,ll &n){
    x=( (i128)x*(i128)x+(i128)1)%((i128)n);
}

ll split(ll x){

    ll c1=gen()%x;
    if(c1<0)c1+=x;
    ll c2=c1;

    while(1){

        advance2(c1,x);
        advance2(c2,x);
        advance2(c2,x);

        ll pom=__gcd((ll)max(c1,c2)-min(c1,c2) , (ll)x );

        if(pom!=1)return pom;

    }

}

void factorise(ll x){

    vector<ll>cand;

    for(int i=2;i<100;i++){
        if(x%i==0){
            cand.pb(i);
            x/=i;
            i--;
        }
    }
    int start;
    if(x==1)start=cand.size();
    else{
        start=cand.size();
        cand.pb(x);
    }
    for(int i=start;i<cand.size();i++){

        ll pom=split(cand[i]);
        if(pom==cand[i])continue;

        cand[i]/=pom;
        cand.pb(pom);
        i--;
    }

    sort(cand.begin(),cand.end());

    vector<pii>c;
    c.pb({cand[0],1});
    for(int i=1;i<cand.size();i++){
        if(cand[i]==c.back().ff)c[c.size()-1].ss++;
        else c.pb({cand[i],1});
    }

    for(int i=0;i<c.size();i++)
        printf("%lld^%d ",c[i].ff,c[i].ss);

    printf("\n");

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    while(1){

        ll n;
        scanf("%lld",&n);
        if(n==0)break;

        factorise(n);

    }

    return 0;
}

