/**

    https://www.spoj.com/problems/FACT0/

    u pollardu obavezno oba x moraju krenuti iz iste vrednosti jer u suprotnom mozda nece ni biti u istom ciklusu

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

using u64=uint64_t;
using u128=__uint128_t;

int primes[15]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
inline u64 mul(u64 a,u64 b,u64 mod){
    return ((u128)a*b)%mod;
}
u64 step(u64 base,u64 pw,u64 mod){
    u64 ret=1;
    while(pw){
        if(pw&1)ret=mul(ret,base,mod);
        base=mul(base,base,mod);
        pw>>=1;
    }
    return ret;
}
bool check(u64 a,u64 n,u64 k,u64 r){

    a%=n;
    if(a==0)return true;

    a=step(a,r,n);
    if(a==1)return true;
    for(int i=0;i<k;i++){
        if(a==n-1)return true;
        a=mul(a,a,n);
    }
    return false;
}
bool isprime(u64 n){

    if(n==1)return false;

    u64 pom=n-1;
    u64 k=0;
    u64 r=0;
    while((pom&1)==0){
        k++;
        pom>>=1;
    }
    r=pom;

    for(auto p:primes)
        if(!check(p,n,k,r))return false;
    return true;
}

void adv(u64 &x,u64 b,u64 n){
    x=(mul(x,x,n)+b)%n;
}
mt19937 gen(10);
u64 pollard(u64 n,u64 b){

    u64 x1=gen()%n;
    if(x1<0)x1+=n;
    u64 x2=x1;

    while(1){
        adv(x1,b,n);
        adv(x2,b,n);
        adv(x2,b,n);

        u64 g=__gcd(n, max(x1,x2)-min(x1,x2) );
        if(g!=1)return g;
    }

}
vector<u64> factorise(u64 n){

    vector<u64>ret;
    if(isprime(n)){
        ret.pb(n);
        return ret;
    }

    u64 lp;
    if(n<20){
        for(int i=2;i<n;i++){
            if(n%i==0){
                lp=i;
                break;
            }
        }
    }
    else{
        for(u64 b=1;;b++){
            lp=pollard(n,b);
            if(lp!=n)break;
        }
    }
    vector<u64>lv=factorise(lp);
    vector<u64>rv=factorise(n/lp);

    for(int i=0;i<lv.size();i++)ret.pb(lv[i]);
    for(int i=0;i<rv.size();i++)ret.pb(rv[i]);
    return ret;
}

int main(){


    ///freopen("test.txt","r",stdin);

    u64 n;
    while(1){
        scanf("%llu",&n);
        if(n==0)break;
        if(n==1){
            printf("\n");
            continue;
        }
        vector<u64>pom=factorise(n);
        sort(pom.begin(),pom.end());
        vector<pair<u64,int>>cand;
        cand.pb({pom[0],1});
        for(int i=1;i<pom.size();i++){
            if(pom[i]==cand.back().ff)cand[cand.size()-1].ss++;
            else cand.pb({pom[i],1});
        }
        for(int i=0;i<cand.size();i++){
            printf("%llu^%d ",cand[i].ff,cand[i].ss);
        }
        printf("\n");
    }


    return 0;
}
