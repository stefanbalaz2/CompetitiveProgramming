/*

    idea:https://codeforces.com/blog/entry/53268

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=5e5+10;

struct edge{
    int a,b,l,r;

    bool operator <(const edge &b) const {
        return l>b.l;
    }
};

int last[maxn][2],n,m;
vector<edge>vect[maxn][2];
priority_queue<edge>q;

void extend(int x,int tim,int r){

    last[x][tim%2]=max(last[x][tim%2],r);

    int p=tim%2;
    for(int i=0;i<vect[x][p].size();i++){
        edge pom=vect[x][p][i];
        pom.l=tim;
        q.push(pom);
    }

    vect[x][p].clear();
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){
        int u,v,l,r;
        scanf("%d %d %d %d",&u,&v,&l,&r);
        r--;

        int pom1=(l^r);

        q.push({u,v,l,r-(pom1&1)});
        q.push({v,u,l,r-(pom1&1)});

        q.push({u,v,l+1,r-((pom1&1)^1)});
        q.push({v,u,l+1,r-((pom1&1)^1)});
    }

    memset(last,-1,sizeof(last));

    last[1][0]=0;
    while(q.size()){

        edge x=q.top();

        ///printf("%d %d EDGE\n",x.a,x.b);

        q.pop();
        if(x.l>x.r)continue;

        int p=(x.l%2);

        if(x.l>last[x.a][p])vect[x.a][p].pb(x);
        else{

            if(x.b==n){
                printf("%d\n",x.l+1);
                return 0;
            }
            else extend(x.b,x.l+1,x.r+1);
        }

    }

    if(n==1)printf("0");
    else printf("-1\n");

	return 0;
}
