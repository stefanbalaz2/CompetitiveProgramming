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
typedef multiset<ll>::iterator sit;
const int maxn=2e5+10;
ll rez=0;
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    multiset<ll>levo,desno;
    ll llazy=0,rlazy=0,p=0;

    int n;
    scanf("%d",&n);

    ll l,r;
    scanf("%lld %lld",&l,&r);

    levo.insert(l);
    desno.insert(l);
    p=r-l;
    for(int i=2;i<=n;i++){

        scanf("%lld %lld",&l,&r);
        ll q=r-l;

        llazy-=q;
        rlazy+=p;

        ll lp=(*levo.rbegin())+llazy;
        ll rp=(*desno.begin())+rlazy;

        ///printf("%lld %lld %lld %lld\n",lp,rp,p,q);

        if(l<lp){

            rez+=lp-l;

            desno.insert(lp-rlazy);
            levo.erase(levo.find(*levo.rbegin()));
            levo.insert(l-llazy);
            levo.insert(l-llazy);

        }
        else if(l>rp){

            rez+=l-rp;

            desno.erase(desno.begin());
            levo.insert(rp-llazy);
            desno.insert(l-rlazy);
            desno.insert(l-rlazy);
        }
        else{

            levo.insert(l-llazy);
            desno.insert(l-rlazy);

        }

        p=q;
    }

    printf("%lld\n",rez);
    return 0;
}
