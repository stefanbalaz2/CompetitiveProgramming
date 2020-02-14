/*

    idea : https://github.com/dolphingarlic/CompetitiveProgramming/blob/master/APIO/APIO%2017-rainbow.cpp

*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
const int maxseg=9*1e5*25;
int tree[maxseg],lc[maxseg],rc[maxseg];
int cnt=1,minr,maxr,minc,maxc;
struct segtree{

    int root[maxn+10];
    set<int>ind[maxn+10];

    void add(int x,int y){
        ind[x].insert(y);
    }

    void build(){

        for(int i=1;i<=maxn;i++){
            root[i]=root[i-1];
            for(set<int>::iterator it=ind[i].begin();it!=ind[i].end();it++)update(root[i],1,maxn,*it);
        }
    }

    void update(int &x,int l,int r,int id){

        tree[cnt]=tree[x]+1;
        lc[cnt]=lc[x];
        rc[cnt]=rc[x];
        x=cnt++;

        if(l==r)return;

        int mid=(l+r)/2;
        if(id<=mid)update(lc[x],l,mid,id);
        else update(rc[x],mid+1,r,id);
    }

    int query(int u,int d,int l,int r){
        return query(root[d],1,maxn,l,r)-query(root[u-1],1,maxn,l,r);
    }
    int query(int x,int l,int r,int ll,int rr){
        if(l>rr || r<ll)return 0;
        if(l>=ll && r<=rr)return tree[x];
        int mid=(l+r)/2;
        return query(lc[x],l,mid,ll,rr)+query(rc[x],mid+1,r,ll,rr);
    }

}river,horiz_edges,vert_edges,vert;
void add_river(int x,int y){

    vert.add(x,y);
    vert.add(x,y+1);
    vert.add(x+1,y);
    vert.add(x+1,y+1);

    horiz_edges.add(x,y);
    horiz_edges.add(x+1,y);

    vert_edges.add(x,y);
    vert_edges.add(x,y+1);

    river.add(x,y);
}
void init(int R, int C, int sr, int sc, int M, char *S) {

    add_river(sr,sc);
    minr=maxr=sr;
    minc=maxc=sc;
    for(int i=0;i<M;i++){

        if(S[i]=='N')sr--;
        if(S[i]=='S')sr++;
        if(S[i]=='E')sc++;
        if(S[i]=='W')sc--;

        add_river(sr,sc);

        minr=min(minr,sr);
        maxr=max(maxr,sr);
        minc=min(minc,sc);
        maxc=max(maxc,sc);
    }

    river.build();
    horiz_edges.build();
    vert_edges.build();
    vert.build();

}

int colour(int ar, int ac, int br, int bc) {

    /// F = E - N + C - R

    int E = horiz_edges.query(ar+1,br,ac,bc) + vert_edges.query(ar,br,ac+1,bc);
    int N = vert.query(ar+1,br,ac+1,bc);
    int C = ((minr>ar && minc>ac && maxr<br && maxc<bc)?2:1);
    int R = river.query(ar,br,ac,bc);

    return E-N+C-R;
}
