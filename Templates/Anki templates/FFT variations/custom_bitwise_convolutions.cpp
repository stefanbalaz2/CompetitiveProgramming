/**

  https://codeforces.com/gym/102956/problem/A

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

struct mat{

    int a[2][2];

    int det(){
        return a[0][0]*a[1][1]-a[1][0]*a[0][1];
    }

    mat inv(){

        mat ret;
        int d=det();
        if(d==0)return ret;
        ret.a[0][0]=(a[1][1]*2)/d;
        ret.a[1][1]=(2*a[0][0])/d;
        ret.a[0][1]=-(2*a[0][1])/d;
        ret.a[1][0]=-(2*a[1][0])/d;

        return ret;
    }

    void ispis(){

        printf("%d %d \n %d %d  mat\n",a[0][0],a[0][1],a[1][0],a[1][1]);
    }

};

bool check(mat f,mat a,mat b,mat c){

    if(c.det()==0)return 0;

    for(int i=0;i<2;i++)
    for(int j=0;j<2;j++)
        for(int k=0;k<2;k++)
            if(a.a[i][k]*b.a[j][k]!=c.a[f.a[i][j]][k])return false;

    return true;
}

pair<mat,pair<mat,mat> > get_f(mat f){


    mat a,b,c;

    for(int i=0;i<531441;i++){

        int cc=i;
        for(int j=0;j<4;j++){
            a.a[j/2][j%2]=cc%3-1;
            cc/=3;
        }
        for(int j=0;j<4;j++){
            b.a[j/2][j%2]=cc%3-1;
            cc/=3;
        }
        for(int j=0;j<4;j++){
            c.a[j/2][j%2]=cc%3-1;
            cc/=3;
        }


        if(check(f,a,b,c))return {c.inv(),{a,b}};

    }

}

void fft(vector<ll>&a,vector<mat>ts,bool invert){
    int n=a.size();
    int c=-1;
    for(int len=2;len<=n;len<<=1){
        c++;
        int hlen=len/2;

        for(int i=0;i<n;i+=len){

            for(int j=0;j<hlen;j++){

                ll pom1=a[i+j]*ts[c].a[0][0]+a[i+j+hlen]*ts[c].a[1][0];
                ll pom2=a[i+j]*ts[c].a[0][1]+a[i+j+hlen]*ts[c].a[1][1];

                a[i+j]=pom1;
                a[i+j+hlen]=pom2;

                if(invert){
                    a[i+j]/=2;
                    a[i+j+hlen]/=2;
                }

            }

        }

    }

}

vector<ll>pmul(vector<ll>a,vector<ll>b,vector<mat>A,vector<mat>B,vector<mat>C){

    fft(a,A,0);
    fft(b,B,0);
    for(int i=0;i<a.size();i++)a[i]*=b[i];
    fft(a,C,1);
    ///for(int i=0;i<a.size();i++)a[i]/=a.size();

    return a;
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int n;
    scanf("%d",&n);
    vector<mat>A,B,C;
    for(int i=0;i<n;i++){

        string s;
        cin>>s;

        mat pom;
        for(int i=0;i<4;i++)
            pom.a[i/2][i%2]=s[i]-'0';

        pair<mat,pair<mat,mat> >pp=get_f(pom);

        /*printf("AAA\n");

        pp.ff.ispis();
        pp.ss.ff.ispis();
        pp.ss.ss.ispis();*/

        C.pb(pp.ff);
        A.pb(pp.ss.ff);
        B.pb(pp.ss.ss);
    }


    vector<ll>a((1<<n)),b(1<<n);

    for(int i=0;i<(1<<n);i++)
        scanf("%lld",&a[i]);

    for(int i=0;i<(1<<n);i++)
        scanf("%lld",&b[i]);

    a=pmul(a,b,A,B,C);

    for(int i=0;i<(1<<n);i++)printf("%lld ",a[i]);


    return 0;
}
