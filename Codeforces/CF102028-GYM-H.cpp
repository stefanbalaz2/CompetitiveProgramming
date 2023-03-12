#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,ll> pii;
const int maxn=2e5+10;
int n,c[maxn],niz[maxn],tc[maxn],r[maxn],lc[maxn];
ll a[maxn];
vector<int>cnt[maxn];

bool srt(int a,int b){
    return c[a]<c[b];
}
void sort_suffix(){

    a[n++]=0;

    int h=0;
    while((1<<h)<=n)h++;

    map<int,int>mapa;
    for(int i=0;i<n;i++)mapa[a[i]]=0;
    int br2=0;
    for(map<int,int>::iterator it=mapa.begin();it!=mapa.end();it++)it->second=++br2;

    for(int i=0;i<n;i++){
        c[i]=mapa[a[i]];
        niz[i]=i;
    }
    sort(niz,niz+n,srt);

    for(int i=1;i<=h;i++){

        /*for(int j=0;j<n;j++){
            printf("%d %d AAA\n",j,niz[j]);
        }*/

        int stp=(1<<(i-1));

        for(int j=0;j<n;j++){
            cnt[c[(j+stp)%n]].pb(j);
            ///printf("%d %d %d DSAF\n",j,c[(j+stp)%n],(j+stp)%n);
        }

        int br=n;
        for(int j=n;j>=0;j--)
        while(cnt[j].size()){
            niz[--br]=cnt[j].back();
            cnt[j].pop_back();
        }

        /*for(int j=0;j<n;j++){
            printf("%d %d AAA\n",j,niz[j]);
        }*/

        for(int j=0;j<n;j++)cnt[c[niz[j]]].pb(niz[j]);

        br=n;
        for(int j=n;j>=0;j--)
        while(cnt[j].size()){
            niz[--br]=cnt[j].back();
            cnt[j].pop_back();
        }

        tc[niz[0]]=1;
        for(int j=1;j<n;j++){

            if(c[niz[j]]==c[niz[j-1]] && c[(niz[j]+stp)%n]==c[(niz[j-1]+stp)%n])tc[niz[j]]=tc[niz[j-1]];
            else tc[niz[j]]=tc[niz[j-1]]+1;

        }

        for(int j=0;j<n;j++)c[j]=tc[j];
    }


    /*for(int i=0;i<n;i++){
        printf("%d %d AAA\n",i,niz[i]);
    }*/
}

void calculate_lca(){

    for(int i=0;i<n;i++)r[niz[i]]=i;

    int lca=0;
    for(int i=0;i<n;i++){

        if(r[i]==n-1){
            lca=0;
            continue;
        }

        while(i+lca<n && niz[r[i]+1]+lca<n && a[i+lca]==a[niz[r[i]+1]+lca])lca++;

        lc[r[i]]=lca;
        if(lca)lca--;

    }


}

ll sol(){

    n--;

    ll rez=0;
    vector<pii>stek;
    stek.pb({n,0});
    a[n]=1e6+10;
    for(int i=n-1;i>=0;i--){

        ///printf("%d DSA\n",i);

        while(a[stek.back().ff]<=a[i])stek.pop_back();
        stek.pb({i,stek.back().ss+ ((ll)stek.back().ff-i)*a[i] });

        ///rintf("%d DSA\n",i);

        int lca=i+lc[r[i]-1];

        int r=stek.size()-1;
        int l=0;
        int sr,ret;
        while(l<=r){

            sr=(l+r)/2;

            if(stek[sr].ff>=lca){
                ret=sr;
                l=sr+1;
            }
            else r=sr-1;

        }
///printf("%d DSA\n",i);
        if(stek[ret].ff<=lca)ret--;
        rez+=stek[ret].ss;
        ret++;
        rez+=a[stek[ret].ff]*((ll)stek[ret-1].ff-lca);

    }

    return rez;
}

int main(){

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d",&n);
        for(int i=0;i<n;i++)scanf("%lld",&a[i]);

        sort_suffix();
        calculate_lca();

        printf("%lld\n",sol());

    }

    return 0;
}
