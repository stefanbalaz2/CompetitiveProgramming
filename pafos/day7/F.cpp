#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef long long ll;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=2e6+10;
const int maxn2=1e5+10;
vector<int>sorts[2];/// napravis sa obicnim sortom preko SA table-a
int start_ind[2][maxn2];
const int mb=23;
int SA_table[mb][maxn];
int *SA_sort_c;
int n,m;
int prek_h[maxn];
string a[maxn2],b[maxn2];
int lp[maxn],rp[maxn];
int mxs;



int comp_interval(pii a,pii b){

    int l=min(a.ss-a.ff+1,b.ss-b.ff+1);
    int h=prek_h[l];

    pii pom1={SA_table[h][a.ff],SA_table[h][a.ff+l-(1<<h)]};
    pii pom2={SA_table[h][b.ff],SA_table[h][b.ff+l-(1<<h)]};

    if(pom1==pom2){
        if(a.ss-a.ff==b.ss-b.ff)return 0;
        if(a.ss-a.ff<b.ss-b.ff)return -1;
        return 1;
    }
    else{
        if(pom1<pom2)return -1;
        else return 1;
    }
}
int comp_interval_eq(pii a,pii b){

    int l=a.ss-a.ff+1;
    int h=prek_h[l];

    pii pom1={SA_table[h][a.ff],SA_table[h][a.ff+l-(1<<h)]};
    pii pom2={SA_table[h][b.ff],SA_table[h][b.ff+l-(1<<h)]};

    if(pom1==pom2)return 0;
    else{
        if(pom1<pom2)return -1;
        else return 1;
    }
}
int comp_pair_intervals(pair<pii,pii>a,pair<pii,pii>b){

    while(a.ss!=(pii){-1,-1} && b.ss!=(pii){-1,-1}){

        pii *pom1=&a.ff;
        if(a.ff.ff==-1)pom1=&a.ss;
        pii *pom2=&b.ff;
        if(b.ff.ff==-1)pom2=&b.ss;

        int l=min(pom1->ss-pom1->ff+1,pom2->ss-pom2->ff+1);

        int ret=comp_interval({pom1->ff,pom1->ff+l-1},{pom2->ff,pom2->ff+l-1});
        if(ret!=0)return ret;

        pom1->ff+=l;
        if(pom1->ff>pom1->ss)pom1->ff=pom1->ss=-1;
        pom2->ff+=l;
        if(pom2->ff>pom2->ss)pom2->ff=pom2->ss=-1;

    }

    if(a.ss==(pii){-1,-1} && b.ss==(pii){-1,-1})return 0;
    if(a.ss==(pii){-1,-1})return -1;
    return 1;

}
pii get_se(int f,int x){
    int l;
    if(f==0)l=a[x].size();
    else l=b[x].size();
    return {start_ind[f][x],start_ind[f][x]+l-1};
}
int comp_pair_intervals_aux(pii ac,pii bc){

    /// ubacim da prekalkulisem predjenje a-stringova
    /// ako je jedan prefiks drugog onda pustim funkciju, u suprotnom znam vec odmah kako da returnujem

    int l=min(a[ac.ff].size(),a[bc.ff].size());
    int pom2=comp_interval_eq({start_ind[0][ac.ff],start_ind[0][ac.ff]+l-1},
                              {start_ind[0][bc.ff],start_ind[0][bc.ff]+l-1});
    if(pom2!=0)return pom2;

    int pom=comp_pair_intervals( { get_se(0,ac.ff) , get_se(1,ac.ss) }  , { get_se(0,bc.ff) , get_se(1,bc.ss) } );

    if(pom==0){
        if(ac==bc)return 0;
        if(ac<bc)return -1;
        return 1;
    }

    return pom;
}

