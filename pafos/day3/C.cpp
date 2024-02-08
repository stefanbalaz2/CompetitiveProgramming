#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int maxk=110;
unordered_map<ll,long double>mapa[maxk];
vector<int>a;
ll ccc=0;
int n,k;
ll pw10n;


ll get_state(int mask,vector<int>b){/// smanji state maske, jer ces overflow

    ll ret=0;
    ret=mask;
    ret=ret*10+1;

    b.resize(n);
    for(int i=0;i<b.size();i++)
        ret=ret*10+b[i];

    return ret;
}
int get_ways(vector<int>&pom,vector<int>&b){

    int pt=pom.size();
    int ways=1;
    for(int i=b.size()-1;i>=0;i--){
        while(pt>0 && pom[pt-1]>b[i])pt--;
        ways*=max(0,i-pt+1);
    }
    return ways;
}
pii calc_prob3(int mask,vector<int>b,int p){

    vector<int>pom;
    for(int i=0;i<n;i++)
        if(mask&(1<<i)){
            pom.pb(a[i]);
        }

    vector<pii>cand;
    for(int i=0;i<b.size();i++){
        cand.pb({b[i],i});
    }
    sort(cand.begin(),cand.end());
    int e=0;
    int vv=b[p];
    for(int i=0;i<b.size();i++){
        b[i]=cand[i].ff;
        if(cand[i].ff==vv && e==0){
            p=i;
            e=1;
        }
    }
    int ways=get_ways(pom,b);
    int ps=-1;
    int pcnt=0;
    for(int i=0;i<pom.size();i++){
        if(pom[i]==b[p]){
            pcnt++;
            ps=i;
        }
    }
    if(ps==-1){
        return {0,1};
    }
    b.erase(b.begin()+p);
    pom.erase(pom.begin()+ps);
    int ways2=get_ways(pom,b)*pcnt;

    return {ways2,ways+ways2};

}
long double go(int mask,vector<int>b,int k){

    if(k==0)return 0;
    ll state=get_state(mask,b);


    if(mapa[k].find(state)!=mapa[k].end())return mapa[k][state];

    ccc++;

    long double &s=mapa[k][state];
    s=0;

    vector<int>pom;
    bool bpos[15];
    memset(bpos,0,sizeof(bpos));
    for(int i=0;i<b.size();i++){

        if(bpos[b[i]]){
            pom.pb(b[i]);
            continue;
        }
        bpos[b[i]]=1;

        b[i]++;
        pii p=calc_prob3(mask,b,i);
        vector<int>nv=pom;
        for(int j=i+1;j<b.size();j++)nv.pb(b[j]);

        long double pd=0;
        if(p.ff!=0){
            int bpos;
            for(int j=0;j<a.size();j++){
                if(a[j]==b[i] && (mask&(1<<j))!=0){
                    bpos=j;
                    break;
                }
            }
            pd+=((long double)(p.ff)/(long double)p.ss)*(go(mask^(1<<bpos),nv,k-1)+1);
        }
        if( p.ss!=0 && p.ff!=p.ss ){
            pd+=( (long double)(p.ss-p.ff)/(long double)p.ss )*go(mask,b,k-1);
        }
        s=max(s,pd);
        b[i]--;

        pom.pb(b[i]);
    }

    return s;
}

int main(){

    ///freopen("test.txt","r",stdin);

    for(int i=0;i<maxk;i++){
        mapa[i].reserve(1024);
        mapa[i].max_load_factor(0.25);
    }

    scanf("%d %d",&n,&k);
    for(int i=0;i<n;i++){
        int cc;
        scanf("%d",&cc);
        a.pb(cc);
    }
    sort(a.begin(),a.end());

    vector<int>b(n,0);
    cout<<fixed<<setprecision(8)<<go((1<<n)-1,b,k)<<endl;

    return 0;
}
