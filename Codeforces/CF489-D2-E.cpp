/*

    idea: https://codeforces.com/blog/entry/14741?#comment-197192

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=1010;
int l,x[maxn],b[maxn],p[maxn],n;
double dp[maxn];
vector<int>vect;
double check(double r){

    dp[0]=0;

    for(int i=1;i<=n;i++){
        dp[i]=1e18;
        for(int j=0;j<i;j++){

            double w=sqrt(abs((double)x[i]-x[j]-l))-r*(double)b[i];

            if(dp[j]+w<dp[i]){
                dp[i]=dp[j]+w;
                p[i]=j;
            }

        }

    }

    return dp[n];
}

int main(){


    scanf("%d %d",&n,&l);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&x[i],&b[i]);
    }

    double l=0;
    double r=1e8;
    double sr,ret;
    int it=0;
    while(it++<100){

        sr=(l+r)/2;

        if(check(sr)<=0){
            r=sr;
            ret=sr;
        }
        else l=sr;

    }

    check(ret);

    int curr=n;
    while(curr!=0){
        vect.pb(curr);
        curr=p[curr];
    }

    while(vect.size()){
        printf("%d ",vect.back());
        vect.pop_back();
    }
    printf("\n");

    return 0;
}
