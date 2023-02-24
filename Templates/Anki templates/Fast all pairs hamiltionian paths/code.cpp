#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;


const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){if(base==0)return 0;int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}


const int maxn=24;

int dp[1<<maxn],rez[maxn],adj[maxn],n;

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);

    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        for(int j=0;j<n;j++){
            int d=s[j]-'0';
            adj[i]|=(d<<j);
        }
    }

    ///printf("poceo1\n");
    dp[1<<(n-1)]=(1<<(n-1));
    for(int i=1;i<(1<<n);i++){
        if(i==(1<<(n-1)) || (i&(1<<(n-1)))==0 )continue;

        for(int j=0;j<n;j++){
            if(i&(1<<j)){
                if(dp[i^(1<<j)]&adj[j]){
                    dp[i]|=(1<<j);
                }
            }
        }

    }
    ///printf("zavrsio1\n");

    ///printf("poceo2\n");
    int rel,comp;
    for(int i=0;i<(1<<n);i++){

        rel=i;
        comp=(((1<<n)-1)^i);

        rel|=(1<<(n-1));
        comp|=(1<<(n-1));
        if(rel>comp)continue;

        int pom=dp[comp];
        int pom2=dp[rel];
        for(int j=0;j<n;j++){
            if(pom2&(1<<j)){
                rez[j]|=pom;
            }
        }
    }
    ///printf("zavrsio2\n");

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if( (rez[i]&(1<<j)) || (rez[j]&(1<<i)) )printf("1");
            else printf("0");
        }
        printf("\n");
    }


return 0;
}
