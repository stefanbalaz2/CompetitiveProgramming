/*

    idea:

        dp[i] where dp[i] is the solution for the prefix i

        to update dp[i]
        u traverse from left to right
        and maintain all the candidates for the answer
        the candidates are of the form dp[i], how much cost make the last segment u take is from i to k, k is the current position ur calculating
        and last[i] is the time that the last transport in the group i to k started its journey
        maintain a dequeue, merge from the beggining, pop from the end, insert the new node
        and the result is the first node in dequeue

        sry for a rough explanation, im not in a mood to explain this task

*/
#include<bits/stdc++.h>
#include<set>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<ll,int> pii;
const int maxn=1e6+10;
ll s,dp[maxn],last[maxn],rez;
int a[maxn];
pii st1[maxn];
int lp=1,rp;
int n;
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);


    scanf("%d %lld",&n,&s);
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);


    dp[0]=0;
    last[0]=-1;

    ll cnt1=0;
    ll cnt2=0;

    for(int i=1;i<=n;i++){

        /// UPDATE
        vector<int>pom;
        for(int it=lp;it<=rp;it++){
            if(st1[it].ff+cnt1>=a[i])break;
            pom.pb(st1[it].ss);
        }

        int fid=-1;
        if(pom.size())fid=pom[0];
        ll minn=1e18;
        for(int j=0;j<pom.size();j++){
            int id=pom[j];
            lp++;

            ll pval;
            pval=dp[id]+cnt2+(a[i]-last[id]-cnt1+1);

            minn=min(minn,pval);
        }


        cnt1++;
        cnt2+=2;

        if(fid!=-1){
            dp[fid]=minn-cnt2;
            last[fid]=a[i]-cnt1;
            st1[--lp]={last[fid],fid};
        }


        int id=i-1;
        if(dp[id]+cnt2-2<=a[i]){
            dp[id]=a[i]+2*s-cnt2;
            last[id]=a[i]-cnt1;
        }
        else{
            last[id]=dp[id]+cnt2-2-cnt1;
            dp[id]=dp[id]+cnt2-2+2*s-cnt2;
        }

        for(int it=rp;it>=lp;it--){
            if(st1[it].ff<last[id])break;
            rp--;
        }

        st1[++rp]={last[id],id};


        /// GET SOLUTION
        ll p=dp[st1[lp].ss];
        if(i==n)rez=p+cnt2;
        dp[i]=p;
        last[i]=-1-cnt1;

    }

    printf("%lld\n",rez);

    return 0;
}
