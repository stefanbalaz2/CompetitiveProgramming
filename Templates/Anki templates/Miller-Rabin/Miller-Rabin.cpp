/**
  
    https://www.spoj.com/problems/PON/
    
    problem samo cini kad za test pokusas a neki koji je
    tacno jedan od primeova koje koristis, jer
    ako je neki bilo koji drugi composite broj, onda 
    je svejedno, nece proci svaki test
    a ako je neki prime, jedino kad testiras taj tacno prime
    ce biti problem jer ce tvoj a zapravo biti 0
    a za a=0 ne vazi fermat property, i returnovace da nije prime
    
    to se resi lako tako sto prvo prodjem kroz listu da proverim da li moj broj
    pripada listi
    
    takodje moram proveriti da li je x=1, ako jeste onda return false
    jer inace zabode u vecnoj for petlji na pocetku

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<ll,int> pii;

using u64=uint64_t;
using u128=__uint128_t;

int primes[15]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

u64 mul(u64 a,u64 b,u64 mod){
    return ((u128)a*b)%mod;
}
u64 step(u64 base,u64 pw,u64 mod){

    u64 ret=1;
    while(pw){

        if(pw&1)ret=mul(ret,base,mod);

        base=mul(base,base,mod);
        pw/=2;
    }

    return ret;
}

bool check(u64 a,u64 k,u64 c,u64 mod){

    a=step(a,k,mod);

    ///if(__gcd(c,mod)>1)return false;

    if(a==1)return true;
    if(a==mod-1)return true;

    for(int i=1;i<c;i++){
        a=mul(a,a,mod);
        if(a==mod-1)return true;
    }

    return false;
}

bool isprime(u64 x){

    if(x==1)return false;
  
    u64 k=x-1;
    u64 c=0;
    while(k%2==0){
        c++;
        k/=2;
    }

    for(int i=0;i<15;i++)
        if(x==primes[i])return true;


    for(int i=0;i<15;i++)
        if(!check(primes[i],k,c,x))return false;

    return true;
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int t;
    scanf("%d",&t);

    while(t--){

        u64 n;
        scanf("%llu",&n);

        if(isprime(n))printf("YES\n");
        else printf("NO\n");

    }

    return 0;
}

