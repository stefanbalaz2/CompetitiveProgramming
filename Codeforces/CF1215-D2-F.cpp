/*

tutorial solution: https://codeforces.com/blog/entry/69815
too much debug time because of missed corner cases and lacked attention

*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair< int,int> pii;
const int maxv=2e6;
int lim,pos[maxv],color[maxv],br,stek[maxv],clr,n,p,F,m,rezf,dep[maxv];
vector<int>vect[maxv],vect2[maxv],rez;
int neg(int x){
    if(x>lim)return x-lim;
    return x+lim;
}
void make_edge(int x,int y){
    vect[neg(x)].pb(y);
    vect[neg(y)].pb(x);
}
void ts(int x){

    pos[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        ts(id);
    }
    stek[++br]=x;
}
void reverse_edges(){

    for(int i=1;i<=2*lim;i++)
        for(int j=0;j<vect[i].size();j++)
            vect2[vect[i][j]].pb(i);

}
void go_color(int x){

    color[x]=clr;
    for(int i=0;i<vect2[x].size();i++){
        int id=vect2[x][i];
        if(color[id])continue;
        go_color(id);
    }
}
bool sat2(){

    memset(pos,0,sizeof(pos));
    br=0;
    for(int i=1;i<=lim*2;i++){
        if(pos[i])continue;
        ts(i);
    }

    reverse_edges();

    for(int i=br;i>=1;i--){
        int id=stek[i];
        if(color[id])continue;
        clr++;
        go_color(id);
    }

    for(int i=1;i<=lim;i++)
        if(color[i]==color[neg(i)])return false;

    return true;
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d %d %d",&n,&p,&F,&m);
    lim=p+F;
    for(int i=2;i<=F;i++)make_edge(neg(p+i),p+i-1);
    for(int i=1;i<=n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        make_edge(u,v);
    }
    for(int i=1;i<=p;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        if(u!=1)make_edge(p+u,neg(i));
        if(v!=F)make_edge(neg(i),neg(p+v+1));
    }
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        make_edge(neg(u),neg(v));
    }

    if(!sat2()){
        printf("-1\n");
        return 0;
    }

    for(int i=1;i<=br;i++){
        dep[stek[i]]=br-i;
    }

    for(int i=1;i<=p;i++)
        if(dep[i]>dep[neg(i)])rez.pb(i);

    rezf=F;
    for(int i=1;i<=F;i++){
        if(dep[i+p]<dep[neg(i+p)]){
            rezf=i-1;
            break;
        }
    }

    printf("%d %d\n",rez.size(),rezf);
    for(int i=0;i<rez.size();i++)printf("%d ",rez[i]);

    return 0;
}

