#include<bits/stdc++.h>
/*

    problem: https://codeforces.com/contest/506/problem/E

*/

#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int mod=10007;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}


const int maxn=210;
string s;
int n,m,flen,dp[maxn][maxn],temp[maxn][maxn];

void adv(int dp[maxn][maxn]){

    memset(temp,0,sizeof(temp));

    for(int i=0;i<=n+1;i++){
        for(int j=0;j<=n+1;j++){
            if(i>=j)continue;


            if(j-i==1){

                temp[i][j]=add(temp[i][j],mul(26,dp[i][j]));

            }
            else if(j-i==2){

                temp[i][j]=add(temp[i][j],mul(25,dp[i][j]));
                temp[i+1][j]=add(temp[i+1][j],dp[i][j]);

            }
            else{

                if(s[i]==s[j-2]){
                    temp[i][j]=add(temp[i][j],mul(dp[i][j],25) );
                    temp[i+1][j-1]=add(temp[i+1][j-1],dp[i][j]);
                }
                else{
                    temp[i][j]=add(temp[i][j],mul(dp[i][j],24) );
                    temp[i+1][j]=add(temp[i+1][j],dp[i][j]);
                    temp[i][j-1]=add(temp[i][j-1],dp[i][j]);
                }

            }

        }
    }

    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=n+1;j++)
            dp[i][j]=temp[i][j];

}

void shift_right(vector<int>&v,int d){
    v.resize(v.size()+d);
    for(int i=v.size()-1;i>=d;i--)v[i]=v[i-d];
    for(int i=d-1;i>=0;i--)v[i]=0;
}
vector<int>berlekamp_massey(vector<int>v){

   vector<int>oldc,currc;
   int olddelta,f;

   for(int i=0;i<v.size();i++){

        int delta=v[i];
        for(int j=0;j<currc.size();j++)
            delta=sub(delta,mul(currc[j],v[i-j-1]));

        if(delta==0)continue;

        if(currc.size()==0){
            currc.resize(i+1);
            olddelta=delta;
            f=i;
        }
        else{

            vector<int>pom1,pom2;
            pom1=oldc;
            pom2=currc;

            for(int j=0;j<oldc.size();j++)pom1[j]=sub(0,pom1[j]);
            shift_right(pom1,1);
            pom1[0]=1;
            int dm=mul(delta,invv(olddelta));
            for(int j=0;j<pom1.size();j++)pom1[j]=mul(dm,pom1[j]);
            shift_right(pom1,i-f-1);

            pom1.resize(max(pom1.size(),pom2.size()));
            pom2.resize(max(pom1.size(),pom2.size()));

            for(int j=0;j<pom1.size();j++)
                pom1[j]=add(pom1[j],pom2[j]);

            if(f-oldc.size()<i-currc.size()){
                oldc=currc;
                f=i;
                olddelta=delta;
            }

            currc=pom1;

        }


   }

   return currc;

}
int solve(vector<int>c,vector<int>s,ll n){

    int m=c.size();
    assert(m>0);

    auto mul2 = [&](const vector<int>v1,const vector<int>v2) -> vector<int>{
        vector<int>ret(v1.size()-1+v2.size());
        for(int i=0;i<v1.size();i++)
            for(int j=0;j<v2.size();j++)
                ret[i+j]=add(ret[i+j],mul(v1[i],v2[j]));
        for(int i=ret.size()-1;i>=m;i--)
            for(int j=m-1;j>=0;j--)
            ret[i-j-1]=add(ret[i-j-1],mul(ret[i],c[j]));
        ret.resize(min((int)ret.size(),m));
        return ret;
    };

    std::function<vector<int>(ll)> step2 = [&] (ll n)->vector<int>{

        if(n==0)return {1};
        if(n==1){
            if(m==1)return {c[0]};
            else return {0,1};
        }

        vector<int>pom=step2(n/2);
        pom=mul2(pom,pom);
        vector<int>pom2={c[0]};
        if(m>1)pom2={0,1};
        if(n&1)pom=mul2(pom,pom2);

        return pom;
    };

    vector<int>ret=step2(n);

    int rez=0;
    s.resize(m);
    ret.resize(m);
    for(int i=0;i<m;i++)
        rez=add(rez,mul(ret[i],s[i]));

    return rez;
}

void go(int m){

    flen=n+m;
    dp[0][n+1]=1;

    vector<int>rez;
    for(int i=1;i<=min(flen/2,2500);i++){
        adv(dp);

        int pom=0;
        for(int j=0;j<=n;j++)
            pom=add(pom,dp[j][j+1]);
        if(flen%2==0)rez.pb(pom);

        pom=mul(pom,26);
        for(int j=0;j<n;j++)
            pom=add(pom,dp[j][j+2]);

        if(flen%2==1)rez.pb(pom);

    }
    if((flen-2)/2<rez.size())
        printf("%d\n",rez[(flen-2)/2]);
    else
        printf("%d\n",solve(berlekamp_massey(rez),rez,(flen-2)/2));

}

int main(){


    ///freopen("test.txt","r",stdin);

    cin>>s;
    scanf("%d",&m);
    n=s.size();
    flen=n+m;

    go(m);



    return 0;
}
