/*

    idea:

        - a[i]=a[i]-n
        - dp1[i] min number of moves to reach sum of i with positive numbers
        - dp2[i] min number of moves to reach sum of i with negative numbers
        - in the end we need to find min(dp1[i],dp2[i]) bcs i-i gives 0

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
const int maxv=4e5;
int dp1[maxv],dp2[maxv],n,k,inf=1e9;
set<int>stp,stm;
void go(set<int> &st,int dp[]){

    dp[0]=0;

    for(sit it=st.begin();it!=st.end();it++){
        int val=(*it);
        for(int i=0;i<=maxv-val-1;i++)dp[i+val]=min(dp[i+val],dp[i]+1);
    }
}
int main(){
    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d %d",&n,&k);

    int e=0;
    for(int i=1;i<=k;i++){
        int a;
        scanf("%d",&a);
        if(a-n>0)stp.insert(a-n);
        else if(a-n<0)stm.insert(-a+n);
        else e=1;
    }
    if(e){
        printf("1\n");
        return 0;
    }

    memset(dp1,-1,sizeof(dp1));
    memset(dp2,-1,sizeof(dp2));
    for(int i=0;i<maxv;i++)dp1[i]=inf;
    for(int i=0;i<maxv;i++)dp2[i]=inf;
    go(stp,dp1);
    go(stm,dp2);

    int rez=inf;
    for(int i=1;i<maxv;i++){
        if(dp1[i]!=inf && dp2[i]!=inf)rez=min(rez,dp1[i]+dp2[i]);
    }

    printf("%d\n",rez==inf?-1:rez);

	return 0;
}
