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
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
const int maxn=1e5+10;
char dir[4]={'R','L','D','U'};
vector<vector<int> >a,ind,nxt;
pii rh[maxn];
vector<int>vect[maxn],pos_undo;
int nxt2[maxn],pos[maxn],n,m,mt[maxn],cnt,r;
bool outside(int x,int y){
    if(x>n || x<1 || y>m || y<1)return true;
    return false;
}
void add_edge(int x,int y){
    vect[x].pb(y);
    vect[y].pb(x);
}
bool srt(int x,int y){
    return nxt2[x]<nxt2[y];
}
int kuhn(int x,int tip){
    if(pos[x])return 0;
    pos[x]=1;
    pos_undo.pb(x);

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(tip==1 && nxt2[id]==1)break;

        if(mt[id]==-1 || kuhn(mt[id],tip)){
            mt[id]=x;
            mt[x]=id;
            return 1;
        }
    }
    return 0;
}
void random_matching(){

    for(int i=1;i<=cnt;i++){
        if(mt[i]!=-1)continue;
        if(nxt2[i]!=0)continue;
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j];
            if(mt[id]!=-1)continue;
            if(nxt2[id]!=0)continue;
            mt[i]=id;
            mt[id]=i;
            r-=2;
            break;
        }
    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d %d",&n,&m);
        a.clear();
        nxt.clear();
        ind.clear();
        a.resize(n+2,vector<int>(m+2));
        nxt.resize(n+2,vector<int>(m+2));
        ind.resize(n+2,vector<int>(m+2));

        cnt=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                scanf("%d",&a[i][j]);
                nxt[i][j]=-1;
                nxt2[cnt]=0;
                ind[i][j]=++cnt;
                rh[cnt]={i,j};
                mt[cnt]=-1;
                vect[cnt].clear();
            }

        int fucked=0;

        r=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++){
                int e=0;
                for(int k=0;k<4;k++){
                    int idx=i+dx[k];
                    int idy=j+dy[k];
                    if(outside(idx,idy))continue;

                    if(a[idx][idy]<a[i][j]){
                        nxt[i][j]=k;
                        nxt2[ind[i][j]]=1;
                    }
                    else if(a[idx][idy]==a[i][j]){
                        e=1;
                        if((i+j)%2)add_edge(ind[i][j],ind[idx][idy]);
                    }
                }

                if(e==0 && nxt[i][j]==-1)fucked=1;

                if(nxt[i][j]==-1)r++;
            }

        if(fucked){
            printf("NO\n");
            continue;
        }

        for(int i=1;i<=cnt;i++)
            sort(vect[i].begin(),vect[i].end(),srt);

        random_matching();

        /// phase 1
        for(int i=1;i<=cnt;i++){
            if(nxt[rh[i].ff][rh[i].ss]!=-1 || mt[i]!=-1)continue;
            if(kuhn(i,1))r-=2;
            for(int j=0;j<pos_undo.size();j++)pos[pos_undo[j]]=0;
            pos_undo.clear();
        }

        /// phase 2
        for(int i=1;i<=cnt;i++){
            if(nxt[rh[i].ff][rh[i].ss]!=-1 || mt[i]!=-1)continue;
            if(kuhn(i,0))r-=1;
            for(int j=0;j<pos_undo.size();j++)pos[pos_undo[j]]=0;
            pos_undo.clear();
        }


        if(r>0){
            printf("NO\n");
            continue;
        }

        printf("YES\n");
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){

                if(mt[ind[i][j]]!=-1){
                    if((i+j)%2)printf("%d ",a[i][j]/2+(a[i][j]%2));
                    else printf("%d ",a[i][j]/2);
                }
                else{
                    printf("%d ",a[i][j]-a[i+dx[nxt[i][j]]][j+dy[nxt[i][j]]]);
                }

            }
            printf("\n");
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){

                if(mt[ind[i][j]]!=-1){

                    for(int k=0;k<4;k++){
                        int idx=i+dx[k];
                        int idy=j+dy[k];
                        if(ind[idx][idy]==mt[ind[i][j]]){
                            printf("%c ",dir[k]);
                            break;
                        }
                    }

                }
                else{
                    printf("%c ",dir[nxt[i][j]]);
                }

            }
            printf("\n");
        }

    }

    return 0;
}
