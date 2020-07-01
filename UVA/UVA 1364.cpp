/*

    idea:

        - the actual task is to find for every i whether it belongs to a simple odd cycle in the complement graph
        - i tried to tweak the trick that is used to check whether a node is in a component which contains an odd cycle
        - the trick goes like this: - we clone every node i into node i+n
                                    - then for each edge (u,v) we make (u+n,v) and (u,v+n)
                                    - if the node i is in the same component as i+n then the node i is in the component with an odd cycle
        - so how to tweak it?
        - the idea was to check whether i and i+n are in the same biconnected component because we will definately have a simple odd cycle including them,
         but that fails to an original graph like this: https://github.com/stefanbalaz2/CompetitiveProgramming/blob/master/UVA/QrjIHG5.png
        - but no worries, if we split the original graph into biconnected components, and solve the same thing for every biconnected component of the
         original graph, then it works, because when everything is a cycle, only way that i and i+n could be connected is if there is an simple odd cycle
         in the biconnected component

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e3+10;
const int maxm=1e6+10;
bool adj[maxn][maxn];
int n,m,disc[maxn*2],low[maxn*2],tim,br,pos[maxn*2],rz[maxn];
int disc2[maxn*2],low2[maxn*2],pos2[maxn*2],br2;
pii stek[maxm],stek2[maxm];
vector<int>vect[maxn*2],vect2[maxn*2];

void go2(int x,int prv){

    disc2[x]=++tim;
    low2[x]=tim;

    for(int i=0;i<vect2[x].size();i++){
        int id=vect2[x][i];
        if(id==prv)continue;

        if(disc2[id]){
            low2[x]=min(low2[x],disc2[id]);
            if(disc2[id]<disc2[x])stek2[++br2]={x,id};
        }
        else{
            stek2[++br2]={x,id};
            go2(id,x);

            low2[x]=min(low2[x],low2[id]);

            if(low2[id]>=disc2[x]){

                for(int j=br2;;j--){
                    pos2[stek2[j].ff]=1;
                    pos2[stek2[j].ss]=1;

                    int ind=stek2[j].ff;
                    if(ind>n)ind-=n;
                    if(pos2[ind] && pos2[ind+n])rz[ind]=1;

                    ind=stek2[j].ss;
                    if(ind>n)ind-=n;
                    if(pos2[ind] && pos2[ind+n])rz[ind]=1;

                    if(stek2[j]==(pii){x,id})break;
                }

                for(int j=br2;;j--){
                    pos2[stek2[j].ff]=0;
                    pos2[stek2[j].ss]=0;

                    if(stek2[j]==(pii){x,id}){
                        br2=j-1;
                        break;
                    }
                }

            }
        }

    }

}

void radi(vector<pii> &vect){

    set<int>st;

    for(int i=0;i<vect.size();i++){
        int id=vect[i].ff;
        vect2[id].clear();
        vect2[id+n].clear();

        id=vect[i].ss;
        vect2[id].clear();
        vect2[id+n].clear();
    }

    for(int i=0;i<vect.size();i++){
        int id=vect[i].ff;
        disc2[id]=0;
        low2[id]=0;
        pos2[id]=0;
        disc2[id+n]=0;
        low2[id+n]=0;
        pos2[id+n]=0;
        st.insert(id);
        st.insert(id+n);

        id=vect[i].ss;
        disc2[id]=0;
        low2[id]=0;
        pos2[id]=0;
        disc2[id+n]=0;
        low2[id+n]=0;
        pos2[id+n]=0;
        st.insert(id);
        st.insert(id+n);


        vect2[vect[i].ff].pb(id+n);
        vect2[id+n].pb(vect[i].ff);

        vect2[vect[i].ff+n].pb(id);
        vect2[id].pb(vect[i].ff+n);
    }

    for(set<int>::iterator it=st.begin();it!=st.end();it++){
        int id=(*it);
        if(disc2[id])continue;

        go2(id,0);
    }

}

void go(int x,int prv){

    disc[x]=++tim;
    low[x]=tim;

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        if(id==prv)continue;

        if(disc[id]==0){
            stek[++br]={x,id};
            go(id,x);

            low[x]=min(low[x],low[id]);

            if(low[id]>=disc[x]){

                vector<pii>v;
                while(br){
                    if(stek[br]==(pii){x,id}){
                        v.pb(stek[br]);
                        br--;
                        break;
                    }
                    else v.pb(stek[br--]);
                }

                radi(v);
            }

        }
        else{
            low[x]=min(low[x],disc[id]);
            if(disc[x]>disc[id])stek[++br]={x,id};
        }

    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    while(1){

        memset(adj,0,sizeof(adj));
        memset(disc,0,sizeof(disc));
        memset(low,0,sizeof(low));
        memset(rz,0,sizeof(rz));

        scanf("%d %d",&n,&m);

        for(int i=1;i<=n*2;i++)vect[i].clear();

        if(n==0 && m==0)break;
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            adj[u][v]=1;
            adj[v][u]=1;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<i;j++){
                if(adj[i][j]==1)continue;
                if(i==j)continue;

                vect[i].pb(j);
                vect[j].pb(i);
            }
        }


        for(int i=1;i<=n;i++){
            if(disc[i])continue;

            go(i,0);
        }


        int rez=n;
        for(int i=1;i<=n;i++)
            if(rz[i])rez--;


        printf("%d\n",rez);
    }

	return 0;
}
