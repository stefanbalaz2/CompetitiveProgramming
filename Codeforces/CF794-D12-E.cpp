/*

    observation: game revolves around the center of the array, so first player always tries
    to get the best element for him to the middle, sometimes he needs to carry
    the best 2 to the middle(case when remaining no. of elements is odd)
    more info about this: https://codeforces.com/blog/entry/51962

    so we evaluate every number how much operations does it take to get it to middle
    and as we iterate k we take the max result of all the numbers  that take <=k operations

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,pair<int,int> > pii;
pii p[300010];
int n,a[300010];
int eval(int x,int y){

    if(n%2){
        if(y==n/2+1)return 0;

        if(y<n/2+1)return n-y*2;
        else {
            y=n-y+1;
            return n-y*2;
        }
    }
    else{
        if(y==n/2+1)return 0;
        if(y==n/2)return 0;

        if(y<n/2)return n-y*2;
        else {
            y=n-y+1;
            return n-y*2;
        }
    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    a[0]=2e9;
    a[n+1]=2e9;
    for(int i=1;i<=n;i++)
        p[i]={eval(a[i],i),{a[i],max(min(a[i],a[i-1]),min(a[i],a[i+1]))} };

    sort(p+1,p+n+1);


    int rez=0;
    int rez2=0;
    int curr=0;
    for(int i=0;i<n;i++){

        while(p[curr+1].ff<=i && curr<n){
            curr++;
            rez=max(rez,p[curr].ss.ff);
            rez2=max(rez2,p[curr].ss.ss);
        }

        int left=n-i;
        if(left==1)printf("%d ",rez);
        else if(left%2)printf("%d ",rez2);
        else printf("%d ",rez);
    }

    return 0;
}
