/*

    idea:

        -binary search on the answer
        -do a dp to check if the answer can be achieved


        Doing a dp

        we will have a constant t which we will binary search
        t will denote the answer, and all the dynamites have to be at most t distance
        from any lit node

        at first we can try to construct any dp and optimize it to pass

        what information do we need to store in a node?
        well, we definately need to store how far from the node is the farthest undone dynamite which is contained
        in that nodes subtree
        is that enough? no
        imagine two trees being merged during dp, a lit node from one subtree can also 'do' dynamites from the other subtree
        which lowers the answer
        so we also need to store how far from the root of the subtree the closest lit node is

        for now we have a 3D dp of size n^3
        DP[I][J][K] -meaning minimum number of nodes we have to light to make the I subtree have
        the FARTHEST undone dynamite at most J distance away from I node and the CLOSEST lit node K distance
        away from I

        i wont get into details for the update of this dp, but rather reduce it further

        is this to much information? can we somehow notice some relations between the 2nd and the 3rd dimenstion?
        if the farthest undone dynamite is J distance from I, first, that means that our subtree I isnt completely solved,
        secondly, if thats the case, we dont have to store the K information because its useless, bcs if that lit node which is
        K distance from I wasnt able to light our dynamite on J distance from I, then we dont care what nodes it will light
        from other subtrees because what ever it lights it will be on lesser depth from the root of the subtree than our
        'J' node
        so when the tree isnt solved we only have to store the farthest undone dynamite, but when its solved
        we have to only store the closest lit node

        so now we have a dp something like this

        DP[I][J][K]

        where I is the node, J is either 0 or 1, 0 meaning that the subtree of I is not solved and that the farthest dynamite is
        on distance atmost K, and 1 meaning that the subtree is solved and there is lit node on the distance at most K

        it would be hard to maintain  this dp  efficiently using small to big to make the DP part nlogn so well try to reduce it
        even firther

        lets try reducing the "solved subtree" part(the part where J is 1)
        when a tree is solved do we actually need to store every posibility of the lit node depth?
        no
        if a subtree is solved with lighting P nodes, ouur only interest is the minimum K we can achieve with it
        because lets say that the distance to the shortest lit node was K in a solved subtree, then if we wanna make it less
        we have to increase the result by 1, and there is no point in doing that since we can just do that when we actually need it
        and we will have a lit node closer to the root than in the original case

            A
           /  \
          B    C

        if we are merging B and C that "when we actually need it" would be every time we merge that subtree, in this case while
        solving A

        so now we only have to store and maintain DP[I][J] and DP2[I]

        where DP[I][J] is minimum number of nodes to light to have subtree of I have the farthest undone dynamite
        on distance J, and DP2[I] is a pair of values, min number of nodes to solve the I subtree and the minimum distance
        from the closest lit node to I

        maintaining this is a bit hard
        in order to make the DP part nlogn, we have to do small to big technique
        in order to do that we need to maintain the 2nd dimenstion of the DP as a sorted stack
        querying our DP for values will require binary search, and updating will require merge sort
        and lazy addition

        i wont explain the dp transitions because they are rather straightforward

        Complexity: O(nlog^2)

*/
#include<bits/stdc++.h>
#include<set>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef set<int>::iterator sit;
const int maxn=3e5+10;
struct node{
    int val,lazy,pos;
};
pii dp2[maxn];
int d[maxn],n,ind[maxn],m,lazy[maxn],h[maxn],e2;
vector<pii>stek[maxn];
vector<node>dp1[maxn];
vector<int>vect[maxn];
void ins(int x,int val,int id){

    if(stek[x].size()==0){
        stek[x].pb({-lazy[x],id});
        lazy[x]+=val;
        return;
    }

    if(stek[x].back().ss==id)lazy[x]+=val;
    else{
        stek[x].pb({-lazy[x],id});
        lazy[x]+=val;
    }

}
void ers(int x,int id){

    while(stek[x].size() && stek[x].back().ss<=id){
        lazy[x]-=stek[x].back().ff+lazy[x];
        stek[x].pop_back();
    }

    return;
}
int get_dp(int x,int id){

    if(id<dp1[x].back().pos)return 1e9;

    int l=0;
    int r=stek[x].size()-1;
    int ret=-1,sr;

    while(l<=r){
        sr=(l+r)/2;
        if(stek[x][sr].ss<=id){
            ret=sr;
            r=sr-1;
        }
        else l=sr+1;
    }
    int val=0;
    if(ret!=-1)val=stek[x][ret].ff+lazy[x];

    l=0;
    r=dp1[x].size()-1;
    ret=-1;
    while(l<=r){
        sr=(l+r)/2;
        if(dp1[x][sr].pos<=id){
            ret=sr;
            r=sr-1;
        }
        else l=sr+1;
    }

    return min(dp1[x][ret].val+val,dp2[x].ff);
}
void go(int x,int prv,int val){


    ind[x]=x;
    for(int j=0;j<vect[x].size();j++){
        int id=vect[x][j];
        if(id==prv)continue;

        go(id,x,val);
        if(e2)return;
        if(dp1[ind[x]].size()==0){
            swap(ind[x],ind[id]);
            continue;
        }
        if(dp1[ind[x]][0].pos<dp1[ind[id]][0].pos)swap(ind[x],ind[id]);

        /// merge trees

            /// dp2
            pii pom;
            pom={dp2[ind[x]].ff+dp2[ind[id]].ff,min(dp2[ind[x]].ss,dp2[ind[id]].ss)};
            pom=min(pom,{dp2[ind[x]].ff+get_dp(ind[id],dp1[ind[id]].back().pos+(val-dp2[ind[x]].ss-2)),dp2[ind[x]].ss});
            pom=min(pom,{dp2[ind[id]].ff+get_dp(ind[x],dp1[ind[x]].back().pos+(val-dp2[ind[id]].ss-2)),dp2[ind[id]].ss});


            ///dp1

            vector<node>v1,v2;
            int ind1=dp1[ind[x]].size()-1;
            int ind2=dp1[ind[id]].size()-1;
            while(ind1>=0 && ind2>=0){
                if(dp1[ind[x]][ind1].pos>dp1[ind[id]][ind2].pos){
                    v2.pb(dp1[ind[id]].back());
                    dp1[ind[id]].pop_back();
                    ind2--;
                }
                else if(dp1[ind[x]][ind1].pos<dp1[ind[id]][ind2].pos){
                    v1.pb(dp1[ind[x]].back());
                    dp1[ind[x]].pop_back();
                    ind1--;
                }
                else{
                    v1.pb(dp1[ind[x]].back());
                    dp1[ind[x]].pop_back();
                    ind1--;

                    v2.pb(dp1[ind[id]].back());
                    dp1[ind[id]].pop_back();
                    ind2--;
                }
            }

            ind1=0;
            ind2=0;
            int minn1=dp2[ind[x]].ff;
            int minn2=dp2[ind[id]].ff;
            int cnt1=0;
            int cnt2=0;
            vector<node>fin;

            while(ind1<v1.size() || ind2<v2.size()){


                if(ind1>=v1.size()){

                    cnt2+=v2[ind2].lazy;
                    v2[ind2].lazy=0;
                    v2[ind2].val+=cnt2;

                    minn2=min(minn2,v2[ind2].val);

                    fin.pb({minn1+minn2,0,v2[ind2].pos});

                    ind2++;
                }
                else if(ind2>=v2.size()){

                    cnt1+=v1[ind1].lazy;
                    v1[ind1].lazy=0;
                    v1[ind1].val+=cnt1;

                    minn1=min(minn1,v1[ind1].val);

                    fin.pb({minn1+minn2,0,v1[ind1].pos});

                    ind1++;
                }
                else if(v1[ind1].pos==v2[ind2].pos){

                    cnt1+=v1[ind1].lazy;
                    v1[ind1].lazy=0;
                    v1[ind1].val+=cnt1;

                    cnt2+=v2[ind2].lazy;
                    v2[ind2].lazy=0;
                    v2[ind2].val+=cnt2;

                    minn1=min(minn1,v1[ind1].val);
                    minn2=min(minn2,v2[ind2].val);

                    fin.pb({minn1+minn2,0,v1[ind1].pos});

                    ind2++;
                    ind1++;
                }
                else if(v1[ind1].pos>v2[ind2].pos){/// prvo v2

                    cnt2+=v2[ind2].lazy;
                    v2[ind2].lazy=0;
                    v2[ind2].val+=cnt2;

                    minn2=min(minn2,v2[ind2].val);

                    fin.pb({minn1+minn2,0,v2[ind2].pos});

                    ind2++;
                }
                else{

                    cnt1+=v1[ind1].lazy;
                    v1[ind1].lazy=0;
                    v1[ind1].val+=cnt1;

                    minn1=min(minn1,v1[ind1].val);

                    fin.pb({minn1+minn2,0,v1[ind1].pos});

                    ind1++;
                }
            }


            ers(x,fin.back().pos);
            ins(x,cnt1+minn2,fin.back().pos);
            fin[fin.size()-1].val-=cnt1+minn2;
            fin[fin.size()-1].lazy+=cnt1+minn2;

            while(fin.size()){
                dp1[ind[x]].pb(fin.back());
                fin.pop_back();
            }


            dp2[ind[x]]=pom;

            dp1[ind[id]].clear();
            stek[ind[id]].clear();
    }


    if(dp1[ind[x]].size()==0){

        if(d[x]){
            dp1[ind[x]].pb({0,0,h[x]});
            dp2[ind[x]]={1,0};
        }
        else{
            dp1[ind[x]].pb({0,0,h[x]});
            dp2[ind[x]]={0,1e8};
        }

        return;
    }


    dp2[ind[x]].ss++;
    pii pom;
    pom={min(dp2[ind[x]].ff,get_dp(ind[x],dp1[ind[x]].back().pos+val-1))+1,0};
    if(d[x]==0 || dp2[ind[x]].ss<=val)pom=min(pom,dp2[ind[x]]);
    if(pom.ff==0)pom.ss=1e8;


    int cnt1=0;
    int last=-2;
    while(dp1[ind[x]].size()){
        if(cnt1+dp1[ind[x]].back().lazy+dp1[ind[x]].back().val<dp2[ind[x]].ff)break;

        cnt1+=dp1[ind[x]].back().lazy;
        last=dp1[ind[x]].back().pos;
        dp1[ind[x]].pop_back();
    }
    ers(ind[x],last);
    if(dp1[ind[x]].size()>0){
        dp1[ind[x]][dp1[ind[x]].size()-1].lazy+=cnt1;
        ins(ind[x],cnt1,dp1[ind[x]].back().pos);
    }
    dp1[ind[x]].pb({dp2[ind[x]].ff,0,h[x]});

    dp2[ind[x]]=pom;


    if(dp2[ind[x]].ff>m)e2=1;

}
bool check(int x){

    e2=0;
    memset(dp2,0,sizeof(dp2));
    for(int i=1;i<=n;i++){
        dp1[i].clear();
        stek[i].clear();
        lazy[i]=0;
    }

    go(1,0,x);
    if(e2)return false;

    int ret=dp2[ind[1]].ff;

    if(ret<=m)return true;
    else return false;
}
void hp(int x,int prv,int hh){

    h[x]=hh;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        if(id==prv)continue;
        hp(id,x,hh+1);
    }
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&d[i]);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        vect[u].pb(v);
        vect[v].pb(u);
    }


    hp(1,0,1);

    int l=0;
    int r=n;
    int sr,ret=-1;


    while(l<=r){
        sr=(l+r)/2;

        if(check(sr)){
            ret=sr;
            r=sr-1;
        }
        else l=sr+1;

    }

    printf("%d\n",ret);

    return 0;
}
