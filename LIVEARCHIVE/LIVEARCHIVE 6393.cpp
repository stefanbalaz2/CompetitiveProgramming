/*

    idea: unbound is equivalent to having a cycle
          find a cycle with a bit smarter implementation than the
          straightforward to evade a big complexity

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxn=4e4+10;
struct bond{
    int t,p,ind;
}a[maxn][4];
int e,pos2[maxn][4],pos[maxn][4],n;
vector<pii>cand[50][4];
void go(int x,int y){

    if(e)return;
    int tt=a[x][y].t;
    int pp=(a[x][y].p^1);

    pos2[x][y]=2;

    if(pos[tt][pp]>0){
        e=1;
        return;
    }

    while(cand[tt][pp].size()){

        int id1=cand[tt][pp].back().ff;
        int id2=cand[tt][pp].back().ss;
        cand[tt][pp].pop_back();

        if(pos2[id1][id2]==2){
            e=1;
            return;
        }

        pos[tt][pp]++;

        go(id1,id2);
        pos[tt][pp]--;
        if(e)return;


    }

    pos2[x][y]=1;

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    while(scanf("%d",&n)==1){

        for(int i=0;i<='Z'-'A';i++)
            for(int j=0;j<=1;j++)cand[i][j].clear();

        memset(pos,0,sizeof(pos));
        memset(pos2,0,sizeof(pos2));
        for(int i=1;i<=n;i++){
            string s;
            cin>>s;

            for(int j=0;j<8;j+=2){
                if(s[j]=='0')a[i][j/2]={-1,0,i};
                else a[i][j/2]={s[j]-'A',s[j+1]=='+'?1:0,i};
            }

            for(int j=0;j<4;j++){

                if(a[i][j].t==-1)continue;

                for(int k=0;k<4;k++){
                    if(k==j)continue;
                    if(a[i][k].t==-1)continue;

                    cand[a[i][j].t][a[i][j].p].pb({i,k});
                }

            }
        }


        e=0;
        for(int i=0;i<='Z'-'A';i++){
            for(int j=0;j<2;j++){
                while(cand[i][j].size()){
                    int id1=cand[i][j].back().ff;
                    int id2=cand[i][j].back().ss;
                    cand[i][j].pop_back();

                    pos[i][j]++;
                    go(id1,id2);
                    pos[i][j]--;
                }
            }
        }

        if(e)printf("unbounded\n");
        else printf("bounded\n");


    }

    return 0;
}
