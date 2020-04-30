/*

    idea: look at it as a graph
    it is a tree
    so
    we need to check somehow for every node what is the sum of distances
    from every tourist to that node and take the minimum from all the nodes

    an observation that helps is that the upperleft, upperright and lowerleft
    square of size 2^k will be the same, and the remaining square will be
    blocked

    so we can recursively solve the problem

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<ll,ll> pii;
typedef pair<pii,pii> ppp;
const int maxn=1e9-1;
ppp nula_ppp={{0,0},{0,0}};
ll rez;
ppp dp[32*100000];
struct ss{
    int b1,b2,b3;
}child[32*100000];
typedef map<ppp,ppp>::iterator mitp;
int maxr,n,cnt=1;
int get_tip(ppp b,int x,int y){

    int up=b.ff.ff;
    int down=b.ff.ss;
    int left=b.ss.ff;
    int right=b.ss.ss;

    if(x<=(up+down)/2){
        if(y<=(left+right)/2)return 1;
        else return 2;
    }
    else{
        if(y<=(left+right)/2)return 3;
        else return 4;
    }
}
ppp new_bounds(ppp b,int x,int y){

    int up=b.ff.ff;
    int down=b.ff.ss;
    int left=b.ss.ff;
    int right=b.ss.ss;

    if(x<=(up+down)/2)b.ff.ss=(up+down)/2;
    else b.ff.ff=(up+down)/2+1;

    if(y<=(left+right)/2)b.ss.ss=(left+right)/2;
    else b.ss.ff=(left+right)/2+1;

    return b;
}
ppp add(ppp a,ppp b){
    a.ff.ff+=b.ff.ff;
    a.ff.ss+=b.ff.ss;
    a.ss.ff+=b.ss.ff;
    a.ss.ss+=b.ss.ss;
    return a;
}
ppp update(int &id,ppp b,int x,int y){

    if(id==0)id=++cnt;

    int up=b.ff.ff;
    int down=b.ff.ss;
    int left=b.ss.ff;
    int right=b.ss.ss;

    int tip=get_tip(b,x,y);

    ppp ret=nula_ppp;
    ret.ss.ss=1;
    int len=(right-left+1)/2;
    if(len*2<=2){

        if(tip==1){
            ret.ff.ff=0;
            ret.ff.ss=1;
            ret.ss.ff=1;
        }
        else if(tip==2){
            ret.ff.ff=1;
            ret.ff.ss=0;
            ret.ss.ff=2;
        }
        else if(tip==3){
            ret.ff.ff=1;
            ret.ff.ss=2;
            ret.ss.ff=0;
        }

        dp[id]=add(dp[id],ret);

        return ret;
    }


    ppp b2=new_bounds(b,x,y);

    ppp pom;

    if(tip==1)pom=update(child[id].b1,b2,x,y);
    else if(tip==2)pom=update(child[id].b2,b2,x,y);
    else pom=update(child[id].b3,b2,x,y);


    if(tip==1){
        ret.ff.ff=pom.ff.ff;
        ret.ff.ss=pom.ff.ss+len;
        ret.ss.ff=pom.ss.ff+len;
    }
    else if(tip==2){
        ret.ff.ff=pom.ff.ff+len;
        ret.ff.ss=pom.ff.ss;
        ret.ss.ff=pom.ff.ff+3*len-1;
    }
    else if(tip==3){
        ret.ff.ff=pom.ff.ff+len;
        ret.ff.ss=pom.ff.ff+3*len-1;
        ret.ss.ff=pom.ss.ff;
    }

    dp[id]=add(dp[id],ret);

    return ret;
}
ppp get_block(int b){
    return dp[b];
}
void go(int id,ppp b,ll unode,ll dnode,ll lnode,ll rnode,ll sum){

    int up=b.ff.ff;
    int down=b.ff.ss;
    int left=b.ss.ff;
    int right=b.ss.ss;
    ll len=(down-up+1);

    if(id==0)return;

    rez=min(rez,sum+unode+lnode+rnode*len+dnode*len+dp[id].ff.ff);
    rez=min(rez,sum+unode*len+lnode*len+rnode+dnode*(len*2-1)+dp[id].ff.ss);
    rez=min(rez,sum+unode*len+lnode*len+rnode*(len*2-1)+dnode+dp[id].ss.ff);


    if(len<=2)return;

    ppp b1=get_block(child[id].b1);
    ppp b2=get_block(child[id].b2);
    ppp b3=get_block(child[id].b3);

    ll len2=len/2;
    go(child[id].b1,new_bounds(b,up,left),unode,dnode+b3.ss.ss,lnode,rnode+b2.ss.ss,sum+dnode*len2+rnode*len2+b2.ff.ff+b3.ff.ff);
    go(child[id].b2,new_bounds(b,up,right),0,0,lnode+unode+dnode+b1.ss.ss+b3.ss.ss,rnode,sum+dnode*(len2*3-1)+unode*len2+lnode*len2+b1.ff.ss+b3.ff.ff+b3.ss.ss*(2*len2-1));
    go(child[id].b3,new_bounds(b,down,left),unode+b1.ss.ss+b2.ss.ss+lnode+rnode,dnode,0,0,sum+lnode*len2+unode*len2+rnode*(3*len2-1)+b1.ss.ff+b2.ff.ff+b2.ss.ss*(len2*2-1));

}
int main(){

    ///freopen("test.txt","r",stdin);

    maxr=1;
    while(maxr<maxn)maxr*=2;
    maxr--;

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        int pom=1;
        update(pom,(ppp){{0,maxr},{0,maxr}},x,y);
    }


    rez=1e18;
    go(1,(ppp){{0,maxr},{0,maxr}},0,0,0,0,0);

    cout<<rez<<endl;

	return 0;
}
