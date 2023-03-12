/*

    idea:   solve it using diophantine equations

            solve one by one
            first solve a1*x+a2*y=gcd(a1,a2)=g
            then solve g*x+a3*y=gcd(g,a3)=g
            and so on, update the coefficients correspondingly
            and in the end multiply the coefficients by b/g


    second idea: (derived from the first one)

            we can see that if g doesnt change in the transition from i to i+1
            the coef. which belongs to g can be 1 and the other one can be 0: g*1+0*a[i]=gcd(a[i],g)=g
            that means that there always exist a solution to the equation
            with <=log(m) values non-zero and the rest of them zero
            which leads us to the clasical dp solution dp[i] - whether we can reach sum i
            we can do it with bfs which leads to complexity O(mlogm)
            im not sure if this can be sqeezed in to pass, but its an interesting idea so i wrote it


*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<ll,ll> pii;
const int maxn=110;
int n;
ll a[maxn],p,m,b,rez[maxn],minn,mind;

ll gcd(ll a,ll b,ll &x,ll &y){

    if(b==0){
        x=1;
        y=0;
        return a;
    }

    ll x1,y1;
    ll g=gcd(b,a%b,x1,y1);

    x=y1;
    y=x1-y1*(a/b);

    return g;
}
void get_coef(ll x,ll y,ll rez,ll &xx,ll &yy){

    gcd(x,y,xx,yy);
    xx*=rez/__gcd(x,y);
    yy*=rez/__gcd(x,y);
}
void regulate(ll &x,ll m){
    x%=m;
    x+=m;
    x%=m;
    return;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d",&n);

        memset(rez,0,sizeof(rez));
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
        scanf("%lld %lld",&b,&m);
        for(int i=1;i<=n;i++)a[i]%=m;

        ll g=a[1];
        rez[1]=1;
        for(int i=2;i<=n;i++){

            ll x,y;
            get_coef(g,a[i],__gcd(g,a[i]),x,y);

            rez[i]=y;
            for(int j=i-1;j>=1;j--){
                rez[j]=(rez[j]*x)%m;
                regulate(rez[j],m);
            }

            g=__gcd(g,a[i]);
        }

        if(b%__gcd(g,m)){
            printf("NO\n");
            continue;
        }

        ll x,y;
        get_coef(g,m,b,x,y);
        for(int j=n;j>=1;j--)rez[j]=(rez[j]*x)%m;

        for(int i=1;i<=n;i++){
            regulate(rez[i],m);
            printf("%lld ",rez[i]);
        }
        printf("\n");
    }

    return 0;
}
