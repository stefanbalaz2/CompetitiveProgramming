/*

    idea:   try every order
            when an order is fixed, the min number of moves requred is
            n-number of cycles

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int>pii;
const int maxn=510;

int a[maxn],b[maxn],n,rez,ap[maxn],pos[maxn];

int count_cycles(){

    memset(pos,0,sizeof(pos));
    int ret=0;
    for(int i=0;i<n;i++){
        if(pos[i])continue;

        ret++;

        int x=i;
        while(1){

            pos[x]=1;
            int id=ap[a[x]];

            if(pos[id])break;
            x=id;
        }

    }

    return ret;
}

void check(){

    for(int i=0;i<n;i++)ap[b[i]]=i;

    rez=min(rez,n-count_cycles());

}

int main(){


    ///freopen("test.txt","r",stdin);

    while(1){

        scanf("%d",&n);
        if(n==0)break;


        for(int i=0;i<n;i++){
            scanf("%d",&a[i]);
            a[i]--;
        }

        rez=1e9;
        for(int i=0;i<n;i++){

            for(int j=i;j<i+n;j++)
                b[j%n]=j-i;
            check();


            for(int j=i;j>i-n;j--)
                b[(j+n)%n]=i-j;
            check();

        }


        printf("%d\n",rez);
    }


    return 0;
}
