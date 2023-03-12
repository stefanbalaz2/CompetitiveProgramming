/*

    idea:

        lets analyse what we need in every turn
        we will greedily take as much as we can every time we can
        in the first turn we have to take the 1, so we need to traverse at upto 1
        all consecutive numbers bigger than 1 that we visited while traversing to 1 (meaning 2,3,4 ... upto the first one thats missing)
        will have to be handled right now
        why? because if we cant solve those right now then we cant solve them later when they are even more pilled up
        so the best moment to solve them is the first time we can

        observation: in every moment our 2 piles have to be sorted

        we can greedily put every element on some pile such that we put it on the pile that has the bigger number on top(in the code i built the piles from top to bottom
        but here i will explain from bottom to top)
        i wont prove the correctness of this, it is quite straightforward

        so what are we left after "solving" the last k elements that we needed? we are left with something like this

        1
        3 2
        9 4
        10 5

        when we solve 1, we are left with

        9
        10

        now, we can mby color the nodes(thats how ill call those numbers) straight up when we assemble them like in the first picture?
        well, for me it was easier just to nitice that the color doesnt matter(color=which pile, colors are 0 and 1) but only their pairwise distribution
        we can somehow momrise that, like, connect 1,3,9,10 with an edge which says that they have to be the same color, 2,4,5 also the same type of edge
        and then connect 1 and 2 with an edge that says they have to be of different color
        now we have our restrictions and we can do with  the remaining thing what we want
        we will compress the remaining parts(it can be 1 column, or even a pair of columns) and after popping all the used nodes, we can
        put in the new set of nodes(in this case column 9,10) which we will later used just like a regular node,
        sometimes u will be left with 2 columns, for that i kept 2 sets in dsu to resemble which one is which,
        but when putting them on top of piles u can either put them the original way, or swap the places of those 2 columns

        after we solve that for 1, we find the next undone node and traverse to it, and do the same thing

        after that process is done, we have our restrictions that we have to obey in a form of a graph
        just color the graph greedily and after that check if the distribution yields NIE or TAK

        so our algo looks like:

            maintain a stack of active building blocks
            when building, build greedily and make edges of restriction
            color the graph
            check the validity

        complexity: O(nlog^2) because of sets and bcs of merging small to large, but the complexity is much smaller actually

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
const int maxn=1e5+10;
vector<pii>vect[maxn];
int br,stek[maxn],col[maxn],taken[maxn],a[maxn],lstek[maxn],rstek[maxn];
struct dsu{

    int sz1,sz2,p;
    set<int>vect1,vect2;

    int get_min(){
        if(get_min1()==-1)return get_min2();
        else if(get_min2()==-1)return get_min1();
        else return min(get_min1(),get_min2());
    }
    int get_max(){
        if(get_max1()==-1)return get_max2();
        else if(get_max2()==-1)return get_max1();
        else return max(get_max1(),get_max2());
    }
    int get_min1(){
        if(sz1==0)return -1;
        return (*vect1.begin());
    }
    int get_max1(){
        if(sz1==0)return -1;
        return (*vect1.rbegin());
    }
    int get_min2(){
        if(sz2==0)return -1;
        return (*vect2.begin());
    }
    int get_max2(){
        if(sz2==0)return -1;
        return (*vect2.rbegin());
    }
    void swp(){
        swap(sz1,sz2);
        swap(vect1,vect2);
    }
    int skini(int x){
        int ret=0;
        while(vect1.size() && (*vect1.begin())<x){
            ret++;
            vect1.erase(vect1.begin());
            sz1--;
        }
        while(vect2.size() && (*vect2.begin())<x){
            ret++;
            vect2.erase(vect2.begin());
            sz2--;
        }
        return ret;
    }

}st[maxn];
int root(int x){
    if(st[x].p==x)return x;
    else return st[x].p=root(st[x].p);
}
void join(int x,int y){
    if(x==-1 || y==-1 || x==0 || y==0)return;

    x=root(x);
    y=root(y);

    if(x==y)return;

    if(st[x].sz1+st[x].sz2<st[y].sz1+st[y].sz2)swap(x,y);

    st[x].sz1+=st[y].sz1;
    st[x].sz2+=st[y].sz2;
    st[y].p=x;

    for(sit it=st[y].vect1.begin();it!=st[y].vect1.end();it++)
        st[x].vect1.insert(*it);

    for(sit it=st[y].vect2.begin();it!=st[y].vect2.end();it++)
        st[x].vect2.insert(*it);
}
int n;
void reset_dsu(){
    for(int i=1;i<=n;i++){
        st[i].sz1=1;
        st[i].sz2=0;
        st[i].p=i;
        st[i].vect1.insert(i);
    }
}
void make_edge(int x,int y,int c){
    if(x==-1 || y==-1 || x==0 || y==0)return;
    vect[x].pb({y,c});
    vect[y].pb({x,c});
}
bool sol(){

    int curr=1;
    br=0;
    int pt=1;
    while(1){

        while(pt<=n && taken[curr]==0){
            stek[++br]=a[pt];
            taken[a[pt]]=1;
            pt++;
        }

        int nxt=-1;
        for(int i=curr;i<=n;i++){
            if(taken[i]==0){
                nxt=i;
                break;
            }
        }
        if(nxt==-1)nxt=n+1;


        int cnt=nxt-curr;
        int fst;
        for(int i=br;i>=1;i--){

            int id=root(stek[i]);
            for(sit it=st[id].vect1.begin();it!=st[id].vect1.end();it++){
                if(*it>=nxt)break;
                cnt--;
            }
            for(sit it=st[id].vect2.begin();it!=st[id].vect2.end();it++){
                if(*it>=nxt)break;
                cnt--;
            }

            if(cnt==0){
                fst=i;
                break;
            }
        }


        int pile[2]={0,0};
        int ids[2]={0,0};
        while(br>=fst){
            int id=stek[br];

            int type=0;
            if(st[id].sz1>0)type++;
            if(st[id].sz2>0)type++;

            if(type==1){

                vector<pii>candidates;

                if(st[root(ids[0])].get_max1()<st[id].get_min())candidates.pb({-st[root(ids[0])].get_max1(),0});
                if(st[root(ids[1])].get_max2()<st[id].get_min())candidates.pb({-st[root(ids[1])].get_max2(),1});
                if(candidates.size()==0)return false;
                sort(candidates.begin(),candidates.end());

                int id2=candidates[0].ss;
                if(id2==0){
                    if(st[id].sz1==0)st[id].swp();
                    make_edge(st[root(ids[id2])].get_min1(),st[id].get_min1(),0);
                    make_edge(st[root(ids[id2^1])].get_min2(),st[id].get_min1(),1);
                    join(ids[id2],id);
                    ids[id2]=id;
                }
                else{
                    if(st[id].sz2==0)st[id].swp();
                    make_edge(st[root(ids[id2])].get_min2(),st[id].get_min2(),0);
                    make_edge(st[root(ids[id2^1])].get_min1(),st[id].get_min2(),1);
                    join(ids[id2],id);
                    ids[id2]=id;
                }
            }
            else{

                if(st[root(ids[0])].get_max1()<st[id].get_min1() && st[root(ids[1])].get_max1()<st[id].get_min2()){

                    make_edge(st[id].get_min1(),st[root(ids[0])].get_min1(),0);
                    make_edge(st[id].get_min2(),st[root(ids[1])].get_min2(),0);

                    join(ids[0],id);
                    join(ids[1],id);

                    ids[0]=id;
                    ids[1]=id;
                }
                else if(st[root(ids[1])].get_max1()<st[id].get_min1() && st[root(ids[0])].get_max1()<st[id].get_min2()){
                    st[id].swp();

                    make_edge(st[id].get_min1(),st[root(ids[0])].get_min1(),0);
                    make_edge(st[id].get_min2(),st[root(ids[1])].get_min2(),0);

                    join(ids[0],id);
                    join(ids[1],id);

                    ids[0]=id;
                    ids[1]=id;
                }
                else return false;

            }

            br--;
        }

        join(ids[0],ids[1]);
        st[root(ids[0])].skini(nxt);

        if(st[root(ids[0])].sz1+st[root(ids[0])].sz2>0)stek[++br]=root(ids[0]);

        curr=nxt;

        if(pt>n)break;
    }

    return 1;
}
void go(int x,int c){

    col[x]=c;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i].ff;
        int w=vect[x][i].ss;

        if(col[id]!=-1){}
        else go(id,c^w);
    }

}
void color(){
    memset(col,-1,sizeof(col));
    for(int i=1;i<=n;i++){
        if(col[i]!=-1)continue;
        go(i,0);
    }
}
bool check(){

    int brl=0;
    int brr=0;
    int curr=1;
    for(int i=1;i<=n;i++){

        if(col[a[i]]==0)lstek[++brl]=a[i];
        else rstek[++brr]=a[i];

        while(1){
            if(lstek[brl]==curr){
                curr++;
                brl--;
            }
            else if(rstek[brr]==curr){
                curr++;
                brr--;
            }
            else break;
        }
    }


    if(curr>n)return true;
    else return false;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);


    reset_dsu();

    if(!sol()){
        printf("NIE\n");
        return 0;
    }

    color();
    if(check()){
        printf("TAK\n");
        for(int i=1;i<=n;i++)printf("%d ",col[a[i]]+1);
    }
    else printf("NIE\n");

    return 0;
}
