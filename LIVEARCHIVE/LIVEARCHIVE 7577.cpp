/*

    this solution gives TLE but works in complexity O(n^2*log(2e15)), which is 4 times
    slower than the intended solution, which doesnt pass on the server, but i still uploaded
    it bcs its different from the intended solution and the solution from darkcyan which i saw

    this solution passes all the test cases(i downloaded them and tried them all) even though
    it gives TLE


    idea: we can observe that the route of 1 delivery can be decomposed into the part when we go
    from A to HQ and from HQ to B, this implies that A and B are in the same group so we will
    also have a route from B to A, so we will also have B to HQ and HQ to A
    so for every node A we will keep the distance from it to the HQ+distance from HQ to A
    lets call that sum Pi for a node i
    our answer consists of some sum of Pi
    if i is in a group of x people then Pi will be included in our answer x-1 times
    so our answer consists of some S groups, lets write their sizes into the array q
    let our array be sorted descendingly
    because the number of times Pi is included in the result is dependend on just the size of the group ith node is in
    then it means that we will put the biggest Pi in the smallest group(smallest qi)
    we can then notice that a group will contain only consecutive elements
    which leads us to this problem, divide the array into s subarrays so that the sum of costs is minimum, given the cost function

    so now we can do a regular dp[i][j] meaning that we did the positions up to ith, and we split into j subarrays, this yields n^3 complexity
    we can either observe something more to simplify our dp, or we can cut down a dimension, or we can speed up our update process

    we can observe that the sizes of the subarrays will be in descending order which can be used to solve the problem like in the model solution
    http://www.csc.kth.se/~austrin/icpc/finals2016solutions.pdf

    or we can observe convexity of our cost function
    https://github.com/quangloc99/CompetitiveProgramming/blob/master/Livearchive/7577.cpp

    or we can cut down a dimension like i did it with lambda optimisation
    what it bassically does it gives some additional cost to forming another subarray,
    and then we greedily do an n^2 dp to see what is the cost and how many groups are there for that subarray cost
    and we binary search over the cost, and when we reach our desired number of groups thats it

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<ll,ll> pli;
const int maxn=5010;
ll dist[2][maxn];
vector<pli>vect[2][maxn];
pli dp[maxn];
int b,n,r,s;
ll a[maxn];
void calc(ll x,int y){

    memset(dist[y],-1,sizeof(dist[y]));
    dist[y][x]=0;
    set<pli>st;
    st.insert({0,x});

    while(st.size()){

        x=(*st.begin()).ss;
        st.erase(st.begin());


        for(int i=0;i<vect[y][x].size();i++){
            ll id=vect[y][x][i].ff;
            ll w=vect[y][x][i].ss;

            if(dist[y][id]==-1){
                dist[y][id]=dist[y][x]+w;
                st.insert({dist[y][id],id});
            }
            else{
                if(dist[y][id]>dist[y][x]+w){
                    st.erase({dist[y][id],id});
                    dist[y][id]=dist[y][x]+w;
                    st.insert({dist[y][id],id});
                }
            }

        }

    }

}
ll calc_val(int x){
    return dist[0][x]+dist[1][x];
}
pli check(ll price){

    for(int i=1;i<=b;i++){

        ll sum=0;
        pli pom={1e18,1e18};
        for(int j=i;j>0;j--){
            sum+=a[j];
            pom=min(pom,{sum*((ll)i-j)+dp[j-1].ff+price,dp[j-1].ss+1});
        }

        dp[i]=pom;
    }

    return dp[b];
}
ll solve(){

    ll l=0;
    ll r=2e15;
    ll sr,ret=-1;

    while(l<=r){
        sr=(l+r)/2;

        if(check(sr).ss>=(ll)s){
            l=sr+1;
            ret=sr;
        }
        else r=sr-1;

    }

    pli pom=check(ret);
    if(pom.ss>s)ret++;
    pom=check(ret);

    pom.ff-=((ll)s*ret);

    return pom.ff;
}
int main(){

    ///freopen("49.in","r",stdin);
    ///freopen("out.txt","w",stdout);

    while(cin>>n>>b>>s>>r){

        for(int i=1;i<=n;i++){
            vect[0][i].clear();
            vect[1][i].clear();
        }

        for(int i=1;i<=r;i++){
            ll u,v,w;
            scanf("%lld %lld %lld",&u,&v,&w);
            vect[0][u].pb({v,w});
            vect[1][v].pb({u,w});
        }

        calc(b+1,0);
        calc(b+1,1);

        for(int i=1;i<=b;i++)
            a[i]=calc_val(i);

        sort(a+1,a+b+1);

        printf("%lld\n",solve());
    }


    return 0;
}
