/*

    idea:

        too lazy to write it

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<ll,ll> pii;
typedef set<pii>::iterator sit;
const int maxn=5e5+10;
ll a[maxn];
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%lld",&a[i]);

        set<pii>cand;
        int rez=0;
        if(a[1]%2==0){
            cand.insert({a[1]/2,a[1]/2});
            rez=1;
        }
        else cand.insert({1,a[1]-1});

        ll mul=1;
        ll lazy=0;
        for(int i=2;i<=n;i++){

            if(mul==1){/// pop od nazad

                while(cand.size()){
                    pii pom=(*cand.rbegin());

                    if(pom.ff*mul+lazy>a[i]-1)cand.erase(pom);
                    else break;
                }
                if(cand.size()){
                    pii pom=(*cand.rbegin());
                    cand.erase(pom);

                    int pom2=min(pom.ss*mul+lazy,a[i]-1);
                    pom.ss=pom2-lazy;
                    cand.insert(pom);
                }

                if(cand.size()==0){

                    lazy=0;
                    mul=1;

                    if(a[i]%2==0){
                        cand.insert({a[i]/2,a[i]/2});
                        rez++;
                    }
                    else cand.insert({1,a[i]-1});

                }
                else{

                    sit it=cand.lower_bound({(a[i]/2-lazy)*mul,(a[i]/2-lazy)*mul});
                    if(it==cand.end())it--;
                    else if((*it).ff*mul+lazy>a[i]/2 && it!=cand.begin())it--;

                    if((*it).ff*mul+lazy<=a[i]/2 && (*it).ss*mul+lazy>=a[i]/2 && a[i]%2==0){
                        mul=1;
                        lazy=0;
                        cand.clear();
                        rez+=2;
                        cand.insert({a[i]/2,a[i]/2});
                    }
                    else{
                        if(a[i]%2==0)cand.insert({(a[i]/2-lazy)*mul,(a[i]/2-lazy)*mul});
                        mul*=-1;
                        lazy*=-1;
                        lazy+=a[i];
                        rez++;
                    }
                }
            }
            else{/// pop od napred

                while(cand.size()){
                    pii pom=(*cand.begin());

                    if(pom.ss*mul+lazy>a[i]-1)cand.erase(pom);
                    else break;
                }
                if(cand.size()){
                    pii pom=(*cand.begin());
                    cand.erase(pom);

                    int pom2=min(pom.ff*mul+lazy,a[i]-1);
                    pom.ff=(pom2-lazy)*mul;
                    cand.insert(pom);
                }

                if(cand.size()==0){

                    lazy=0;
                    mul=1;

                    if(a[i]%2==0){
                        cand.insert({a[i]/2,a[i]/2});
                        rez++;
                    }
                    else cand.insert({1,a[i]-1});

                }
                else{

                    sit it=cand.lower_bound({(a[i]/2-lazy)*mul,(a[i]/2-lazy)*mul});
                    if(it==cand.end())it--;
                    else if((*it).ff*mul+lazy<a[i]/2 && it!=cand.begin())it--;

                    if((*it).ff*mul+lazy>=a[i]/2 && (*it).ss*mul+lazy<=a[i]/2 && a[i]%2==0){
                        mul=1;
                        lazy=0;
                        cand.clear();
                        rez+=2;
                        cand.insert({a[i]/2,a[i]/2});
                    }
                    else{
                        if(a[i]%2==0)cand.insert({(a[i]/2-lazy)*mul,(a[i]/2-lazy)*mul});
                        mul*=-1;
                        lazy*=-1;
                        lazy+=a[i];
                        rez++;
                    }
                }

            }

        }


        printf("%d\n",n*2-rez);

    }

    return 0;
}
