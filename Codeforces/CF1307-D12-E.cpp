/*

    only one cow of a color can be in one group
    cows have fixed points of finish for both groups
    dofferent colors are independend, bcs we can sort them
    every configuration has its unique right boundary of the first group
    we just try to place pairs of cows before and after that unique right boundary for every  boundary

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=5e3+10;
int pref[maxn][maxn],n,m,a[maxn],maxx=-1;
ll mod=1e9+7,rez;
pii c[maxn];
vector<pii>stek[maxn];
void check(int col,int rp){

    ll ret=0;
    for(int i=0;i<stek[col].size();i++){
        if(stek[col][i].ff==rp)continue;

        ret+=(stek[col][i].ss>rp);
    }
    int cnt=(col!=0);
    if(ret==0)ret=1;
    else cnt++;

    for(int i=1;i<=n;i++){
        if(i==col)continue;

        int cnt2=0;
        for(int j=0;j<stek[i].size();j++)
            if(stek[i][j].ss>rp)cnt2++;

        ll pom=0;
        for(int j=0;j<stek[i].size();j++)
            if(stek[i][j].ff<rp)
                pom+=cnt2-(stek[i][j].ss>rp);


        if(pom){
            cnt+=2;
            ret=(ret*pom)%mod;
            continue;
        }

        pom=0;
        for(int j=0;j<stek[i].size();j++){
            if(stek[i][j].ff<rp)pom++;
            if(stek[i][j].ss>rp)pom++;
        }

        if(pom){
            cnt++;
            ret=(ret*pom)%mod;
            continue;
        }
    }

    if(cnt>maxx){
        maxx=cnt;
        rez=ret;
    }
    else if(cnt==maxx)
        rez=(rez+ret)%mod;

}
int main(){

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);

        for(int j=1;j<=n;j++)
            pref[j][i]=pref[j][i-1];

        pref[a[i]][i]++;
    }

    for(int i=1;i<=m;i++){
        scanf("%d %d",&c[i].ff,&c[i].ss);

        int l=1;
        int r=n;
        int sr,ret=-1;
        while(l<=r){
            int sr=(l+r)/2;
            if(pref[c[i].ff][sr]<c[i].ss)l=sr+1;
            else{
                r=sr-1;
                if(c[i].ss==pref[c[i].ff][sr])ret=sr;
            }
        }

        if(ret==-1)continue;

        l=1;
        r=n;
        int ret2=-1;
        int nd=pref[c[i].ff][n];
        while(l<=r){
            int sr=(l+r)/2;
            if(nd-pref[c[i].ff][sr-1]<c[i].ss)r=sr-1;
            else{
                l=sr+1;
                if(nd-pref[c[i].ff][sr-1]==c[i].ss)ret2=sr;
            }
        }


        stek[c[i].ff].pb({ret,ret2});
    }

    for(int i=1;i<=n;i++){

        for(int j=0;j<stek[i].size();j++){
            check(i,stek[i][j].ff);
        }
    }
    check(0,0);

    printf("%d %lld\n",maxx,rez);

return 0;
}
