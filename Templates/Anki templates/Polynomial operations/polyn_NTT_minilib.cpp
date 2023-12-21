#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

namespace polynomial{

    const int maxn=(1<<20);
    int proot=step(3,7*17*8);
    int prekw[maxn];
    int prekinv[maxn];
    int INF=1e9;
    bool prek_flag=0;
    void prek(){

        if(prek_flag)return;
        prek_flag=1;

        prekw[0]=1;
        for(int i=1;i<maxn;i++)
            prekw[i]=mul(prekw[i-1],proot);


        prekinv[0]=1;
        for(int i=1;i<maxn;i++)prekinv[i]=mul(prekinv[i-1],i);

        int curr=invv(prekinv[maxn-1]);
        for(int i=maxn-1;i>0;i--){
            prekinv[i]=mul(curr,prekinv[i-1]);
            curr=mul(curr,i);
        }

    }
    const int MAGIC=500;

    struct polyn{

        vector<int>a;

        polyn(){}
        polyn(vector<int>b){a=b;}

        void push_back(int x){
            a.pb(x);
        }
        int size(){return a.size();}
        void resize(int n){a.resize(n);}

        int& operator [](int x){
            if(x>=a.size())a.resize(x+1);
            return a[x];
        }

        polyn operator -(polyn b){
            polyn ret;
            ret.resize(max(b.size(),(int)a.size()));
            for(int i=0;i<a.size();i++)ret[i]=add(ret[i],a[i]);
            for(int i=0;i<b.size();i++)ret[i]=sub(ret[i],b[i]);
            return ret;
        }

        polyn operator +(polyn b){
            polyn ret;
            ret.resize(max(b.size(),(int)a.size()));
            for(int i=0;i<a.size();i++)ret[i]=add(ret[i],a[i]);
            for(int i=0;i<b.size();i++)ret[i]=add(ret[i],b[i]);
            return ret;
        }

        polyn operator *(int c){
            polyn ret=(*this);
            for(int i=0;i<ret.size();i++)ret[i]=mul(ret[i],c);
            return ret;
        }

        friend polyn operator *(const int c,polyn p){
            return p*c;
        }


