/*

    idea:

        lets observe the taxis in a plane as y=kx+b lines
        when 2 lines intersect, then they are next to each other and they swap places
        brute force would be to sort all intersections and traverse from left to right and when we have an intersection we swap
        correspoinging points, if at any point we have our permutation then we have our answer,else its NIE

        we can notice that if we put a condition that the ith position is to the left of the i+1th position,
        meaning that we take the intervals for which i is to the left of i+1 holds, and take their intersection, we get our answer
        by induction we can prove that this is correct
        calculating the interval for which i is left of i+1 can be done by calculating the line intersection and choosing the proper
        side of the intersection as an interval

        so we only have to maintain intervals for every 2 adjacent lines, and when swaping we only need to update at most 4 positions

*/
#include<bits/stdc++.h>
#include<set>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<ll,ll> pii;
const int maxn=5e5+10;
int n,reind[maxn],a[maxn],q;
pii its[maxn];
ll inf=2e9;
struct ss{
    bool operator () (const pii &a,const pii &b) const{
        return a.ff*b.ss<b.ff*a.ss;
    }
};
multiset<pii,ss>rset,lset;
struct line{
    ll k,b,id;
}ln[maxn];
bool srt(line a,line b){
    return (a.k>b.k)||(a.k==b.k && a.b<b.b);
}
pii get_intersection(line x,line y,int bb){

    if(x.k==y.k){
        if(bb==0){
            if(x.b==y.b)return {-inf,1};
            else return {inf+1,1};
        }
        else{
            return {inf,1};
        }
    }
    pii ret={y.b-x.b,x.k-y.k};
    ll g=abs(__gcd(ret.ff,ret.ss));
    ret.ff/=g;
    ret.ss/=g;

    if(ret.ff<0 && ret.ss<0){
        ret.ff*=-1;
        ret.ss*=-1;
    }
    else{
        if(ret.ff*ret.ss<=0){
            if(ret.ss<0){
                ret.ff*=-1;
                ret.ss*=-1;
            }
        }
    }

    return ret;
}
void build(){

    lset.clear();
    rset.clear();

    for(int i=1;i<n;i++){

        if(a[i]<a[i+1]){

            its[i]=get_intersection(ln[a[i]],ln[a[i+1]],1);
            rset.insert(its[i]);

        }
        else{

            its[i]=get_intersection(ln[a[i]],ln[a[i+1]],0);
            lset.insert(its[i]);

        }

    }

}
bool comp(pii a,pii b){
    return a.ff*b.ss<=b.ff*a.ss;
}
void ispis(){

    pii ret={0,0};

    if(lset.size()==0 && rset.size()==0){
        printf("1/1\n");
        return;
    }
    else if(lset.size()==0)ret=(*rset.begin());
    else if(rset.size()==0){
        ret=(*lset.rbegin());
        if(ret.ff*ret.ss<=0ll)ret={1,1};
    }
    else{
        if(comp((*lset.rbegin()),(*rset.begin())))ret=(*rset.begin());
        else{
            printf("NIE\n");
            return;
        }
    }

    ret.ff=min(ret.ff,1000000000ll);

    if(ret.ff==0 || ret.ff*ret.ss<=0ll)printf("NIE\n");
    else printf("%lld/%lld\n",ret.ff,ret.ss);
}
void izbaci(int x){
    if(x<1)return;
    if(x>=n)return;

    if(a[x]<a[x+1])rset.erase(rset.find(its[x]));
    else lset.erase(lset.find(its[x]));
}
void ubaci(int x){
    if(x<1)return;
    if(x>=n)return;

    if(a[x]<a[x+1]){
        its[x]=get_intersection(ln[a[x]],ln[a[x+1]],1);
        rset.insert(its[x]);
    }
    else{
        its[x]=get_intersection(ln[a[x]],ln[a[x+1]],0);
        lset.insert(its[x]);
    }
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);


    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld %lld",&ln[i].b,&ln[i].k);
        ln[i].id=i;
    }

    sort(ln+1,ln+1+n,srt);
    for(int i=1;i<=n;i++)reind[ln[i].id]=i;

    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        a[i]=reind[a[i]];
    }
    build();
    ispis();

    scanf("%d",&q);
    while(q--){

        int l,r;
        scanf("%d %d",&l,&r);
        if(l>r)swap(l,r);

        set<int>pos;
        pos.insert(l-1);
        pos.insert(l);
        pos.insert(r-1);
        pos.insert(r);

        for(set<int>::iterator it=pos.begin();it!=pos.end();it++)
            izbaci(*it);

        swap(a[l],a[r]);

        for(set<int>::iterator it=pos.begin();it!=pos.end();it++)
            ubaci(*it);

        ispis();
    }

    return 0;
}
