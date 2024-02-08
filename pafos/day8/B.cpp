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


namespace poly{

    const int maxn=(1<<20);
    const int proot=step(3,7*17*8);
    int prekw[maxn];
    bool isPrek=false;;

    void prek(){
        if(isPrek)return;
        isPrek=true;
        prekw[0]=1;
        for(int i=1;i<maxn;i++)
            prekw[i]=mul(prekw[i-1],proot);
    }

    void fft(vector<int>&a,bool invert){

        prek();

        int j=0;
        int n=a.size();
        for(int i=1;i<n;i++){
            int bit=n>>1;
            for(;bit&j;bit>>=1)j^=bit;
            j^=bit;
            if(i<j)swap(a[i],a[j]);
        }
        for(int len=2;len<=n;len<<=1){
            int hlen=len>>1;
            for(int i=0;i<n;i+=len){
                int d=maxn/len;
                int curr=0;
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

    struct polyn{

        vector<int>a;
        int shift=0;

        int& operator [](int x){
            if(x>=a.size())a.resize(x+1);
            return a[x];
        }

        int size(){return a.size();}
        void resize(int x){a.resize(x);}
        int back(){return a.back();}

        polyn brute_mul(polyn b){

            polyn ret;
            ret.shift=shift+b.shift;

            for(int i=0;i<a.size();i++)
            for(int j=0;j<b.size();j++)
                ret[i+j]=add(ret[i+j],mul(a[i],b[j]));

            return ret;
        }

        polyn operator *(polyn b){

            polyn f=(*this);

            if(min(b.size(),(int)a.size())<=100)return brute_mul(b);

            int n=1;
            while(n<(int)f.size()+(int)b.size()-(int)1)n<<=1;


            f.resize(n);
            b.resize(n);

            fft(f.a,0);
            fft(b.a,0);
            for(int i=0;i<n;i++)f[i]=mul(f[i],b[i]);
            fft(f.a,1);

            while(f.size() && f.back()==0)f.a.pop_back();
            if(f.size()==0)f.a.push_back(0);
            f.shift+=b.shift;

            return f;
        }

        polyn rev(){

            polyn ret=(*this);
            int n=ret.a.size()-1;
            reverse(ret.a.begin(),ret.a.end());
            ret.shift=-n-ret.shift;

            return ret;
        }

        polyn operator +(polyn b){

            polyn ret=(*this);

            if(ret.shift<b.shift)swap(ret,b);

            int d=ret.shift-b.shift;
            int n=ret.size();
            ret.a.resize(ret.a.size()+d);
            for(int i=n-1;i>=0;i--)ret[i+d]=ret[i];
            for(int i=0;i<d;i++)ret[i]=0;
            ret.shift=b.shift;

            ret.resize(max(ret.size(),b.size()));
            for(int i=0;i<b.size();i++)ret[i]=add(ret[i],b[i]);

            return ret;
        }

        void ispis(){

            for(int i=0;i<a.size();i++){
                printf("%d ",a[i]);
            }
            printf(" | shift=%d ISPIS\n",shift);

        }

    };

}

using namespace poly;

int n;
string s;

map<pair<pii,pii>,polyn>mapa;

polyn go(int l,int r,int lc,int rc){

    if(l==r){
        polyn ret;
        if(lc==rc){
            ret[0]=1;
            if(s[l]=='?')ret[0]=2;
            return ret;
        }
        if(s[l]=='R'){
            ret[0]=1;
            ret.shift=1;
            return ret;
        }
        if(s[l]=='B'){
            ret[0]=1;
            ret.shift=0;
            return ret;
        }
        if(s[l]=='?'){
            ret.shift=0;
            ret[0]=1;
            ret[1]=1;
            return ret;
        }
    }

    if(mapa.find({ {l,r} , {lc,rc} })!=mapa.end())return mapa[{ {l,r} , {lc,rc} }];

    polyn &currp=mapa[{ {l,r} , {lc,rc} }];

    int mid;
    if((r-l)%4==0)mid=(l+r)/2+1;
    else mid=(l+r)/2;

    polyn p1,p2;
    if(s[mid]=='Y'){
        p1=go(l,mid-1,lc,0);
        p2=go(mid+1,r,0,rc);
        if(lc!=0)p2=p2.rev();

        currp=p1*p2;
    }
    else if(s[mid]=='P'){
        p1=go(l,mid-1,lc,1);
        p2=go(mid+1,r,1,rc);
        if(lc!=1)p2=p2.rev();

        currp=p1*p2;
    }
    else if(s[mid]=='?'){
        p1=go(l,mid-1,lc,1);
        p2=go(mid+1,r,1,rc);
        if(lc!=1)p2=p2.rev();

        currp=p1*p2;

        p1=go(l,mid-1,lc,0);
        p2=go(mid+1,r,0,rc);
        if(lc!=0)p2=p2.rev();

        currp=currp+p1*p2;
    }


    return currp;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    cin>>s;


    polyn r;
    if(s[0]=='Y'){
        r=go(1,s.size()-1,0,0);
    }
    else if(s[0]=='P'){
        r=go(1,s.size()-1,1,1);
    }
    else{
        r=go(1,s.size()-1,1,1);
        r=r+go(1,s.size()-1,0,0);
    }

    if(-r.shift<0)printf("0\n");
    else printf("%d\n",r[-r.shift]);

    return 0;
}
