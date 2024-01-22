/**

    problem: https://codeforces.com/contest/1423/problem/H

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=1e5+10;

struct dsu{

    vector<int>p,sz;
    int n;
    int op;
    vector<pair<int,pair<int*,int>>>stek;

    dsu(){}

    dsu(int n){
        this->n=n;
        p.resize(n+1);
        sz.resize(n+1);
        op=0;
        for(int i=1;i<=n;i++){
            p[i]=i;
            sz[i]=1;
        }
    }

    int root(int x){
        if(p[x]==x)return x;
        return root(p[x]);
    }

    void join(int u,int v){

        op++;

        u=root(u);
        v=root(v);

        if(u==v)return;

        if(sz[u]<sz[v])swap(u,v);

        stek.pb({op,{&p[v],p[v]} });
        stek.pb({op,{&sz[u],sz[u]} });

        p[v]=u;
        sz[u]+=sz[v];

    }

    void pop(){
        while(stek.size() && stek.back().ff==op){
            (*stek.back().ss.ff)=stek.back().ss.ss;
            stek.pop_back();
        }
        op--;
    }

    int get_sz(int x){
        x=root(x);
        return sz[x];
    }

};

struct queue_dsu{

    int n,op_cnt;
    dsu *d;
    vector<pair<bool,pii>>stek;
    bool phase;

    queue_dsu(int n){
        this->n=n;
        d=new dsu(n);
        phase=0;
        op_cnt=0;
    }


    void push(pii e){
        stek.pb({1,e});
        d->join(e.ff,e.ss);
    }

    void pop(){

        if(phase==0){
            phase=1;
            op_cnt=stek.size();

            for(int i=1;i<=op_cnt;i++)d->pop();
            reverse(stek.begin(),stek.end());
            for(int i=0;i<stek.size();i++){
                stek[i].ff=0;
                d->join(stek[i].ss.ff,stek[i].ss.ss);
            }
        }


        if(stek.back().ff!=0){

            vector<pii>tmp[2];
            int acnt=0;
            int balance=0;
            while(stek.size() && acnt<op_cnt){

                acnt+=(!stek.back().ff);
                tmp[stek.back().ff].pb(stek.back().ss);
                if(stek.back().ff==0)balance--;
                else balance++;
                stek.pop_back();
                d->pop();

                if(balance==0)break;
            }

            for(int i=1;i>=0;i--)
                while(tmp[i].size()){
                    stek.pb({i,tmp[i].back()});
                    d->join(tmp[i].back().ff,tmp[i].back().ss);
                    tmp[i].pop_back();
                }

        }

        d->pop();
        stek.pop_back();

        op_cnt--;
        if(op_cnt==0)phase=0;
    }

    int get_sz(int x){
        return d->get_sz(x);
    }

};


int main(){

    ///freopen("test.txt","r",stdin);

    int n,qp,k;
    scanf("%d %d %d",&n,&qp,&k);
    queue_dsu qd(n);
    queue<pair<int,pii>>q;
    int cd=0;
    while(qp--){

        int tip;
        scanf("%d",&tip);
        if(tip==1){
            int u,v;
            scanf("%d %d",&u,&v);
            qd.push({u,v});
            q.push({cd,{u,v}});
        }
        else if(tip==2){
            int x;
            scanf("%d",&x);
            printf("%d\n",qd.get_sz(x));
        }
        else{
            cd++;
            while(q.size() && q.front().ff<=cd-k){
                q.pop();
                qd.pop();
            }
        }

    }


    return 0;
}
