/*

    idea: https://www.hackerrank.com/contests/hourrank-30/challenges/diverse-strings/editorial

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,int> pii;
const int maxn=1e5+10;
const int maxk=26;
int n,q,k,sz[maxk+10],dp[maxk+10];
struct node{
    node *l,*r;
    int val;

    node(){
    }

    node(node *lp,node *rp,int val2){
        l=lp;
        r=rp;
        val=val2;
    }

}*sol[27];
node *kopiraj(node *x,node *prv){
    if(x==NULL)return NULL;

    node *ret=new node(prv,kopiraj(x->r,x),x->val);

    return ret;
}
node *add_end(node *x,int val,node *prv){

    if(x==NULL){
        x=new node(prv,NULL,val);
        return x;
    }
    else x->r=add_end(x->r,val,x);

    return x;
}
node *add_begin(node *x,int val){

    node *pom=new node(NULL,x,val);
    x->l=pom;

    return pom;
}
void go(node *x,int id){

    if(x==NULL)return;

    if(x->val!=id)go(x->r,id);
    else{
        sz[id+1]++;
        node *pom=new node(x,x->r,id+1);
        x->r->l=pom;
        x->r=pom;

        go(x->r,id);
    }

}
void prek(){

    int last=1;
    sz[1]=1;
    sol[1]=new node(NULL,NULL,1);

    sz[2]=5;
    sol[2]=kopiraj(sol[1],NULL);
    sol[2]=add_end(sol[2],2,NULL);
    sol[2]=add_end(sol[2],2,NULL);
    sol[2]=add_begin(sol[2],2);
    sol[2]=add_begin(sol[2],2);

    for(int i=3;i<=maxk;i++){

        sol[i]=kopiraj(sol[i-1],NULL);
        sol[i]=add_end(sol[i],i,NULL);
        sol[i]=add_begin(sol[i],i);
        sol[i]=add_begin(sol[i],i);

        sz[i]=sz[i-1]+3;

        go(sol[i],i-1);
    }
}
void ispis(node *x,int kk){
    if(x==NULL)return;
    printf("%c",kk-x->val+'a');
    ispis(x->r,kk);
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out2.txt","w",stdout);

    prek();

    scanf("%d",&q);
    while(q--){

        scanf("%d %d",&n,&k);

        if(sz[k]>n){
            printf("NONE\n");
            continue;
        }

        for(int i=1;i<=n-sz[k];i++)cout<<'a';
        ispis(sol[k],k);
        cout<<endl;
    }

	return 0;
}
