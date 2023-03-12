/*

    we can seperate the whole expexcet value sumation into probabilities
    that an inversion happens at indices i and j, so we just need to sum up those probabilities
    we will maintain a dp[i][i] meaning, probability that a[i]>a[j] after some swaps

    transition between states:
        for every swap, the dp values that change are all 1<=i<=n

        for a swap (l,r)  (l<r)

        cases:

        i<l
        1/2 cases that the value in l stays there, and 1/2 that value from r comes to l
        dp[i][l]=dp[i][r]=0.5*dp[i][l]+0.5*dp[i][r]

        i>r
        same observation as the previous case
        dp[l][i]=dp[r][i]=0.5*dp[l][i]+0.5*dp[r][i]

        l<i<r
        same observation as the previous case
        dp[i][r]=0.5*dp[i][r]+0.5*(1-dp[l][i])
        dp[l][i]=0.5*dp[l][i]+0.5*(1-dp[i][r])


        last case
        dp[l][r]=0.5

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
double dp[1010][1010];
int a[1010],n,m;
void init(){

    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(a[i]>a[j])dp[i][j]=1;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    init();

    for(int i=1;i<=m;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        if(l>r)swap(l,r);

        for(int j=1;j<l;j++){
            double pom=0.5*dp[j][l]+0.5*dp[j][r];
            dp[j][l]=pom;
            dp[j][r]=pom;
        }

        for(int j=r+1;j<=n;j++){
            double pom=0.5*dp[l][j]+0.5*dp[r][j];
            dp[l][j]=pom;
            dp[r][j]=pom;
        }

        for(int j=l+1;j<r;j++){
            double pom=0.5*dp[j][r]+0.5*(1-dp[l][j]);
            double pom2=0.5*dp[l][j]+0.5*(1-dp[j][r]);
            dp[j][r]=pom;
            dp[l][j]=pom2;
        }

        dp[l][r]=0.5;
    }

    double rez=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)rez+=dp[i][j];

    cout<<fixed<<setprecision(8)<<rez<<endl;

    return 0;
}
