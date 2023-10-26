/**

    Pick ur own Nim
    https://codeforces.com/gym/102156/problem/D

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=130;

struct xorbasis{

    vector<ll>base;

    void add_vector(ll x){
        base.pb(x);
    }

    int size(){return base.size();}
    void clear(){base.clear();}

    void gaus(){

        for(int i=0;i<base.size();i++){
            for(int j=i;j<base.size();j++){
                if(base[i]<base[j])swap(base[i],base[j]);
            }
            for(int j=i+1;j<base.size();j++)
                base[j]=min(base[j],base[j]^base[i]);
        }

        while(base.size() && base.back()==0)base.pop_back();
    }
    ll minimize(ll x){

        for(int i=0;i<base.size();i++)
            x=min(x,x^base[i]);

        return x;
    }

};
struct gse{

    int color;
    ll vec;
    bool in_s;

};
vector<gse>groundset;
vector<int>s;
xorbasis sbase,wbase[5010];
int color[maxn],ende[5010];
int n,m;

void prepare_xor(){

    sbase.clear();
    for(int i=0;i<s.size();i++)
        wbase[s[i]].clear();

    for(int i=0;i<s.size();i++){
        int id=s[i];
        sbase.add_vector(groundset[id].vec);
        for(int j=0;j<s.size();j++){
            if(j==i)continue;
            wbase[s[j]].add_vector(groundset[id].vec);
        }
    }
    for(int i=0;i<s.size();i++)
        wbase[s[i]].gaus();
    sbase.gaus();
}
void prepare_color(){

    memset(color,0,sizeof(color));
    for(int i=0;i<s.size();i++)color[groundset[s[i]].color]++;

}
bool can_put_in_xor(int x){
    if(sbase.minimize(groundset[x].vec)==0)return false;
    return true;
}
bool can_put_in_color(int x){
    if(color[groundset[x].color]!=0)return false;
    return true;
}
bool can_switch_xor(int x,int y){
    if(wbase[x].minimize(groundset[y].vec)==0)return false;
    return true;
}
bool can_switch_color(int x,int y){
    color[groundset[x].color]--;
    bool ret=false;
    if(color[groundset[y].color]==0)ret=true;
    color[groundset[x].color]++;
    return ret;
}

bool augment(){

    prepare_xor();
    prepare_color();

    vector<int>y1,y2;
    for(int i=0;i<groundset.size();i++){
        if(groundset[i].in_s)continue;
        if(can_put_in_xor(i))y2.pb(i);
        if(can_put_in_color(i))y1.pb(i);
    }

    queue<int>q;
    vector<int>p(groundset.size(),-1);
    for(int i=0;i<y1.size();i++){
        q.push(y1[i]);
        p[y1[i]]=y1[i];
    }
    memset(ende,0,sizeof(ende));
    for(int i=0;i<y2.size();i++)
        ende[y2[i]]=1;

    int id=-1;

    while(q.size()){

        int x=q.front();
        q.pop();

        if(groundset[x].in_s){

            for(int i=0;i<groundset.size();i++){
                if(groundset[i].in_s)continue;
                if(p[i]!=-1)continue;
                if(!can_switch_color(x,i))continue;

                p[i]=x;
                q.push(i);
            }

        }
        else{

            if(ende[x]){
                id=x;
                break;
            }

            for(int i=0;i<groundset.size();i++){
                if(!groundset[i].in_s)continue;
                if(p[i]!=-1)continue;
                if(!can_switch_xor(i,x))continue;

                p[i]=x;
                q.push(i);
            }

        }

    }

    if(id==-1)return false;

    vector<int>path;
    while(1){
        path.pb(id);
        if(p[id]==id)break;
        id=p[id];
    }

    for(int i=0;i<path.size();i++){
        int id=path[i];
        groundset[id].in_s^=1;
    }

    s.clear();
    for(int i=0;i<groundset.size();i++)
        if(groundset[i].in_s)s.pb(i);

    return true;

}
void go(){


    while(augment()){}

    if(s.size()<n+m){
        printf("-1\n");
        return;
    }

    vector<pii>rez;
    for(int i=0;i<s.size();i++){
        int id=s[i];
        rez.pb({ groundset[id].color,id });
    }
    sort(rez.begin(),rez.end());
    xorbasis pp;
    for(int i=n;i<rez.size();i++)
        printf("%lld\n",groundset[rez[i].ss].vec );

}

int main(){


    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        ll a;
        scanf("%lld",&a);
        groundset.pb({i,a,false});
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        int k;
        scanf("%d",&k);
        for(int j=0;j<k;j++){
            ll a;
            scanf("%lld",&a);
            groundset.pb({i+n,a,false});
        }
    }

    go();

    return 0;
}
