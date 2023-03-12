/*

    idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/IOI-09-salesman.txt

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
///#define ll long long
typedef pair<int,int> pii;
const int maxtree=1300000;
const int maxn=500001;
const int inf=INT_MAX-10000000;
int n,s,u,d;
int tree[maxtree],tree2[maxtree],lazy[maxtree],lazy2[maxtree];
vector<pii>vect[maxn+10];
int dist(int x,int y){
    return y-x+1;
}
void build(int x,int l,int r){

    if(l==r){
        if(l==s)tree[x]=-l*d;
        else tree[x]=-inf;

        if(l==s)tree2[x]=-dist(l,maxn)*u;
        else tree2[x]=-inf;

        return;
    }
    int mid=(l+r)/2;

    build(x*2,l,mid);
    build(x*2+1,mid+1,r);

    tree[x]=max(tree[x*2],tree[x*2+1]);
    tree2[x]=max(tree2[x*2],tree2[x*2+1]);
}
void push(int x,int tree1[],int lazy1[]){
    if(lazy1[x]==0)return;

    tree1[x*2]+=lazy1[x];
    lazy1[x*2]+=lazy1[x];

    tree1[x*2+1]+=lazy1[x];
    lazy1[x*2+1]+=lazy1[x];

    lazy1[x]=0;
}
void update(int x,int l,int r,int ll,int rr,int val,int tree1[],int lazy1[],int tip){
    if(l>rr || r<ll)return;
    if(l>=ll && r<=rr){
        if(tip==0){
            tree1[x]=val;
            return;
        }
        else{
            tree1[x]+=val;
            lazy1[x]+=val;
            return;
        }
    }

    int mid=(l+r)/2;
    push(x,tree1,lazy1);

    update(x*2,l,mid,ll,rr,val,tree1,lazy1,tip);
    update(x*2+1,mid+1,r,ll,rr,val,tree1,lazy1,tip);

    tree1[x]=max(tree1[x*2],tree1[x*2+1]);
}
int query(int x,int l,int r,int ll,int rr,int tree1[],int lazy1[]){
    if(l>rr || r<ll)return -inf;
    if(l>=ll && r<=rr)return tree1[x];
    int mid=(l+r)/2;
    push(x,tree1,lazy1);
    return max(query(x*2,l,mid,ll,rr,tree1,lazy1),query(x*2+1,mid+1,r,ll,rr,tree1,lazy1));
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d %d %d",&n,&u,&d,&s);
    u=-u;
    d=-d;

    build(1,1,maxn);

    for(int i=1;i<=n;i++){
        int t,l,k;
        scanf("%d %d %d",&t,&l,&k);
        vect[t].pb({l,k});
    }

    for(int i=1;i<=maxn;i++){
        sort(vect[i].begin(),vect[i].end());

        pii niz[vect[i].size()];
        int niz2[vect[i].size()];
        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j].ff;

            niz[j].ff=query(1,1,maxn,1,id,tree,lazy)+d*id;
            niz[j].ss=query(1,1,maxn,id,maxn,tree2,lazy2)+u*dist(id,maxn);
        }

        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j].ff;

            int pom=query(1,1,maxn,1,id,tree,lazy);
            pom=max(pom+d*id,niz[j].ss);
            niz2[j]=pom+vect[i][j].ss;

            update(1,1,maxn,id,id,pom-d*id,tree,lazy,0);
            update(1,1,maxn,1,id,vect[i][j].ss,tree,lazy,1);
        }
        for(int j=vect[i].size()-1;j>=0;j--){
            int id=vect[i][j].ff;

            int pom=query(1,1,maxn,id,maxn,tree2,lazy2);
            pom=max(pom+u*dist(id,maxn),niz[j].ff);
            niz2[j]=max(niz2[j],pom+vect[i][j].ss);

            update(1,1,maxn,id,id,pom-u*dist(id,maxn),tree2,lazy2,0);
            update(1,1,maxn,id,maxn,vect[i][j].ss,tree2,lazy2,1);
        }

        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j].ff;

            update(1,1,maxn,1,id,-vect[i][j].ss,tree,lazy,1);
            update(1,1,maxn,id,maxn,-vect[i][j].ss,tree2,lazy2,1);
        }

        for(int j=0;j<vect[i].size();j++){
            int id=vect[i][j].ff;


            update(1,1,maxn,id,id,niz2[j]-d*id,tree,lazy,0);
            update(1,1,maxn,id,id,niz2[j]-u*dist(id,maxn),tree2,lazy2,0);
        }

    }

    printf("%d\n",max(query(1,1,maxn,1,s,tree,lazy)+d*s,query(1,1,maxn,s,maxn,tree2,lazy2)+u*dist(s,maxn)));

	return 0;
}