        void fft(vector<int>&a,bool invert){

            prek();

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

        polyn brute_pmul(polyn b){
            polyn ret;
            ret.resize(a.size()+b.size()-1);
            for(int i=0;i<a.size();i++)
                for(int j=0;j<b.size();j++)
                    ret[i+j]=add(ret[i+j],mul(a[i],b[j]));
            return ret;
        }

        polyn operator *(polyn b){

            int n=1;
            while(n<(int)a.size()+(int)b.size()-1)n<<=1;
            vector<int>ret=a;

            if(min((int)a.size(),b.size())<MAGIC)return brute_pmul(b);

            ret.resize(n);
            b.resize(n);

            fft(ret,0);
            fft(b.a,0);
            for(int i=0;i<n;i++)ret[i]=mul(ret[i],b[i]);
            fft(ret,1);
            return ret;
        }

        polyn mod_xk(int n){
            polyn ret(a);
            ret.resize(n);
            return ret;
        }

        polyn mul_xk(int n){

            polyn ret=(*this);

            int pom=ret.size();
            ret.resize(ret.size()+n);

            for(int i=ret.size()-1;i>=n;i--)ret[i]=ret[i-n];
            for(int i=0;i<n;i++)ret[i]=0;
            return ret;
        }

        polyn inv(int n){

            polyn bk;
            assert(a[0]!=0);
            bk.pb(invv(a[0]));
            int sz=1;
            while(sz<n){
                sz<<=1;
                polyn pom=((*this).mod_xk(sz)*bk).mod_xk(sz);
                for(int i=0;i<pom.size();i++)pom[i]=sub(0,pom[i]);
                pom[0]=add(pom[0],2);
                bk=(bk*pom).mod_xk(sz);
            }
            return bk.mod_xk(n);
        }

        void reduce(){
            while(a.size() && a.back()==0)a.pop_back();
        }

        polyn reverse(){
            polyn ret(a);
            std::reverse(ret.a.begin(),ret.a.end());
            return ret;
        }

        polyn operator %(polyn b){

            b.reduce();
            reduce();

            int n=a.size();
            int m=b.size();
            if(n<m){
                return (*this);
            }

            polyn p=(reverse()*b.reverse().inv(n-m+1)).mod_xk(n-m+1).reverse();

            return (*this)-p*b;
        }

        polyn operator /(polyn b){

            b.reduce();
            reduce();

            int n=a.size();
            int m=b.size();
            if(n<m){
                polyn ret;
                return ret;
            }

            polyn p=(reverse()*b.reverse().inv(n-m+1)).mod_xk(n-m+1).reverse();
            return p;
        }


        void build_multipoint_eval_tree(int x,int l,int r,vector<polyn>&tree,vector<int>&xp){
            if(l==r){
                tree[x].pb(sub(0,xp[l]));
                tree[x].pb(1);
                return;
            }
            int mid=(l+r)/2;
            build_multipoint_eval_tree(x*2,l,mid,tree,xp);
            build_multipoint_eval_tree(x*2+1,mid+1,r,tree,xp);
            tree[x]=tree[x*2]*tree[x*2+1];
        }
        void multipoint_evaluate_tree(int x,int l,int r,vector<polyn>&tree,vector<int>&ret,polyn p){
            p=p%tree[x];
            if(l==r){
                ret.pb(p[0]);
                return;
            }
            int mid=(l+r)/2;
            multipoint_evaluate_tree(x*2,l,mid,tree,ret,p);
            multipoint_evaluate_tree(x*2+1,mid+1,r,tree,ret,p);
        }
        vector<int> multipoint_eval(vector<int>x){

            vector<polyn>tree(4*x.size()+10);
            build_multipoint_eval_tree(1,0,x.size()-1,tree,x);
            vector<int>ret;
            multipoint_evaluate_tree(1,0,x.size()-1,tree,ret,(*this));

            return ret;
        }

        polyn integral(){

            polyn ret=(*this);

            prek();

            ret.a.resize(a.size()+1);
            for(int i=ret.a.size()-2;i>=0;i--){
                ret.a[i+1]=mul(ret.a[i],prekinv[i+1]);
            }
            ret.a[0]=0;

            return ret;
        }

        polyn deriv(){

            polyn ret=(*this);

            for(int i=0;i<ret.a.size()-1;i++){
                ret.a[i]=mul(i+1,ret.a[i+1]);
            }
            ret.a.pop_back();

            return ret;
        }

        polyn log(int n){
            assert(a[0]==1);
            return (deriv().mod_xk(n)*inv(n)).mod_xk(n).integral().mod_xk(n);
        }

        polyn exp(int n){

            assert(a[0]==0);

            int sz=1;
            polyn bk;
            bk[0]=1;

            while(sz<n){
                sz<<=1;
                polyn pom=mod_xk(sz)-bk.log(sz);
                pom[0]=add(pom[0],1);
                bk=(bk*pom).mod_xk(sz);
            }

            return bk.mod_xk(n);

        }


        void ispis(){
            for(int i=0;i<a.size();i++)printf("%d ",a[i]);
            printf("POLYN ispis\n");
        }

    };

}

using namespace polynomial;

void ispis(vector<int>a){
    for(int i=0;i<a.size();i++)printf("%d ",a[i]);
    printf("ISPIS\n");
}

int main(){


    ///freopen("test.txt","r",stdin);

    polyn a,b;
    a.pb(1);
    a.pb(1);
    b.pb(2);
    b.pb(13);
    b.pb(4);

    vector<int>pts=b.multipoint_eval({1,2,100});
    ispis(pts);

    return 0;
}
