/**

    problem: https://vjudge.net/problem/UVA-719

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

const int maxn=1e4+10;

int go(string s){

    vector<string>fact;

    int i=0;
    s=s+s;
    int n=s.size();
    int rez=-1;
    int rez2=-1;
    while(i<n){

        if(i<n/2)rez=i;
        int k=i;
        int j=i+1;
        while(j<n && s[k]<=s[j]){
            if(s[k]<s[j])k=i;
            else k++;
            j++;
        }

        while(i<=k){
            fact.pb(s.substr(i,j-k));
            if(i<n/2)rez2=i;
            i+=j-k;
        }

    }



    return rez+1;
}

int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        string s;
        cin>>s;
        printf("%d\n",go(s));

    }

    return 0;
}
