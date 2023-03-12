
/*

    greska je bila sto se moze dogoditi ciklus velicine 2, a njega ne mozemo
    bas na onaj nacin naci u dvosmernom grafu, pa sam morao da ostavim grane da budu jednosmerne
    i tako da nadjem cikluse

    za jednosmeran graf sam koristio vect2 u kodu


    u dvosmernom grafu smo jednu stvar jos zaboravili kod trazenja ciklusa, a to je da
    ako sam u cvor x dosao iz cvora p, onda mi ne moze biti ciklus grana koja me vodi
    nazad u p

*/
#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;

const int maxn=3e5+10;

vector<int>stek,vect[maxn],vect2[maxn];
int e,p[maxn],pos[maxn],dp[maxn][2],n,dp2[maxn][2];

void get_comp(int x,vector<int> &v){

    p[x]=1;
    v.pb(x);

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(p[id])continue;

        get_comp(id,v);
    }

}

void nadji_ciklus(int x,vector<int> &v){

    pos[x]=1;

    stek.pb(x);

    for(int i=0;i<vect2[x].size();i++){

        int id=vect2[x][i];

        if(pos[id]==2)continue;

        if(pos[id]==0)nadji_ciklus(id,v);
        else{/// pos[id]==1

            while(stek.size() && stek.back()!=id){
                v.pb(stek.back());
                pos[stek.back()]=3;
                stek.pop_back();
            }
            v.pb(id);
            pos[id]=3;

            e=1;

            return;
        }


        if(e)return;
    }
    if(e)return;
    stek.pop_back();
    pos[x]=2;
}

void dfs(int x){

    pos[x]=3;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id]==3)continue;

        dfs(id);

        dp[x][0]+=max(dp[id][0],dp[id][1]);
        dp[x][1]+=dp[id][0];
    }
    dp[x][1]++;

}

int resi_komponentu(vector<int> &v){

    vector<int>ciklus;
    stek.clear();
    e=0;
    nadji_ciklus(v[0],ciklus);


    if(ciklus.size()==0){
        /// resi stablo
        dfs(v[0]);
        return max(dp[v[0]][0],dp[v[0]][1]);
    }

    for(int i=0;i<ciklus.size();i++){
        int id=ciklus[i];
        dfs(id);
    }

    int rez=0;

    /// prvi nije uzet
    for(int i=0;i<ciklus.size();i++)dp2[i][0]=dp2[i][1]=0;

    dp2[0][0]=dp[ciklus[0]][0];
    dp2[0][1]=0;
    for(int i=1;i<ciklus.size();i++){

        int id=ciklus[i];

        dp2[i][0]=max(dp2[i-1][0],dp2[i-1][1])+dp[id][0];
        dp2[i][1]=dp2[i-1][0]+dp[id][1];
    }

    rez=max(dp2[ciklus.size()-1][1],dp2[ciklus.size()-1][0]);


    /// prvi je uzet
    for(int i=0;i<ciklus.size();i++)dp2[i][0]=dp2[i][1]=0;

    dp2[0][0]=0;
    dp2[0][1]=dp[ciklus[0]][1];
    for(int i=1;i<ciklus.size();i++){

        int id=ciklus[i];

        if(i==ciklus.size()-1){
            dp2[i][1]=0;
            dp2[i][0]=max(dp2[i-1][0],dp2[i-1][1])+dp[id][0];
        }
        else{
            dp2[i][0]=max(dp2[i-1][0],dp2[i-1][1])+dp[id][0];
            dp2[i][1]=dp2[i-1][0]+dp[id][1];
        }
    }

    rez=max(rez,dp2[ciklus.size()-1][0]);


    return rez;
}


int main(){

   /// freopen("10.in","r",stdin);


   scanf("%d",&n);
   for(int i=1;i<=n;i++){
    int a;
    scanf("%d",&a);
    if(a==-1)continue;

    vect[i].pb(a);
    vect[a].pb(i);

    vect2[i].pb(a);
   }

    int rez=0;

    for(int i=1;i<=n;i++){
        if(p[i])continue;

        vector<int>cvorovi_komponente;
        get_comp(i,cvorovi_komponente);

        int pom=resi_komponentu(cvorovi_komponente);
        rez+=pom;

    }

    printf("%d\n",rez);

   /* freopen("10.out","r",stdin);
    int p;
    scanf("%d",&p);
    printf("%d\n",p);*/

   return 0;
}
