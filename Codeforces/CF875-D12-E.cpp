/*

    idea:    binary search the answer
              imagine dp[i] being if we can do the first i points
              so that means we have some segment of points done by 1 player which ends at i
              so we can try all j<i
              when is j ellegible to be taken?
              if dp[j]==true then one of the players is at a[j], and the other one
              is in the range x that we are binary searching
              as long as the points a[j+1 -> i] are in the range [a[j]-x,a[j]+x]
              we can construct the segment [j+1 -> i] onto the solution for j
              maintain a set of dp`s which are valid and update them when
              inserting a point
    
*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
const int maxn=1e5+10;
int s1,s2,n,a[maxn];
bool check(int x){

    set<int>st;
    if(abs(s1-s2)>x)return false;

    st.insert(s1);
    st.insert(s2);

    for(int i=1;i<=n;i++){

        while(st.size() && (*st.begin())<a[i]-x)st.erase(st.begin());
        while(st.size() && (*st.rbegin())>a[i]+x)st.erase(*st.rbegin());

        if(st.size()==0)return false;

        st.insert(a[i]);

    }

    return true;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d %d",&n,&s1,&s2);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);

    int l=0;
    int r=1e9;
    int sr,ret=-1;
    while(l<=r){
        sr=(l+r)/2;
        if(check(sr)){
            r=sr-1;
            ret=sr;
        }
        else l=sr+1;
    }

    printf("%d\n",ret);

    return 0;
}
