/*
    same idea as in editorial
    https://img.atcoder.jp/agc027/editorial.pdf
*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<char,int> pii;
const int maxv=2300000;
int n,pos[maxv+10],br;
ll primes[maxv],rows[1010],cols[1010],aa[519][510];
void sito(){

    for(int i=2;i<=maxv;i++){
        if(pos[i])continue;
        primes[++br]=i;
        for(int j=i;j<=maxv;j+=i)pos[j]=1;
    }

}
ll lcm(ll a,ll b){
  return (a/__gcd(a,b))*b;
}
void fix(int x,int y){

    ll lc=1;

    if(aa[x+1][y]!=0){lc=lcm(lc,aa[x+1][y]);}
    if(aa[x-1][y]!=0){lc=lcm(lc,aa[x-1][y]);}
    if(aa[x][y+1]!=0){lc=lcm(lc,aa[x][y+1]);}
    if(aa[x][y-1]!=0){lc=lcm(lc,aa[x][y-1]);}

    aa[x][y]=lc+1;
}
int dist(int x,int y,int x1,int y1){
   return abs(x-x1)+abs(y-y1);
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);

    if(n==2){
        printf("4 7\n23 10\n");
        return 0;
    }

    sito();

    int curr=0;
    for(int i=0;i<n;i++)
        rows[i*2]=primes[++curr];

    for(int i=0;i<n;i++)
        cols[i*2]=primes[++curr];

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){

            if(dist(1,1,i,j)%2==0){
                aa[i][j]=rows[dist(1,1,i,j)];
            }

        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){

            if(n%2){
               if(dist(n,1,i,j)%2==0){
                aa[i][j]*=cols[dist(n,1,i,j)];
               }
            }
            else{
                if(dist(n,1,i,j)%2==1){
                    aa[i][j]*=cols[dist(n,1,i,j)-1];
                }
            }

        }
    }


    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if((i+j)%2)fix(i,j);
            printf("%lld ",aa[i][j]);
        }
        printf("\n");
    }


    return 0;
}
