/**

  https://codeforces.com/gym/102956/problem/A

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;

const int maxn=(1<<18);

int n;

struct mat{
    int a[2][2];
    void ispis(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                printf("%d ",a[i][j]);
            }
            printf("\n");
        }
        printf("gotova MAT\n");
    }
};
struct trans{
    mat a[3];
    void ispis(){
        for(int i=0;i<3;i++){
            a[i].ispis();
        }
        printf("GOTOV TRANS\n");
    }
};
int det(mat a){
    return a.a[0][0]*a.a[1][1]-a.a[0][1]*a.a[1][0];
}
mat inverse(mat a){

    int d=det(a);

    swap(a.a[0][0],a.a[1][1]);
    a.a[1][0]=-a.a[1][0];
    a.a[0][1]=-a.a[0][1];

    a.a[0][0]*=2;
    a.a[0][1]*=2;
    a.a[1][0]*=2;
    a.a[1][1]*=2;

    a.a[0][0]/=d;
    a.a[0][1]/=d;
    a.a[1][0]/=d;
    a.a[1][1]/=d;

    return a;
    /// returns inverse multiplied with 2
}
bool check(trans x,mat y){

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                if(x.a[0].a[i][k]*x.a[1].a[j][k]!=x.a[2].a[y.a[i][j]][k])return false;

    if(det(x.a[2])==0)return false;

    return true;
}
trans get_trans(mat a){

    for(int i=0;i<531441;i++){

        int mask=i;

        trans pom;
        for(int j=0;j<3;j++)
            for(int k=0;k<2;k++)
                for(int k2=0;k2<2;k2++){
                    pom.a[j].a[k][k2]=mask%3-1;
                    mask/=3;
                }

        if(check(pom,a))return pom;
    }

}

void fft(vector<ll>&a,bool invert,vector<trans>trs,int c){
    int n=a.size();
    int cnt=-1;
    for(int len=2;len<=n;len<<=1){

        cnt++;
        mat ct=trs[cnt].a[c];
        if(invert)ct=inverse(ct);

        for(int i=0;i<n;i+=len){

            for(int j=0;j<len/2;j++){

                ll pom1=a[i+j];
                ll pom2=a[i+j+len/2];

                a[i+j]=pom1*ct.a[0][0]+pom2*ct.a[1][0];
                a[i+j+len/2]=pom1*ct.a[0][1]+pom2*ct.a[1][1];

                if(invert){
                    a[i+j]/=2;
                    a[i+j+len/2]/=2;
                }
            }

        }

    }


}
vector<ll> pol_mul(vector<ll>a,vector<ll>b,vector<trans>trs){
    fft(a,0,trs,0);
    fft(b,0,trs,1);
    for(int i=0;i<a.size();i++)a[i]*=b[i];
    fft(a,1,trs,2);
    return a;
}

int main() {


    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);

    vector<trans>pom;
    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        mat p;
        p.a[0][0]=s[0]-'0';
        p.a[0][1]=s[1]-'0';
        p.a[1][0]=s[2]-'0';
        p.a[1][1]=s[3]-'0';
        pom.pb(get_trans(p));
    }

    vector<ll>a((1<<n)),b((1<<n));
    for(int i=0;i<(1<<n);i++)
        scanf("%lld",&a[i]);
    for(int i=0;i<(1<<n);i++)
        scanf("%lld",&b[i]);

    a=pol_mul(a,b,pom);

    for(int i=0;i<a.size();i++)printf("%lld ",a[i]);

    return 0;
}

