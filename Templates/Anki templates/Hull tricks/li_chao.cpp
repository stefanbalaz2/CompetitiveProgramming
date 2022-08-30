/**



*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

struct line{

    ll k,b;

    ll eval(ll x){
        return x*k+b;
    }

};

void update(int x,int l,int r,line val){

    int m=(l+r)/2;

    if(tree[x].eval(m)>val.eval(m))swap(tree[x],val);

    if(r-l==1)return;

    if(tree[x].eval(l)>val.eval(l))update(x*2,l,m,val);
    else update(x*2+1,m,r,val);

}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);



    return 0;
}
