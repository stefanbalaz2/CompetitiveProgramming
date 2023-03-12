/*

    idea: traversing the "trie" with the help of a function that counts how many times
    a string p appears in the nth fibonacci, it works by keeping the prefix and the suffix of the fibonacci numbers

*/
#include<bits/stdc++.h>
#define ss second
#define ff first
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=210;
int n,m,maxstep;
ll k;
string rez;
int zalg(string p,string s){

    string pom=p+'$'+s;

    int l=0;
    int r=-1;
    int z[pom.size()];
    memset(z,0,sizeof(z));
    for(int i=1;i<pom.size();i++){

        if(i>r){

            l=i;
            r=i-1;
            while(r+1<pom.size() && pom[r+1]==pom[r-l+1])r++;
            z[i]=r-l+1;
        }
        else{

            if(i+z[i-l]-1>=r){

                l=i;
                while(r+1<pom.size() && pom[r+1]==pom[r-l+1])r++;
                z[i]=r-l+1;

            }
            else z[i]=z[i-l];

        }

    }

    int ret=0;
    for(int i=0;i<pom.size();i++)
        if(z[i]==p.size())ret++;

    return ret;
}
ll izbroj(string &s){

    string prvpref="0",prvsuff="0",currpref="1",currsuff="1";
    ll cntprv=0;
    ll cntcurr=0;

    if(s==prvpref)cntprv=1;
    else if(s==currpref)cntcurr=1;

    if(s.size()==1){
        prvpref.clear();
        prvsuff.clear();
        currpref.clear();
        currsuff.clear();
    }

    for(int i=2;i<=maxstep;i++){

        string pom1=currpref;
        string pom2=currsuff;

        swap(cntprv,cntcurr);
        if(cntcurr>k)return cntcurr;
        cntcurr+=cntprv;
        cntcurr+=zalg(s,prvsuff+currpref);


        ///correct suffix
        int kolko=s.size()-1-currsuff.size();
        string pp;
        for(int j=max(0,(int)prvsuff.size()-kolko);j<prvsuff.size();j++)pp.pb(prvsuff[j]);
        for(int j=0;j<currsuff.size();j++)pp.pb(currsuff[j]);
        currsuff=pp;

        ///correct prefix
        kolko=s.size()-1-prvpref.size();
        for(int j=0;j<min(kolko,(int)currpref.size());j++)prvpref.pb(currpref[j]);
        currpref=prvpref;

        prvpref=pom1;
        prvsuff=pom2;
    }

    return cntcurr;
}
ll get_suff(string &s,string &currsuff){

    string prvpref="0",prvsuff="0",currpref="1";
    currsuff="1";

    for(int i=2;i<=maxstep;i++){

        string pom1=currpref;
        string pom2=currsuff;

        ///correct suffix
        int kolko=s.size()-currsuff.size();
        string pp;
        for(int j=max(0,(int)prvsuff.size()-kolko);j<prvsuff.size();j++)pp.pb(prvsuff[j]);
        for(int j=0;j<currsuff.size();j++)pp.pb(currsuff[j]);
        currsuff=pp;

        ///correct prefix
        kolko=s.size()-prvpref.size();
        for(int j=0;j<min(kolko,(int)currpref.size());j++)prvpref.pb(currpref[j]);
        currpref=prvpref;

        prvpref=pom1;
        prvsuff=pom2;
    }

    return 0;
}
bool jeste_sub(string &x){

    string pom;
    get_suff(x,pom);


    for(int i=x.size()-1;i>=0;i--)
        if(x[i]!=pom[pom.size()-(x.size()-i)])return false;

    return true;
}
void build(){

    rez="";

    for(int i=0;i<m;i++){


        rez.pb('0');
        ll pom=izbroj(rez);

        if(pom<k){/// nije 0
            rez[rez.size()-1]='1';
            k-=pom;
        }

        if(jeste_sub(rez))k--;

        if(k==0)break;

    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %lld %d",&n,&k,&m);

    maxstep=n;

    build();

    cout<<rez<<endl;

return 0;
}
