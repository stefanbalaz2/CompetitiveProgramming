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

const int maxn=30;

map<ll,int>dp[maxn][maxn];
int a[maxn],n;
map<ll,vector< pair<ll,vector<pii>> > > gi[maxn][maxn];
vector<pii>get_intervals(int l,int r,int minn){

    vector<int>cand;
    cand.pb(l-1);
    for(int i=l;i<=r;i++)if(minn==a[i])cand.pb(i);
    cand.pb(r+1);

    vector<pii>ret;
    for(int i=1;i<cand.size();i++){
        ret.pb({cand[i-1]+1,cand[i]-1});
    }
    return ret;
}
vector<pair<ll,vector<pii>>>get_intervals2(int l,int r,ll s){

    if(gi[l][r].find(s)!=gi[l][r].end())return gi[l][r][s];

    vector<vector<pii>>ret;
    set<int>st;
    for(int i=l;i<=r;i++){
        st.insert(a[i]);
    }

    for(set<int>::iterator it=st.begin();it!=st.end();it++){
        gi[l][r][s].pb({ -(*it)-s,get_intervals(l,r,*it)} );
    }

    return gi[l][r][s];
}
int go(int l,int r,ll s){

    if(l>r)return 0;
    if(dp[l][r].count(s)!=0){
        return dp[l][r][s];
    }

    int &aa=dp[l][r][s];
    aa=2e9;

    for(int i=l;i<=r;i++){
        for(int j=i;j<=r;j++){

            vector<pair<ll,vector<pii>> >cand2=get_intervals2(i,j,s);

            for(int c=0;c<cand2.size();c++){

                vector<pii>cand=cand2[c].ss;
                int pom=0;
                ll ss=cand2[c].ff+s;

                ///if(l==3 && r==4 && s==-1)printf("%d %d | %d %d INTERVALS\n",l,r,i,j);
                for(int k=0;k<cand.size();k++){
                    pom+=go(cand[k].ff,cand[k].ss,ss);
                    ///if(l==3 && r==4 && s==-1)printf("%d %d INTS | %d %d | %d %d %d %d\n",l,r,i,j,cand[k].ff,cand[k].ss,ss,go(cand[k].ff,cand[k].ss,ss));
                }

                int isnula=0;
                for(int k=i;k<=j;k++)if(a[k]+s!=0)isnula=1;

                aa=min(aa, go(l,i-1,s)+go(j+1,r,s)+pom+isnula );

                /*if(go(l,i-1,s)+go(j+1,r,s)+pom+isnula ==0 && l==1 && r==n){

                    printf("%d %d %d | %d %d %d | %d %d %d %d IJ\n",l,r,s,i,j,ss,go(l,i-1,s),go(j+1,r,s),pom,isnula);

                }*/
            }
        }
    }
    ///printf("%d %d %d | %d DP\n",l,r,s,aa);
    return aa;
}

int main(){

    ///freopen("test.txt","r",stdin);

    ///memset(dp,-1,sizeof(dp));

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }

    printf("%d\n",go(1,n,0));

    return 0;
}
