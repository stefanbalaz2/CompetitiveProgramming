/*

    idea: lets look at the solution

    in column i there must be exactly a[i] 1bits
    so the problem is now permuting the columns so that we dont have any 2 same rows
    first column we will set first a[1] bits, and the rest bits wont be set
    so we have 2 intervals now which we have to continue dividing with the next columns in the similair manner
    all the rows which are in the same interval are the same
    let the sum of same pairs be P
    our result will have P=0
    lets say we are gonna add bit by bit to our next column, column i
    we need to add a[i] bits there
    by adding a bit to the interval we decrease P by some amount
    we are gonna put all the intervals with their value that they decrease P into a priority queue
    and every time we wanna add a bit we are gonna add it to the most profitable interval
    after we finish adding all the bits we are gonna split out intervals into 2 more intervals(except for the case when the interval is full of same bits)
    first interval will be full of one`s and the second full of zero`s
    after we split every interval we continue doing that for i-1 column with our new intervals

    this works because u take the best option every time and it doesnt screw up other options, meaning they are independent

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxn=1e3+10;
int n,cnt[2*maxn];
pii p[maxn];
string nula;
vector<string>s;
struct itv{
    int val,l,r;
};
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&p[i].ff);
        p[i].ss=i-1;
        nula.pb('0');
    }
    sort(p+1,p+n+1);
    for(int i=1;i<=n+1;i++)s.pb(nula);

    vector<itv>intervals;
    intervals.pb({p[n].ff,1,p[n].ff});
    intervals.pb({n+1-p[n].ff,p[n].ff+1,n+1});
    for(int k=1;k<=p[n].ff;k++)s[k-1][p[n].ss]='1';

    for(int i=n-1;i>=1;i--){

        set<pii>st;
        /// sledeci -2
        for(int j=0;j<intervals.size();j++)st.insert({-intervals[j].val-1,j});

        for(int j=1;j<=p[i].ff;j++){

            pii pom=*st.begin();

            cnt[pom.ss]++;
            st.erase(pom);
            pom.ff+=2;
            if(cnt[pom.ss]==intervals[pom.ss].r-intervals[pom.ss].l+1){}
            else st.insert(pom);
        }

        vector<itv>pint;
        for(int j=0;j<intervals.size();j++){

            itv pom1,pom2;

            pom1.l=intervals[j].l;
            pom1.r=intervals[j].l+cnt[j]-1;
            pom1.val=cnt[j];

            for(int k=pom1.l;k<=pom1.r;k++)s[k-1][p[i].ss]='1';

            pom2.l=pom1.r+1;
            pom2.r=intervals[j].r;
            pom2.val=intervals[j].r-intervals[j].l+1-cnt[j];

            if(pom1.l<=pom1.r)pint.pb(pom1);
            if(pom2.l<=pom2.r)pint.pb(pom2);

            cnt[j]=0;
        }

        intervals.clear();
        intervals=pint;
    }

    int rc=0;
    for(int i=0;i<n+1;i++)if(s[i]!=nula)rc++;

    printf("%d\n",rc);
    for(int i=0;i<n+1;i++){
        if(s[i]!=nula)cout<<s[i]<<endl;
    }

    return 0;
}
