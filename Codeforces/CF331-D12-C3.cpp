/*

    https://codeforces.com/contest/331/status/C3

*/
#include<bits/stdc++.h>
#define ll long long
#define ss second
#define ff first
#define pb push_back
using namespace std;
typedef pair<ll,ll> pii;
ll n;
map<pii,pii>mapa;
pii go(ll x,ll left_max){

    if(x<10)return {x>0||left_max>0,x-max(x,left_max)};
    if(mapa.find({x,left_max})!=mapa.end())return mapa[{x,left_max}];

    ll m=1;
    while(m<=x/10)m*=10;
    pii a=go(x%m,max(left_max,x/m));
    pii b=go((x/m)*m+a.ss,left_max);
    return mapa[{x,left_max}]={a.ff+b.ff,b.ss};
}
int main(){

	///freopen("test.txt","r",stdin);

    scanf("%lld",&n);
    printf("%lld\n",go(n,0).ff);

	return 0;
}
