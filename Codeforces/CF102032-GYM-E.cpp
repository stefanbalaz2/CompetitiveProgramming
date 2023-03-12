/*

    idea:    https://github.com/mraron/CompetitiveProgramming/blob/master/CodeForces/102032E.cpp

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<ll,ll>pii;
///const int maxn=1e5+10;
const int qs=7500;
const int maxn=3e5+10;
ll c1[50][2],c2[50][50][4],c3[50][50][50][8],mod=998244353,pw2[100000];
int n,kk,x;
struct btst{

    vector<ll>a;
    const ll bs=60;
    const ll mov=(1ll<<bs)%mod;

    void build(string &s){
        a.resize(s.size()/bs+1);
        for(int i=0;i<a.size();i++)a[i]=0;

        ll cb=-1;
        int cbk=0;
        for(int i=0;i<s.size();i++){
            cb++;
            if(cb==bs){
                cb=0;
                cbk++;
            }

            if(s[i]=='1')a[cbk]^=(1ll<<cb);
        }
    }


}niz[qs+10];

static ll xorsum(btst &x,btst &y){

        ll cmul=1;
        ll ret=0;
        for(int i=0;i<x.a.size();i++){

            ll pom=(x.a[i]^y.a[i])%mod;
            ret=(ret+pom*cmul)%mod;

            cmul=(cmul*x.mov)%mod;
        }

        return ret;
}

int main(){

    ///freopen("56","r",stdin);
    ///freopen("moj.txt","w",stdout);

    scanf("%d %d %d",&n,&kk,&x);

    if(n<=qs){

        for(int i=1;i<=n;i++){
            string s;
            cin>>s;
            niz[i].build(s);
        }

        ll rez=0;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                ll pom=xorsum(niz[i],niz[j]);
                ll ret=1;
                for(int p=1;p<=x;p++)
                    ret=(ret*pom)%mod;

                rez=(rez+ret);
                if(rez>=mod)rez-=mod;
            }
        }

        printf("%lld\n",rez);
    }
    else{

        pw2[0]=1;
        for(int i=1;i<=3*kk;i++){
            pw2[i]=(pw2[i-1]*2)%mod;
        }

        ll rez=0;
        for(int i=1;i<=n;i++){

            string s;
            cin>>s;

            if(x==1){

                for(int j=0;j<s.size();j++)
                    c1[j][s[j]-'0']++;


            }
            else if(x==2){

                for(int j=0;j<s.size();j++)
                    for(int k=0;k<s.size();k++)
                        c2[j][k][s[j]-'0'+2*(s[k]-'0')]++;




            }
            else{

                for(int j=0;j<s.size();j++)
                    for(int k=0;k<s.size();k++)
                        for(int p=0;p<s.size();p++)
                        c3[j][k][p][s[j]-'0'+2*(s[k]-'0')+4*(s[p]-'0')]++;


            }

        }

        if(x==1){

            for(int i=0;i<kk;i++){
                rez=(rez+((c1[i][0]*c1[i][1])%mod)*pw2[i] )%mod;
            }

        }
        else if(x==2){

            for(int i=0;i<kk;i++){
                for(int k=0;k<kk;k++){

                    rez=(rez+((c2[i][k][0]*c2[i][k][3])%mod)*pw2[i+k] )%mod;
                    rez=(rez+((c2[i][k][2]*c2[i][k][1])%mod)*pw2[i+k] )%mod;

                }

            }

        }
        else{

            for(int i=0;i<kk;i++){
                for(int k=0;k<kk;k++){
                    for(int p=0;p<kk;p++){

                        rez=(rez+((c3[i][k][p][0]*c3[i][k][p][7])%mod)*pw2[i+k+p] )%mod;
                        rez=(rez+((c3[i][k][p][1]*c3[i][k][p][6])%mod)*pw2[i+k+p] )%mod;
                        rez=(rez+((c3[i][k][p][2]*c3[i][k][p][5])%mod)*pw2[i+k+p] )%mod;
                        rez=(rez+((c3[i][k][p][3]*c3[i][k][p][4])%mod)*pw2[i+k+p] )%mod;

                    }
                }

            }

        }

        printf("%lld\n",rez);

    }

    return 0;
}
