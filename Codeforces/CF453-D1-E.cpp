#include<bits/stdc++.h>
#define ff first
#define ss second
#define ll long long
#define pb push_back
using namespace std;
const int maxn=1e5+10;
const int bsize=120;
int blp[maxn/bsize+10],brp[maxn/bsize+10],pos[2][maxn],isReset[maxn/bsize],n,br,bid[maxn],q;
int rt[maxn],m[maxn],s[maxn],re[maxn],regen[2][maxn],sum[2][maxn],maxx[2][maxn],lasttime[maxn/bsize+10],inf=1e9;
bool srt(int x,int y){
    return rt[x]>rt[y];
}
void recalc(int i,int t){

    for(int j=blp[i];j<=brp[i];j++){
        if(re[j]==0)rt[j]=inf;
        else rt[j]=(m[j]-s[j])/re[j]+((m[j]-s[j])%re[j]>0);
    }
    sort(pos[0]+blp[i],pos[0]+brp[i]+1,srt);

    regen[0][blp[i]]=re[pos[0][blp[i]]];
    sum[0][blp[i]]=s[pos[0][blp[i]]];
    for(int j=blp[i]+1;j<=brp[i];j++){
        sum[0][j]=sum[0][j-1]+s[pos[0][j]];
        regen[0][j]=regen[0][j-1]+re[pos[0][j]];
    }

    maxx[0][brp[i]]=m[pos[0][brp[i]]];
    for(int j=brp[i]-1;j>=blp[i];j--){
        maxx[0][j]=maxx[0][j+1]+m[pos[0][j]];
    }

    lasttime[i]=t;
    isReset[i]=0;
}
void build(){

    int l=1;
    int r=bsize;
    while(1){

        if(r>n)r=n;
        if(l>n)break;

        blp[++br]=l;
        brp[br]=r;

        l+=bsize;
        r+=bsize;
    }


    for(int i=1;i<=br;i++){

        for(int j=blp[i];j<=brp[i];j++){
            pos[1][j]=j;
            pos[0][j]=j;
            bid[j]=i;
        }

        /// solve init
        for(int j=blp[i];j<=brp[i];j++){
            if(re[j]==0)rt[j]=inf;
            else rt[j]=m[j]/re[j]+(m[j]%re[j]>0);
        }
        sort(pos[1]+blp[i],pos[1]+brp[i]+1,srt);

        regen[1][blp[i]]=re[pos[1][blp[i]]];
        sum[1][blp[i]]=0;
        for(int j=blp[i]+1;j<=brp[i];j++){
            sum[1][j]=0;
            regen[1][j]=regen[1][j-1]+re[pos[1][j]];
        }

        maxx[1][brp[i]]=m[pos[1][brp[i]]];
        for(int j=brp[i]-1;j>=blp[i];j--){
            maxx[1][j]=maxx[1][j+1]+m[pos[1][j]];
        }

        recalc(i,0);
    }

}
ll update_part(int i,int l,int r,ll t){

    int ws=isReset[i];
    ll ret=0;
    for(int j=blp[i];j<=brp[i];j++){

        if(ws)s[pos[ws][j]]=0;
        ll poms=s[pos[ws][j]];
        poms+=((ll)t-lasttime[i])*(ll)re[pos[ws][j]];
        poms=min(poms,(ll)m[pos[ws][j]]);
        s[pos[ws][j]]=(int)poms;

        if(pos[ws][j]>=l && pos[ws][j]<=r){
            ret+=s[pos[ws][j]];
            s[pos[ws][j]]=0;
        }
    }

    recalc(i,t);

    return ret;
}
ll update_whole(int i,int t){

    ll ret=0;

    int l=blp[i];
    int r=brp[i];
    int sr,rid=brp[i]+1;
    int ws=isReset[i];
    while(l<=r){
        sr=(l+r)/2;

        int pid=pos[ws][sr];
        ll poms=s[pid];
        if(ws)poms=0;
        poms+=((ll)t-lasttime[i])*(ll)re[pid];

        if(poms>=(ll)m[pid] && re[pid]>0){
            rid=sr;
            r=sr-1;
        }
        else l=sr+1;
    }

    if(rid<=brp[i])ret+=(ll)maxx[ws][rid];
    if(rid-1>=blp[i])ret+=(ll)sum[ws][rid-1]+(ll)regen[ws][rid-1]*((ll)t-lasttime[i]);

    /*int lp=pos[ws][blp[i]];
    int rp=pos[ws][brp[i]];
    if(ret==107)printf("%lld %lld | ws= %d  rid= %d | s= %lld %lld | m= %lld %lld | re= %lld %lld | time= %lld %lld RETRET\n",ret,ret,ws,rid,s[lp],s[rp],m[lp],m[rp],re[lp],re[rp],t,lasttime[i]);
    ll ret2=update_part(i,blp[i],brp[i],t);*/


    isReset[i]=1;
    lasttime[i]=t;

    return ret;
}
ll query(int l,int r,int t){

    if(bid[l]==bid[r])return update_part(bid[l],l,r,t);

    ll ret=0;
    ret+=update_part(bid[l],l,brp[bid[l]],t);
    ret+=update_part(bid[r],blp[bid[r]],r,t);

    for(int i=bid[l]+1;i<bid[r];i++)
        ret+=update_whole(i,t);

    return ret;
}
int main(){

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d %d %d",&s[i],&m[i],&re[i]);
    }
    build();

    scanf("%d",&q);
    ///q=min(q,80000);
    while(q--){

        int l,r,t;
        scanf("%d %d %d",&t,&l,&r);

        printf("%lld\n",query(l,r,t));

    }


return 0;
}
