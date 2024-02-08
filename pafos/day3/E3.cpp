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

/*int delta=13;
const int mxy=27;*/
int delta=5;
const int mxy=18;
const int mxx=19;
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
int mxyc=0;
struct state{
    ll a[2][mxy];

    state(){memset(a,0,sizeof(a));}

    state mul_and_section(trans t,int k){

        state ret;

        int curr=1;
        for(int i=k;i<20;i+=10){
            curr^=1;

            int cx=i;
            ll ym1=t.a[cx][0];
            ll y0=t.a[cx][1];
            ll y1=t.a[cx][2];
            for(int j=0;j<mxyc;j++){
                ret.a[curr][j]=a[0][j]*y0;
                if(j>=1)ret.a[curr][j]+=a[0][j-1]*y1;
                if(j+1<mxyc)ret.a[curr][j]+=a[0][j+1]*ym1;
            }

            cx--;
            ym1=t.a[cx][0];
            y0=t.a[cx][1];
            y1=t.a[cx][2];
            if(cx<0)continue;
            for(int j=0;j<mxyc;j++){
                ret.a[curr][j]+=a[1][j]*y0;
                if(j>=1)ret.a[curr][j]+=a[1][j-1]*y1;
                if(j+1<mxyc)ret.a[curr][j]+=a[1][j+1]*ym1;
            }

        }

        return ret;
    }

    state operator +(state b)const {
        state ret;
        for(int i=0;i<2;i++)
            for(int j=0;j<mxy;j++)
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
vector<ll>operator -(vector<ll>a,vector<ll>b){
    a.resize(max(a.size(),b.size()));
    for(int i=0;i<b.size();i++)a[i]-=b[i];
    return a;
}

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
   // q0.ispis();
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
    int kc=0;
    while(n){
        int k=n%10;
        kc++;
        mxyc=mxy;
        //s=s.mul_and_section(xsum,k);
        //state pom=p.mul_and_section(q1,k);
        //s=s+pom;
        p=p.mul_and_section(q0,k);
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
vector<interval>cand;
vector<ll>pref;
void prek(){
    ll mxa=1e12;
    for(ll i=1;i*i<=mxa;i++){
        ll lp=i*i;
        ll rp=(i+1)*(i+1)-1;
        cand.pb({lp,rp,i,nth_digital(rp)});
        if(i%10000==0)printf("%lld\n",i);
    }

    for(int i=0;i<cand.size();i++){

    }

}

int main(){

    /*vector<ll>pom=nth_digital(10);
    for(int i=0;i<pom.size();i++){
        if(pom[i]==0)continue;
        printf("%d %lld\n",i-delta,pom[i]);
    }*/

    prek();




    return 0;
}
