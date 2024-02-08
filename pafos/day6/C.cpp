#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=22;
int n,W,h;
pii p[maxn];

vector<pair<pii,int>>hprek[(1<<(maxn/2))],lprek[(1<<(maxn/2))];

void prek_h(){

    int ch=n-h;

    for(int i=0;i<(1<<ch);i++){
        int rmask=(((1<<ch)-1)^i);
        int pom=rmask;
        while(rmask>0){

            int sumw=0;
            int mx=0;
            for(int j=0;j<ch;j++){
                if(rmask&(1<<j)){
                    sumw+=p[h+j].ss;
                    mx=max(mx,p[h+j].ff);
                }
            }

            hprek[i].pb({{sumw,mx},i|rmask});

            rmask--;
            rmask&=pom;
        }

        sort(hprek[i].begin(),hprek[i].end());
    }


}
void prek_l(){

    int ch=h;

    for(int i=0;i<(1<<ch);i++){
        int rmask=i;
        int pom=rmask;
        while(rmask>=0){

            int sumw=0;
            int mx=0;
            for(int j=0;j<ch;j++){
                if(rmask&(1<<j)){
                    sumw+=p[j].ss;
                    mx=max(mx,p[j].ff);
                }
            }

            lprek[i].pb({{sumw,mx},i^rmask});
            //printf("%d %d AAA\n",i,sumw);

            if(rmask==0)break;
            rmask--;
            rmask&=pom;
        }

        sort(lprek[i].begin(),lprek[i].end());
    }

   // printf("SZ %d\n",lprek[1].size());
}

pii dp[(1<<maxn)];
int pos[(1<<maxn)];
inline void mrg(pii &a,pii b){

    if(a.ff<b.ff)return;

    if(a.ff==b.ff){
        a.ss=add(a.ss,b.ss);
    }
    else{
        a=b;
    }

}
void go(){

    int ch=n-h;

    int inf=2e9;
    for(int i=0;i<(1<<n);i++)dp[i]={inf,0};
    dp[0]={0,1};
    for(int ah=0;ah<(1<<ch);ah++){

        for(int aub=0;aub<(1<<h);aub++){

            if(ah==0){
                int fmask=(aub|(ah<<h));
                if(fmask==0)goto nxt;
                ///printf("%d <- %d %d TO DP\n",fmask,aub,(ah<<h));
                for(int bl=0;bl<lprek[aub].size();bl++){
                    if((aub^lprek[aub][bl].ss)<lprek[aub][bl].ss)continue;
                   // printf("%d <- %d FROM\n",fmask,lprek[aub][bl].ss|(ah<<h));
                    if(aub==lprek[aub][bl].ss || lprek[aub][bl].ff.ff>W)continue;

                    pos[lprek[aub][bl].ss|(ah<<h)]=1;

                    if(pos[fmask]){
                    while(1){}

                   }
                    mrg(dp[fmask],{dp[lprek[aub][bl].ss|(ah<<h)].ff+lprek[aub][bl].ff.ss,dp[lprek[aub][bl].ss|(ah<<h)].ss});
                }
            }

            nxt:

            int pt=0;
            pii pom={2e9,0};
            for(int bh=hprek[ah].size()-1;bh>=0;bh--){

                int cost=hprek[ah][bh].ff.ss;
                int mask=(hprek[ah][bh].ss<<h);
                int pmask=(ah<<h);

                if(pmask>(mask^pmask))continue;

                while(pt<lprek[aub].size() && lprek[aub][pt].ff.ff+hprek[ah][bh].ff.ff<=W){
                   pos[pmask|(lprek[aub][pt].ss)]=1;
                    mrg(pom,dp[pmask|(lprek[aub][pt].ss)]);
                    //printf("UPD POM %d %d %d\n",pmask|(aub^lprek[aub][pt].ss),pt,lprek[aub][pt].ss);
                    pt++;
                }

               // printf("%d %d %d | %d %d TO DP %d %d %d\n",aub,pmask,mask^pmask,aub|mask,pom.ff+cost,pom.ff,pt,pom.ss);
               // printf("%d <-   DP FROM\n",aub|mask);
               /// printf("%d %d AA\n",lprek[aub].size(),lprek[aub][pt].ff.ff);
               if(pos[aub|mask]){
                while(1){}

               }
                mrg(dp[aub|mask],{pom.ff+cost,pom.ss});

            }


        }

    }

    /*for(int i=0;i<(1<<n);i++){
        printf("%d ",dp[i].ss);
    }
    printf(" DP\n");*/

}

int prekmask[(1<<maxn)];
pii dp2[(1<<maxn)];
void go2(){


    int inf=2e9;

    int pf=1000000000;
    for(int i=0;i<(1<<n);i++){
        int rmask=i;
        int sumw=0;
        int mx=0;
        for(int j=0;j<n;j++){
            if(rmask&(1<<j)){
                sumw+=p[j].ss;
                mx=max(mx,p[j].ff);
            }
        }
        if(sumw>W)prekmask[i]=pf;
        else{
            prekmask[i]=mx;
        }
    }


    for(int i=0;i<(1<<n);i++)dp2[i]={inf,0};
    dp2[0]={0,1};
    for(int i=1;i<(1<<n);i++){
        int mask=i;

        int mb=-1;
        for(int j=n-1;j>=0;j--){
            if(mask&(1<<j)){
                mb=j;
                break;
            }
        }

        while(mask>0){
            if(mask&(1<<mb)){}
            else{
                mask--;
                mask&=i;
                continue;
            }
            pii pom={dp2[i^mask].ff+prekmask[mask],dp2[i^mask].ss};
            mrg(dp2[i],pom);
            mask--;
            mask&=i;
        }
    }

    printf("%d %d\n",dp2[(1<<n)-1].ff,dp2[(1<<n)-1].ss);

}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&W);
    //if(n==22)return 10;
    for(int i=0;i<n;i++){
        scanf("%d %d",&p[i].ss,&p[i].ff);
    }
    sort(p,p+n);

    /*for(int i=0;i<n;i++){
        printf("%d %d PRINT\n",p[i].ss,p[i].ff);
    }*/

    if(n==1){
        printf("%d %d\n",p[0].ff,1);
        return 0;
    }

    h=n/2;

    prek_h();
    prek_l();

    go();
    //go2();

   /* for(int i=0;i<(1<<n);i++){
        if(dp[i]!=dp2[i])printf("%d || %d %d | %d %d diff\n",i,dp[i].ff,dp[i].ss,dp2[i].ff,dp2[i].ss);
    }*/

    printf("%d %d\n",dp[(1<<n)-1].ff,dp[(1<<n)-1].ss);


    return 0;
}
