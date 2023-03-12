#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10;

long double a[maxn],b[maxn],pb[maxn],pa[maxn];
int n;

long double solve(long double a,long double b,long double c){

    return (-b+sqrt(abs(b*b-4*a*c)))/2*a;

}

int main(){


    scanf("%d",&n);

    for(int i=1;i<=n;i++)scanf("%Lf",&a[i]);
    for(int i=1;i<=n;i++)scanf("%Lf",&b[i]);

    long double suma=1;
    long double sumb=1;
    for(int i=n;i>1;i--){

        long double c=a[i]+b[i];
        pb[i]=solve(1,suma-sumb-c,c*sumb-a[i]);

        pa[i]=a[i]+b[i]-pb[i];

        suma-=pa[i];
        sumb-=pb[i];
    }
    pa[1]=1+(suma-1);
    pb[1]=1+(sumb-1);

    for(int i=1;i<=n;i++)printf("%Lf ",pa[i]);
    cout<<endl;
    for(int i=1;i<=n;i++)printf("%Lf ",pb[i]);
    cout<<endl;


    return 0;
}
