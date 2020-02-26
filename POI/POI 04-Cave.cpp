/*

    idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2004/editorial/jas.pdf
    
    clarification: "choosing a node" means choosing a node which splits the graph into subtrees of its children
    which narrows down our search
    
    the implemetation is the same as the editorial, but i didnt see a point guessing a random function like they did
    so i tried to find an intuitive exlpanation for what is actually happening in the editorial
    
    look at it like this, we will root the tree in any node(its not important what is the root), and then we will do a dfs
    on the tree, and solve the problem for every nodes subtree
    
    lets say that you are currently in node U trying to solve its subtree, and for some child of U lets inspect what 
    we are keeping, for every solution J(number of moves needed to solve its subgraph, i will explain later what i mean by subgraph)
    we are keeping the number of nodes which solve their subgraph in J moves(these numbers will be <=1 always for a node)
    
    now ill explain what i mean by "nodes subgraph"
    imagine that when solving a subtree of U it can be solved in K moves, so we have a node that if we choose it as the first one
    we can solve the pieces that remain in K-1, lets choose such a vertex that it is the highest in the subtree of U, meaning,
    such vertex that choosing it first we can solve the remaining pieces in K-1 moves and that means that if we move our "starting node"
    up the result for the subtree of U would increase to K+1 (which of course we dont want to)
    lets call that node P,this makes the nodes below P irrelevant, and they will not be included in any more calculations(you will
    see why soon)
    for our node P, node P`s subgraph is the whole subtree U
    lets observe the subgraph made as a (subtree of U without subtree of P), we will call it T, 
    those are all nodes of subtree U that are above P
    when "choosing" the P, the subtree of U splits into pieces, on of them being T
    so we can observe that we have the same stuff for T that we had for our subtree of U, we will have a node that if "chosen"
    first,we need Q moves to clear T, and as that node is the highest in T with such property(that it needs Q moves), the nodes in T
    which are below it become irrelevant(the same stuff as with P happen), so then we are again left with 
    (subgraph T without the subtree of T`s "starting node")
    the process repeats until we are left with 1 node which is trivial
    
    
    
*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
const int maxn=5e4;
vector<int>val[maxn],vect[maxn];
int dp[maxn],n;
void go(int x,int prv){

    for(int i=1;i<=25;i++)val[x].pb(0);

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];
        if(id==prv)continue;

        go(id,x);

        for(int j=0;j<val[x].size();j++)val[x][j]+=val[id][j];
    }

    int p=val[x].size()-1;
    while(p>=0 && val[x][p]<2)p--;
    p++;

    while(val[x][p]>0)p++;

    dp[x]=p;

    val[x][p]=1;
    p--;
    while(p>=0)val[x][p--]=0;
}
int main(){

    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }

    go(1,0);

    int rez=0;
    for(int i=1;i<=n;i++)
        rez=max(rez,dp[i]);

    printf("%d\n",rez);

return 0;
}
