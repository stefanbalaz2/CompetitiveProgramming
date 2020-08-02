/*

    idea:

        compress the points
        first construct a greedy solution
        by doing this u get the rightmost places where u can place for every check
        intervals where u can place checks will be disjoint, thats easy to prove
        do a dp where u calculate where nubmer of ways to place remaining checks if the last check placed was on r

        this is O(n) and compressing the points is O(nlogn)

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef map<int,int>::iterator mit;
const int maxn=5e5+10;
const int maxbr=4*maxn;
int rightmost[maxbr],br,left_boundary[maxbr],revert[maxbr],k,jeste;
ll dp[maxbr],mod=1e9+7;
vector<int>v[maxbr];
vector<pii>p;
map<int,int>mapa;
int pos[maxbr];
int prek_rightmost(int br,int n){

    for(int i=0;i<=n;i++)pos[i]=0;
    vector<int>vect;
    int ret=0;
    for(int i=1;i<=br;i++){


        int e=0;
        for(int j=0;j<v[i].size();j++){
            int id=v[i][j];

            if(p[id].ff==i){
                vect.pb(id);
            }
            if(p[id].ss==i)
                if(pos[id]==0)e=1;
        }

        if(e==1){
            for(int j=0;j<vect.size();j++){
                pos[vect[j]]=1;
            }
            vect.clear();
            rightmost[++ret]=i;
        }

    }

    return ret;
}
ll go(int r,int k){


    if(k==0)return 1;
    if(r>br+1)return 0;
    if(dp[r]!=-1)return dp[r];
    dp[r]=0;

    if(r+1>rightmost[k+1]){
        left_boundary[r]=rightmost[k];
        dp[r]+=((revert[rightmost[k]]-revert[rightmost[k]-1])*go(rightmost[k],k-1))%mod;
    }
    else{
        left_boundary[r]=left_boundary[r+1];
        dp[r]+=go(r+1,k);
    }


    while(1){
        if(left_boundary[r]-1==0)break;
        int id=left_boundary[r]-1;

        int e=0;
        for(int j=0;j<v[id].size();j++){
            int id2=v[id][j];

            if(p[id2].ff==id){
                if(p[id2].ss<r){
                    e=1;
                    break;
                }
            }
        }
        if(e==1)break;

        dp[r]=(dp[r]+(revert[left_boundary[r]-1]-revert[left_boundary[r]-2])*go(left_boundary[r]-1,k-1))%mod;

        left_boundary[r]--;
    }


    return dp[r];
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    scanf("%d",&t);
    while(t--){

        int n,m;
        scanf("%d %d",&m,&n);

        mapa.clear();
        p.clear();
        for(int i=1;i<=n;i++){
            int a,b;
            scanf("%d %d",&a,&b);
            a++;
            mapa[a]=0;
            mapa[b]=0;
            mapa[a-1]=0;
            p.pb({a,b});
        }
        br=0;
        for(mit it=mapa.begin();it!=mapa.end();it++){
            it->ss=++br;
            revert[br]=it->ff;
        }

        for(int i=0;i<p.size();i++)p[i].ff=mapa[p[i].ff],p[i].ss=mapa[p[i].ss];
        for(int i=0;i<=br+2;i++)dp[i]=-1;
        for(int i=0;i<=br+2;i++)v[i].clear();
        for(int i=0;i<p.size();i++)v[p[i].ff].pb(i),v[p[i].ss].pb(i);

        k=prek_rightmost(br,n);
        rightmost[k+1]=-1;

        for(int i=0;i<p.size();i++)p[i].ff--;
        for(int i=0;i<=br+2;i++)v[i].clear();
        for(int i=0;i<p.size();i++)v[p[i].ff].pb(i),v[p[i].ss].pb(i);

        printf("%d %lld\n",k,go(br+1,k));
    }

    return 0;
}
