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



vector<int> berlekamp_massey(vector<int>s){

    int f=-1;
    int last_eval=-1;
    vector<int>c,oldc;
    for(int i=0;i<s.size();i++){

        int eval=s[i];
        for(int j=0;j<c.size();j++)
            eval=sub(eval,mul(s[i-j-1],c[c.size()-j-1]));

        if(eval==0)continue;

        if(f==-1){
            c.resize(i+1);
            for(int j=0;j<=i;j++)c[j]=0;
            f=i;
            last_eval=eval;
        }
        else{

            vector<int>d=oldc;

            for(int j=0;j<d.size();j++)d[j]=sub(0,d[j]);
            d.pb(1);

            for(int j=1;j<=i-f-1;j++)d.pb(0);

            int pom_inv=mul(invv(last_eval),eval);
            for(int j=0;j<d.size();j++)
                d[j]=mul(d[j],pom_inv);

            vector<int>temp=c;
            int oldcsz=c.size();
            c.resize(max(c.size(),d.size()));
            int cszdelta=c.size()-oldcsz;
            for(int j=c.size()-1;j>=cszdelta;j--)c[j]=c[j-cszdelta];
            for(int j=0;j<cszdelta;j++)c[j]=0;
            for(int j=0;j<d.size();j++)
                c[c.size()-j-1]=add(c[c.size()-j-1],d[d.size()-j-1]);

            if(i-(int)temp.size()>f-(int)oldc.size()){
                last_eval=eval;
                f=i;
                oldc=temp;
            }

        }

    }

    if(s.size()<c.size()*2){
        c.clear();
        return c;
    }

    reverse(c.begin(),c.end());

    return c;
}
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
