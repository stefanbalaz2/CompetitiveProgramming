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


namespace polynomial{

    const int maxn=(1<<20);
    int proot=step(3,7*17*8);
    int prekw[maxn];
    bool prek_flag=0;
    void prek(){

        if(prek_flag)return;
        prek_flag=1;

        prekw[0]=1;
        for(int i=1;i<maxn;i++)
            prekw[i]=mul(prekw[i-1],proot);
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

            prek();

            int n=1;
            while(n<a.size()+b.size()-1)n<<=1;
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



        void ispis(){
            for(int i=0;i<a.size();i++)printf("%d ",a[i]);
            printf("POLYN ispis\n");
        }

    };

}


const int maxalp=26;
const int maxn=2e5+10;
string s,p;
int n,m;
int Z[maxn];

using namespace polynomial;
void prek_z(){

    p=s+'$'+s;

    int l=1;
    int r=0;
    int pt=0;
    while(1){

        pt++;
        if(pt>=p.size())break;

        if(pt>r || l>r){
            l=pt;
            r=l-1;
            while(r+1<p.size() && p[r+1]==p[r+1-l])r++;
            Z[pt]=r-l+1;
        }
        else{

            if(pt+Z[pt-l]-1>=r){
                l=pt;
                while(r+1<p.size() && p[r+1]==p[r+1-l])r++;
                Z[pt]=r-l+1;
            }
            else{
                Z[pt]=Z[pt-l];
            }

        }

    }

   // cout<<p<<endl;
    //for(int i=0;i<p.size();i++)printf("%d ",Z[i]);
   // printf("\n");

}
polyn construct_g(){
    polyn ret;
    for(int k=1;k<n;k++){
        if(Z[p.size()-k]>=k){
            ret[n-k]=1;
        }
    }
   // ret.ispis();
    return ret;
}
polyn minp(polyn a){
    for(int i=1;i<a.size();i+=2)a[i]=sub(0,a[i]);
    return a;
}
polyn section(int i,polyn p){
    polyn ret;
    for(int j=i;j<p.size();j+=2)ret.pb(p[j]);
    return ret;
}
int calc_xn(polyn g,int m){

    polyn p,q,pom;
    pom[0]=1;
    pom[1]=sub(0,maxalp);
    p[n]=1;
    g[0]=1;
    g=g*pom;
    g[n]=add(g[n],1);
    q=g;

    //p=(p*q.inv(10)).mod_xk(10);
    //p.ispis();

    //return 0;

    //(p*q.inv(10)).mod_xk(10).ispis();
    while(m){
        //printf("GO %d\n",n);
        p=section(m%2,p*minp(q));
        q=section(0,q*minp(q));
        m>>=1;
        //(p*q.inv(10)).mod_xk(10).ispis();
        //q.ispis();
    }
    //printf("%d %d AA\n",p[0],q[0]);
    return mul(p[0],invv(q[0]));
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    cin>>s;

    prek_z();

    polyn g=construct_g();

    printf("%d\n",calc_xn(g,m));

    return 0;
}
