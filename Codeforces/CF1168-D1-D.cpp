/*

    idea:https://codeforces.com/blog/entry/67241

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef pair<int,char> pic;
const int maxn=150010;
const int alp=27;
int n,moze[maxn],cnt[maxn][alp],q,pc[maxn],nxt[maxn],len[maxn],sum[maxn];
int p[maxn],pe[maxn][alp];
vector<pii>vect[maxn];
void build(int x){

    int g[2][27];
    memset(g,0,sizeof(g));
    moze[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;

        build(id);
        moze[x]&=moze[id];

        for(int j=0;j<alp;j++)g[1][j]=cnt[id][j]+pe[id][j];
        for(int j=0;j<alp;j++)g[0][j]=max(g[0][j],g[1][j]);
        len[x]=len[id];
        for(int j=0;j<alp;j++)len[x]+=pe[id][j];
    }

    for(int j=0;j<alp;j++){
        cnt[x][j]=g[0][j];
        if(j<alp-1)sum[x]+=cnt[x][j];
    }

}
void update(int x,int c){

    if(c==26)return;

    while(1){

        moze[x]=1;
        int pv=cnt[x][c];
        cnt[x][c]=0;
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i].ff;

            moze[x]&=moze[id];
            cnt[x][c]=max(cnt[x][c],pe[id][c]+cnt[id][c]);
        }
        sum[x]+=(cnt[x][c]-pv);

        if(sum[x]>len[x])moze[x]=0;

        if(x==1)return;
        x=p[x];
    }

}
int compress(int x,int prv){

    p[x]=prv;
    if(vect[x].size()==2 || x==1)prv=x;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        int c=vect[x][i].ss;

        nxt[x]=compress(id,prv);

        vect[x][i].ff=nxt[x];
        pe[nxt[x]][c]++;
    }

    if(vect[x].size()==2 || vect[x].size()==0)nxt[x]=x;

    if(vect[x].size()==2 || vect[x].size()==0)return x;
    else return nxt[x];
}
int suma(int g[]){
    int ret=0;
    for(int i=0;i<alp-1;i++)ret+=g[i];
    return ret;
}
bool eq(int x,int curr,int len){

    int e=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;

        e&=eq(id,curr+suma(pe[id]),len);
    }
    return e;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&q);

    for(int i=2;i<=n;i++){
        char c;
        scanf("%d %c",&p[i],&c);
        if(c=='?')c=26;
        else c-='a';
        pc[i]=c;
        vect[p[i]].pb({i,c});
    }

    compress(1,0);
    build(1);

    if(!eq(1,0,len[1])){
        for(int i=1;i<=q;i++)printf("Fou\n");
        return 0;
    }


    for(int i=1;i<=q;i++){
        int v;
        char c;
        scanf("%d %c",&v,&c);
        if(c=='?')c=26;
        else c-='a';

        int c2=pc[v];
        pc[v]=c;

        v=nxt[v];

        pe[v][c2]--;
        pe[v][c]++;

        update(p[v],c2);
        update(p[v],c);


        if(moze[1]){
            printf("Shi ");
            int ret=0;
            for(int j=0;j<alp-1;j++)
                ret+=(j+1)*(cnt[1][j]+(len[1]-sum[1]));

            printf("%d\n",ret);
        }
        else printf("Fou\n");

    }

    return 0;
}
