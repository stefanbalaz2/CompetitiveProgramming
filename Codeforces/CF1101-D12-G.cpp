/*

    idea: https://codeforces.com/blog/entry/64483

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
const int maxn=2e5+10;
const int maxb=30;
int pref[maxn],a[maxn],n;
int go(){

    int start=0;
    for(int i=0;i<maxb;i++){

        int id=-1;
        for(int j=start+1;j<=n;j++){
            if(pref[j]&(1<<i)){
                id=j;
                break;
            }
        }

        if(id==-1)continue;

        start++;
        swap(pref[start],pref[id]);

        for(int j=start+1;j<=n;j++)
            if(pref[j]&(1<<i))pref[j]^=pref[start];
    }


return start;
}
int main(){

    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        pref[i]=(pref[i-1]^a[i]);
    }

    if(pref[n]==0){
        printf("-1\n");
        return 0;
    }

    swap(pref[1],pref[n]);

    printf("%d\n",go());

    return 0;
}
