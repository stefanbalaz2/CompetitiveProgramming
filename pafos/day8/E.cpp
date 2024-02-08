#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;
typedef long long ll;

int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

int cnt[10000];
void go(int pos,int last,int t,int no,int prod,int flag){

    if(pos==t+1){
        if(flag){
            cnt[prod]++;
            sum=add(sum,prod);
        }
        return;
    }

    for(int i=last+1;i<mod;i++){
        if(i!=no)go(pos+1,i,t,no,mul(prod,i),flag);
        else go(pos+1,i,t,no,mul(prod,i),1);
    }

}

int main(){

    while(1){
        int p,k,t;
        scanf("%d %d %d",&p,&k,&t);
        mod=p;
        go(1,0,t,k,1,0);

        int rez=0;
        for(int i=0;i<p;i++){
            printf("%d %d\n",i,cnt[i]);
            rez=add(rez,mul(cnt[i],i));
        }
        printf("%d\n",rez);
    }

    return 0;
}
