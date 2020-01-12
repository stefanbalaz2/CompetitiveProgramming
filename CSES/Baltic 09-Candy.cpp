/*

    idea: https://github.com/Szawinis/CompetitiveProgramming/blob/master/Olympiad/Baltic/Baltic09-candy.cpp

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define ull unsigned long long
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
vector<pair<pii,int> >rez;
vector<int>vect;
int n;
pii p[100010];
bool srt(pii a,pii b){
    pii a1={a.ff+a.ss,a.ss-a.ff};
    pii b1={b.ff+b.ss,b.ss-b.ff};

    return a1<b1;
}
int gt(pii a){
    return a.ss-a.ff;
}
int check(int x){

    if(x<vect[vect.size()-1])return vect.size();

    int l=0;
    int r=vect.size()-1;
    int sr,ret=vect.size();
    while(l<=r){
        sr=(l+r)/2;
        if(vect[sr]<=x){
            ret=sr;
            r=sr-1;
        }
        else l=sr+1;
    }
return ret;
}
int main(){


    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d %d",&p[i].ff,&p[i].ss);

    sort(p+1,p+n+1,srt);

    vect.pb(gt(p[1]));
    rez.pb({p[1],vect.size()-1});
    for(int i=2;i<=n;i++){
        int id=gt(p[i]);

        int x=check(id);
        if(x==vect.size()){
            vect.pb(id);
            rez.pb({p[i],vect.size()-1});
        }
        else{
            vect[x]=id;
            rez.pb({p[i],x});
        }

    }

    printf("%d\n",vect.size());
    for(int i=0;i<rez.size();i++){
        printf("%d %d %d\n",rez[i].ff.ff,rez[i].ff.ss,rez[i].ss+1);
    }

return 0;
}
