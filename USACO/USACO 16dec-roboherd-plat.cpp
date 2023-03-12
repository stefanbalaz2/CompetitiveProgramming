/*

    idea and thought process:

        - after reading the task, i went through few questions:

            -how does the solution look like and what does it consist of
            -is there some ordering in which we could do some dp or similar

        the first question got me to observe that the solution consists of the
        K smallest choices
        the second question got me to think whether we could somehow generate
        first K choices

        so, as the first one is the smallest, it is definately the one which
        takes the minimum from each

        then, we can see that the next one will substitute one of those for the second smallest etc.

        actually, every next choice will be some subset of microcontrollers which subtitutes
        their corresponding microcontrollers from the smallest choice

        we can see that we need to generate smallest K subsets of the microcontrollers
        (of course watch out not to take 2 on the same position)

        so can we do it fast enough?
        we can use the usual dp[i] which denotes number of subsets with sum i to calculate it
        but that would take too long, but we can somehow optimize it not to do unnecesarry work

        lets try to generate those k subsets from smallest to largest
        we can first sort all our options to insert and proces each of them one after another
        lets say that relaxing our solution means updating our dp upto the next element which has to be processed
        because when that element gets processed, the smallest subset it can produce is itself, so any subset
        smaller that him has to be processed first bcs we are processing from smallest to biggest
        then, we maintain a set to know which is the next smallest update we have to do
        and in order to not get TLE u must terminate the first second u have more than K subsets

        update: we keep for every dp[i] a implicit segtree which on i-th position tells us
        how much the i-th element contributed, and when pushing from dp[i] to dp[i]+x
        we must subtract those indices from dp[i] which correspond to the same group(bcs we cant take 2 on the same position)
        and we must add all the indices from 0 to (index of the elemnt we are adding)(by index, we mean the index in the sorted array
        as we process it), because in the regular dp for number of subsets, we must update in some order not to generate same subsets multiple times
*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,int> pii;
const int maxn=1e5+10;
int cnt,n,k,m[maxn];
ll inf=1e18;
struct tr{
    int l,r,val;
}tree[maxn*100];
map<ll,int>mapa,mapa_single[maxn];
vector<int>position[maxn];
vector<ll>vect[maxn];
vector<pii>niz;
void update(int &x,int l,int r,int id,int val){
    if(l>id || r<id)return;
    if(x==0)x=++cnt;

    if(l==r){
        tree[x].val+=val;
        return;
    }

    int mid=(l+r)/2;

    update(tree[x].l,l,mid,id,val);
    update(tree[x].r,mid+1,r,id,val);

    tree[x].val=tree[tree[x].l].val+tree[tree[x].r].val;
}
int query(int x,int l,int r,int lp,int rp){

    if(x==0)return 0;
    if(l>rp || r<lp)return 0;
    if(l>=lp && r<=rp)return tree[x].val;

    int mid=(l+r)/2;

    return query(tree[x].l,l,mid,lp,rp)+query(tree[x].r,mid+1,r,lp,rp);
}
int main(){

    freopen("roboherd.in","r",stdin);
    freopen("roboherd.out","w",stdout);


    scanf("%d %d",&n,&k);
    ll sum=0;
    for(int i=1;i<=n;i++){

        scanf("%d",&m[i]);
        for(int j=1;j<=m[i];j++){
            int a;
            scanf("%d",&a);
            vect[i].pb(a);
        }
        sort(vect[i].begin(),vect[i].end());
        sum+=vect[i][0];

        for(int j=1;j<m[i];j++){

            niz.pb({vect[i][j]-vect[i][0],i});

        }
    }

    sort(niz.begin(),niz.end());

    update(mapa[0],0,niz.size(),0,1);
    int cmade=1;

    set<pair<pii,pii> >st;
    for(int i=0;i<niz.size();i++){

        st.insert({{niz[i].ff,i+1},niz[i]});

        ll next;
        if(i==niz.size()-1)next=inf;
        else next=niz[i+1].ff;

        while(st.size() && (*st.begin()).ff.ff<=next){

            pair<pii,pii> pom=(*st.begin());

            int px=mapa[pom.ff.ff-pom.ss.ff];
            ll toadd=0;

            for(int j=0;j<position[pom.ss.ss].size();j++){
                if(position[pom.ss.ss][j]>=pom.ff.ss)continue;
                toadd-=query(px,0,niz.size(),position[pom.ss.ss][j],position[pom.ss.ss][j]);
            }

            toadd+=query(px,0,niz.size(),0,pom.ff.ss-1);


            if(toadd>0){
                update(mapa[pom.ff.ff],0,niz.size(),pom.ff.ss,toadd);
                mapa_single[pom.ss.ss][pom.ff.ff]+=toadd;
                cmade+=toadd;
            }

            st.erase(st.begin());

            map<ll,int>::iterator it=mapa.find(pom.ff.ff-pom.ss.ff);
            it++;
            if(it!=mapa.end()){
                pom.ff.ff=it->ff+pom.ss.ff;
                st.insert(pom);
            }

            if(cmade>=k)break;
        }

        if(cmade>=k)break;

        position[niz[i].ss].pb(i+1);
    }

    ll rez=k*sum;

    for(map<ll,int>::iterator it=mapa.begin();it!=mapa.end();it++){

        ll decr=min(k,query(it->ss,0,niz.size(),0,niz.size()));

        k-=decr;
        rez+=decr*it->ff;

        if(k==0)break;
    }

    printf("%lld\n",rez);


	return 0;
}
