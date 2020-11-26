/*

    idea:    https://codeforces.com/blog/entry/43886?#comment-285657

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int>pii;
const int maxn=3e5+10;
const int maxa=3e5+10;
ll fact[maxn],inv[maxn],mod=1e9+7,pref[maxn];
int n,mp[maxn];
vector<int>vect[maxn];
ll step(ll base,ll pw){

    ll ret=1;
    while(pw){

        if(pw&1)ret=(ret*base)%mod;

        base=(base*base)%mod;
        pw/=2;

    }

    return ret;
}
ll c(int k,int n){

    ll ret=fact[n];
    ret=(ret*inv[k])%mod;
    ret=(ret*inv[n-k])%mod;

    return ret;
}
void prek_bin(){

    fact[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fact[i]=(fact[i-1]*i)%mod;
        inv[i]=step(fact[i],mod-2);
    }

    pref[0]=1;
    for(int i=1;i<=n-1;i++){
        pref[i]=(pref[i-1]+c(i,n-1))%mod;
    }
}
void prek_sito(){

    for(int i=2;i<maxa;i++){
        if(mp[i])continue;

        for(int j=i;j<maxa;j+=i){
            if(mp[j])continue;
            mp[j]=i;
        }

    }

}
void obradi(int x){

    vector<pii>cp;
    while(x){

        if(x==1)break;

        if(cp.size()==0)cp.pb({mp[x],1});
        else if(cp.back().ff==mp[x])cp[cp.size()-1].ss++;
        else cp.pb({mp[x],1});

        x/=mp[x];
    }

    for(int i=0;i<cp.size();i++){
        vect[cp[i].ff].pb(cp[i].ss);
    }
}
ll get_ways(int x){
    if(x==0)return 0;
    return pref[x-1];
}
ll go(int p){

    if(vect[p].size()==0)return 0;

    sort(vect[p].begin(),vect[p].end());

    ll ret=0;


    for(int i=0;i<vect[p].size();i++){


        ret=(ret- ( (ll)vect[p][i]*get_ways(vect[p].size()-i-1) ) )%mod;
        if(ret<0)ret+=mod;
        ret=(ret+ ( (ll)vect[p][i]*get_ways(n-(vect[p].size()-i-1)-1) ) )%mod;
    }

    return ret;
}
int main(){


    scanf("%d",&n);

    prek_bin();
    prek_sito();

    for(int i=1;i<=n;i++){

        int a;
        scanf("%d",&a);
        obradi(a);
    }

    ll rez=0;
    for(int i=2;i<maxa;i++){
        rez=(rez+go(i))%mod;
    }

    printf("%lld\n",rez);


    return 0;
}
