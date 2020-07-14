/*

    idea: https://codeforces.com/blog/entry/63877

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=2e5+10;
int n,m,col[maxn],a[maxn],b[maxn];
int tmp[maxn];
struct qv{
    int tip,la,lb,ra,rb;
}q[maxn];
vector<int>val[maxn],f[maxn];

void addget(int x,int y){
    if(x<0 || y<0)return;
    for(int i=x;i>=0;i=(i & (i + 1)) - 1)
        val[i].pb(y);

}
void addupd(int x,int y){

    for(int i=x;i<n;i|=(i+1))
        val[i].pb(y);

}

int get(int x,int y){

    int ret=0;
    if(x<0 || y<0)return 0;
    for(;x>=0;x=(x&(x+1))-1)
        for(int i=lower_bound(val[x].begin(),val[x].end(),y)-val[x].begin();i>=0;i=(i & (i + 1)) - 1)
        ret+=f[x][i];

    return ret;
}

void upd(int x,int y,int z){

    for(;x<n;x|=x+1)
        for(int i=lower_bound(val[x].begin(),val[x].end(),y)-val[x].begin();i<val[x].size();i |= i + 1)
        f[x][i]+=z;

}

int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out2.txt","w",stdout);

    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        a[i]--;
        col[a[i]]=i;
    }

    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
        b[i]--;
        b[i]=col[b[i]];

        tmp[i]=b[i];
    }

    for(int i=0;i<n;i++)addupd(i,b[i]);

    for(int i=1;i<=m;i++){
        scanf("%d",&q[i].tip);
        if(q[i].tip==1){

            scanf("%d %d %d %d",&q[i].la,&q[i].ra,&q[i].lb,&q[i].rb);
            q[i].la--;
            q[i].lb--;
            q[i].ra--;
            q[i].rb--;


            addget(q[i].lb-1,q[i].la-1);
            addget(q[i].lb-1,q[i].ra);

            addget(q[i].rb,q[i].la-1);
            addget(q[i].rb,q[i].ra);
        }
        else{

            scanf("%d %d",&q[i].la,&q[i].ra);
            q[i].la--;
            q[i].ra--;

            addupd(q[i].la,b[q[i].la]);
            addupd(q[i].ra,b[q[i].ra]);
            swap(b[q[i].la],b[q[i].ra]);
            addupd(q[i].la,b[q[i].la]);
            addupd(q[i].ra,b[q[i].ra]);
        }
    }

    for(int i=0;i<=n;i++){
        sort(val[i].begin(),val[i].end());
        val[i].resize(unique(val[i].begin(),val[i].end())-val[i].begin());
        f[i].resize(val[i].size(),0);
    }

    for(int i=0;i<n;i++){
        b[i]=tmp[i];
        upd(i,b[i],1);
    }

    for(int i=1;i<=m;i++){

        if(q[i].tip==1){

            int ret=0;
            ret+=get(q[i].rb,q[i].ra);
            ret-=get(q[i].rb,q[i].la-1);

            ret-=get(q[i].lb-1,q[i].ra);
            ret+=get(q[i].lb-1,q[i].la-1);

            printf("%d\n",ret);
        }
        else{
            upd(q[i].la,b[q[i].la],-1);
            upd(q[i].ra,b[q[i].ra],-1);
            swap(b[q[i].la],b[q[i].ra]);
            upd(q[i].la,b[q[i].la],1);
            upd(q[i].ra,b[q[i].ra],1);
        }

    }


	return 0;
}
