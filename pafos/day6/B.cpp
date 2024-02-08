#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

vector<int>get_full(int n){

    if(n==0){
        vector<int>ret;
        ret.pb(1);
        return ret;
    }

    vector<int>pom=get_full(n-1);



    int pp=pom.size();
    for(int i=pp-1;i>=0;i--)pom.pb(pom[i]);
    pom.pb(0);
    for(int i=pp;i<pom.size();i++)pom[i]|=(1<<n);

    return pom;
}
bool prefix(int x,int n){

    int f=0;
    int cnt=0;
    int e=1;
    for(int i=n;i>=0;i--){
        if(x&(1<<i)){
            f++;
            cnt+=e;
        }
        else{
            e=0;
        }

    }
    if(cnt==0)return 0;
    if(f==cnt)return 1;
    return 0;
}
vector<int>get_full2(int n){
    //printf("USAO %d\n",n);
    if(n==2){

        vector<int>ret;
        ret.pb(4);
        ret.pb(6);
        ret.pb(2);
        ret.pb(3);
        ret.pb(1);
        ret.pb(5);
        ret.pb(7);
        return ret;
    }

    //printf("%d AA\n",n);
    vector<int>ret=get_full2(n-1);
    int pp=ret.size();
    int prv=0;
    int mask=(1<<n);
    int e=1;
    for(int i=0;i<pp;i++){
        int x=ret[i];
        x|=mask;

        if(prefix(prv,n) && prefix(x,n) && e){
            ret.pb(mask);
            e=0;
        }
        ret.pb(x);
        prv=x;
    }

    return ret;
}
int msb(int n){

    for(int i=20;i>=0;i--){
        if((1<<i)&n)return i;
    }
}

const int maxn=2e5+10;
const int maxb=20;
int p[maxn*maxb],mat[maxn][maxb],cc=0;
int root(int x){
    if(p[x]==x)return x;
    return p[x]=root(p[x]);
}
void join(int x,int y){
    x=root(x);
    y=root(y);
    if(x==y)return;
    p[x]=y;
    cc--;
}
bool check(vector<int>rez,int n){

    memset(mat,0,sizeof(mat));
    for(int i=1;i<maxn*maxb;i++){
        p[i]=i;
    }

    int cnt=0;
    set<int>st;
    for(int i=0;i<rez.size();i++){
        int x=rez[i];

        for(int j=0;j<maxb;j++){
            if(x&(1<<j)){
                cc++;
                mat[i][j]=++cnt;
                printf("1");
            }
            else printf("0");
        }
        st.insert(x);
        printf("\n");
    }
    if(rez.size()!=n)return false;
    if(st.size()!=n)return false;

    for(int i=0;i<rez.size();i++){
        int x=rez[i];

        for(int j=0;j<maxb;j++){
            if(mat[i][j]==0)continue;

            if(i>0 && mat[i-1][j])join(mat[i-1][j],mat[i][j]);
            if(j>0 && mat[i][j-1])join(mat[i][j-1],mat[i][j]);
        }
    }

    if(cc==1)return 1;
    return 0;
}
int main(){


/// 24 mozda moze??
    int n;
    scanf("%d",&n);

    ///if(n==53)while(1){}


    if(n==1){
        printf("YES\n1\n");
        return 0;
    }
    if(n==2){
        printf("NO\n");
        return 0;
    }
    if(n==3){
        printf("YES\n");
        vector<int>rez=get_full(1);

        for(int i=0;i<rez.size();i++)printf("%d ",rez[i]);
        return 0;
    }
    if(n==7){
        printf("YES\n");
        vector<int>rez=get_full2(2);
        for(int i=0;i<rez.size();i++)printf("%d ",rez[i]);
        return 0;
    }

    int m=msb(n);
    if(n&(1<<m-1)){
        if(n==( (1<<m)+(1<<(m-1)) )){
            printf("NO\n");
            return 0;
        }
    }
    else{
        printf("NO\n");
        return 0;
    }

    vector<int>rez;

    rez=get_full2(m-1);
    vector<int>pom=get_full(m-2);

    int pmask=((1<<m)+(1<<(m-1)));
    int mask=(1<<m);

    for(int i=0;i<pom.size();i++){
        int x=pom[i];
        if(x+pmask<=n)rez.pb(x+pmask);
        rez.pb(x+mask);
    }
    rez.pb(pmask);
    rez.pb(mask);
    printf("YES\n");
   // if(!check(rez,n)){///13
            /// ili ne radi check
            /// ili oni caseovi gore su losi
            /// i NO je los
       //while(1){}
    //}
    for(int i=0;i<rez.size();i++)printf("%d ",rez[i]);

    return 0;
}
