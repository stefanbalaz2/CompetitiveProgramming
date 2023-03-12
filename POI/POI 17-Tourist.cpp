/*

    idea:

        observation: if we compress our graph into scc we and do a top sort on it
        we get an array which we can traverse from left to right

        so if we start in a node in ith scc then we can only reach nodes from jth scc where j>i
        and we can enter them from any node bcs all the edges between those two scc are directed from ith to jth
        so we can answer our queries for every starting node, and it will be the longest path from that nodes scc + longest path of the next scc etc.
        so we just have to find the longest path in every scc for a fixed starting node, and then we can answer queries
        how do we do that?
        lets try to build our path
        it is a permutation of nodes
        lets add node by node to our permutation
        we can add the node x between node i and i+1 if we have an edge i->x and edge x->i+1 or the last node in the permutation is j and we have edge j->x
        so we can see that when adding our node x to the permutation, we can add it only if there is a node i for which we have an edge i->x
        so if at any point of building the permutation we maintain the nodes which are adjacent to our permutation we can easily insert a node
        into the permutation and update the adjacent nodes, all that in O(size of the scc)
        so we just find the rightmost place where we can fit our candidate and place it there, the important part here is the fact that we are taking the rightmost
        else we would get tle, i suppose because probably we could get into some kind of a loop, or either the complexity would rise significantly
        but i didnt bother proving that stuff
        so we can add a node to our permutation in O(scc size) so to construct a permutation for a scc we need O(scc_size^2)
        how do we get all the other permutation in a scc from the given one?
        we can just erase the first element from the permutation, and then add it to the RIGHTMOST place where it can fit
        that place will definately exist because its a scc and our node which we erased will definately have a node which has an edge to it,otherwise it wouldnt be a scc
        we can repeat that process until we get every node to the first position, and memorise the permutation every time a new node gets to the first position

        i have a proof that the process of removing the first element and adding it to the rightmost place has a bound on (scc_size^3) but i
        suppose it can be proved that the upper bound can be lowered

        anyways, it passes way below the time limit

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef map<int,int>::iterator mit;
const int maxn=2010;
int pos[maxn],stek[maxn],br,col,n,taken[maxn],ind[maxn],adj[maxn][maxn],brscc,pos2[maxn];
vector<int>vect[maxn],vect2[maxn];
struct scc{

    vector<int>nodes;
    vector<vector<int> >paths;

}niz[maxn];
void go1(int x){

    pos[x]=1;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(pos[id])continue;
        go1(id);
    }

    stek[++br]=x;
}
void reverse_edges(){

    for(int i=1;i<=n;i++){
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j];
            vect2[id].pb(i);
        }
    }
}
void go2(int x){

    pos[x]=col;
    for(int i=0;i<vect2[x].size();i++){
        int id=vect2[x][i];
        if(pos[id])continue;
        go2(id);
    }
}
int find_scc(){

    for(int i=1;i<=n;i++){
        if(pos[i])continue;
        go1(i);
    }

    reverse_edges();

    memset(pos,0,sizeof(pos));
    while(br){
        if(pos[stek[br]]){br--;continue;}
        col++;
        go2(stek[br]);
        br--;
    }

    return col;
}
void ubaci(int x,vector<int> &v){
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(taken[id])continue;

        taken[id]=1;
        v.pb(id);
    }
}
void solve(int x){

    for(int i=0;i<niz[x].nodes.size();i++){
        ind[niz[x].nodes[i]]=i;
        vector<int>pom;
        niz[x].paths.pb(pom);
    }
    vector<int>available,perm;
    perm.pb(niz[x].nodes[0]);
    taken[niz[x].nodes[0]]=1;
    ubaci(niz[x].nodes[0],available);

    for(int i=1;i<niz[x].nodes.size();i++){

        int id=available.back();
        available.pop_back();

        int id2=-1;
        int c1=perm.back();
        int c2;
        if(adj[c1][id]){
            perm.pb(id);
            ubaci(id,available);
            continue;
        }
        for(int j=perm.size()-2;j>=0;j--){
            c1=perm[j];
            c2=perm[j+1];
            if(adj[c1][id] && adj[id][c2]){
                id2=j+1;
                break;
            }
        }
        perm.insert(perm.begin()+id2,id);
        ubaci(id,available);
    }

    niz[x].paths[0]=perm;


    memset(pos2,0,sizeof(pos2));
    pos2[0]=1;
    int cnt=niz[x].nodes.size()-1;
    for(int i=0;cnt;i++){
        int id=perm[0];
        perm.erase(perm.begin());

        int id2=-1;
        int c1=perm.back();
        int c2;
        if(adj[c1][id]){
            perm.pb(id);
        }
        else{
            for(int j=perm.size()-2;j>=0;j--){
                c1=perm[j];
                c2=perm[j+1];
                if(adj[c1][id] && adj[id][c2]){
                    id2=j+1;
                    break;
                }
            }
            perm.insert(perm.begin()+id2,id);
        }

        if(pos2[ind[perm[0]]]==0){

            niz[x].paths[ind[perm[0]]]=perm;
            pos2[ind[perm[0]]]=1;
            cnt--;
        }
    }
}
void split(){

    brscc=find_scc();

    for(int i=1;i<=n;i++)niz[pos[i]].nodes.pb(i);

    for(int i=1;i<=n;i++){
        vector<int>pom;
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j];
            if(pos[i]==pos[id]){
                pom.pb(id);
                adj[i][id]=1;
            }
        }
        vect[i]=pom;
    }

    for(int i=1;i<=brscc;i++)
        solve(i);
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d",&n);
    for(int i=2;i<=n;i++){

        for(int j=1;j<i;j++){
            int a;
            scanf("%d",&a);
            if(a)vect[j].pb(i);
            else vect[i].pb(j);
        }
    }

    split();

    for(int i=1;i<=n;i++){

        int cl=pos[i];

        vector<int>rez;
        for(int k=0;k<niz[cl].paths[ind[i]].size();k++)
                rez.pb(niz[cl].paths[ind[i]][k]);

        for(int j=cl+1;j<=brscc;j++){
            for(int k=0;k<niz[j].paths[0].size();k++)
                rez.pb(niz[j].paths[0][k]);
        }

        printf("%d ",rez.size());
        for(int j=0;j<rez.size();j++)printf("%d ",rez[j]);
        printf("\n");
    }

    return 0;
}
