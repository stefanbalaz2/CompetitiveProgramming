/*

    idea:    https://discuss.codechef.com/t/iai-editorial/26354

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll>pii;
const int maxn=1e5+10;
ll inf=1e18,pref[maxn],pref2[maxn];
int n;
vector<int>ubaci[maxn],izbaci[maxn];
int Q=0;
struct line{

    mutable pii p;
    mutable ll x;

    bool operator <(const line &b)const {
        if(Q==0)return (*this).p<b.p;
        else return (*this).x<b.x;
    }

};
typedef multiset<line>::iterator spit;
struct cht {

    multiset<line>lines;

    void build(){
        lines.clear();
    }

    spit get_prv(spit it){
        if(it==lines.begin())return lines.end();
        it--;
        return it;
    }

    spit get_nxt(spit it){
        it++;
        return it;
    }

    bool ostaje(spit it){

        spit prv,nxt;

        prv=get_prv(it);
        nxt=get_nxt(it);

        if(nxt!=lines.end()){
            if((*nxt).p.ff==(*it).p.ff)return (*it).p.ss<(*nxt).p.ss;
        }
        if(prv!=lines.end()){
            if((*prv).p.ff==(*it).p.ff)return (*it).p.ss<(*prv).p.ss;
        }
        if(prv==lines.end() || nxt==lines.end())return true;

        if(intersection((*prv).p,(*it).p)<intersection((*prv).p,(*nxt).p))return true;
        return false;
    }

    void erase_line(spit it){

        if(it==lines.end())return;

        spit prv=get_prv(it);

        if(prv!=lines.end())intersection(prv,get_nxt(it));

        lines.erase(it);
    }

    void erase_line(pii x){
        erase_line(lines.find({x,0}));
    }

    spit ins_line(pii x){

        spit it=(lines.insert({x,0}));
        spit prv=get_prv(it);

        if(prv!=lines.end())intersection(prv);

        intersection(it);

        return it;
    }

    ll intersection(pii a,pii b){
        if(a.ff==b.ff)return 2*inf;
        return (b.ss-a.ss)/(a.ff-b.ff);
    }
    ll intersection(spit it){
        spit nxt=get_nxt(it);

        if(nxt==lines.end()){
            (*it).x=inf;
            return inf;
        }
        return intersection((*it).p,(*nxt).p);
    }
    ll intersection(spit it,spit it2){
        if(it2==lines.end()){
            (*it).x=inf;
            return inf;
        }
        ll pom=intersection((*it).p,(*it2).p);
        (*it).x=pom;
        return pom;
    }

    void add_line(pii x){

        spit it=ins_line(x);

        if(ostaje(it)){

            while(1){
                spit it2=it;
                it2++;
                if(it2==lines.end())break;
                if(ostaje(it2))break;
                erase_line(it2);
            }

            while(1){
                spit it2=it;
                if(it2==lines.begin())break;
                it2--;
                if(ostaje(it2))break;
                erase_line(it2);
            }
        }
        else erase_line(it);
    }


    ll query(ll x){
        if(lines.size()==0)return -inf;

        Q=1;
        spit it=lines.lower_bound({{-inf,-inf},x});
        Q=0;

        return (*it).p.ff*x+(*it).p.ss;
    }

}tree[262144+10];

void build(int x,int l,int r){

    tree[x].build();

    if(l==r)return;
    int mid=(l+r)/2;

    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
}

void ins(int x,int l,int r,int id,pii val){

    if(l>id || r<id)return;
    tree[x].add_line(val);
    if(l==r)return;
    int mid=(l+r)/2;

    ins(x*2,l,mid,id,val);
    ins(x*2+1,mid+1,r,id,val);
}
void rem(int x,int l,int r,int id,pii val){

    if(l>id || r<id)return;
    tree[x].erase_line(val);
    if(l==r)return;
    int mid=(l+r)/2;

    rem(x*2,l,mid,id,val);
    rem(x*2+1,mid+1,r,id,val);
}

ll query(int x,int l,int r,int lp,int rp,ll xc){

    if(l>rp || r<lp)return -inf;
    if(l>=lp && r<=rp)return tree[x].query(xc);
    int mid=(l+r)/2;
    return max(query(x*2,l,mid,lp,rp,xc),query(x*2+1,mid+1,r,lp,rp,xc));
}

ll go(){

    build(1,1,n);

    ll ret=-inf;
    for(int i=1;i<=n;i++){

        for(int j=0;j<ubaci[i].size();j++){
            int id=ubaci[i][j];
            ins(1,1,n,id,{-pref2[id],pref[id]});



            ret=max(ret,query(1,1,n,i,id,i-1)-pref[i-1]+((ll)i-1)*pref2[i-1]);
        }

        ubaci[i].clear();
    }

    return ret;
}

int main(){

    ///freopen("test2.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int t;
    scanf("%d",&t);
    int cc=0;
    while(t--){

        int m;
        cc++;
        scanf("%d %d",&n,&m);


        for(int i=1;i<=n;i++){
            ll a;
            scanf("%lld",&a);
            pref[i]=pref[i-1]+a*(ll)i;
            pref2[i]=pref2[i-1]+a;
        }

        for(int i=1;i<=m;i++){
            int l,r;
            scanf("%d %d",&l,&r);
            ubaci[l].pb(r);
        }

        printf("%lld\n",go());

    }

    return 0;
}
