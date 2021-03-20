#include <bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
using cd=complex<double>;
#define PI 3.14159265359

void fft(vector<cd> &a,bool invert){

    int n=a.size();

    for(int i=1,j=0;i<n;i++){

        int bit=n>>1;
        for(;j&(bit);bit>>=1)j^=bit;
        j^=bit;

        if(i<j)swap(a[i],a[j]);
    }

    for(int len=2;len<=n;len<<=1){

        int hlen=(len>>1);

        double angle=2*PI/len*(invert?-1:1);
        cd wlen(cos(angle),sin(angle));

        for(int i=0;i<n;i+=len){

            cd w(1);
            for(int j=0;j<hlen;j++){

                cd pom1=a[i+j];
                cd pom2=w*a[i+j+hlen];

                a[i+j]=pom1+pom2;
                a[i+j+hlen]=pom1-pom2;

                w*=wlen;
            }

        }

    }

    if(invert){
        for(int i=0;i<n;i++)a[i]/=n;
    }


}
vector<ll> mul(vector<ll> &a,vector<ll> &b){

    vector<cd>fa(a.begin(),a.end()),fb(b.begin(),b.end());

    int n=1;
    while(n<a.size()+b.size())n<<=1;

    fa.resize(n);
    fb.resize(n);
    ///printf("%d %d %d dsAFSA\n",n,a.size(),b.size());

    fft(fa,0);
    fft(fb,0);

    for(int i=0;i<n;i++)fa[i]*=fb[i];

    fft(fa,1);

    vector<ll>ret(n);
    for(int i=0;i<n;i++)ret[i]=round(fa[i].real());


    return ret;
}

int main(){

    int t;
    scanf("%d",&t);

    while(t--){

        int n;
        scanf("%d",&n);

        vector<ll>a(n+1);
        vector<ll>b(n+1);
        for(int i=0;i<=n;i++){
            int pom;
            scanf("%d",&pom);
            a[i]=pom;
        }
        for(int i=0;i<=n;i++){
            int pom;
            scanf("%d",&pom);
            b[i]=pom;
        }

        reverse(a.begin(),a.end());
        reverse(b.begin(),b.end());

        vector<ll>pom=mul(a,b);

        for(int i=2*n+1-1;i>=0;i--)printf("%lld ",pom[i]);
        printf("\n");

    }

    return 0;
}
