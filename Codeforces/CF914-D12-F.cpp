/*

    idea: https://codeforces.com/blog/entry/57250

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int bsize=300;
const int alph=26;
const int maxn=1e5+10;
int blp[bsize*2+10],brp[bsize*2+10],br,n,ind[maxn];
string s;
struct SuffixAutomaton{

    int last,len[bsize*2+1],link[bsize*2+1],nxt[bsize*2+1][alph],cnt=0,dp[bsize*2+1];

    void build(string &s){

        cnt=0;
        last=0;
        link[0]=-1;
        memset(nxt,-1,sizeof(nxt));
        memset(dp,0,sizeof(dp));
        for(int i=0;i<s.size();i++){
            if(cnt>bsize*2)while(1){}
            push(s[i]-'a');
        }


        calc();
    }

    void push(int c){

        int x=last;
        len[++cnt]=len[x]+1;
        last=cnt;
        dp[last]=1;

        int p=-1;
        while(x!=-1){
            if(nxt[x][c]==-1)nxt[x][c]=last;
            else{
                p=nxt[x][c];
                break;
            }
            x=link[x];
        }

        if(x==-1){
            link[last]=0;
            return;
        }
        if(len[x]+1==len[p]){
            link[last]=p;
            return;
        }

        int clone=++cnt;
        link[clone]=link[p];
        link[p]=clone;
        link[last]=clone;
        len[clone]=len[x]+1;
        for(int i=0;i<alph;i++)nxt[clone][i]=nxt[p][i];

        while(x!=-1){
            if(nxt[x][c]==p)nxt[x][c]=clone;
            else break;
            x=link[x];
        }
    }

    bool operator()(int x,int y){
        return len[x]>len[y];
    }

    void calc(){

        pii niz[cnt*2+1];
        for(int i=0;i<=cnt;i++)niz[i]={-len[i],i};

        sort(niz,niz+cnt+1);

        for(int i=0;i<=cnt;i++){
            int id=niz[i].ss;
            if(id==0)continue;
            dp[link[id]]+=dp[id];
        }
    }

    int go(int x,string &s,int pos){
        if(x==-1)return 0;
        if(pos==s.size())return dp[x];
        return go(nxt[x][s[pos]-'a'],s,pos+1);
    }

    int query(string &s){
        return go(0,s,0);
    }

}sa[800];
int algz(string &s2,string &p){

    string s=p+'$'+s2;


    int ret=0;
    int r=0;
    int l=0;
    int z[s.size()+10];
    memset(z,0,sizeof(z));
    for(int i=1;i<s.size();i++){

        if(i>r){
            l=i;
            r=l-1;
            while(r+1<s.size() && s[r+1]==s[r-l+1])r++;
            z[i]=r-l+1;
        }
        else{
            if(i+z[i-l]-1>=r){
                l=i;
                while(r+1<s.size() && s[r+1]==s[r-l+1])r++;
                z[i]=r-l+1;
            }
            else{
                z[i]=z[i-l];
            }
        }
    }


    for(int i=0;i<s.size();i++)
        if(z[i]==p.size())ret++;

    return ret;
}
void make_blocks(){

    int l=1;
    int r=bsize;
    while(1){

        blp[++br]=l;
        brp[br]=r;

        l+=bsize;
        r+=bsize;

        if(r>n)r=n;
        if(l>n)break;
    }

    for(int i=1;i<=br;i++){
        for(int j=blp[i];j<=brp[i];j++)ind[j]=i;

        string pom=s.substr(blp[i]-1,brp[i]-blp[i]+1);
        sa[i].build(pom);
    }
}
int query(int l,int r,string &p){

    int lid=ind[l];
    int rid=ind[r];

    if(lid==rid){
        string pom=s.substr(l-1,r-l+1);
        return algz(pom,p);
    }

    int ret=0;
    string pom=s.substr(l-1,brp[lid]-l+1);
    ret+=algz(pom,p);
    pom=s.substr(blp[rid]-1,r-blp[rid]+1);
    ret+=algz(pom,p);



    for(int i=lid+1;i<rid;i++)ret+=sa[i].query(p);

    for(int i=lid;i<rid;i++){

        pom.clear();
        for(int j=max(max(blp[i],brp[i]-(int)p.size()+2),l);j<=brp[i];j++)pom.pb(s[j-1]);
        for(int j=blp[i+1];j<=min(min(blp[i+1]+(int)p.size()-2,brp[i+1]),r);j++)pom.pb(s[j-1]);

        ret+=algz(pom,p);
    }

    return ret;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    cin>>s;

    n=s.size();

    make_blocks();

    int q;
    scanf("%d",&q);

    int brr=0;
    while(q--){

        int tip;
        scanf("%d",&tip);
        if(tip==1){
            int id;
            char c;
            cin>>id>>c;

            s[id-1]=c;
            int bid=ind[id];
            string p=s.substr(blp[bid]-1,brp[bid]-blp[bid]+1);
            sa[bid].build(p);
        }
        else{
            int l,r;
            string qq;
            cin>>l>>r>>qq;

            brr++;

            if(qq.size()>bsize){
                string p=s.substr(l-1,r-l+1);
                int pr=algz(p,qq);

                printf("%d\n",pr);
            }
            else{
                int pr=query(l,r,qq);
                printf("%d\n",pr);
            }
        }

    }

	return 0;
}
