/*

    idea:   use the identity gcd(fn,fm)=f(gcd(n,m))

            this gives us a clear observation that
            only the fibonacci with prime indices are fibonacci coprime(except for N=1, N=2)
            then we have to output first 9 digits
            do that with log10
            use the formula for fn=phi^n/sqrt(5)
            use long double, on double its WA
            for the first few fibonaccis we gotta do it seperatelly
            because our implementation gives us WA for those because the
            formula should be rounded to the nearest integer, but in my implementation
            i didnt find a way to do it

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxa=3e5;
int primes[100000],pos[maxa+10],br;
string rez[100000];
void sito(){

    for(int i=2;i<maxa;i++){
        if(pos[i])continue;
        primes[++br]=i;
        for(int j=i;j<maxa;j+=i)pos[j]=1;
    }

}
ll ff[100];
ll f(int x){
    if(x==0)return 0;
    if(x==1)return 1;
    if(ff[x]!=0)return ff[x];
    ff[x]=f(x-1)+f(x-2);
    return f(x-1)+f(x-2);
}
string go(int x){

    if(x<=43){
        ll pom=f(x);
        string ret;
        while(pom){
            ret.pb('0'+pom%10);
            pom/=10;
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }

    long double phi=(1+sqrt(5))/2;
    long double pom=(long double)x*log10(phi);
    pom-=log10((long double)sqrt(5));
    int digits=min(9,(int)trunc(pom)+1);
    pom=pom-trunc(pom);


    pom=pow(10,pom);

    string ret;
    for(int i=1;i<=digits;i++){
        int dig=trunc(pom);
        ret.pb('0'+dig);
        pom=pom-trunc(pom);
        pom*=10;
    }

    return ret;
}
void prek(){
    for(int i=1;i<=br;i++){
        rez[i]=go(primes[i]);
    }
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    sito();
    prek();

    int n;
    while(scanf("%d",&n)==1){
        if(n==1)printf("2\n");
        else if(n==2)printf("3\n");
        else cout<<rez[n]<<endl;
    }

    return 0;
}
