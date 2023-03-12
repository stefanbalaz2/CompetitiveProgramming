/*

    idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/tree/master/Olympiad/JOI/official/JOIOC/2017

    code is really messy and slow, didnt optimise anything

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define lld long long
#define pb push_back
using namespace std;
typedef pair<lld,lld> pii;
const int maxn=2e3+10;
lld inf=2e9+100;
lld rez=-inf*inf,pref[maxn],tree[maxn*4],mtree[maxn*4];
int n,curr_here[maxn],curr_pos[maxn];
bool srt_pii(pair<pii,int> a,pair<pii,int> b){
    if(a.ff.ff==-inf || b.ff.ff==-inf)return a.ff.ff<b.ff.ff;
    if(a.ff.ff==0 || b.ff.ff==0){
        if(a.ff.ff==0 && b.ff.ff==0)return false;

        if(b.ff.ff==0 && a.ff.ff>0)return false;
        if(b.ff.ff==0 && a.ff.ff<0)return true;

        if(a.ff.ff==0 && b.ff.ff<0)return false;
        if(a.ff.ff==0 && b.ff.ff>0)return true;
    }
    return a.ff.ff*b.ff.ss<b.ff.ff*a.ff.ss;
}
vector<pair<pii,int> >mapa;
struct st{
    lld x,y,w;
    int id;
}p[maxn];
bool srt(st a,st b){
    return (a.y<b.y)||(a.y==b.y && a.x<b.x);
}
void regulate(pii &x){

    lld g=__gcd(x.ff,x.ss);
    x.ff/=g;
    x.ss/=g;

    int cnt=0;
    if(x.ff<0)cnt++;
    if(x.ss<0)cnt++;

    if(cnt==2){
        x.ff*=-1;
        x.ss*=-1;
    }
    else if(cnt==1){
        if(x.ss<0){
            x.ss*=-1;
            x.ff*=-1;
        }
    }
}
pii get_line(st a,st b){

    pii ret={0,0};

    if(a.x==b.x)return {-inf,-inf};
    if(a.y==b.y)return {0,0};
    ret={a.y-b.y,a.x-b.x};
    regulate(ret);

    return ret;
}
void degree90(pii &x){

    if(x.ff==-inf){
        x={0,0};
        return;
    }
    if(x.ff==0){
        x={-inf,-inf};
        return;
    }

    swap(x.ff,x.ss);
    x.ff*=-1;
    regulate(x);
}
void add_pair(st a,st b){

    pii pom=get_line(a,b);

    degree90(pom);

    mapa.pb({pom,a.id});
    mapa.pb({pom,b.id});
}
void extract_pairs(){

    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            add_pair(p[i],p[j]);
}
void update(int x,int l,int r,int id,lld val){
    if(l==r){
        tree[x]=val;
        mtree[x]=val;
        return;
    }
    int mid=(l+r)/2;
    if(id>mid)update(x*2+1,mid+1,r,id,val);
    else update(x*2,l,mid,id,val);
    tree[x]=min(tree[x*2],tree[x*2+1]);
    mtree[x]=max(mtree[x*2],mtree[x*2+1]);
}
lld query(int x,int l,int r,int ll,int rr){
    if(l>rr || r<ll)return inf*inf;
    if(l>=ll && r<=rr)return tree[x];
    int mid=(l+r)/2;
    return min(query(x*2,l,mid,ll,rr),query(x*2+1,mid+1,r,ll,rr));
}
lld query2(int x,int l,int r,int ll,int rr){
    if(l>rr || r<ll)return -inf*inf;
    if(l>=ll && r<=rr)return mtree[x];
    int mid=(l+r)/2;
    return max(query2(x*2,l,mid,ll,rr),query2(x*2+1,mid+1,r,ll,rr));
}
void make_seg_tree(){

    lld minn=0;
    update(1,0,n,0,0);
    for(int i=1;i<=n;i++){
        pref[i]=pref[i-1]+p[i].w;
        update(1,0,n,i,pref[i]);
        minn=min(minn,pref[i]);

        rez=max(rez,pref[i]-minn);
    }
}
void process(vector<int> &vect){

    sort(vect.begin(),vect.end());

    int rr=vect.size()-1;
    int i;
    for(i=0;i<rr;i++,rr--){

        int id1=vect[i];
        int id2=vect[rr];

        swap(curr_here[id1],curr_here[id2]);
        swap(curr_pos[curr_here[id1]],curr_pos[curr_here[id2]]);
        swap(p[id1],p[id2]);

        pref[id1]=pref[id1-1]+p[id1].w;
        update(1,0,n,id1,pref[id1]);
    }

    for(;i<vect.size();i++){
        int id=vect[i];

        pref[id]=pref[id-1]+p[id].w;
        update(1,0,n,id,pref[id]);
    }
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%lld %lld %lld",&p[i].x,&p[i].y,&p[i].w),p[i].id=i;

    sort(p+1,p+n+1,srt);
    for(int i=1;i<=n;i++){
        curr_here[i]=p[i].id;
        curr_pos[p[i].id]=i;
    }
    extract_pairs();
    make_seg_tree();

    sort(mapa.begin(),mapa.end(),srt_pii);

    for(int pp=0;pp<mapa.size();pp++){
        vector<int> vect;
        vect.pb(mapa[pp].ss);
        pii pah=mapa[pp].ff;

        while(mapa[pp+1].ff==mapa[pp].ff){
            vect.pb(mapa[++pp].ss);
        }

        sort(vect.begin(),vect.end());
        vect.resize(unique(vect.begin(),vect.end())-vect.begin());
        int pos[vect.size()+10];
        memset(pos,0,sizeof(pos));


        for(int i=0;i<vect.size();i++){


            if(pos[i])continue;
            int id1=vect[i];
            id1=curr_pos[id1];
            pos[i]=1;

            vector<int>curr;
            curr.pb(id1);

            for(int j=i+1;j<vect.size();j++){
                if(pos[j])continue;
                int id2=vect[j];
                id2=curr_pos[id2];

                pii pom=get_line(p[id1],p[id2]);
                degree90(pom);

                if(pom==pah){
                    curr.pb(id2);
                    pos[j]=1;
                }
            }

            process(curr);
        }


        for(int i=0;i<vect.size();i++){
            int id=curr_pos[vect[i]];

            rez=max(rez,pref[id]-query(1,0,n,0,id-1));
            rez=max(rez,-pref[id]+query2(1,0,n,id,n));
        }
    }

    printf("%lld\n",rez);

return 0;
}
