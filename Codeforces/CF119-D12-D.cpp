/*

    idea:   https://codeforces.com/blog/entry/3229

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef multiset<ll>::iterator sit;
const int maxn=1e6+10;
string a,b;
int z1[maxn*2],z2[maxn*2],niz[maxn*2],minn[maxn*2];
vector<pii>vect;
string reversed(string b){
    reverse(b.begin(),b.end());
    return b;
}
void calcZ(string p,string s,int z[maxn*2]){

    string pom=p+(char)(30)+s;

    int n=pom.size();
    int l=0;
    int r=0;
    for(int i=1;i<pom.size();i++){

        if(i>r){

            l=i;
            r=l-1;
            while(pom[r+1]==pom[r-l+1])r++;
            z[i]=r-l+1;

        }
        else{

            if(i+z[i-l]-1>=r){
                l=i;
                while(pom[r+1]==pom[r-l+1])r++;
                z[i]=r-l+1;
            }
            else{
                z[i]=z[i-l];
            }

        }

    }

    for(int i=0;i<s.size();i++){
        z[i]=z[i+p.size()+1];
    }

}
bool srt(pii a,pii b){
    return a>b;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    getline(cin,a);
    getline(cin,b);

    if(a.size()!=b.size()){
        printf("-1 -1\n");
        return 0;
    }

    calcZ(reversed(a),b,z1);
    calcZ(b,a,z2);

    for(int i=0;i<b.size();i++){
        niz[i]=i+1+z1[i+1];
        vect.pb({niz[i],i});
    }
    vect.pb({z1[0],-1});
    sort(vect.begin(),vect.end(),srt);

    minn[0]=vect[0].ss;
    for(int i=1;i<vect.size();i++){
        minn[i]=min(minn[i-1],vect[i].ss);
    }

    pii rez={-1,-1};
    for(int i=0;i<a.size()-1;i++){
        if(a[i]!=b[b.size()-i-1])break;

        int diff=b.size()-i-1;
        int l=0;

        int r=vect.size()-1;
        int sr,ret=-1;

        while(l<=r){
            sr=(l+r)/2;
            if(vect[sr].ff>=diff){
                ret=sr;
                l=sr+1;
            }
            else r=sr-1;
        }

        if(ret==-1)continue;
        if(minn[ret]>=z2[i+1])continue;

        rez={i,i+minn[ret]+2};

    }

    printf("%d %d\n",rez.ff,rez.ss);

    return 0;
}

