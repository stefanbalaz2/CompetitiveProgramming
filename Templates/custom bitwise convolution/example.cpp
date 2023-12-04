#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=3e5+10;
int n;

struct trans{

    ll a[2][2];


    trans get_inv();

    void ispis(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++)printf("%lld ",a[i][j]);
            printf("\n");
        }
        printf("ISPIS\n");
    }

};
int det(trans c){
    return c.a[0][0]*c.a[1][1]-c.a[1][0]*c.a[0][1];
}
trans trans::get_inv(){

    trans ret=(*this);

    swap(ret.a[0][0],ret.a[1][1]);
    ret.a[1][0]=-ret.a[1][0];
    ret.a[0][1]=-ret.a[0][1];

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)ret.a[i][j]*=2;

    int d=det(*this);
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)ret.a[i][j]/=d;

    return ret;
}
struct ftrans{
    trans a,b,c;

    void ispis(){

        a.ispis();
        b.ispis();
        c.ispis();
        printf("FTRANS ISPIS\n");

    }

};

bool check(trans a,trans b,trans c,trans f){

    if(det(c)==0)return false;

    for(int i=0;i<2;i++)
    for(int j=0;j<2;j++){
        int sum=0;
        for(int k=0;k<2;k++){
            sum=a.a[i][k]*b.a[j][k];
            if(sum!=c.a[f.a[i][j]][k])return false;
        }
    }
    return true;
}

int pw3=531441;
ftrans get_trans(trans f){

    for(int i=0;i<pw3;i++){

        trans a,b,c;
        int mask=i;
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++){
                a.a[j][k]=mask%3-1;
                mask/=3;
            }

        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++){
                b.a[j][k]=mask%3-1;
                mask/=3;
            }

        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++){
                c.a[j][k]=mask%3-1;
                mask/=3;
            }

        if(check(a,b,c,f))return {a,b,c};

    }

    ///printf("AAAAAAAAAAAAAAAAAAA\n");

}


void fft(vector<ll>&a,vector<trans>tr,bool invert){

    int n=a.size();
    int cid=0;
    for(int len=2;len<=n;len<<=1){

        trans pom=tr[cid];
        int hlen=len/2;
        for(int i=0;i<n;i+=len){
            for(int j=0;j<hlen;j++){

                ll pom1=a[i+j];
                ll pom2=a[i+j+hlen];

                a[i+j]=pom1*pom.a[0][0]+pom2*pom.a[1][0];
                a[i+j+hlen]=pom1*pom.a[0][1]+pom2*pom.a[1][1];

                if(invert){
                    a[i+j]/=2;
                    a[i+j+hlen]/=2;
                }
            }
        }

        cid++;
    }

}
vector<ll>convolute(vector<ll>a,vector<ll>b,vector<ftrans>f){

    vector<trans>pom;
    for(int i=0;i<f.size();i++)pom.pb(f[i].a);
    fft(a,pom,0);

    pom.clear();
    for(int i=0;i<f.size();i++)pom.pb(f[i].b);
    fft(b,pom,0);

    for(int i=0;i<a.size();i++)a[i]*=b[i];

    pom.clear();
    for(int i=0;i<f.size();i++)pom.pb(f[i].c.get_inv());
    fft(a,pom,1);

    return a;
}

int main(){


    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    vector<trans>f;
    for(int i=0;i<n;i++){

        string s;
        cin>>s;
        trans pom;
        for(int j=0;j<4;j++){
            pom.a[j/2][j%2]=s[j]-'0';
        }

        f.pb(pom);
    }

    vector<ll>a,b;
    for(int i=0;i<(1<<n);i++){
        int cc;
        scanf("%d",&cc);
        a.pb(cc);
    }
    for(int i=0;i<(1<<n);i++){
        int cc;
        scanf("%d",&cc);
        b.pb(cc);
    }

    vector<ftrans> t;
    for(int i=0;i<n;i++){
        t.pb(get_trans(f[i]));
        ///t.back().ispis();
    }

    a=convolute(a,b,t);

    for(int i=0;i<a.size();i++)printf("%lld ",a[i]);

    return 0;
}
