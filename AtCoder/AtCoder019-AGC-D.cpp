/*

    idea:  https://img.atcoder.jp/agc019/editorial.pdf

*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=2010;

string a,b;
int n,cleft[maxn],cright[maxn];

int probaj(int sp){

    vector<pii>cand;
    for(int i=0;i<n;i++)
        if(b[i]!=a[(i+sp)%n])cand.pb({cleft[(i+sp)%n],(i+sp)%n});


    int ret=cand.size();
    if(cand.size()==0)return min(sp,n-sp);

    sort(cand.begin(),cand.end());

    int mx=0;
    int ret2=1e9;
    for(int i=cand.size()-1;i>=0;i--){

        int mleft=cand[i].ff;
        int id=cand[i].ss;

        /// left->right
        if(mx>0)ret2=min(ret2,mleft*2+mx+min( (sp+mx)%n,n-(sp+mx)%n ));
        else ret2=min(ret2,mleft+min( (sp-mleft+n)%n,n-(sp-mleft+n)%n ));

        if(mleft>0)ret2=min(ret2,mleft+mx*2+min( (sp-mleft+n)%n,n-(sp-mleft+n)%n ));
        else ret2=min(ret2,mx+min( (sp+mx)%n,n-(sp+mx)%n ));

        mx=max(mx,cright[id]);
    }

    int mleft=0;
    if(mx>0)ret2=min(ret2,mleft*2+mx+min( (sp+mx)%n,n-(sp+mx)%n ));
    else ret2=min(ret2,mleft+min( (sp-mleft+n)%n,n-(sp-mleft+n)%n ));

    if(mleft>0)ret2=min(ret2,mleft+mx*2+min( (sp-mleft+n)%n,n-(sp-mleft+n)%n ));
    else ret2=min(ret2,mx+min( (sp+mx)%n,n-(sp+mx)%n ));


    return ret+ret2;
}

int sol(){

    int c1=0;
    for(int i=0;i<n;i++)if(b[i]=='1')c1++;
    int c2=0;
    for(int i=0;i<n;i++)if(a[i]=='1')c2++;
    if(c1==0 && c2==0)return 0;
    if(c1==0)return -1;

    for(int i=0;i<n;i++){

        /// cleft
        int p=i;
        int br=0;
        while(1){
            if(b[p]=='1'){
                cleft[i]=br;
                break;
            }
            p--;
            if(p<0)p+=n;
            br++;
        }

        p=i;
        br=0;
        while(1){
            if(b[p]=='1'){
                cright[i]=br;
                break;
            }
            p++;
            if(p>=n)p-=n;
            br++;
        }
    }


    int ret=1e9;

    for(int i=0;i<n;i++)
        ret=min(ret,probaj(i));

    return ret;

}

int main(){

    ///freopen("test.txt","r",stdin);


    cin>>a>>b;
    n=a.size();

    printf("%d\n",sol());


    return 0;
}
