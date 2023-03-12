/*

    idea:https://csacademy.com/contest/round-84/task/the-sprawl/solution/

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
const int maxn=250010;

struct edge{
    int a,b,w;
};

int sz[maxn],pr[maxn];
ll rez;

int inf=1e9;
int n;
vector<edge>e;

struct pt{
    int x,y,id;
}p[maxn];
bool srt(pt a,pt b){
    return (a.y<b.y)||(a.y==b.y && a.x<b.x);
}
bool srt2(pt a,pt b){
    return (a.x<b.x)||(a.x==b.x && a.y<b.y);
}
bool srt3(edge a,edge b){
    return a.w<b.w;
}

void make_edge(pt x,pt y){
   e.pb((edge){x.id,y.id,abs(x.x-y.x)+abs(x.y-y.y)});
}

void solve15(int l,int r){

    if(r==l)return;
    int mid=(l+r)/2;
    solve15(l,mid);/// donji
    solve15(mid+1,r);/// gornji

    /// resi donji
    int ptr=mid+1;
    int maxx=inf;
    int maxid=-1;
    for(int i=l;i<=mid;i++){
        while(ptr<=r && p[ptr].x+p[ptr].y<=p[i].x+p[i].y){
            if(maxx>-p[ptr].x+p[ptr].y){
                maxx=-p[ptr].x+p[ptr].y;
                maxid=ptr;
            }
            ptr++;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }

    ptr=mid;
    maxx=inf;
    maxid=-1;
    for(int i=r;i>=mid+1;i--){
        while(ptr>=l && p[ptr].x+p[ptr].y>=p[i].x+p[i].y){
            if(maxx>p[ptr].x-p[ptr].y){
                maxx=p[ptr].x-p[ptr].y;
                maxid=ptr;
            }
            ptr--;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }


    int br=0;
    pt niz[r-l+1];
    int ptrl=l;
    int ptrr=mid+1;
    while(ptrl<=mid && ptrr<=r){
        if(p[ptrl].x+p[ptrl].y<=p[ptrr].x+p[ptrr].y)niz[br++]=p[ptrl++];
        else niz[br++]=p[ptrr++];
    }
    while(ptrl<=mid)niz[br++]=p[ptrl++];
    while(ptrr<=r)niz[br++]=p[ptrr++];

    for(int i=0;i<br;i++)p[l+i]=niz[i];
}
void solve84(int l,int r){

    if(r==l)return;
    int mid=(l+r)/2;
    solve84(l,mid);/// donji
    solve84(mid+1,r);/// gornji

    /// resi donji
    int ptr=r;
    int maxx=inf;
    int maxid=-1;
    for(int i=mid;i>=l;i--){
        while(ptr>=mid+1 && p[ptr].x-p[ptr].y>=p[i].x-p[i].y){
            if(maxx>p[ptr].x+p[ptr].y){
                maxx=p[ptr].x+p[ptr].y;
                maxid=ptr;
            }
            ptr--;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }

    ptr=l;
    maxx=inf;
    maxid=-1;
    for(int i=mid+1;i<=r;i++){
        while(ptr<=mid && p[ptr].x-p[ptr].y<=p[i].x-p[i].y){
            if(maxx>-p[ptr].x-p[ptr].y){
                maxx=-p[ptr].x-p[ptr].y;
                maxid=ptr;
            }
            ptr++;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }


    int br=0;
    pt niz[r-l+1];
    int ptrl=l;
    int ptrr=mid+1;
    while(ptrl<=mid && ptrr<=r){
        if(p[ptrl].x-p[ptrl].y<=p[ptrr].x-p[ptrr].y)niz[br++]=p[ptrl++];
        else niz[br++]=p[ptrr++];
    }
    while(ptrl<=mid)niz[br++]=p[ptrl++];
    while(ptrr<=r)niz[br++]=p[ptrr++];

    for(int i=0;i<br;i++)p[l+i]=niz[i];
}
void solve26(int l,int r){

    if(r==l)return;
    int mid=(l+r)/2;
    solve26(l,mid);/// donji
    solve26(mid+1,r);/// gornji

    /// resi donji
    int ptr=mid+1;
    int maxx=inf;
    int maxid=-1;
    for(int i=l;i<=mid;i++){
        while(ptr<=r && p[ptr].x+p[ptr].y<=p[i].x+p[i].y){
            if(maxx>p[ptr].x-p[ptr].y){
                maxx=-p[ptr].x-p[ptr].y;
                maxid=ptr;
            }
            ptr++;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }

    ptr=mid;
    maxx=inf;
    maxid=-1;
    for(int i=r;i>=mid+1;i--){
        while(ptr>=l && p[ptr].x+p[ptr].y>=p[i].x+p[i].y){
            if(maxx>-p[ptr].x+p[ptr].y){
                maxx=-p[ptr].x+p[ptr].y;
                maxid=ptr;
            }
            ptr--;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }


    int br=0;
    pt niz[r-l+1];
    int ptrl=l;
    int ptrr=mid+1;
    while(ptrl<=mid && ptrr<=r){
        if(p[ptrl].x+p[ptrl].y<=p[ptrr].x+p[ptrr].y)niz[br++]=p[ptrl++];
        else niz[br++]=p[ptrr++];
    }
    while(ptrl<=mid)niz[br++]=p[ptrl++];
    while(ptrr<=r)niz[br++]=p[ptrr++];

    for(int i=0;i<br;i++)p[l+i]=niz[i];

}
void solve37(int l,int r){

    if(r==l)return;
    int mid=(l+r)/2;
    solve37(l,mid);/// donji
    solve37(mid+1,r);/// gornji

    /// resi donji
    int ptr=mid+1;
    int maxx=inf;
    int maxid=-1;
    for(int i=l;i<=mid;i++){
        while(ptr<=r && p[ptr].x-p[ptr].y<=p[i].x-p[i].y){
            if(maxx>p[ptr].x+p[ptr].y){
                maxx=p[ptr].x+p[ptr].y;
                maxid=ptr;
            }
            ptr++;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }

    ptr=mid;
    maxx=inf;
    maxid=-1;
    for(int i=r;i>=mid+1;i--){
        while(ptr>=l && p[ptr].x-p[ptr].y>=p[i].x-p[i].y){
            if(maxx>-p[ptr].x-p[ptr].y){
                maxx=-p[ptr].x-p[ptr].y;
                maxid=ptr;
            }
            ptr--;
        }
        if(maxid!=-1)make_edge(p[i],p[maxid]);
    }


    int br=0;
    pt niz[r-l+1];
    int ptrl=l;
    int ptrr=mid+1;
    while(ptrl<=mid && ptrr<=r){
        if(p[ptrl].x-p[ptrl].y<=p[ptrr].x-p[ptrr].y)niz[br++]=p[ptrl++];
        else niz[br++]=p[ptrr++];
    }
    while(ptrl<=mid)niz[br++]=p[ptrl++];
    while(ptrr<=r)niz[br++]=p[ptrr++];

    for(int i=0;i<br;i++)p[l+i]=niz[i];
}

int root(int x){
    if(pr[x]==x)return x;
    else return pr[x]=root(pr[x]);
}
void join(int x,int y,ll w){

    x=root(x);
    y=root(y);

    if(x==y)return;

    rez=(rez+(ll)sz[x]*sz[y]*w);

    pr[x]=y;
    sz[y]+=sz[x];
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d %d",&p[i].x,&p[i].y);
        p[i].id=i;
    }

    sort(p+1,p+n+1,srt);
    solve15(1,n);

    sort(p+1,p+n+1,srt);
    solve84(1,n);

    sort(p+1,p+n+1,srt2);
    solve26(1,n);

    sort(p+1,p+n+1,srt2);
    solve37(1,n);

    sort(e.begin(),e.end(),srt3);


    for(int i=1;i<=n;i++)sz[i]=1,pr[i]=i;
    for(int i=0;i<e.size();i++)
        join(e[i].a,e[i].b,e[i].w/2);


    printf("%lld\n",rez);

	return 0;
}
