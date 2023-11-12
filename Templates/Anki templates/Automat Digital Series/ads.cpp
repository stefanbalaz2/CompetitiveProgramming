/**

    https://atcoder.jp/contests/joi2012yo/tasks/joi2012yo_f

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int mod=10000;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=3e5+10;

const int mxs=32;
using trans=int;
struct state{

    int a[mxs];

    state(){memset(a,0,sizeof(a));}

    state operator *(trans t){

        if(t==10){
            state ret;
            memcpy(ret.a,a,sizeof(a));
            return ret;
        }

        state ret;

        ret.a[t]=add(ret.a[t],a[30]);

        for(int i=0;i<10;i++){
            if(i==t)continue;
            if(i>t)ret.a[t+10]=add(ret.a[t+10],a[i]);
            else ret.a[t+20]=add(ret.a[t+20],a[i]);
        }
        for(int i=0;i<10;i++){
            if(i>=t)continue;
            ret.a[t+20]=add(ret.a[t+20],a[i+10]);
        }
        for(int i=0;i<10;i++){
            if(i<=t)continue;
            ret.a[t+10]=add(ret.a[t+10],a[i+20]);
        }

        if(t==0){
            for(int i=0;i<30;i++)ret.a[31]=add(ret.a[31],a[i]);
            ret.a[31]=sub(ret.a[31],a[0]);
            ret.a[31]=sub(ret.a[31],a[10]);
            ret.a[31]=sub(ret.a[31],a[20]);
            ret.a[31]=add(ret.a[31],a[31]);
            ret.a[31]=add(ret.a[31],a[30]);
        }

        return ret;
    }

    state operator +(state b){
        state ret;
        for(int i=0;i<mxs;i++)ret.a[i]=add(a[i],b.a[i]);
        return ret;
    }

};
using poly_state=vector<state>;
using poly_trans=vector<trans>;
poly_state operator *(poly_state a,poly_trans b){
    poly_state ret;
    ret.resize(a.size()+b.size()-1);
    for(int i=0;i<a.size();i++)
        for(int j=0;j<b.size();j++){
            if(b[j]==-1)continue;
            ret[i+j]=ret[i+j]+a[i]*b[j];
        }
    return ret;
}
poly_state section(poly_state a,int i,int j){
    poly_state ret;
    for(int k=i;k<a.size();k+=j)
        ret.pb(a[k]);
    return ret;
}
int n_th_digital(string n,int d){

    int nmd=0;
    for(int i=0;i<n.size();i++)nmd=(nmd*10+n[i]-'0')%d;

    poly_trans q0(d*9+1,-1),q1(10);
    for(int i=0;i<=9;i++)q0[i*d]=10;
    for(int i=0;i<=9;i++)q1[i]=i;

    poly_state p(nmd);
    state pom;
    pom.a[30]=1;
    p.pb(pom);


    while(n.size()){
        int k=(n.back()-'0');
        p=section(((p*q1)*q0),k,10);
        n.pop_back();
    }
    p=section(((p*q1)*q0),0,10);


    int ret=p[0].a[31];
    return ret;
}

int main(){


    ///freopen("test.txt","r",stdin);

    string a,b;
    int m;
    cin>>a>>b>>m;

    int carry=1;
    for(int i=a.size()-1;i>=0;i--){
        if(a[i]-'0'>=carry){a[i]--;break;}
        else a[i]='9';
    }

    printf("%d\n",sub(n_th_digital(b,m),n_th_digital(a,m)));



    return 0;
}
