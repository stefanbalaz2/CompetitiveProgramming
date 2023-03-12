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
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

int mod=998244353;
int phimod=0;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){if(base==0)return 0;int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,phimod-1);}

int pos[100000];
vector<int>primes;
void sito(){
    for(int i=2;i<100000;i++){
        if(pos[i])continue;
        primes.pb(i);
        for(int j=i;j<100000;j+=i)pos[j]=1;
    }
}

int phi(int n){

    if(n==1)return 1;

    int ret=1;
    for(int i=0;i<primes.size();i++){

        int id=primes[i];
        if(id*id>n)break;
        if(n%id)continue;

        int pret=1;
        while(n%id==0){
            n/=id;
            pret*=id;
        }

        ret*=pret-pret/id;
    }
    if(n>1)ret*=n-1;

    return ret;
}

int stb(int x,int k){

    int bsize=sqrt(mod)+1;

    unordered_map<int,int>mapa;
    int invr=invv(x);
    int right=k;
    mapa[right]=0;
    for(int i=1;i<bsize;i++){
        right=mul(right,invr);
        if(mapa.find(right)!=mapa.end())continue;
        mapa[right]=i;
    }


    invr=step(x,bsize);
    int left=1;
    for(int i=0;i<=bsize;i++){
        if(mapa.find(left)!=mapa.end())return mapa[left]+bsize*i;
        left=mul(left,invr);
    }

    return -1;
}

int go(int x,int k){

    int curr=1;
    for(int i=0;i<=40;i++){
        if(curr==k)return i;
        curr=mul(curr,x);
    }

    int g=__gcd(x,mod);
    int c=0;
    int a=1;
    while(g!=1){

        if(k%g!=0)return -1;

        k/=g;
        mod/=g;
        if(mod==0)return -1;
        c++;
        a=mul(a,x/g);

        g=__gcd(x,mod);
    }


    phimod=phi(mod);
    k=mul(k,invv(a));

    int pom=stb(x,k);
    if(pom==-1)return pom;
    return pom+c;

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    sito();

    while(1){

        int x,z,k;
        scanf("%d %d %d",&x,&z,&k);
        if(x==0 && k==0 && z==0)break;
        x%=z;
        k%=z;
        mod=z;
        int pom=go(x,k);

        if(pom==-1)printf("No Solution\n");
        else printf("%d\n",pom);

    }

    return 0;
}

