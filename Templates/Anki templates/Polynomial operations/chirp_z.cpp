/**



*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

const int mod=101;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){if(base==0)return 0;int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

using cd=complex<double>;

const double PI=acos(-1);
const int maxn=(1<<20);

cd prekw[maxn];
void prek(){

    prekw[0]=1;
    for(int i=1;i<maxn;i++){
        double angle=2.0*PI/maxn*i;
        prekw[i]=cd( cos(angle) , sin(angle) );
    }
}

void fft(vector<cd>&a,bool invert){

    int n=a.size();
    int j=0;
    for(int i=1;i<n;i++){
        int bit=n>>1;
        for(;bit&j;bit>>=1)j^=bit;
        j^=bit;
        if(i<j)swap(a[i],a[j]);
    }


    for(int len=2;len<=n;len<<=1){

        int hlen=len/2;

        for(int i=0;i<n;i+=len){


            int d=maxn/len;
            if(invert)d=maxn-d;
            int curr=0;
            for(int j=0;j<hlen;j++){

                cd pom1=a[i+j];
                cd pom2=a[i+hlen+j]*prekw[curr];

                a[i+j]=pom1+pom2;
                a[i+j+hlen]=pom1-pom2;

                curr+=d;
                if(curr>=maxn)curr-=maxn;
            }

        }

    }

}

cd iconj(cd a){
    a.real(-a.real());
    return a;
}
cd conj(cd a){
    a.imag(-a.imag());
    return a;
}
cd operator / (cd a,double n){
    a.real(a.real()/n);
    a.imag(a.imag()/n);
    return a;
}
cd cswap(cd a){
    double c1=a.real();
    double c2=a.imag();
    a.real(c2);
    a.imag(c1);
    return a;
}

vector<int> pol_mul(vector<int>a,vector<int>b,int mod){

    int n=1;
    while(n<=a.size()+b.size())n<<=1;

    vector<cd>fa(n);
    for(int i=0;i<a.size();i++)fa[i].real(a[i]);
    for(int i=0;i<b.size();i++)fa[i].imag(b[i]);

    fft(fa,0);

    for(int i=0;i<n;i++){

        int sc=n-i;
        if(sc>=n)sc-=n;
        if(i>sc && i!=0)break;


        cd A=fa[i];
        cd B=fa[sc];

        cd pom1=(A+conj(B))/2.0/n;
        cd pom2=cswap((iconj(A)+B)/2.0);

        fa[i]=pom1*pom2;
        fa[sc]=conj(fa[i]);

    }

    fft(fa,1);

    vector<int>ret(n);
    for(int i=0;i<n;i++)
        ret[i]=(((ll)round(fa[i].real())) %mod );

    return ret;
}

void ispis(vector<int>a){

    for(int i=0;i<a.size();i++){

        printf("%d ",a[i]);
    }
    printf("\n");

}

vector<int> chirpz_even(vector<int>a,int z,int m){

    int n=a.size()-1;
    vector<int>b(n+m);
    for(int i=0;i<a.size();i++)
        a[i]=mul(a[i],step(z,i*i));

    for(int i=n+m-1;i>=0;i--)
        b[i]=invv(step(z,(i-n)*(i-n)) );


    a=pol_mul(a,b,mod);

    vector<int>ret;

    for(int i=n;i<n+m;i++)
        ret.pb(mul(a[i],step(z, (i-n)*(i-n) ) ));

    return ret;
}
vector<int> chirpz_odd(vector<int>a,int z,int m){

    int cz=1;
    for(int i=0;i<a.size();i++){
        a[i]=mul(a[i],cz);
        cz=mul(cz,z);
    }

    return chirpz_even(a,z,m);
}

vector<int>chirpz_all(vector<int>a,int z,int m){

    vector<int>r1,r2,ret;

    r1=chirpz_even(a,z,m);
    r2=chirpz_odd(a,z,m);

    for(int i=0;i<m;i++){
        ret.pb(r1[i]);
        ret.pb(r2[i]);
    }

    /*vector<int>ret2;
    for(int i=0;i<m*2;i++){

        int sum=0;
        for(int j=0;j<a.size();j++){
            sum=add(sum, mul(a[j],step(z,i*j)) );
        }

        ret2.pb(sum);
    }

    ispis(ret);
    ispis(ret2);*/

    return ret;
}


int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    prek();


    vector<int>a,b;
    a.pb(1);
    a.pb(3);
    a.pb(4);

    a=chirpz_all(a,18,30);

    /*b=inverse(a,11);
    a=pol_mul(a,b,mod);*/

    ispis(a);

    /*b.pb(1);
    b.pb(1);
    b.pb(6);

    a=pol_mul(a,b);

    ispis(a);*/




    return 0;
}

