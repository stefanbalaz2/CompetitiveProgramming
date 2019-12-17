/*

    euclid non-prime modulo generalisation

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxv=1e7;
int pos[maxv+10];
ll rez[110][110];
void sito(){

    for(int i=2;i<=maxv;i++){
        if(pos[i])continue;
        for(int j=i;j<=maxv;j+=i){
            if(pos[j])continue;
            pos[j]=i;
        }
    }

}
void factorisation(int x,vector<int> &vect){

    while(x>1){

        if(vect.size()==0)vect.pb(pos[x]);
        else if(vect[vect.size()-1]!=pos[x])vect.pb(pos[x]);

        x/=pos[x];
    }
}
ll phi(ll x){

   vector<int>fact;
   factorisation(x,fact);

   ll ret=x;
   for(int i=0;i<fact.size();i++)
    ret=ret-ret/fact[i];

return ret;
}
ll step(ll base,ll pw,ll mod){

    ll ret=1;
    while(pw){
        if(pw%2)ret=(ret*base)%mod;
        base=(base*base)%mod;

        pw/=2;
    }
return ret;
}
ll step_no_mod(ll base,ll pw){

    ll ret=1;
    while(pw){
        if(pw%2)ret=(ret*base);
        base=(base*base);

        pw/=2;
    }
return ret;
}
ll step_manji(ll base,ll x){
    if(x==0)return 1;
    return step_no_mod(base,step_manji(base,x-1));
}
bool check(ll base,ll x,ll mod){

    if(x==0)return false;
    if(base==1)return false;

    if(check(base,x-1,mod))return true;
    ll pw=step_manji(base,x-1);

    while(pw--){
        base*=base;
        if(base>mod)return true;
    }
    return false;
}
ll go(ll base,ll x,ll mod){

    if(x==0)return 1;

    if(check(base,x-1,mod)){
        ll ph=phi(mod);
        ll pom=go(base,x-1,ph);

        return step(base,pom+ph,mod);
    }

    return step(base,step_manji(base,x-1),mod);
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("test.txt","w",stdout);

    sito();
    for(int i=1;i<=100;i++)
        for(int j=1;j<=100;j++)
            rez[i][j]=go(i,j,10000000);

    while(1){

        int b,i,n;
        scanf("%d",&b);
        if(!b)break;

        scanf("%d %d",&i,&n);

        ll pom=rez[b][i];

        int niz[10];
        int br=0;

        for(int i=1;i<=n;i++){
            niz[++br]=pom%10;
            pom/=10;
        }
        for(int i=n;i>=1;i--)printf("%d",niz[i]);
        printf("\n");
    }

    return 0;
}
