#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;

const int mod=998244353;
const double dmod=(double)1/mod;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){

    ll ret=(ll)x*y;
    ret=ret-((ll)(dmod*ret))*mod;
    if(ret<0)ret+=mod;
    if(ret>=mod)ret-=mod;
    return ret;

    return ((ll)x*y)%mod;
}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=(1<<20);
int proot=step(3,7*17*8);
int prekw[maxn];

void prek(){

    prekw[0]=1;
    for(int i=1;i<maxn;i++)
        prekw[i]=mul(prekw[i-1],proot);

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

        for(int i=0;i<n;i+=len){

            int cw=maxn/len;
            if(invert)cw=maxn-cw;
            int curr=0;
            for(int j=0;j<len/2;j++){

                int pom1=a[i+j];
                int pom2=mul(a[i+j+len/2],prekw[curr]);

                a[i+j]=add(pom1,pom2);
                a[i+j+len/2]=sub(pom1,pom2);

                curr+=cw;
                if(curr>=maxn)curr-=maxn;

            }

        }

    }


    if(invert){
        int invn=invv(n);
        for(int i=0;i<n;i++)
            a[i]=mul(a[i],invn);
    }

}

int brute_par=500;
vector<int>pol_mul_brute(vector<int>a,vector<int>b){

    vector<int>ret(a.size()-1+b.size()-1+1);

    for(int i=0;i<a.size();i++)
    for(int j=0;j<b.size();j++){
        ret[i+j]=add(ret[i+j], mul(a[i],b[j]) );
    }

    return ret;
}

vector<int> pol_mul(vector<int>a,vector<int>b){

    while(a.size() && a.back()==0)a.pop_back();
    while(b.size() && b.back()==0)b.pop_back();

    if(a.size()*b.size()<brute_par){
        return pol_mul_brute(a,b);
    }

    int n=2;
    while(n<a.size()-1+b.size()-1+1)n<<=1;

    a.resize(n);
    b.resize(n);

    fft(a,0);
    fft(b,0);

    for(int i=0;i<n;i++)
        a[i]=mul(a[i],b[i]);

    fft(a,1);
    return a;
}


void ispis(vector<int>a){

    for(int i=0;i<a.size();i++)printf("%d ",a[i]);
    printf(" ISPIS\n");
}


int main() {

    prek();

    ///freopen("test.txt","r",stdin);

    scanf("%d %d %d",&n,&x,&k);

    return 0;
}