void do_SA(string &s){


    int n=s.size();
    vector<int>c(n),ind(n),ind2(n),tmp(n),vect(n),cnt(maxn);
    SA_sort_c=&c[0];
    for(int i=0;i<n;i++){
        c[i]=s[i];
        ind[i]=i;
    }
    sort(ind.begin(),ind.end(),[](const int &a,const int &b)->bool
         {
            return SA_sort_c[a]<SA_sort_c[b];
         });

    for(int i=0;i<n;i++)SA_table[0][i]=c[i];


    int classes;
    classes='z'+1;
    for(int i=0;i<mb-1;i++){

        if((1<<(i+1))>mxs)break;

        for(int j=0;j<n;j++){
            ind2[j]=ind[j]-(1<<i);
            if(ind2[j]<0)ind2[j]+=n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[ind2[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            ind[--cnt[c[ind2[i]]]] = ind2[i];

        tmp[ind[0]]=0;
        for(int j=1;j<n;j++){

            int A1=ind[j];
            int A2=ind[j]+(1<<i);
            if(A2>=n)A2-=n;

            int B1=ind[j-1];
            int B2=ind[j-1]+(1<<i);
            if(B2>=n)B2-=n;

            tmp[ind[j]]=tmp[ind[j-1]];
            if(c[A1]==c[B1] && c[A2]==c[B2]){}
            else tmp[ind[j]]++;

            classes=tmp[ind[j]]+1;
        }

        c.swap(tmp);
        for(int j=0;j<n;j++)
            SA_table[i+1][j]=c[j];


    }

    int curr=0;
    for(int i=1;i<maxn;i<<=1){
        for(int j=i;j<maxn;j++)prek_h[j]=curr;
        curr++;
    }

}
void prek(){

    /// suffix
    /// sort niz indeksa za a i b

    string s;
    for(int i=0;i<n;i++){
        start_ind[0][i]=s.size();
        s+=a[i];
        mxs=max(mxs,(int)a[i].size());
    }
    for(int i=0;i<m;i++){
        start_ind[1][i]=s.size();
        s+=b[i];
        mxs=max(mxs,(int)b[i].size());
    }

    do_SA(s);


    for(int i=0;i<n;i++)sorts[0].pb(i);
    for(int i=0;i<m;i++)sorts[1].pb(i);

    sort(sorts[0].begin(),sorts[0].end(),[](int c,int d)->bool{
            return comp_interval({start_ind[0][c],start_ind[0][c]-1+a[c].size()},
                                 {start_ind[0][d],start_ind[0][d]-1+a[d].size()})<0;
         });
    sort(sorts[1].begin(),sorts[1].end(),[](int c,int d)->bool{
            return comp_interval({start_ind[1][c],start_ind[1][c]-1+b[c].size()},
                                 {start_ind[1][d],start_ind[1][d]-1+b[d].size()})<0;
         });

}


mt19937_64 gen(10);
pii get_random_pair(ll sz,vector<int>&cand){

    ll x=gen()%sz;
    x++;
    for(int j=0;j<cand.size();j++){
        int id=cand[j];
        if(rp[id]-lp[id]+1<x)x-=rp[id]-lp[id]+1;
        else {
            return {id,sorts[1][lp[id]+x-1]};
        }
    }
    assert(1==0);
}
pii go(ll x){

    vector<int>cand;
    for(int i=0;i<n;i++){
        lp[i]=0;
        rp[i]=m-1;
        cand.pb(i);
    }

    ll sz=(ll)n*m;
    while(1){

        pii pom=get_random_pair(sz,cand);

        vector<int>pts(cand.size(),-1);
        ll sum=0;
        for(int i=0;i<cand.size();i++){
            int id=cand[i];

            int l=lp[id];
            int r=rp[id];
            int sr,ret=lp[id]-1;
            while(l<=r){
                sr=(l+r)/2;
                if(comp_pair_intervals_aux({id,sorts[1][sr] },pom)<=0){
                    ret=sr;
                    l=sr+1;
                }
                else r=sr-1;
            }
            pts[i]=ret;

            sum+=ret-lp[id]+1;
        }

        if(sum==x){
            return pom;
        }

        vector<int>tmp;
        if(sum>x){// zadrzi manje
            for(int i=0;i<cand.size();i++){
                int id=cand[i];
                rp[id]=pts[i];
                if(lp[id]<=rp[id])tmp.pb(id);
            }
        }
        else{// zadrzi vece
            for(int i=0;i<cand.size();i++){
                int id=cand[i];
                lp[id]=pts[i]+1;
                if(lp[id]<=rp[id])tmp.pb(id);
            }
            x-=sum;
        }

        cand=tmp;
        sz=0;
        for(int i=0;i<cand.size();i++){
            int id=cand[i];
            sz+=rp[id]-lp[id]+1;
        }

    }

    return get_random_pair(sz,cand);

}


int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<m;i++){
        cin>>b[i];
    }

    prek();

    int q;
    scanf("%d",&q);
    while(q--){

        ll x;
        scanf("%lld",&x);

        pii ret=go(x);
        printf("%d %d\n",ret.ff+1,ret.ss+1);
    }


    return 0;
}
