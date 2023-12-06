/*
  https://codeforces.com/contest/1906/problem/K

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
void fft(vector<int>&a){

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

}

int main(){


    ///freopen("test.txt","r",stdin);

    int n;
    scanf("%d",&n);
    vector<int>niz(maxn);
    for(int i=1;i<=n;i++){
        int a;
        scanf("%d",&a);
        niz[a]++;
    }
    fft(niz);
    for(int i=0;i<maxn;i++){

        int c=niz[i];
        int cnt0=mul((c+n),invv(2));
        int cnt1=sub(n,cnt0);

        niz[i]=mul(step(3,cnt0),step(sub(0,1),cnt1));
    }
    invfft(niz);

    printf("%d\n",niz[0]);

    return 0;
}
