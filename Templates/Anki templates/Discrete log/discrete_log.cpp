/**

    https://www.spoj.com/problems/MOD/


    naci najmanji stepen y tako da x^y=k(mod m)

    kod resavanja generalno je fora da ako x generise ciklicnu grupu(sto moze biti iako nisu x i m coprime)
    ako to generisu, onda mozemo kolko hocemo puta primenjivati redukciju i na kraju naci rezultat
    ako nije tako onda ne mozemo bas da radimo redukciju kolko puta hocemo jer cemo ne mozemo
    da uradimo redukciju vise od y puta
    x ne generise ciklicnu grupu ako je set distinct primeova od m podskup distinct primeova od x
    jer ce onda stepenovanjem kad tad se napraviti bar skup m, ali to ce biti u najvise logm koraka
    u suprotnom nikad nece doci do broja 0 i imacemo ciklus

    lako cemo onda prvo proveriti da li je y<=logm tj da li je y mali, pa ako nije znamo
    da mozemo uraditi kolko hocemo redukcija
    nakon sto proverimo da li je mali, u oba slucaja mozemo nastaviti dalje, ali moramo
    u redukciji staviti da ako je mod=0 da prekidamo, onda nemamo resenje

    posto trazimo najmanji stepen y, ako imam c redukcija, mi cemo sa small to big naci
    najmanji stepen koji je >=c, da bismo proverili da li je <c mozemo brute forceom


*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef unsigned long long ll;
using namespace std;
typedef pair<int,int> pii;

using int128=__int128_t;

ll mod;
ll phimod;
inline ll add(ll x,ll y){ll ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline ll sub(ll x,ll y){ll ret=x-y;if(ret<0)ret+=mod;return ret;}
inline ll mul(ll x,ll y){return ((int128)x*y)%mod;}
inline ll step(ll base,ll pw){ll ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline ll invv(ll x){return step(x,phimod-1);}

const int maxn=2e5+10;

int phi(int x){
    int ret=1;
    for(int i=2;i*i<=x;i++){
        if(x%i)continue;
        int pom=1;
        while(x%i==0){
            pom*=i;
            x/=i;
        }
        ret*=pom-pom/i;
    }
    if(x>1)ret*=x-1;
    return ret;
}

int shanks(int a,int b){

    int block=sqrt(mod)+5;
    int curr=b;
    int d=invv(a);
    unordered_map<int,int>mapa;
    for(int i=0;i<block;i++){
        if(mapa.find(curr)==mapa.end()){
            mapa[curr]=i;
        }
        curr=mul(curr,d);
    }

    curr=1;
    d=step(a,block);
    for(int i=0;i<=block;i++){
        if(mapa.find(curr)!=mapa.end()){
            return i*block+mapa[curr];
        }
        curr=mul(curr,d);
    }
    return -1;
}
int go(int a,int b,int m){
    mod=m;

    if(m==1)return 0;

    int curr=1;
    for(int i=0;i<50;i++){
        if(curr==b)return i;
        curr=mul(curr,a);
    }

    int g;
    int c=0;
    int coef=1;
    while((g=__gcd(a,(int)mod)) != 1){
        mod/=g;
        coef=mul(coef,a/g);
        c++;
        if(b%g!=0)return -1;
        assert(mod!=0);
        b/=g;
    }
    phimod=phi(mod);
    b=mul(b,invv(coef));

    if(mod==1)return c;

    int pom=shanks(a,b);
    if(pom==-1)return pom;
    else return pom+c;
}

int main(){

    //freopen("test.txt","r",stdin);

    while(1){

        int x,z,k;
        scanf("%d %d %d",&x,&z,&k);

        if(x==0 && z==0 && k==0){
            break;
        }

        x%=z;
        k%=z;

        int pom=go(x,k,z);
        if(pom==-1)printf("No Solution\n");
        else printf("%d\n",pom);

    }

    return 0;
}
