/*

    idea: https://img.atcoder.jp/agc037/editorial.pdf

    my code is probably similair to the editorial

*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;
string s,rez,glob,cs[3];
int n,k,br;
vector<pii>candidates;
void do1(){

    string p=s+s;
    reverse(p.begin()+s.size(),p.end());

    for(int i=0;i<=s.size();i++){
        rez=min(rez,p.substr(i,n));
    }
}
void do13(){

    char minel='z';
    for(int i=0;i<n;i++)minel=min(minel,s[i]);
    for(int i=0;i<n;i++)rez[i]=minel;
}
void radi(pii x,int pcnt){

    int sz=x.ss;

    for(int j=1+pcnt;j<=k;j++){


        string p=glob+glob;
        reverse(p.begin()+s.size(),p.end());

        if(j!=k){
            int pos=n-1+sz;
            if(pos>=(int)p.size())break;

            glob=p.substr(pos-n+1,n);

            sz*=2;
        }
        else{
            if(n-1-sz+1<0)break;
            glob=p.substr(n-1-sz+1,n);
        }
    }
}
void go(){

    char minel='z';
    for(int i=0;i<n;i++)minel=min(minel,s[i]);

    if(s[n-1]==minel){
        int sz=1;
        while(n-sz-1>=0 && s[n-sz-1]==minel)sz++;
        candidates.pb({n-1,sz});

        cs[br++]=s;
    }

    string p=s+s;
    string prez="";
    for(int i=0;i<n;i++)prez.pb('z'+1);
    reverse(p.begin()+s.size(),p.end());
    for(int i=s.size()-1;i<p.size();i++){
        string bla=p.substr(i-n+1,n);
        reverse(bla.begin(),bla.end());

        prez=min(prez,bla);
    }
    reverse(prez.begin(),prez.end());

    int sz=1;
    cs[br++]=prez;
    while(n-sz-1>=0 && prez[n-sz-1]==minel)sz++;
    candidates.pb({n-2,sz});


    for(int i=0;i<candidates.size();i++){

        glob=cs[i];

        if(candidates[i].ff==n-1){
            radi(candidates[i],0);
        }
        else{
            radi(candidates[i],1);
        }
        rez=min(rez,glob);
    }
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&k);
    cin>>s;

    for(int i=1;i<=n;i++)rez.pb('z'+1);

    if(k==1)do1();
    else if(k>=13)do13();
    else go();

    cout<<rez<<endl;

	return 0;
}
