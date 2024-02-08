#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define all(x) begin(x), end(x)
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef long double ld;
#define double ld

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=1e3+10;

bool eq(double a,double b){
    double eps=1e-7;
    if(abs(a-b)<=eps)return true;
    return false;
}
struct pt{
    double x,y;
    pt operator - (pt&b)const{
        return {x-b.x,y-b.y};
    }
    double cross(pt b){
        return x*b.y-y*b.x;
    }
    void ispis(){
        cout<<x<<" "<<y<<"  POINT"<<endl;
    }
}c,p[maxn];
double inf=1e18;
struct line{
    pt a,b;
    double k,ck;
    void calc_kb(){
        if(a.x==b.x){
            k=inf;
            ck=a.x;
            return;
        }
        k=(a.y-b.y)/(a.x-b.x);
        ck=a.y-k*a.x;
    }
    double eval(double x){
        return k*x+ck;
    }

    void ispis(){

        cout<<a.x<<" "<<a.y<<" | "<<b.x<<" "<<b.y<<"  LINE"<<endl;

    }
};
int n;

vector<line>split_line(line x){

    vector<line>ret;
    if(eq(x.a.cross(x.b),0))return ret;
    if((x.a.x<0 && x.b.x>0)||(x.a.x>0 && x.b.x<0)){

        x.calc_kb();
        if(eq(x.ck,0))return ret;

        pt pom={0,x.eval(0)};

        ret.pb({x.a,pom});
        ret.pb({pom,x.b});
        return ret;
    }
    else{
        x.calc_kb();
        if(eq(x.ck,0))return ret;
        ret.pb(x);
        return ret;
    }
}

int e=0;
int cc=0;
const double PI=acos(-1)/2;
namespace funct{

    double k,b;

    inline double sqr(double x){return x*x;}
    double f(double alpha){

        if(eq(abs(alpha),PI)){
            return b;
        }


        double pom=tan(alpha);
        cc++;
        if(!eq(k,inf)){
            ///cout<<b/(tan(alpha)-k)<<" "<<(b*tan(alpha))/(tan(alpha)-k)<<"  INTER"<<endl;
            return sqrt( sqr(b/(pom-k))+sqr( (b*pom)/(pom-k)) );
        }
        else{
            return sqrt(sqr(b)+sqr(b*pom));
        }

    }

}
int sgn(line a){
    double pom=a.a.cross(a.b);
    if(pom>0)return 1;
    if(pom==0)return 0;
    return -1;
}
double get_angle(pt a,int invert){

    if(eq(a.x,0)){
        if(a.y>0)return invert*PI;
        else return -PI*invert;
    }

    line pom={{0,0},a};
    pom.calc_kb();

    return atan(pom.k);
}

const int sn=1*2;
double simpsons(double lp,double rp){

    double h=(rp-lp)/sn;
    double ret=funct::f(lp)+funct::f(rp);
    for(int i=1;i<sn;i++){
        if(i&1)ret+=4*funct::f(lp+i*h);
        else ret+=2*funct::f(lp+i*h);
    }
    ret*=h/3;
    return ret;
}
double inte(double lp,double rp){
    double curr=simpsons(lp,rp);
    double mid=(lp+rp)/2;
    double nxt=simpsons(lp,mid)+simpsons(mid,rp);
    if(eq(nxt,curr))return curr;
    else return inte(lp,mid)+inte(mid,rp);
}

int main(){

    freopen("test.txt","r",stdin);

    cin>>n>>c.x>>c.y;

    vector<pt>pts(n);
    for(int i=0;i<n;i++){
        cin>>pts[i].x>>pts[i].y;
        pts[i]=pts[i]-c;
    }
    c.x=0;c.y=0;
    vector<line>lines,pom;
    for(int i=1;i<n;i++)
        lines.pb({pts[i],pts[i-1]});
    lines.pb({pts[0],pts[n-1]});
    for(int i=0;i<lines.size();i++){
        vector<line>pp=split_line(lines[i]);
        for(int j=0;j<pp.size();j++)pom.pb(pp[j]);
    }
    lines=pom;

    double rez=0;
    for(int i=0;i<lines.size();i++){


        int coef=sgn(lines[i]);

        int invert=1;
        if(lines[i].a.x<0 || lines[i].b.x<0)invert=-1;
        double lp=get_angle(lines[i].a,invert);
        double rp=get_angle(lines[i].b,invert);
        if(lp>rp)swap(lp,rp);


        lines[i].calc_kb();
        funct::k=lines[i].k;
        funct::b=lines[i].ck;

        rez+=inte(lp,rp)*coef;

        ///if(i==100 && e)break;
        ///if(i%50==0)printf("%d OP\n",i);

    }

    cout<<cc<<" STEPS"<<endl;

    cout<<fixed<<setprecision(10)<<abs(rez)/(2*PI)<<endl;

    return 0;
}
