#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

const int maxn=300;

int n;
int cline[maxn][maxn],triples[maxn][maxn][maxn];

struct pt{

    int first,second;

    pt(int x,int y){
        this->ff=x;
        this->ss=y;
    }
    pt(){
        this->ff=0;
        this->ss=0;
    }

    int cross(pt b){
        int pom=ff*b.ss-ss*b.ff;
        if(pom>0)return 1;
        if(pom==0)return 0;
        return -1;
    }

    pt operator - (pt &b){
        return pt(ff-b.ff,ss-b.ss);
    }
    pt operator + (pt &b){
        return pt(ff+b.ff,ss+b.ss);
    }

}p[maxn];

void prek_lines(){

    /// sa leve strane
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            for(int k=1;k<=n;k++){
                if(k==i || k==j)continue;
                if((p[j]-p[i]).cross(p[k]-p[i])>0)cline[i][j]++;
            }

            ///printf("%d %d | %d ln\n",i,j,cline[i][j]);
        }
    }

}
pt gc,gi,sv;
bool srt(int a,int b){

    int sgna=sv.cross(p[a]);
    int sgnb=sv.cross(p[b]);
    if(sgna!=sgnb){
        return sgna>sgnb;
    }
    return (((p[a]).cross(p[b]))>0);
}
void go(int c,int x,vector<int>&a){

    int lst=-1;

    for(int i=0;i<a.size();i++){
        int id=a[i];
        if(sv.cross(p[id]-gc)>0)lst++;
    }

    int curr=lst+1;
    for(int i=0;i<=lst;i++){
        while(curr<a.size() && (p[a[i]]-gc).cross(p[a[curr]]-gc)>0)curr++;
        triples[x][c][a[i]]=curr-lst-1;
        triples[a[i]][c][x]=curr-lst-1;
        ///printf("%d %d %d | %d TRIP\n",x,c,a[i],triples[x][c][a[i]]);
    }

    lst=a.size();
    for(int i=a.size()-1;i>=0;i--){
        int id=a[i];
        if(sv.cross(p[id]-gc)<0)lst--;
    }
    curr=lst-1;
    for(int i=a.size()-1;i>lst;i--){
        while(curr>=0 &&  (p[a[curr]]-gc).cross(p[a[i]]-gc)>0 )curr--;
        triples[x][c][a[i]]=lst-curr-1;
        triples[a[i]][c][x]=lst-curr-1;
        ///printf("%d %d %d | %d    %d %d TRIP222\n",x,c,a[i],triples[x][c][a[i]],lst,curr);
    }

}
void prek_triples(){

    vector<int>niz(n-2);

    for(int c=1;c<=n;c++){

        for(int i=1;i<=n;i++){
            if(i==c)continue;

            int cid=0;
            for(int j=1;j<=n;j++){
                if(j==c || j==i)continue;
                niz[cid++]=j;
                p[j]=(p[j]-p[c]);
            }

            gc=p[c];
            gi=p[i];
            sv=(gi-gc);
            sort(niz.begin(),niz.end(),srt);

            for(int j=1;j<=n;j++){
                if(j==c || j==i)continue;
                p[j]=(p[j]+p[c]);
            }


            go(c,i,niz);


        }

    }

}

int find_outside(int i,int j,int k){

    if( (p[j]-p[i]).cross(p[k]-p[i])>0 )swap(j,k);
    return cline[i][j]+cline[j][k]+cline[k][i]-triples[i][j][k]-triples[j][k][i]-triples[k][i][j];
}
int get_aa(int i,int j,int k){
    if( (p[i]-p[j]).cross(p[k]-p[j])<0 )swap(i,k);
   /// printf("%d %d %d | %d %d %d TRUOKE\n",i,j,k,cline[k][i],triples[i][k][j],triples[k][i][j]);
    //return cline[i][j]+cline[j][k]-triples[i][j][k];
    return cline[k][i]-triples[i][k][j]-triples[k][i][j];
}

int main(){

    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        scanf("%d %d",&p[i].ff,&p[i].ss);
    }

    prek_lines();
    prek_triples();


    ll rez=(ll)n*((ll)n-1)*((ll)n-2)*((ll)n-3)*((ll)n-4);
    rez*=(5)*((ll)4);
    rez/=(2*3*4*5*2);

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=j+1;k<=n;k++){
                ll pom=find_outside(i,j,k);
                rez-=pom*(n-3-pom);

               /// if(pom*(n-3-pom)>0)printf("%d %d %d | %lld %lld uyyvu\n",i,j,k,pom,rez);

            }
        }
    }


    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=i+1;k<=n;k++){
                if(i==j || j==k)continue;

                ll pom=get_aa(i,j,k);
                rez-=(pom*(pom-1))/2 ;

                ///if(pom*(pom-1)>0)printf("%d %d %d | %d %lld TRIPLE\n",i,j,k,get_aa(i,j,k), pom);
            }
        }
    }

    printf("%lld\n",rez);


    return 0;
}
