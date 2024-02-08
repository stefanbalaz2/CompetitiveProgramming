#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

int n,limit;
const int maxn=1e5+10;
int cnt=0;
struct node{
    vector<pii>intervals;
    vector<int>mids;
    int lp,rp;
    vector<int>nbhr;

    int get_id(int x){
        for(int i=0;i<intervals.size();i++)
            if(intervals[i].ff<=x && intervals[i].ss>=x)return i;
        return -1;
    }
    int get_left(int x){
        for(int i=mids.size()-1;i>=0;i--)if(mids[i]<=x)return mids[i];
    }
    int get_right(int x){
        for(int i=0;i<mids.size();i++)if(mids[i]>=x)return mids[i];
    }

}tree[maxn*4];
vector<pair<int,pii>>edges;
const int maxk=150;
pii dp[maxn];
pii go_cnt(int d){


    if(d<=4)return {-1,0};
    pii &a=dp[d];
    if(a.ff!=-1)return a;


    int l=1;
    int r=d;
    a={-1,1e9};
    for(int k=2;k<min(d+1,maxk);k++){

        int d=(r-l+1)/k;

        int curr=l-1;
        vector<pii>cand;
        while(curr+1<=r){
            if(curr+d==r){
                cand.pb({curr+1,r});
                break;
            }
            cand.pb({curr+1,min(curr+d-1,r) });
            curr+=d;
        }

        vector<int>mids;
        int ret=0;
        for(int i=0;i<cand.size();i++){
            int lp=cand[i].ff;
            int rp=cand[i].ss;
            if(i<cand.size()-1)mids.pb(rp+1);
            ret+=go_cnt(rp-lp+1).ss;
        }

        vector<int>&pts=mids;
        for(int i=0;i<pts.size();i++){

            int x=pts[i];

            int lp=cand[i].ff;
            int rp=cand[i].ss;
            ret+=rp-lp-1;

            lp=cand[i+1].ff;
            rp=cand[i+1].ss;
            ret+=rp-lp-1;

        }

        for(int j=0;j+1<pts.size();j++){
            int xx=pts[j];
            int yy=pts[j+1];
            if(xx+1==yy)continue;
            ret++;
        }
        for(int i=2;i<=pts.size()-1;i++){
            for(int j=0;j+i<pts.size();j++){
                ret++;
            }
        }

        if(ret<a.ss)a={k,ret};

    }
    return a;
}
int switch_k(int d){
    return go_cnt(d).ff;
}
void go(int &x,int l,int r){

    x=++cnt;
    tree[x].intervals.clear();
    tree[x].mids.clear();
    tree[x].lp=l;
    tree[x].rp=r;

    if(r-l+1<=4)return;

    int k=switch_k(r-l+1);

    int d=(r-l+1)/k;

    int curr=l-1;
    vector<pii>cand;
    while(curr+1<=r){
        if(curr+d==r){
            cand.pb({curr+1,r});
            break;
        }
        cand.pb({curr+1,min(curr+d-1,r) });
        curr+=d;
    }

    tree[x].nbhr.resize(cand.size());
    for(int i=0;i<cand.size();i++){
        int lp=cand[i].ff;
        int rp=cand[i].ss;
        tree[x].intervals.pb(cand[i]);
        if(i<cand.size()-1)tree[x].mids.pb(rp+1);
        go(tree[x].nbhr[i],lp,rp);
    }

    vector<int>&pts=tree[x].mids;
    for(int i=0;i<pts.size();i++){

        int x=pts[i];

        int lp=cand[i].ff;
        int rp=cand[i].ss;
        for(int j=rp-1;j>=lp;j--)edges.pb({j,{j+1,x}});

        lp=cand[i+1].ff;
        rp=cand[i+1].ss;
        for(int j=lp+1;j<=rp;j++)edges.pb({x,{j-1,j}});

    }

    for(int j=0;j+1<pts.size();j++){
        int xx=pts[j];
        int yy=pts[j+1];
        if(xx+1==yy)continue;
        edges.pb({xx,{yy-1,yy} });
    }
    for(int i=2;i<=pts.size()-1;i++){
        for(int j=0;j+i<pts.size();j++){
            edges.pb({ pts[j] ,{pts[j+i-1],pts[j+i]} });
        }
    }

}

void solve(){

    edges.clear();

    int root=0;
    cnt=0;
    go(root,0,n);
}

void ans_low(){

    printf("0\n");
    fflush(stdout);

    int q;
    scanf("%d",&q);

    while(q--){
        int l,r;
        scanf("%d %d",&l,&r);
        for(int i=l;i<=r;i++)printf("%d ",i);
        printf("\n");
        fflush(stdout);
    }

}
vector<int>qq(int x,int l,int r){

    int lid=tree[x].get_id(l);
    int rid=tree[x].get_id(r);

    if(lid!=-1 && lid==rid)return qq(tree[x].nbhr[lid],l,r);

    lid=tree[x].get_right(l);
    rid=tree[x].get_left(r);

    vector<int>ret;
    ret.pb(l);
    ret.pb(lid);
    ret.pb(rid);
    ret.pb(r);
    ret.resize(unique(ret.begin(),ret.end())-ret.begin());
    return ret;
}
void go_big(){

    solve();

    printf("%d\n",edges.size());
    for(int i=0;i<edges.size();i++)
        printf("%d %d %d\n",edges[i].ff,edges[i].ss.ff,edges[i].ss.ss);
    fflush(stdout);

    int q;
    scanf("%d",&q);

    while(q--){
        int l,r;
        scanf("%d %d",&l,&r);
        if(r-l+1<=4){
            for(int i=l;i<=r;i++)printf("%d ",i);
            printf("\n");
            fflush(stdout);
            continue;
        }

        vector<int>rez=qq(1,l,r);
        for(int i=0;i<rez.size();i++){
            printf("%d ",rez[i]);
        }
        printf("\n");
        fflush(stdout);

    }

}

int main(){

    memset(dp,-1,sizeof(dp));

    scanf("%d",&n);
    limit=6*n;

    /// posebno radi, ako su 2 cvora na regularnoj distanci <=3 onda samo ispisi redom cvorove
    /// inace ih pretrazi
    if(n<=3){
        ans_low();
    }
    else{
        go_big();
    }

    return 0;
}
