/*

    idea:
*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=210;
ll dp[maxn][maxn][maxn][3];
ll minf=1e18+1;
int b,r,s;

ll go(int bb,int rr,int ss,int lst){

    if(bb<0 || rr<0 || ss<0)return 0;
    if(bb==0 && rr==0 && ss==0)return 1;

    if(dp[bb][rr][ss][lst]!=-1)return dp[bb][rr][ss][lst];

    dp[bb][rr][ss][lst]=0;

    if(lst!=0 && bb>0)dp[bb][rr][ss][lst]+=go(bb-1,rr,ss,0);
    dp[bb][rr][ss][lst]=min(dp[bb][rr][ss][lst],minf);

    if(lst!=1 && rr>0)dp[bb][rr][ss][lst]+=go(bb,rr-1,ss,1);
    dp[bb][rr][ss][lst]=min(dp[bb][rr][ss][lst],minf);

    if(lst!=2 && ss>0)dp[bb][rr][ss][lst]+=go(bb,rr,ss-1,2);
    dp[bb][rr][ss][lst]=min(dp[bb][rr][ss][lst],minf);

    return dp[bb][rr][ss][lst];
}

int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    memset(dp,-1,sizeof(dp));

    string rez;
    ll k;
    scanf("%d %d %d %lld",&b,&r,&s,&k);

    int sum=b+r+s;

    ll curr=0;
    int last=-1;
    for(int i=1;i<=sum;i++){

        ///cout<<rez<<" "<<curr<<" "<<go(b-1,r,s,0)<<endl;

        if(b==0 || last==0 || curr+go(b-1,r,s,0)<k){
            curr+=go(b-1,r,s,0)*(last!=0);
            if(r==0 || last==1 || curr+go(b,r-1,s,1)<k){
                curr+=go(b,r-1,s,1)*(last!=1);

                if(s==0 || last==2 || curr+go(b,r,s-1,2)<k){
                    printf("None\n");
                    return 0;
                }
                else{
                    rez.pb('S');
                    s--;
                    last=2;
                }
            }
            else{
                rez.pb('R');
                r--;
                last=1;
            }
        }
        else{
            rez.pb('B');
            b--;
            last=0;
        }
    }


    cout<<rez<<endl;

    return 0;
}
