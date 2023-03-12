/*

    idea:

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int n=32;

vector<pii>vect[n+10];
int edges;
void add_edge(int x,int y,int w){
    vect[x].pb({y,w});
    edges++;
}

void ispis(){

    printf("YES\n");
    printf("%d %d\n",n,edges);
    for(int i=1;i<=n;i++)
        for(int j=0;j<vect[i].size();j++)
            printf("%d %d %d\n",i,vect[i][j].ff,vect[i][j].ss);

}

int main(){

    ///freopen("test.txt","r",stdin);

    int l,r,range;
    scanf("%d %d",&l,&r);

    range=r-l+1;

    add_edge(1,n,l);

    if(r-l==0){
        ispis();
        return 0;
    }

    for(int i=2;i<n;i++)add_edge(1,i,l);

    int pom=2;
    int last=n-1;
    for(int j=n-1;pom<=range;j--,pom*=2){
        for(int k=j+1;k<=n;k++)add_edge(j,k,pom/2);
        last--;
    }
    pom/=2;

    int cnt=0;
    for(int i=30;i>=0;i--){

        if(range&(1<<i)){
            if(cnt>0){
                add_edge(last,n-i-1,pom-(1<<i));
                pom+=(1<<i);
            }
            else cnt++;
        }

    }

    ispis();


    return 0;
}
