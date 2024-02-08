#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=1e5+10;
int bsize=300;
bitset<maxn>its2[1000],its;
bitset<maxn>bs[3],lst2,pom,pom2,mask,diff,taken,zero;
vector<int>vect[maxn];
int n,m,q,cnt,niz[maxn];

void dod(int x,int c){
    pom=(bs[c]&its);
    bs[c]^=pom;
    bs[c+1]^=pom;
}
void dodaj(int x){
    dod(x,1);
    dod(x,0);
}
void skin(int x,int c){
    pom=(bs[c]&its);
    bs[c-1]^=pom;
    bs[c]^=pom;
}
void skini(int x){
    skin(x,1);
    skin(x,2);
}


int main(){


    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(i);
        vect[v].pb(i);
        mask[i]=1;
        bs[0][i]=1;
        taken[i]=1;
    }
    for(int i=1;i<=n;i++){
        if(vect[i].size()>=bsize){
            niz[i]=++cnt;
            for(int j=0;j<vect[i].size();j++)its2[cnt][vect[i][j]]=1;
        }
    }

    scanf("%d",&q);
    for(int i=1;i<=q;i++){

        char c;
        cin>>c;
        if(c=='?'){

            pom=(bs[1]&taken);
            pom[m+1]=1;
            int k=pom._Find_next(0);
            if(k>m){
                printf("0\n");
                continue;
            }
            printf("%d\n",k);
            taken[k]=0;

        }
        else{
            int x;
            scanf("%d",&x);


            if(vect[x].size()>=bsize){
                its=its2[niz[x]];
            }
            else{
                its=zero;
                for(int i=0;i<vect[x].size();i++)its[vect[x][i]]=1;
            }

            if(c=='+'){
                dodaj(x);
            }
            else{
                skini(x);
            }


        }

    }



    return 0;
}
