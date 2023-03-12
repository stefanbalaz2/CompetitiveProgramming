/*

    two pointer on the number segment
    set of modular equations
    checking the validity by the regular crt condition while adding and removing

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;

const int maxn=1e5+10;

vector<pii>v[maxn];
int k[maxn],n,m;

int solve(int x){

    int ret=1;
    int nn=v[x].size();
    if(nn==0)return 0;

    int lp=0;
    pii niz[41];
    memset(niz,0,sizeof(niz));
    niz[k[v[x][0].ff]]={v[x][0].ss,1};

    int cst=0;
    for(int i=1;i<v[x].size();i++){

        if(i==nn)cst++;
        else if(i==nn+nn)cst++;

        if(v[x][i].ff-v[x][i-1].ff>1){
            lp=i;
            memset(niz,0,sizeof(niz));
        }

        int mod=k[v[x][i].ff];
        int pos=v[x][i].ss-cst;
        pos%=mod;
        if(pos<0)pos+=mod;

        int e=1;
        for(int j=1;j<=40;j++){
            if(niz[j].ss==0)continue;

            int nzd=__gcd(j,mod);
            if(pos%nzd!=niz[j].ff%nzd)e=0;
        }

        while(1){

            e=1;
            for(int j=1;j<=40;j++){
                if(niz[j].ss==0)continue;

                int nzd=__gcd(j,mod);
                if(pos%nzd!=niz[j].ff%nzd)e=0;
            }
            if(e==1)break;

            niz[k[v[x][lp].ff]].ss--;
            lp++;
        }

        niz[mod].ss++;
        niz[mod].ff=pos;

        ret=max(ret,i-lp+1);
    }

    return ret;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&k[i]);
        for(int j=0;j<k[i];j++){
            int a;
            scanf("%d",&a);

            v[a].pb({i,j});
        }
    }

    for(int i=1;i<=m;i++){
        printf("%d\n",solve(i));
    }

	return 0;
}
