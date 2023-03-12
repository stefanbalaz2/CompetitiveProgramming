/*

    https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2014/editorial/sup.pdf

*/
#include<bits/stdc++.h>
#define ll long long
#define ss second
#define ff first
#define pb push_back
using namespace std;
using namespace std::chrono;
typedef pair<int,int> pii;
const int maxn=1e6+10;
const int mb=15000000;
clock_t start,now;
int n,q,k[maxn],dubina,cnt[maxn],f[maxn],sol,rez[maxn],pos[maxn],velicina[maxn],ptr,ops;
char buffer[mb];
vector<pii>vect2[maxn];
vector<int>vect[maxn];
void prek(int x,int dep){

    dubina=max(dubina,dep);
    cnt[dep]++;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];

        prek(id,dep+1);
    }

}
int get_num(){

    while(buffer[ptr]<'0' || buffer[ptr]>'9')ptr++;
    int ret=0;
    while(buffer[ptr]>='0' && buffer[ptr]<='9'){
        ret*=10;
        ret+=buffer[ptr]-48;
        ptr++;
    }
    return ret;
}
int main(){


    fread(buffer,1,mb-500000,stdin);

    n=get_num();
    q=get_num();

    for(int i=1;i<=q;i++){
        k[i]=get_num();
    }

    for(int i=2;i<=n;i++){
        int a;
        a=get_num();
        vect[a].pb(i);
    }
    prek(1,1);

    for(int i=1;i<=dubina;i++){
        f[i]=cnt[i];
        vect2[f[i]].pb({i,1});
        velicina[i]=1;
    }


    sol=dubina;

    for(int i=n-1;i>1;i--){

        sort(vect2[i+1].begin(),vect2[i+1].end());
        for(int j=0;j<vect2[i+1].size();j++){


            pii pom=vect2[i+1][j];

            int id=pom.ff;
            if(pos[id])continue;
            int delta=pom.ss;

            int curr=id+delta;

            while(delta){

                ops++;

                if(f[curr]<=i){

                    int diff=i-f[curr];

                    if(delta>=diff){
                        delta-=diff;
                        pos[curr]=1;
                        pom.ss++;
                        curr++;

                        if(delta==0)curr--;
                    }
                    else{
                        f[curr]+=delta;
                        velicina[curr]=1;
                        delta=0;
                    }

                }
                else{

                    int vel=velicina[curr];

                    delta+=vel;
                    pom.ss+=vel;
                    pos[curr]=1;
                    curr+=vel;

                }

            }

            velicina[id]=pom.ss;
            vect2[i].pb(pom);

            sol=max(sol,curr);
        }

        rez[i]=sol;
    }



    for(int i=1;i<=q;i++){
        if(k[i]==1){
            printf("%d ",n);
            continue;
        }
        printf("%d ",(rez[k[i]]==0)?dubina:rez[k[i]]);
    }

    return 0;
}
