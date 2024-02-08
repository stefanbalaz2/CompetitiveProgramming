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


void ispis(vector<int>a){
    for(int i=0;i<a.size();i++){
        if(a[i]>100000000)printf("%d ",mod-a[i]);
        else printf("%d ",a[i]);
    }
    printf("   ISPISf\n");
}
int proot=step(3,7*17*4);
const int maxn=(1<<21);
int prekw[maxn],fact[maxn],inv[maxn];
void prek(){
    fact[0]=inv[0]=1;
    for(int i=1;i<maxn;i++){
        fact[i]=mul(fact[i-1],i);
    }
    inv[maxn-1]=invv(fact[maxn-1]);
    for(int i=maxn-1;i>0;i--)
        inv[i-1]=mul(inv[i],i);
    prekw[0]=1;
    for(int i=1;i<maxn;i++){
        prekw[i]=mul(prekw[i-1],proot);
    }
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

        int hlen=len>>1;

        for(int i=0;i<n;i+=len){

            int curr=0;
            int d=maxn/len;
            if(invert)d=maxn-d;
            for(int j=0;j<hlen;j++){

                int pom1=a[i+j];
                int pom2=mul(a[i+j+hlen],prekw[curr]);

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
int MAGIC=500;
vector<int> brute_mul(vector<int>a,vector<int>b){
    vector<int>ret(a.size()+b.size()-1);
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++)
        ret[i+j]=add(ret[i+j],mul(a[i],b[j]));
    return ret;
}
vector<int> pol_mul(vector<int>a,vector<int>b){

    if(min(a.size(),b.size())<MAGIC)return brute_mul(a,b);

    int n=1;
    while(n<a.size()+b.size()-1)n<<=1;

    a.resize(n);
    b.resize(n);

    fft(a,0);
    fft(b,0);
    for(int i=0;i<n;i++)a[i]=mul(a[i],b[i]);
    fft(a,1);
    return a;
}
vector<int> pol_sqr(vector<int>a){

    if(min(a.size(),a.size())<MAGIC)return brute_mul(a,a);

    int n=1;
    while(n<a.size()+a.size()-1)n<<=1;

    a.resize(n);

    fft(a,0);
    for(int i=0;i<n;i++)a[i]=mul(a[i],a[i]);
    fft(a,1);
    return a;
}
vector<int>mod_xk(vector<int>a,int n){
    a.resize(n);
    return a;
}
vector<int>pol_inv(vector<int>a,int n){

    assert(a[0]!=0);

    int sz=1;
    vector<int>bk;
    bk.pb(invv(a[0]));

    while(sz<n){

        sz<<=1;
        vector<int>pom=pol_mul(mod_xk(a,sz),mod_xk(bk,sz));
        for(int i=0;i<pom.size();i++)pom[i]=sub(0,pom[i]);
        pom[0]=add(pom[0],2);
        bk=mod_xk(pol_mul(bk,pom),sz);

    }

    bk.resize(n);
    return bk;
}
vector<int>taylor_shift(vector<int>a,int c){


    /// verovatno ovde BUG jer ako radis shift a ukljucio si veci stepen od X nego sto treba onda si ga sjebao

    int n=a.size();
    int currc=1;
    for(int i=0;i<a.size();i++){
        a[i]=mul(a[i], mul(fact[i],currc) );
        currc=mul(currc,c);
    }
    vector<int>b(n);
    for(int i=0;i<n;i++)b[i]=inv[i];
    reverse(b.begin(),b.end());

    a=pol_mul(a,b);

    for(int i=0;i+n-1<a.size();i++)a[i]=a[i+n-1];
    a.resize(n);
    currc=1;
    int d=invv(c);
    for(int i=0;i<n;i++){
        a[i]=mul(a[i],mul(currc,inv[i]));
        currc=mul(currc,d);
    }

    return a;
}
vector<int> stirling(int k){

    vector<int>ret;
    if(k==1){
        ret.pb(0);
        ret.pb(1);
        return ret;
    }

    int m=k/2;

    ret=stirling(m);
    ret.resize(m+1);
    ret=pol_mul(ret, taylor_shift(ret,sub(0,m) ) );
    ret.resize(m*2+1);
    if(k%2){
        vector<int>pom;
        pom.pb(sub(0,k-1));
        pom.pb(1);
        ret=pol_mul(ret,pom);
    }
    ret.resize(k+1);

    return ret;
}
vector<int> stirling_brute(int k){

    vector<int>ret={1};
    for(int i=0;i<k;i++){
        vector<int>pom={sub(0,i),1};
        ret=pol_mul(ret,pom);
    }
    return ret;
}
vector<int>pol_step(vector<int>a,int k){

    if(k==0){
        vector<int>ret;
        ret.pb(1);
        return ret;
    }
    if(k==1)return a;

    vector<int>ret=pol_step(a,k/2);
    ret.resize(a.size()*k/2+1);
    ret=pol_sqr(ret);
    ret.resize(a.size()*k+1);
    if(k%2)ret=pol_mul(ret,a);
    ret.resize(a.size()*k+1);
    return ret;
}
void test(){

    vector<int>a,b;

    a=stirling(1000);
    b=stirling_brute(1000);

    if(a.size()!=b.size())printf("%d %d SZ\n",a.size(),b.size());
    for(int i=0;i<a.size();i++){
        if(a[i]!=b[i])printf("%d %d | %d II\n",a[i],b[i],i);

    }

    /*a.pb(1);
    a.pb(1);
    a.pb(1);
    b.pb(2);
    b.pb(3);
    b.pb(5);

    a=stirling(2);
    ispis(a);

    a=taylor_shift(a,1);
    ispis(a);

    a=pol_mul(a,b);
    b=pol_inv(a,6);
    ispis(a);
    ispis(b);
    ispis(pol_mul(a,b));*/

}
int main(){

    prek();

    //test();

    int t;
    scanf("%d",&t);
    while(t--){
        int k,p;
        scanf("%d %d",&k,&p);
        //k=1000000;
        //p=1;

        vector<int>ret=stirling(k);
        ///ispis(ret);

        //return 0;
        ret=pol_step(ret,p);

        int n=k*p+1;

        vector<int>pom(n);
        for(int i=0;i<pom.size();i++)pom[i]=sub(0,mul(inv[i],inv[2]));
        pom[0]=add(pom[0],1);
        pom=pol_inv(pom,n);
        for(int i=0;i<n;i++)pom[i]=mul(pom[i],fact[i]);

        int rez=0;
        for(int i=0;i<ret.size();i++){

            rez=add(rez, mul(ret[i], pom[i] ) );

        }
        rez=mul(rez,step(inv[k],p) );

        //break;
        printf("%d\n",rez);
    }

    return 0;
}
