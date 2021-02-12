/*

    idea: https://discuss.codechef.com/t/psum-editorial/37796

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return (x*1ll*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

int n,k;
vector<int>dp[110];
int fact[2020],inv[2020];

int wn=step(3,7*17);
int alen=step(2,23);
int wpw=23;
int invw,inv2=step(2,mod-2);
int tc[10000];
vector<int>roots[2];


void fft(vector<int> &a,int inverse){

    int n=a.size();
    for(int i=1;i<n;i++)if(i<tc[i])swap(a[i],a[tc[i]]);


    for(int len=2;len<=n;len<<=1){

        int pom2=n/len;

        for(int j=0;j<n;j+=len){

            int cind=0;

            for(int i=0;i<(len>>1);i++){

                int pom=roots[inverse][cind];
                cind+=pom2;

                int a0=a[i+j];
                int a1=mul(a[i+j+(len>>1)],pom);

                a[i+j]=add(a0,a1);
                a[i+j+(len>>1)]=sub(a0,a1);


            }

        }

    }

    if(inverse){

        int invn=invv(n);
        for(int i=0;i<n;i++)a[i]=mul(a[i],invn);

    }

}

void ispis(vector<int> &x){

    for(int i=0;i<x.size();i++)printf("%d ",x[i]);
    printf(" >>>>>>>>>>>>\n");

}


vector<int> multiply(vector<int> a,vector<int> b){

    a.resize(alen);
    b.resize(alen);

    fft(a,0);
    fft(b,0);

    for(int i=0;i<a.size();i++)a[i]=mul(a[i],b[i]);

    fft(a,1);

    a.resize(k+1);
    return a;
}

void prepW(){

    while(alen/2>=2*k+2){
        alen/=2;
        wn=mul(wn,wn);
    }
    invw=invv(wn);

    int pwn=1;
    while(1){
        roots[0].pb(pwn);
        pwn=mul(pwn,wn);
        if(pwn==1)break;
    }
    while(1){
        roots[1].pb(pwn);
        pwn=mul(pwn,invw);
        if(pwn==1)break;
    }


    inv[0]=1;
    fact[0]=1;
    for(int i=1;i<=k;i++){
        fact[i]=mul(fact[i-1],i);
        inv[i]=invv(fact[i]);
    }


    int n=alen;
    for(int i=1,j=0;i<n;i++){
        int bit=(n>>1);
        for(;j&bit;bit>>=1)j^=bit;
        j^=bit;
        tc[i]=j;
    }

}

int main(){

    int s;
    scanf("%d %d %d",&n,&s,&k);

    prepW();


    for(int i=0;i<=s;i++)dp[i].resize(k+1);
    dp[0][0]=1;


    for(int i=1;i<=n;i++){
        int c;
        int v;
        scanf("%d %d",&c,&v);
        v%=mod;

        vector<int>a,b;
        b.resize(k+1);
        int pom=1;
        for(int o=0;o<=k;o++){
            b[o]=mul(pom,inv[o]);
            pom=mul(pom,v);
        }

        for(int j=s-c;j>=0;j--){

            if(!dp[j][0])continue;

            a=multiply(dp[j],b);
            for(int o=0;o<=k;o++)
                dp[j+c][o]=add(dp[j+c][o],a[o]);

        }

    }

    int rez=0;
    for(int i=0;i<=s;i++)
        rez=add(rez,dp[i][k]);

    printf("%d\n",mul(rez,fact[k]));


    return 0;
}
