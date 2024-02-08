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
int a[maxn],niz[maxn];
ll tree[maxn*4],mxt[maxn*4][2],cnt[maxn*4][2];
int inf=1e9;
int n;

void mrg(int x,int y,int z){

    map<int,int>mapa;
    mapa[mxt[y][0]]+=cnt[y][0];
    if(cnt[y][1]>0)mapa[mxt[y][1]]+=cnt[y][1];
    mapa[mxt[z][0]]+=cnt[z][0];
    if(cnt[z][1]>0)mapa[mxt[z][1]]+=cnt[z][1];

    mxt[x][0]=-1;
    mxt[x][1]=-1;
    cnt[x][0]=0;
    cnt[x][1]=0;
    int curr=0;
    for(auto it=mapa.rbegin();it!=mapa.rend();it++){
        if(curr>1)break;
        mxt[x][curr]=it->ff;
        cnt[x][curr]=it->ss;
        curr++;
    }
    tree[x]=tree[y]+tree[z];
}
void build(int x,int l,int r){

    if(l==r){
        tree[x]=inf;
        mxt[x][0]=inf;
        cnt[x][0]=1;
        mxt[x][1]=-1;
        cnt[x][1]=0;
        return;
    }
    int mid=(l+r)/2;
    build(x*2,l,mid);
    build(x*2+1,mid+1,r);
    mrg(x,x*2,x*2+1);

}
void push(int x){

    ll d=mxt[x*2][0]-mxt[x][0];
    if(d>0){
        tree[x*2]-=d*cnt[x*2][0];
        mxt[x*2][0]=mxt[x][0];
    }
    d=mxt[x*2+1][0]-mxt[x][0];
    if(d>0){
        tree[x*2+1]-=d*cnt[x*2+1][0];
        mxt[x*2+1][0]=mxt[x][0];
    }

}
void update(int x,int l,int r,int lp,int rp,int val){

    if(l>rp || r<lp || mxt[x][0]<=val)return;
    if(l>=lp && r<=rp && mxt[x][1]<val){
        ll d=mxt[x][0]-val;
        tree[x]-=d*cnt[x][0];
        mxt[x][0]=val;
        ///printf("%d %d | %d | %d  AA\n",l,r,val,tree[x]);
        return;
    }
    int mid=(l+r)/2;
    push(x);
    update(x*2,l,mid,lp,rp,val);
    update(x*2+1,mid+1,r,lp,rp,val);
    mrg(x,x*2,x*2+1);
}
ll qry(int x,int l,int r,int lp,int rp){
    if(l>rp || r<lp)return 0;
    if(l>=lp && r<=rp)return tree[x];
    int mid=(l+r)/2;
    push(x);
    return qry(x*2,l,mid,lp,rp)+qry(x*2+1,mid+1,r,lp,rp);
}
int main(){

    ///freopen("test.txt","r",stdin);

   /* mt19937 gen(10);

    int n=3e5;
    for(int i=1;i<=n;i++){
        a[i]=gen()%n+1;
        //printf("%d ",a[i]);
    }
   // printf(" AA\n,");

   int maxc=0;
   int sum=0;
   int suml=0;
    for(int i=1;i<=n;i++){
        int curr=1e9;
        int c=0;
        int lst=i;
        for(int j=i+1;j<=n;j++){
            int prv=curr;
            curr=min(curr, max(i+a[j],j+a[i]));
            if(prv!=curr){
                c++;
                lst=j;
            }
            if(j+a[i]>=i+a[j])break;
            ///printf("%d %d | %d %d | %d %d \n",i,j,curr,prv,i+a[j],j+a[i]);
        }
        sum+=c;
        maxc=max(maxc,c);
        suml+=lst-i;
        if(i%1000==0)
            printf("%d | %d %d %d %d CHANGE\n",i,c,maxc,sum,suml);
        //break;
    }*/

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            niz[i]=inf;
        }
        build(1,1,n);

        ll rez=0;
        for(int i=n-1;i>=1;i--){

            vector<pair<int,pii>>cand;
            int lst=i+1;
            int prv=1e9;
            int curr=max(a[i]+i+1,a[i+1]+i);
            for(int j=i+1;j<=n;j++){
                prv=curr;
                curr=min(curr,max(a[i]+j,a[j]+i));
                ///printf("%d %d -> %d CURR\n",i,j,curr);
                if(curr!=prv){
                    cand.pb({ prv,{lst,j-1} });
                    lst=j;
                }
                if(a[i]+j>=a[j]+i)break;
            }
            cand.pb({curr,{lst,n}});

            for(int j=0;j<cand.size();j++){
                ///printf("%d | %d %d %d upd\n",i,cand[j].ff,cand[j].ss.ff,cand[j].ss.ss);
                update(1,1,n,cand[j].ss.ff,cand[j].ss.ss,cand[j].ff);

                int l=cand[j].ss.ff;
                int r=cand[j].ss.ss;
                int val=cand[j].ff;
                //for(int k=l;k<=r;k++){
                    //niz[k]=min(niz[k],val);
                //}

            }

            ///for(int j=i+1;j<=n;j++)rez+=niz[j];

            rez+=qry(1,1,n,i+1,n);

        }

        printf("%lld\n",rez);

    }



    return 0;
}
