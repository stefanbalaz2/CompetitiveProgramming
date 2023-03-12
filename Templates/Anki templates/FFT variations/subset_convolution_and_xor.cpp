/**

    https://codeforces.com/problemset/problem/914/G

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

const int mod=1e9+7;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){if(base==0)return 0;int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}


struct ext{

    vector<ll>a;

    ext(){}
    ext(ll x,ll y){
        a.pb(x);
        a.pb(y);
    }

    ext operator *(const ext &b) const {
        ext ret;
        ret.a.resize(a.size()+b.a.size()-1);
        for(int i=0;i<a.size();i++)
            for(int j=0;j<b.a.size();j++)
                ret.a[i+j]+=a[i]*b.a[j];
        return ret;
    }
    ext operator -(const ext &b) const {
        ext ret;
        int n=max(a.size(),b.a.size());
        ret.a.resize(n);
        for(int i=0;i<a.size();i++)ret.a[i]=a[i];
        for(int i=0;i<b.a.size();i++)ret.a[i]-=b.a[i];
        return ret;
    }
    ext operator +(const ext &b) const {
        ext ret;
        int n=max(a.size(),b.a.size());
        ret.a.resize(n);
        for(int i=0;i<a.size();i++)ret.a[i]=a[i];
        for(int i=0;i<b.a.size();i++)ret.a[i]+=b.a[i];
        return ret;
    }

    void ispis(){

        for(int i=0;i<a.size();i++)printf("%lld ",a[i]);
        printf("EXT\n");

    }

};

const int maxn=(1<<17);
vector<ll>v(maxn);
ext econ(0,1);

void subset_fft(vector<ext>&a,bool invert){
    int n=a.size();
    for(int len=2;len<=n;len<<=1){

        int hlen=(len/2);

        for(int i=0;i<n;i+=len){

            for(int j=0;j<hlen;j++){

                ext pom1=a[i+j];
                ext pom2=a[i+j+hlen];

                ///printf("%d | %d %d |\n",len,pom1.a.size(),pom2.a.size());

                if(!invert){
                    a[i+j]=pom1;
                    a[i+j+hlen]=pom1+pom2*econ;
                }
                else{
                    a[i+j]=econ*pom1;
                    a[i+j+hlen]=pom2-pom1;
                }

            }

        }

    }

}
vector<ll> subset_convolution(vector<ll>a,vector<ll>b){

    int bts=0;
    int n=a.size();
    int n2=n;
    while(n2!=1){
        bts++;
        n2>>=1;
    }
    vector<ext>fa(n),fb(n);

    for(int i=0;i<n;i++){
        fa[i].a.pb(a[i]);
        fb[i].a.pb(b[i]);
    }

    subset_fft(fa,0);
    subset_fft(fb,0);
    for(int i=0;i<n;i++)fa[i]=fa[i]*fb[i];
    subset_fft(fa,1);

    vector<ll>ret(n);
    for(int i=0;i<n;i++)ret[i]=fa[i].a[bts];

    return ret;
}

void ispis(vector<ll>a){
    for(int i=0;i<a.size();i++)printf("%lld ",a[i]);
    printf("\n");
}


void xor_fft(vector<ll>&a,bool invert){
    int n=a.size();
    for(int len=2;len<=n;len<<=1){

        int hlen=(len/2);

        for(int i=0;i<n;i+=len){

            for(int j=0;j<hlen;j++){

                ll pom1=a[i+j];
                ll pom2=a[i+j+hlen];

                ///printf("%d | %d %d |\n",len,pom1.a.size(),pom2.a.size());

                if(!invert){
                    a[i+j]=pom1+pom2;
                    a[i+j+hlen]=pom1-pom2;
                }
                else{
                    a[i+j]=pom1+pom2;
                    a[i+j+hlen]=pom1-pom2;
                    a[i+j]/=2;
                    a[i+j+hlen]/=2;
                }

            }

        }

    }

}
vector<ll> xor_convolution(vector<ll>a,vector<ll>b){

    int n=a.size();

    xor_fft(a,0);
    xor_fft(b,0);
    for(int i=0;i<n;i++)a[i]=a[i]*b[i];
    xor_fft(a,1);

    return a;
}
void and_fft(vector<ll>&a,bool invert){
    int n=a.size();
    for(int len=2;len<=n;len<<=1){

        int hlen=(len/2);

        for(int i=0;i<n;i+=len){

            for(int j=0;j<hlen;j++){

                ll pom1=a[i+j];
                ll pom2=a[i+j+hlen];

                ///printf("%d | %d %d |\n",len,pom1.a.size(),pom2.a.size());

                if(!invert){
                    a[i+j]=pom2;
                    a[i+j+hlen]=add(pom1,pom2);
                }
                else{
                    a[i+j]=sub(pom2,pom1);
                    a[i+j+hlen]=pom1;
                }

            }

        }

    }

}
vector<ll> and_convolution(vector<ll>a,vector<ll>b){

    int n=a.size();

    and_fft(a,0);
    and_fft(b,0);
    for(int i=0;i<n;i++)a[i]=mul(a[i],b[i]);
    and_fft(a,1);

    return a;
}

int fib[maxn];
void transf(vector<ll>&a){

    for(int i=0;i<a.size();i++){
        a[i]%=mod;
        a[i]=mul(a[i],fib[i]);
    }

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    fib[1]=1;
    for(int i=2;i<maxn;i++)fib[i]=add(fib[i-1],fib[i-2]);

    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        v[a]++;
    }

    vector<ll>a,b,c;

    a=subset_convolution(v,v);
    b=v;
    c=xor_convolution(v,v);

    transf(a);
    transf(b);
    transf(c);

    a=and_convolution(a,b);
    a=and_convolution(a,c);

    int rez=0;
    for(int i=0;i<17;i++){
        rez=add(rez,a[(1<<i)]);
    }
    printf("%d\n",rez);

    return 0;
}
