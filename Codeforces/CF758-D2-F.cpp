/*

    idea: for every number k between L and R inclusive find its prime factorisation
    p1^(a1)*p2^(a2)...
    and take mod the ai powers with n-1, lets call that number b
    we actually took the superset of all the valid denominators of the number k, and thats enough because we can get from that denominator to
    every other just by multyplying it with some subset of our superset, and we wont have any overcounting and we will visit every posibble ratio of the GP
    increment cnt[b] to know how much candidates with value b we have
    after processing all the numbers we will try for every number k from 1 to R to find its
    boundaries on the minimum ratio we can take and the maximum ration we can take and add to the result cnt[k]*(rightboundary-leftboundary+1)
    because those are our candidates for out ratios for the number k(notice that those arent actualy ratios, those are the upper part of the fraction)

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=1e7+10;

ll rez,st[maxn];
int mp[maxn],n,cnt[maxn];

void sito(){
    memset(mp,-1,sizeof(mp));
    mp[1]=1;
    for(int i=2;i<maxn;i++){
        if(mp[i]!=-1)continue;
        for(int j=i;j<maxn;j+=i)
            if(mp[j]==-1)mp[j]=i;
    }
}
void process(int x){

    int pom=x;
    int br=0;
    int last=-1;
    int im=1;
    while(1){


        if(mp[pom]!=last){
            if(last==-1){
                br=1;
                last=mp[pom];
            }
            else{
                for(int i=1;i<=br/n;i++)im*=last;

                last=mp[pom];
                br=1;
            }
        }
        else br++;

        if(pom==1)break;

        pom/=mp[pom];
    }

    if(im!=1)for(int i=1;i<=n;i++)x/=im;

    cnt[x]++;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out2.txt","w",stdout);

    sito();

    int l,r;
    scanf("%d %d %d",&n,&l,&r);
    n--;

    for(int i=1;i<=r;i++){

        ll pom=1;
        for(int j=1;j<=n;j++){
            pom*=(ll)i;
            if(pom>r){
                pom=-1;
                break;
            }
        }

        st[i]=pom;
    }

    if(n==0){
        printf("%d\n",r-l+1);
        return 0;
    }

    for(int i=l;i<=r;i++)
        process(i);



    int lp=r;
    int rp=r;
    for(int i=1;i<=r;i++){
        if(cnt[i]==0)continue;

        /*rez+=((ll)cnt[i]*(ll)(cnt[i]-1)); /// this is another way to solve it: by ivan100sic
        continue;*/

        while((ll)i*st[lp]<0 || (ll)i*st[lp]>=(ll)l)lp--;
        while((ll)i*st[rp]<0 || (ll)i*st[rp]>(ll)r)rp--;
        lp++;

        if(lp<=rp)rez+=((ll)rp-lp+1)*(ll)cnt[i];
    }

    printf("%lld\n",rez-((ll)r-l+1));

	return 0;
}
