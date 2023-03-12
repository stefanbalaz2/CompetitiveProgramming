/*

    idea:   for small enough n do exact calculation
            for big enough just do integrals,it approximates good enough

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxv=1e6+10;
long double pref[maxv];
void prek(){
    for(int i=1;i<maxv;i++)pref[i]=pref[i-1]+sqrtl(0.25+(long double)i)+0.5;
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    prek();

    int t;
    scanf("%d",&t);
    while(t--){


        long double n;
        cin>>n;

        if(n<maxv){
            cout<<fixed<<setprecision(5);
            cout<<pref[(int)n-1]/n<<endl;
            continue;
        }

        long double ret=(n-1)*1.0/2.0+2.0/3.0*powl(1.0/4.0+(n-1),3.0/2.0)-1.0/12.0;
        ret=ret*1.0/n;

        cout<<fixed<<setprecision(5);
        cout<<ret<<endl;

    }

    return 0;
}
