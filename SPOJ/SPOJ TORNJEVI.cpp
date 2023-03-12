/*

    idea: https://www.youtube.com/watch?v=yF-iVaouEwg
*/
#include<bits/stdc++.h>
#define pb push_back
#define ll long long
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
const int maxn=110;
int dx[4]={0,0,-1,1};/// levo desno
int dy[4]={-1,1,0,0};/// gore dole
int col;
vector<int>vect[maxn*maxn*4],rev[maxn*maxn*4],stek;
vector<pii>et[maxn*maxn*4],towers,enemy;
int n,m,a[maxn][maxn],t[maxn][maxn],ts[maxn*maxn*4],e[maxn][maxn],pos[maxn*maxn*4],br,rez[maxn*maxn*4];

void make_edge(int x,int xx,int y,int yy){

    x=x*4+xx;
    y=y*4+yy;
    int negx=(x^1);
    int negy=(y^1);

    vect[negx].pb(y);
    vect[negy].pb(x);

    rev[y].pb(negx);
    rev[x].pb(negy);
}
int go(int x,int y,int dir,int t){
    if(x<1 || x>n || y<1 || y>m)return 1;
    if(a[x][y]==3)return 1;
    if(a[x][y]==2)return 0;
    int ret=go(x+dx[dir],y+dy[dir],dir,t);
    if(ret==1 && a[x][y]==1){
        et[e[x][y]].pb({t,dir});
    }

    return ret;
}
void dfs(int x){


    pos[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;

        dfs(id);
    }

    stek.pb(x);
}
void dfs2(int x){

    ts[x]=col;
    for(int i=0;i<rev[x].size();i++){
        int id=rev[x][i];
        if(ts[id])continue;
        dfs2(id);
    }

}
void sat(){

    for(int i=0;i<towers.size()*4;i++){
        if(pos[i]!=0)continue;
        dfs(i);
    }

    while(stek.size()){
        int i=stek.back();
        stek.pop_back();
        if(ts[i]!=0)continue;
        col++;
        dfs2(i);
    }


    for(int i=0;i<towers.size()*4;i+=2){
        if(ts[i]>ts[i^1])rez[i]=1,rez[i^1]=0;
        else rez[i]=0,rez[i^1]=1;

    }

}

int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d",&n,&m);

    for(int i=1;i<=n;i++){

        string s;
        cin>>s;


        for(int j=1;j<=m;j++){
            if(s[j-1]=='.')a[i][j]=0;
            if(s[j-1]=='n'){
                a[i][j]=1;
                e[i][j]=enemy.size();
                enemy.pb({i,j});
            }
            if(s[j-1]=='T'){
                a[i][j]=2;
                t[i][j]=towers.size();
                towers.pb({i,j});
            }
            if(s[j-1]=='#')a[i][j]=3;

        }

    }

    for(int i=0;i<towers.size();i++){

        for(int j=0;j<4;j+=2){

            int a=go(towers[i].ff+dx[j],towers[i].ss+dy[j],j,i);
            int b=go(towers[i].ff+dx[j+1],towers[i].ss+dy[j+1],j+1,i);


            if(a^b){

                if(a==1)make_edge(i,j,i,j);
                else make_edge(i,j+1,i,j+1);
            }

        }
    }

    for(int i=0;i<enemy.size();i++){

        if(et[i].size()==1){
            make_edge(et[i][0].ff,et[i][0].ss,et[i][0].ff,et[i][0].ss);
        }
        else{
            make_edge(et[i][0].ff,et[i][0].ss,et[i][1].ff,et[i][1].ss);
        }
    }


    sat();


    for(int i=1;i<=n;i++){

        for(int j=1;j<=m;j++){

            if(a[i][j]==0)printf(".");
            if(a[i][j]==1)printf("n");
            if(a[i][j]==3)printf("#");
            if(a[i][j]==2){

                int pom=t[i][j];
                pom*=4;

                if(rez[pom] && rez[pom+2])printf("4");/// levo gore
                if(rez[pom] && rez[pom+3])printf("1");/// levo dole
                if(rez[pom+1] && rez[pom+2])printf("3");/// desno gore
                if(rez[pom+1] && rez[pom+3])printf("2");/// desno dole

            }


        }
        printf("\n");

    }


return 0;
}
