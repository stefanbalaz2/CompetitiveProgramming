/*

    idea:https://img.atcoder.jp/data/agc/003/editorial.pdf

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
typedef pair<int,int>pii;
const int maxn=1e5+10;
ll n,niz[maxn],t[maxn];
int q;
void add_interval(ll k,ll oc){

    if(k<1)return;


    niz[1]+=oc;
    niz[k+1]-=oc;
}
int main(){

    ///freopen("test.txt","r",stdin);


    scanf("%lld %d",&n,&q);

    vector<ll>stek;
    stek.pb(n);
    for(int i=1;i<=q;i++){

        ll a;
        scanf("%lld",&a);

        while(stek.size() && stek.back()>=a)stek.pop_back();
        stek.pb(a);
    }


    t[stek.size()-1]=1;

    while(stek.size()){


        ll a=stek.back();
        stek.pop_back();


        ll k=a;

        while(1){

            int l=0;
            int r=stek.size()-1;
            int sr,ret=-1;
            while(l<=r){

                sr=(l+r)/2;
                if(stek[sr]<=k){
                    l=sr+1;
                    ret=sr;
                }
                else r=sr-1;
            }


            if(ret==-1){
                add_interval(k,t[stek.size()]);
                break;
            }
            else{
                t[ret]+=t[stek.size()]*(k/stek[ret]);
                k%=stek[ret];
            }

        }

    }

    ll curr=0;
    for(int i=1;i<=n;i++){
        curr+=niz[i];
        printf("%lld ",curr);
    }


return 0;
}
