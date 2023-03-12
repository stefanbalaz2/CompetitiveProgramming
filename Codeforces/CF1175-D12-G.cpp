/*

    idea: https://codeforces.com/blog/entry/67484

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,ll> pii;
const int maxn=2e4;
int n;
int k,a[maxn+10],dp[maxn+10],dp2[maxn+10],inf=1e9,br,niz[maxn+10],brh,hull[maxn+10],cnt;
struct line{
    int l,r,pt,val,root;
    int size(){
        return r-l+1;
    }
}stek[maxn+10];
struct ln{
    double k,n;
    int id,val;
};
struct ss{
    int l,r;
    ln val;
    void ispis(){
        cout<<val.k<<" "<<val.n<<" "<<val.id<<" "<<val.val<<" ISPIS"<<endl;
    }
}tree[15*4*maxn+10];
int eval(int x,int y,int val){
    if(x==0)return inf;
    return dp[x-1]+(y-x+1)*val;
}
double eval(ln l,double x){
    return l.k*x+l.n;
}
double intersection(int x,int y){

    x--;
    y--;
    double n1=dp[x];
    double n2=dp[y];
    double k1=-x;
    double k2=-y;

    return (n2-n1)/(k1-k2);
}
double intersection(ln x,ln y){
    return (y.n-x.n)/(x.k-y.k);
}
void add_end(line &x,int id){

    if(x.size()<=1){
        niz[++x.r]=id;
        return;
    }

    while(x.size()>1 && intersection(niz[x.r],niz[x.r-1])>intersection(id,niz[x.r-1]))x.r--;

    niz[++x.r]=id;
}
void add_begin(line &x,int id){

    if(x.size()<=1){
        niz[--x.l]=id;
        return;
    }

    while(x.size()>1 && intersection(niz[x.l],niz[x.l+1])<intersection(id,niz[x.l+1]))x.l++;

    niz[--x.l]=id;

}
line mrg(line x,line y){

    int tip=0;
    if(x.r-x.l<y.r-y.l)tip=1;

    if(tip==0){/// ubacujem u levi
        for(int j=y.l;j<=y.r;j++)
            add_end(x,niz[j]);

        return x;
    }
    else{/// ubacujem u desni
        for(int j=x.r;j>=x.l;j--)
            add_begin(y,niz[j]);

        return y;
    }

}
void update(int &x,int l,int r,ln val){

    tree[++cnt]=tree[x];
    x=cnt;

    int mid=(l+r)/2;
    int midv=(eval(tree[x].val,mid)>eval(val,mid));
    int lv=(eval(tree[x].val,l)>eval(val,l));

    if(midv)swap(tree[x].val,val);

    if(r==l)return;

    if(lv!=midv){/// go left
        update(tree[x].l,l,mid,val);
    }
    else{/// go right
        update(tree[x].r,mid+1,r,val);
    }
}
int query(int x,int l,int r,int id){

    if(l==r)return eval(tree[x].val.id,id,tree[x].val.val);

    int mid=(l+r)/2;

    if(id<=mid)return min(eval(tree[x].val.id,id,tree[x].val.val),query(tree[x].l,l,mid,id));
    else return min(eval(tree[x].val.id,id,tree[x].val.val),query(tree[x].r,mid+1,r,id));
}
ln make_ln(int id,int val){
    ln ret;
    ret.id=id;
    ret.val=val;

    id--;
    ret.k=val;
    ret.n=dp[id]-val*id;

    return ret;
}
void go(){

    int start;
    for(int i=0;i<=n;i++)
    if(dp[i]!=inf){
        start=i;
        break;
    }

    br=0;
    int pt=1;
    stek[++br]={start+1,start+1,start+1,a[start+1]};
    niz[start+1]=start+1;
    update(stek[1].root,1,n,make_ln(stek[1].pt,stek[1].val));


    dp2[start+1]=eval(stek[pt].pt,start+1,stek[pt].val);
    for(int i=start+2;i<=n;i++){

        line pom;
        pom.r=i;
        pom.l=i;
        pom.val=a[i];
        pom.pt=-1;
        niz[i]=i;

        stek[++br]=pom;
        int br2=br;
        while(stek[br].val<=a[i] && br){
            br--;
        }

        pom=stek[br+1];
        for(int j=br+2;j<=br2;j++)
            pom=mrg(pom,stek[j]);

        pom.val=a[i];

        int l=pom.l;
        int r=pom.r-1;
        int ret=r+1,sr;
        while(l<=r){
            sr=(l+r)/2;
            if(eval(niz[sr],i,a[i])<=eval(niz[sr+1],i,a[i]) || eval(niz[sr+1],i,a[i])>=inf){
                ret=sr;
                r=sr-1;
            }
            else l=sr+1;
        }
        pom.pt=niz[ret];

        stek[++br]=pom;


        ///HULL
        stek[br].root=stek[br-1].root;
        update(stek[br].root,1,n,make_ln(stek[br].pt,stek[br].val));

        dp2[i]=query(stek[br].root,1,n,i);
    }

}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);

    for(int j=1;j<=n;j++)dp[j]=inf;
    for(int j=0;j<=n;j++)dp2[j]=inf;

    for(int i=1;i<=k;i++){

        cnt=0;
        for(int j=0;j<=15*4*maxn;j++)tree[j]={0,0,{0,inf,0,0}};

        go();
        for(int j=0;j<=n;j++)dp[j]=dp2[j];
        for(int j=0;j<=n;j++)dp2[j]=inf;
    }

    printf("%d\n",dp[n]);

	return 0;
}
