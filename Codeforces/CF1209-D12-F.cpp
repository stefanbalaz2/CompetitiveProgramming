/*

    thought proces:

        - first thing that comes to mind is dijkstra
        - why we cant do dijkstra? because comparing distances takes too much time
        - can we improve it?
        - if we could somehow compress the string when it gets too large, but still maintaining its relation with other strings it could work
        - while doing dijkstra, when the string gets bigger than some block size, that means that every remaining vertex will have at least that much digits
        - we can take all active blocks(these are the first blocksize digits of strings that are currently in the set which are getting ready to get relaxed),
        sort them, and hash them with their position in the sorted array, this way we decrease the string size from blocksize to O(5)
        - after that we just clear our string, and add its hashed value to some vector which we will use for comparing
        - we are actually hashing our strings block by block(when the size gets bigger than the block size), and storing those values in a vector,
        so we are basically representing our string by a vector of numbers(previous hashed blocks) and a string(current not yet fully built block)
        - this way we do our comparison in O(blocksize)

        complexity: O((m+nlogn)blocksize)

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
const int maxn=1e5+10;
const ll mod=1e9+7;
int bsize=1000;
int n,m;
vector<pii>vect[maxn];
struct node{
    ll acval;
    string tval;
    vector<int>hval;
    int sz;
}nd[maxn];
int pos[maxn];
struct cmp{
    bool operator() (int a,int b){
        if(nd[a].sz<nd[b].sz)return true;
        if(nd[a].sz>nd[b].sz)return false;

        for(int i=0;i<nd[a].hval.size();i++){
            if(nd[a].hval[i]<nd[b].hval[i])return true;
            if(nd[a].hval[i]>nd[b].hval[i])return false;
        }

        if(nd[a].tval<nd[b].tval)return true;
        if(nd[a].tval>nd[b].tval)return false;

        return a<b;

        return false;
    }
};
bool cmpf(int a,int b){
    if(nd[a].sz<nd[b].sz)return true;
    if(nd[a].sz>nd[b].sz)return false;

    for(int i=0;i<nd[a].hval.size();i++){
        if(nd[a].hval[i]<nd[b].hval[i])return true;
        if(nd[a].hval[i]>nd[b].hval[i])return false;
    }

    if(nd[a].tval<nd[b].tval)return true;
    if(nd[a].tval>nd[b].tval)return false;

    return false;
}
set<int,cmp>st;
void rehash(){

    vector<pair<string,int>>v;

    for(set<int>::iterator it=st.begin();it!=st.end();it++){
        int id=(*it);
        v.pb({nd[id].tval.substr(0,bsize),id});
    }

    sort(v.begin(),v.end());

    int cnt=1;
    nd[v[0].ss].tval.erase(0,bsize);
    nd[v[0].ss].hval.pb(cnt);

    for(int i=1;i<v.size();i++){

        if(v[i].ff!=v[i-1].ff)cnt++;

        nd[v[i].ss].tval.erase(0,bsize);
        nd[v[i].ss].hval.pb(cnt);
    }
}
int ats(int x,int w){

    int niz[6];
    int br=0;

    while(w){
        niz[br++]=w%10;
        w/=10;
    }

    int ret=br;
    while(br--){
        nd[x].tval.pb(niz[br]+'0');
        nd[x].sz++;
        nd[x].acval*=10;
        nd[x].acval+=niz[br];
        nd[x].acval%=mod;
    }

    return ret;
}
void efs(int x,int br,ll val){

    nd[x].acval=val;

    for(int i=1;i<=br;i++){
        nd[x].sz--;
        nd[x].tval.pop_back();
    }
}
void go(){

    memset(pos,0,sizeof(pos));

    int x=1;
    st.insert(x);
    pos[x]=1;

    while(st.size()){

        x=(*st.begin());

        if(nd[x].tval.size()>bsize)rehash();
        pos[x]=1;

        st.erase(st.begin());

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i].ff;
            int w=vect[x][i].ss;
            if(pos[id])continue;

            if(nd[id].sz==0){

                st.erase(id);
                nd[id]=nd[x];
                ats(id,w);
                st.insert(id);
            }
            else{

                ll pom2=nd[x].acval;
                int pom=ats(x,w);

                if(cmpf(x,id)){
                    st.erase(id);
                    nd[id]=nd[x];
                    st.insert(id);
                }

                efs(x,pom,pom2);
            }
        }

    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);

    for(int i=1;i<=m;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb({v,i});
        vect[v].pb({u,i});
    }

    go();

    for(int i=2;i<=n;i++){
        printf("%lld\n",nd[i].acval);
    }

	return 0;
}
