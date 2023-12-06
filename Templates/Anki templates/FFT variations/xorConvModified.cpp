/*

  https://codeforces.com/contest/1906/problem/K

  in the code there is a method to find:

  Pi(x)=(a0+a1*x^ri)
  a0 and a1 are fixed over the Pi
  we can find xor convolution of all Pi

*/

#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}


const int maxn=(1<<17);
const int maxb=17;

/*const int maxn=(1<<2);
const int maxb=2;*/

int dp[18][2][maxn];

void invfft(vector<int>&a){

    int n=a.size();

    for(int len=2;len<=n;len<<=1){
        int hlen=len/2;

        for(int i=0;i<n;i+=len){
            for(int j=0;j<hlen;j++){

                int pom1=a[i+j];
                int pom2=a[i+j+hlen];

                a[i+j]=add(pom1,pom2);
                a[i+j+hlen]=sub(pom1,pom2);

            }
        }

    }

    int invn=invv(n);
    for(int i=0;i<n;i++)a[i]=mul(a[i],invn);
}

int main(){


    freopen("test.txt","r",stdin);

    int n;
    scanf("%d",&n);
    /// bitovi zajedna shiftovani
    for(int i=1;i<=n;i++){
        int a;
        scanf("%d",&a);
        dp[0][__builtin_popcount(a)%2][a]++;
    }

    int fmask=maxn-1;
    for(int i=1;i<=maxb;i++){
        for(int j=0;j<maxn;j++){

            int cb=i-1;

            int p=j;
            p=(j&(fmask^(1<<cb)));/// nula

            dp[i][0][j]=add(dp[i][0][j],dp[i-1][0][p]);
            dp[i][1][j]=add(dp[i][1][j],dp[i-1][1][p]);

            p^=(1<<cb);/// kec
            int swc=(( (j&(1<<cb))^(1<<cb))>0);

            dp[i][0][j]=add(dp[i][0][j],dp[i-1][0^swc][p]);
            dp[i][1][j]=add(dp[i][1][j],dp[i-1][1^swc][p]);

        }
    }

    vector<int>niz(maxn);
    for(int i=0;i<maxn;i++){
        niz[i]=mul(step(3,dp[maxb][0][i]),step(mod-1,dp[maxb][1][i]));
        ///printf("%d | %d %d\n",dp[maxb-1]);
    }

    invfft(niz);

    printf("%d\n",niz[0]);

    return 0;
}
