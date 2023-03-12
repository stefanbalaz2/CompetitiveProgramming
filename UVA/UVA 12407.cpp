/*

    idea: https://github.com/miguelAlessandro/CompetitiveProgramming/blob/master/UVA/12407.cpp

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=110;
int n;
double s[maxn],D;
double eps=1e-10;
double eval(double x){

    double ret=0;

    for(int i=1;i<=n;i++){
        ret=(ret+ sqrt(-1.0-1.0/(x*x*s[i]*s[i]-1)+eps) );
    }

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    for(int tt=0;tt<t;tt++){

        int d;
        scanf("%d %d",&n,&d);
        D=d;

        double sum=0;
        double maxc=0;
        for(int i=1;i<=n;i++){
            int pom;
            scanf("%d",&pom);
            s[i]=pom;
            maxc=max(s[i],maxc);
        }

        double l=0;
        double r=1/maxc*0.99999999999;
        double h=100;
        double eq=D/h;
        double ret=0;
        for(int i=0;i<=100;i++){

            double sr=(l+r)/2;


            if(eval(sr)>eq){
                r=sr;
            }
            else{
                l=sr;
                ret=sr;
            }

        }

        double rez=0;
        for(int i=1;i<=n;i++){
            rez+=sqrt(-h*h/( s[i]*s[i]*(ret*ret*s[i]*s[i]-1) ) );
        }

        printf("Case %d: %.8lf\n",tt+1,rez);
    }


    return 0;
}
