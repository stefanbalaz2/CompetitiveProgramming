/**

  https://www.codechef.com/problems/TREEWALK?tab=statement
  

*/
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

const int maxn=3010;
int n,k,r;
mt19937 gen(10);

void shift_right(vector<int>&v,int d){
    for(int i=v.size()-1;i>=d;i--)v[i]=v[i-d];
    for(int i=d-1;i>=0;i--)v[i]=0;
}
vector<int> berlekamp_massey(vector<int>s){

    vector<int>c,oldc;
    int f=-1;
    int last_delta=-1;

    for(int i=0;i<s.size();i++){

        int delta=s[i];
        for(int j=1;j<=c.size();j++)
            delta=sub(delta,mul(s[i-j],c[j-1]));

        if(delta==0)continue;

        if(f==-1){
            c.resize(i+1);
            f=i;
            last_delta=delta;
        }
        else{

            vector<int>d=oldc;
            d.resize(d.size()+1);
            shift_right(d,1);
            for(int j=0;j<d.size();j++)d[j]=sub(0,d[j]);
            d[0]=1;

            int pom=mul(invv(last_delta),delta);
            for(int j=0;j<d.size();j++)d[j]=mul(d[j],pom);

            int zeroes=i-f-1;
            d.resize(d.size()+zeroes);
            shift_right(d,zeroes);

            vector<int>temp=c;
            c.resize(max(c.size(),d.size()));
            for(int j=0;j<d.size();j++)c[j]=add(c[j],d[j]);

            if(i-temp.size()>f-oldc.size()){
                last_delta=delta;
                oldc=temp;
                f=i;
            }

        }
    }

    return c;
}

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

using namespace polynomial;


vector<int>mat_recur;
vector<pii>edges;
vector<vector<int>>mpw;

vector<int>mnozi(vector<int>a){

    vector<int>ret(n);
    for(int i=0;i<edges.size();i++){
        int u=edges[i].ff;
        int v=edges[i].ss;
        ret[u]=add(ret[u],a[v]);
        ret[v]=add(ret[v],a[u]);
    }
    return ret;
}

bool step_flag=false;
void prek_step(){
    if(step_flag)return;
    step_flag=true;

    vector<int>curr(n,0);
    curr[r]=1;
    mpw.pb(curr);
    for(int i=1;i<2*n;i++){
        curr=mnozi(curr);
        mpw.pb(curr);

        /*printf("%d MP\n",i);
        for(int j=0;j<mpw.back().size();j++)printf("%d ",mpw[i][j]);
        printf("\n");*/
    }

}
int dot_prod(vector<int>a,vector<int>b){
    int ret=0;
    for(int i=0;i<a.size();i++)ret=add(ret,mul(a[i],b[i]));
    return ret;
}
void generisi_rek(vector<int>&w){

    prek_step();

    vector<int>v;
    for(int i=0;i<2*n;i++)
        v.pb(dot_prod(w,mpw[i]));

    mat_recur=berlekamp_massey(v);

}
void prek_mat_rek(){

    int cc=0;
    while(mat_recur.size()!=n){

        cc++;
        vector<int>w;
        for(int i=0;i<n;i++)w.pb(gen()%mod);

        generisi_rek(w);
        ///printf("%d AAA\n",mat_recur.size());
        if(cc>10)break;
    }


}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        u--;
        v--;
        edges.pb({u,v});
    }
    scanf("%d %d",&r,&k);
    r--;

    if(n==1){
        printf("1\n");
        return 0;
    }

    prek_mat_rek();

    polyn xr,xm,base;
    base.pb(0);base.pb(1);
    for(int i=mat_recur.size()-1;i>=0;i--)xm.pb(sub(0,mat_recur[i]));
    xm.pb(1);
    xr.pb(1);
    while(k){
        if(k&1)xr=(xr*base)%xm;
        base=(base*base)%xm;
        k>>=1;
    }
    xr=xr%xm;


    for(int i=0;i<n;i++){
        int rez=0;
        for(int j=0;j<n;j++){
            rez=add(rez,mul(xr[j], mpw[j][i] ));
        }
        printf("%d ",rez);
    }

    return 0;
}
