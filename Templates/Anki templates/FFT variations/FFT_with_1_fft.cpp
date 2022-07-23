#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;

using cd=complex<double>;

const double PI=acos(-1);
const int maxn=1e5+10;
int maxw;

cd prekw[maxn*4];

void prek(){

    maxw=1;
    while(maxw<=2*maxn)maxw<<=1;

    for(int i=0;i<maxw;i++)
        prekw[i]=cd(cos(2.0*PI/maxw*i),sin(2.0*PI/maxw*i));

    ///cout<<(prekw[maxw-1]*prekw[1]).real()<<endl;

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

        for(int i=0;i<n;i+=len){

            int cw=maxw/len;
            if(invert)cw=maxw-cw;
            int curr=0;
            for(int j=0;j<len/2;j++){

                cd pom1=a[i+j];
                cd pom2=a[i+j+len/2]*prekw[curr];

                a[i+j]=pom1+pom2;
                a[i+j+len/2]=pom1-pom2;

                curr+=cw;
                if(curr>=maxw)curr-=maxw;

            }

        }

    }


    if(invert){
        for(int i=0;i<n;i++)
            a[i]/=n;
    }

}

void ispis(vector<cd>&a){

    for(int i=0;i<a.size();i++){

        cout<<a[i].real()<<" "<<a[i].imag()<<"  | ";

    }

    cout<<"   ISPIS"<<endl;

}

cd conj(cd a){
    cd ret(a.real(),-a.imag());
    return ret;
}

vector<ll> pol_mul(vector<ll>&a,vector<ll>&b){


    int n=2;
    while(n<a.size()+b.size())n<<=1;

    vector<cd>fa(n);

    for(int i=0;i<a.size();i++)fa[i].real(a[i]);
    for(int i=0;i<b.size();i++)fa[i].imag(b[i]);

    fft(fa,0);

    for(int i=0;i<n;i++){

        cd pom1=fa[i];
        cd pom2=fa[(n-i)&(n-1)];

        cd aa=(pom1+conj(pom2))/2.0;
        cd bp=(pom2-conj(pom1))/2.0;
        cd bb(bp.imag(),bp.real());

        fa[i]=aa*bb;
        fa[(n-i)&(n-1)]=conj(aa)*conj(bb);

        if(i!=0 && i==( (n-i)&(n-1) ))break;
    }


    fft(fa,1);

    vector<ll>ret(n);

    for(int i=0;i<n;i++){
        ret[i]=round(fa[i].real());
    }

    while(ret.back()==0)ret.pop_back();

    return ret;

}

int main() {


    ///freopen("test.txt","r",stdin);

    prek();

    int t;
    scanf("%d",&t);

    while(t--){

        int n;
        scanf("%d",&n);

        vector<ll>vecta,vectb;
        for(int i=0;i<=n;i++){
            int a;
            scanf("%d",&a);
            vecta.pb(a);
        }

        for(int i=0;i<=n;i++){
            int a;
            scanf("%d",&a);
            vectb.pb(a);
        }

        vecta=pol_mul(vecta,vectb);

        vecta.resize(2*n+1);
        for(int i=0;i<vecta.size();i++)printf("%lld ",vecta[i]);
        printf("\n");

    }

    return 0;
}

