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

const int maxn=3e5+10;
int n,a[maxn],b[maxn],c[maxn];

struct line{

    ll k,n;
    int id,t;

};

bool should_pop(line a,line b,line c){

    ll lp=(b.n-a.n)*(b.k-c.k);
    ll rp=(c.n-b.n)*(a.k-b.k);

    if(lp>=rp)return true;
    return false;
}
void append(vector<line>&stek,line x){
    while(stek.size()>1 && should_pop(stek[stek.size()-2],stek[stek.size()-1],x))stek.pop_back();
    stek.pb(x);
}
double inf=1e18;
double intersection(line a,line b){
    return ((double)b.n-a.n)/((double)a.k-b.k);
}
void ubaci(vector<pair<double,pii>>&cand,vector<line>stek){

    cand.pb({-inf,{stek[0].t,stek[0].id}});
    for(int i=1;i<stek.size();i++){
        double inter=intersection(stek[i-1],stek[i]);
        cand.pb({inter,{stek[i].t,stek[i].id}});
    }

}

bool eq(double a,double b){
    double eps=1e-9;
    if(abs(a-b)<=eps)return true;
    return false;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    vector<line>stek;
    vector<pair<double,pii>>cand;

    stek.clear();
    for(int i=0;i<=n;i++){
        int a;
        scanf("%d",&a);
        line pom={(ll)i,(ll)a,i,0};
        append(stek,pom);
    }
    ubaci(cand,stek);

    stek.clear();
    for(int i=0;i<=n;i++){
        int a;
        scanf("%d",&a);
        line pom={(ll)i,(ll)a,i,1};
        append(stek,pom);
    }
    ubaci(cand,stek);

    stek.clear();
    for(int i=0;i<=n;i++){
        int a;
        scanf("%d",&a);
        line pom={(ll)i,(ll)a,i,2};
        append(stek,pom);
    }
    ubaci(cand,stek);

    sort(cand.begin(),cand.end());

    /*for(int i=0;i<cand.size();i++){
        cout<<cand[i].ff<<endl;
    }*/

    int pt=0;
    set<int>st;
    int inds[3]={0,0,0};
    while(1){

        if(pt==cand.size())break;

        double cix=cand[pt].ff;
        while(eq(cand[pt].ff,cix)){
            inds[cand[pt].ss.ff]=cand[pt].ss.ss;
            pt++;
        }

        st.insert(inds[0]+inds[1]+inds[2]);
    }

    vector<int>rez;
    for(int i=0;i<=3*n;i++){
        if(st.find(i)==st.end())rez.pb(i);
    }
    printf("%d\n",rez.size());
    for(int i=0;i<rez.size();i++){
        printf("%d ",rez[i]);
    }

    return 0;
}
