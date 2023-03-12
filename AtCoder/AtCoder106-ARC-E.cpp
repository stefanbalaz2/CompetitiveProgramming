#include<bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=20;
const int maxk=1e5+10;
int n;
int k,a[maxn],niz[maxn*maxk*4];
int dp[(1<<maxn)];
bool check(int x){

    memset(dp,0,sizeof(dp));
    for(int i=1;i<=x;i++){
        int rev=(niz[i]^((1<<n)-1) );
        dp[rev]++;
    }


    for(int i=0;i<n;i++)
        for(int j=0;j<(1<<n);j++)
        if(!(j&(1<<i)))dp[j]+=dp[j^(1<<i)];


    for(int i=0;i<(1<<n);i++){
        int sum=x-dp[i];

        if(sum<(__builtin_popcount(i)*k))return false;
    }

    return true;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);

    int l=1;
    int r=n*k*4;
    int sr,ret=-1;

    for(int j=0;j<n;j++){
        int cnt=1;
        for(int i=1;i<=r;i++){

            if(cnt<=a[j+1])niz[i]^=(1<<j);

            cnt++;
            if(cnt>a[j+1]*2)cnt=1;
        }
    }


    while(l<=r){

        sr=(l+r)/2;

        if(check(sr)){
            ret=sr;
            r=sr-1;
        }
        else l=sr+1;
    }



    printf("%d\n",ret);


return 0;
}
