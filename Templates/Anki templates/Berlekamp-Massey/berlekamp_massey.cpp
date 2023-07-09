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
    for(int i=v.size()-1;i>=d;i--)v[i]=v[i-d];
    for(int i=d-1;i>=0;i--)v[i]=0;
}
vector<int> berlekamp_massey(vector<int>s){

    vector<int>c,oldc;
    int f=-1;
    int last_delta=-1;

    for(int i=0;i<s.size();i++){

        int delta=s[i];
        for(int j=1;j<=c.size();j++)
            delta=sub(delta,mul(s[i-j],c[j-1]));

        if(delta==0)continue;

        if(f==-1){
            c.resize(i+1);
            f=i;
            last_delta=delta;
        }
        else{

            vector<int>d=oldc;
            d.resize(d.size()+1);
            shift_right(d,1);
            for(int j=0;j<d.size();j++)d[j]=sub(0,d[j]);
            d[0]=1;

            int pom=mul(invv(last_delta),delta);
            for(int j=0;j<d.size();j++)d[j]=mul(d[j],pom);

            int zeroes=i-f-1;
            d.resize(d.size()+zeroes);
            shift_right(d,zeroes);

            vector<int>temp=c;
            c.resize(max(c.size(),d.size()));
            for(int j=0;j<d.size();j++)c[j]=add(c[j],d[j]);

            if(i-temp.size()>f-oldc.size()){
                last_delta=delta;
                oldc=temp;
                f=i;
            }

        }
    }

    return c;
}
/*
template<typename T>
T solve(const vector<T> &c, const vector<T> &s, long long n) {
    int m = (int) c.size();
    assert(c.size() <= s.size());

    auto mul2 = [&] (const vector<T> &a, const vector<T> &b) -> vector<T> {
        vector<T> ret(a.size() + b.size() - 1);
        for (int i=0; i<(int)a.size(); i++)
            for (int j=0; j<(int)b.size(); j++)
                ret[i+j] =add(ret[i+j],mul(a[i],b[j]));
        for (int i=(int)ret.size()-1; i>=m; i--)
            for (int j=m-1; j>=0; j--)
                ret[i-j-1]=add(ret[i-j-1],mul(ret[i],c[j]));
        ret.resize(min((int) ret.size(), m));
        return ret;
    };

    vector<T> a = m == 1 ? vector<T>{c[0]} : vector<T>{0, 1}, x{1};
    for (; n>0; n/=2) {
        if (n % 2)
            x = mul2(x, a);
        a = mul2(a, a);
    }
    x.resize(m);

    T ret = 0;
    for (int i=0; i<m; i++)
        ret=add(ret,mul(x[i],s[i]));
    return ret;
}*/
int solve(vector<int>c,vector<int>s,ll n){

    int m=c.size();

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

    vector<int>base={0,1};
    if(m==1){
        base.resize(1);
        base[0]=c[0];
    }
    vector<int>ret={1};
    while(n){
        if(n&1)ret=mul2(ret,base);
        base=mul2(base,base);
        n>>=1;
    }

    int rez=0;
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
