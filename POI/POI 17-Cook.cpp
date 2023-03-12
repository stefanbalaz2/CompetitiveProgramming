/*

    idea:

        straightforward dp[i][j] where i is the number of reamining orders and j is remaining energy
        energy is decremented only by using the 3rd operation and every time it decreases our orders by orders/2
        so we only need to have our j to go from 0 to log2(n)+1 because at most log2(n)+1 operation 3 can be used
        now we can easily construct the O(nlogn) memory and time solution

        to solve for 100 we need to notice that we are storing to many unnecesary stuff
        lets check whats necessary
        to update ith position we only need (i-1)th, (i-2)th and (i-i/2)th
        we can easily maintain the (i-1)th and (i-2)th while solving for i from left to right
        but how dp we maintain the (i-i/2)th?
        lets start from the begining, let i be 1
        we can trivially solve for i=1 and for i=2
        lets call the ith and (i-1)th position a block(we will maintain dp for it)
        lets call the (i-i/2)th element the P
        for the rest, we have to check if we have the P already calculated
        if not we gotta do something
        lets say its not calculated and we are at i=6 and we wanna calculate it
        P is 3 then but we have only 4 and 5 calculated
        then we introduce another block which we will calculate up to the position that we need(3 in this case)
        lets keep going with our first block, now our i=7 and P=4,
        we dont have 4, so we gotta push our second block, calculate the next state
        if we cant calculate the next state for it, then we have to update the 3rd block and so on
        so we will recursively oush a block by one place, and if we cant calculate its dp because the next block isnt yet on the position that we need
        then we try to push that block to that position, then the same goes for that block, if we cant push it, we gotta push the next block, etc
        we will have at most logn blocks, each with logn values(our dp), because every next block will be in the middle between our block and the beggining
        so we just maintain blocks and our dp in the blocks(which i wont explain bcs its trivial)

        final complexity:

            time: O(nlogn) -> because the first block takes nlogn, next one n/2*logn,next one n/4*logn => 2nlogn
            memory: O(logn^2)

*/
#include "ckuclib.h"
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef map<int,int>::iterator mit;
const int maxlog=50;
int gb;
struct ss{

    int pos1,pos2;
    ll dp1[maxlog],dp2[maxlog];

}niz[maxlog];

void go(int x){

    if(niz[x].pos1==-1){

        ll pom=jedno(1);
        for(int j=0;j<=gb;j++)niz[x].dp1[j]=pom;
        niz[x].pos1=1;

    }
    else if(niz[x].pos2==-1){

        for(int j=0;j<=gb;j++)niz[x].dp2[j]=niz[x].dp1[j];
        niz[x].pos2=niz[x].pos1;

        ll pom=jedno(2);
        ll pom2=dwa(2);
        ll pom3=polowa(2);
        for(int j=0;j<=gb;j++)niz[x].dp1[j]=min(niz[x].dp2[min(j+1,gb)]+pom,pom2);
        for(int j=1;j<=gb;j++)niz[x].dp1[j]=min(niz[x].dp2[min(j-1,gb)]+pom3,niz[x].dp1[j]);
        niz[x].pos1=2;
    }
    else{

        int nxt=niz[x].pos1+1;
        ll dp[25];
        ll pom1=jedno(nxt);
        ll pom2=dwa(nxt);
        ll pom3=polowa(nxt);
        for(int j=0;j<=gb;j++)dp[j]=min(niz[x].dp1[min(j+1,gb)]+pom1,niz[x].dp2[j]+pom2);

        if(nxt-nxt/2==niz[x].pos1)
            for(int j=1;j<=gb;j++)dp[j]=min(dp[j],niz[x].dp1[j-1]+pom3);
        else if(nxt-nxt/2==niz[x].pos2)
            for(int j=1;j<=gb;j++)dp[j]=min(dp[j],niz[x].dp2[j-1]+pom3);
        else{

            int treba=nxt-nxt/2;

            while(niz[x+1].pos1!=treba)go(x+1);

            for(int j=1;j<=gb;j++)dp[j]=min(dp[j],niz[x+1].dp1[j-1]+pom3);
        }

        for(int j=0;j<=gb;j++){
            niz[x].dp2[j]=niz[x].dp1[j];
            niz[x].dp1[j]=dp[j];
        }
        niz[x].pos2++;
        niz[x].pos1++;
    }

}
int main(){

    ///freopen("test2.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int n=dajn();
    int e=daje();
    memset(niz,-1,sizeof(niz));

    gb=log2(n)+2;

    for(int i=1;i<=n;i++)
        go(1);

    odpowiedz(niz[1].dp1[min(e,gb)]);


    return 0;
}
