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

const int maxn=1e5+10;

ll n;

struct rieman{
    int f(ll n){
        return 1;
    }
    int F(ll n){
        return n%mod;
    }
};

struct mertens{

    vector<int>F,f,a;
    ll n,y,k;

    mertens(ll n){

        this->n=n;
        y=pow(n,0.67);
        k=n/y;
        F.resize(y+1);
        f.resize(y+1);

        do_sieve();
        precalc_a();
    }

    int get_F(ll k){
        int ret;
        if(n/k<=y)ret=F[n/k];
        else ret=a[a.size()-k];
        return ret;
    }

    void do_sieve(){


        f[1]=1;
        vector<int>primes;
        vector<bool>composite(y+1);
        for(int i=2;i<=y;i++){
            if(!composite[i]){
                primes.pb(i);
                f[i]=mod-1;
            }

            for(int j=0;j<primes.size() && i*primes[j]<=y;j++){

                composite[i*primes[j]]=true;

                if(i%primes[j]==0){
                    f[i*primes[j]]=0;
                    break;
                }
                else{
                    f[i*primes[j]]=mul(f[i],mod-1);
                }

            }

        }
        for(int i=1;i<=y;i++)F[i]=add(F[i-1],f[i]);

    }

    int calculate_big_F(ll k){/// calculate F(n/k)

        rieman R;

        ll cn=n/k;
        int b=sqrt(cn);

        int ret=1;
        for(int i=2;i<=b;i++)
            ret=sub(ret, mul(R.f(i),get_F(k*i)) );

        for(int i=1;i<=b;i++)
            ret=sub(ret, mul(f[i],R.F(n/(k*i))) );

        ll ts=n/k;
        ret=add(ret,mul(R.F(b),get_F( (ts/b)*k )));

        return ret;
    }

    void precalc_a(){

        int pt=0;
        a.resize(k);
        for(int j=k;j>=1;j--){
            a[pt++]=calculate_big_F(j);
        }
    }

};


struct identity{

    int inv2=invv(2);

    int f(ll n){
        return n%mod;
    }
    int F(ll n){
        return mul(mul(add(n%mod,1),n%mod),inv2);
    }

};

struct phi{

    vector<int>f,F,a;
    ll n,y,k;

    phi(ll n,mertens &m){

        this->n=n;
        y=pow(n,0.67);
        k=n/y;

        f.resize(y+1);
        F.resize(y+1);

        do_sieve();
        precalc(m);
    }

    void do_sieve(){

        vector<int>primes;
        vector<bool>composite(y+1);
        f[1]=1;
        for(int i=2;i<=y;i++){
            if(!composite[i]){
                f[i]=i-1;
                primes.pb(i);
            }
            for(int j=0;j<primes.size() && i*primes[j]<=y;j++){
                composite[i*primes[j]]=1;
                if(i%primes[j]==0){
                    f[i*primes[j]]=f[i]*primes[j];
                    break;
                }
                else{
                    f[i*primes[j]]=f[i]*f[primes[j]];
                }
            }
        }

        for(int i=1;i<=y;i++){
            f[i]%=mod;
            F[i]=add(f[i],F[i-1]);
        }

    }

    int calc_F(ll k,mertens &m){

        int ret=0;

        identity id;
        ll cn=n/k;
        ll b=sqrt(cn);
        for(int i=1;i<=b;i++){
            ret=add(ret,mul(m.f[i],id.F(cn/i)));
            ret=add(ret,mul(m.get_F(k*i),id.f(i)));
        }
        ll ts=cn;
        assert(n/((ts/b)*k)==b);
        ret=sub(ret,mul(m.get_F( (ts/b)*k ),id.F(b)));

        return ret;
    }

    int get_F(ll k){
        if(n/k<=y)return F[n/k];
        return a[k-1];
    }

    void precalc(mertens &m){

        a.resize(k);
        int pt=0;
        for(int i=1;i<=k;i++){
            a[pt++]=calc_F(i,m);
        }

    }

};


int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%lld",&n);
    mertens m(n);

    phi p(n,m);

    int ret=0;

    identity id;

    ll b=sqrt(n);
    for(int i=1;i<=b;i++){
        ret=add(ret, mul(id.f(i),p.get_F(i) ));
        ret=add(ret,mul(id.F(n/i),p.f[i]) );
    }

    assert(n/(n/b)==b);
    ret=sub(ret, mul(id.F(b), p.get_F(n/b) ) );

    printf("%d\n",ret);

    return 0;
}
