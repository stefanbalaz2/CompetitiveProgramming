/**

    https://www.spoj.com/problems/SARRAY/
*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;


string s;
const int maxn=1e5+10;
int val[maxn],tval[maxn],niz[maxn];
vector<int>pvect[maxn];
bool srt(int a,int b){
    return val[a]<val[b];
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    cin>>s;
    s.pb('$');
    int n=s.size();
    for(int i=0;i<n;i++){
        val[i]=s[i]+1;
        if(i==n-1)val[i]=0;
        niz[i]=i;
    }
    sort(niz,niz+n,srt);

    int h=log2(n)+1;
    for(int i=0;i<h;i++){

        for(int j=0;j<n;j++){
            int id=niz[j];
            pvect[ val[(id-(1<<i)+n)%n] ].pb((id-(1<<i)+n)%n);
        }

        int curr=n-1;
        for(int j=max(n,1000)-1;j>=0;j--){

            while(pvect[j].size()){
                niz[curr--]=pvect[j].back();
                pvect[j].pop_back();
            }
        }

        tval[niz[0]]=0;
        for(int j=1;j<n;j++){

            int id1=niz[j];
            int id0=niz[j-1];

            if( val[id1]!=val[id0] || ( val[id1]==val[id0] && val[ (id1+(1<<i))%n ]!=val[(id0+(1<<i))%n] ) )tval[id1]=tval[id0]+1;
            else tval[id1]=tval[id0];

        }

        for(int j=0;j<n;j++)val[j]=tval[j];

    }

    for(int i=1;i<n;i++)printf("%d\n",niz[i]);

    return 0;
}
