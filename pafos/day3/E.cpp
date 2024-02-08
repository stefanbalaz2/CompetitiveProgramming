#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

int delta=12;
const int mxy=25;
const int mxx=20;
struct trans{
    ll a[mxx][3];

    trans(){memset(a,0,sizeof(a));}

    void ispis(){
        for(int i=0;i<mxx;i++){
            for(int j=0;j<3;j++)printf("%lld ",a[i][j]);
            printf("\n");
        }
        printf(" ISPIS\n");
    }
};
int mxyc,mnyc;
int ops;
struct state{
    ll a[2][mxy];

    state(){memset(a,0,sizeof(a));}

    state mul_and_section(trans &t,int k,int flag){

        state ret;

        if(flag==0){
            int curr=1;
            for(int i=k;i<20;i+=10){
                curr^=1;

                int cx=i;
                ll y0=t.a[cx][1];
                for(int j=mnyc;j<mxyc;++j)
                    ret.a[curr][j]=a[0][j]*y0;


                cx--;
                y0=t.a[cx][1];
                if(cx<0 || y0==0)continue;
                for(int j=mnyc;j<mxyc;++j)
                    ret.a[curr][j]+=a[1][j]*y0;


            }
        }
        else if(flag==1){
            int curr=1;
            for(int i=k;i<20;i+=10){
                curr^=1;

                int cx=i;
                ll ym1=t.a[cx][0];
                ll y1=t.a[cx][2];

                ret.a[curr][mnyc]+=a[0][mnyc+1]*ym1;
                ret.a[curr][mxyc-1]+=a[0][mxyc-2]*y1;
                for(int j=mnyc+1;j<mxyc-1;++j){
                    ret.a[curr][j]+=a[0][j-1]*y1;
                    ret.a[curr][j]+=a[0][j+1]*ym1;
                }

                cx--;
                ym1=t.a[cx][0];
                y1=t.a[cx][2];
                if(cx<0)continue;

                ret.a[curr][mnyc]+=a[1][mnyc+1]*ym1;
                ret.a[curr][mxyc-1]+=a[1][mxyc-2]*y1;
                for(int j=mnyc+1;j<mxyc-1;++j){
                    ret.a[curr][j]+=a[1][j-1]*y1;
                    ret.a[curr][j]+=a[1][j+1]*ym1;
                }

            }
        }



        return ret;
    }

    void oth(int k,state &ret){

        int curr=1;
        for(int i=k;i<20;i+=10){
            curr^=1;

            int cx=i;
            ll y0=(cx<=9);
            if(y0!=0){
            for(int j=mnyc+1;j<mxyc;++j)
                ret.a[curr][j]+=a[0][j-1]*y0;
            }


            cx--;
            y0=(cx<=9);
            if(cx<0 || y0==0)continue;
            for(int j=mnyc+1;j<mxyc;++j)
                ret.a[curr][j]+=a[1][j-1]*y0;


        }

    }


    state operator +(state b) {
        state ret;
        for(int i=0;i<2;i++)
            for(int j=mnyc;j<mxyc;j++)
                ret.a[i][j]=a[i][j]+b.a[i][j];
        return ret;
    }

    void ispis(){

        for(int i=0;i<2;i++){
            for(int j=0;j<mxy;j++)printf("%lld ",a[i][j]);
            printf("\n");
        }
        printf(" ISPIS\n");

    }

};

vector<ll>nth_digital(ll n){

    trans xsum,q0,q1;
    for(int i=0;i<=9;i++)xsum.a[i][1]=1;
    for(int i=0;i<=9;i++){
        if(i%2==0)q0.a[i][2]=1;
        else q0.a[i][0]=1;
    }
    for(int i=mxx-1;i>=0;i--){
        for(int j=1;j<=9;j++){
            if(i-j<0)break;
            q0.a[i][0]+=q0.a[i-j][0];
            q0.a[i][1]+=q0.a[i-j][1];
            q0.a[i][2]+=q0.a[i-j][2];
        }
    }
    for(int i=1;i<=9;i++){
        if(i%2==0)q1.a[i][2]=1;
        else q1.a[i][0]=1;
    }
    for(int i=mxx-1;i>=0;i--){
        for(int j=1;j<=9;j++){
            if(i-j<0)break;
            q1.a[i][0]+=q1.a[i-j][0];
            q1.a[i][1]+=q1.a[i-j][1];
            q1.a[i][2]+=q1.a[i-j][2];
        }
    }


    state s,p;
    p.a[0][delta]=1;
    int ck=0;

    while(n){
        int k=n%10;
        ck++;
        mxyc=min(delta+ck+1,25);
        mnyc=max(0,delta-ck);
        s=s.mul_and_section(xsum,k,0);
        state pom=p.mul_and_section(q1,k,1);
        for(int i=0;i<2;i++)
            for(int j=mnyc;j<mxyc;j++)
                s.a[i][j]+=pom.a[i][j];

        p.oth(k,pom);
        p=pom;

        n/=10;
    }


    vector<ll>ret;
    for(int i=0;i<mxy;i++)ret.pb(s.a[0][i]);
    return ret;
}

struct interval{

    ll l,r,x;
    vector<ll>y;

};

int gdd(ll x){
    int ret=0;
    while(x){
        int d=x%10;
        x/=10;
        if(d%2==1)ret--;
        else ret++;
    }
    return ret;
}

vector<interval>cand;
const int maxa=1e6+10;
ll pref[maxa];

ll get_inter(vector<ll>a,vector<ll>b,ll x){
    ll ret=0;
    int ds=-gdd(x)+1+delta;
    for(int j=ds;j<mxy;j++)
        ret+=b[j]-a[j];
    return ret;
}
void prek(){
    ll mxa=1e12;
    vector<ll>ppp(mxy);
    cand.pb({0,0,0,ppp});
    for(ll i=1;i*i<=mxa;i++){
        ll lp=i*i;
        ll rp=(i+1)*(i+1)-1;
        rp=min(rp,1000000000000ll);
        cand.pb({lp,rp,i,nth_digital(rp)});
    }

    for(int i=1;i<cand.size();i++){
        ll pom=get_inter(cand[i-1].y,cand[i].y,cand[i].x);
        pref[i]=pref[i-1]+pom;
    }

}
int get_block(ll x){

    int l=0;
    int r=cand.size()-1;
    int sr,ret=-1;
    while(l<=r){
        sr=(l+r)/2;
        if(cand[sr].l<=x && cand[sr].r>=x)return sr;
        if(cand[sr].l>x){
            r=sr-1;
        }
        else l=sr+1;
    }

}
ll qry(ll l,ll r){

    int lb=get_block(l);
    int rb=get_block(r);

    if(lb==rb)return get_inter(nth_digital(l-1),nth_digital(r),cand[lb].x);

    ll pom=get_inter(nth_digital(l-1),cand[lb].y,cand[lb].x);
    pom+=get_inter(cand[rb-1].y,nth_digital(r),cand[rb].x);

    pom+=pref[rb-1]-pref[lb];
    return pom;

}

int main(){


    prek();

    int t;
    scanf("%d",&t);
    while(t--){
        ll l,r;
        scanf("%lld %lld",&l,&r);
        printf("%lld\n",qry(l,r));
        fflush(stdout);
    }


    return 0;
}
