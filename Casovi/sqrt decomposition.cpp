/*


*/
#include <bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<ll,ll> pii;

const int maxn=2e5+10;
const int bsize=300;

int br,blp[maxn/bsize+10],brp[maxn/bsize+10],n,bid[maxn+10];
ll rez[maxn/bsize+10][bsize][bsize],a[maxn+10];

void make_blocks(){


    int l=1;
    int r=bsize;
    while(1){

        ++br;
        blp[br]=l;
        brp[br]=r;

        l+=bsize;
        r+=bsize;

        if(l>n)break;
        if(r>n)r=n;

    }


    for(int i=1;i<=br;i++){
        for(int j=blp[i];j<=brp[i];j++){
            bid[j]=i;
        }

        for(int k=1;k<=bsize;k++){

            /// rez[i][k][j]
            int b=0;
            for(int j=0;j<=brp[i]-blp[i];j++){
                rez[i][k][b]+=a[j+blp[i]];

                b++;
                if(b>=k)b=0;
            }

        }

    }


}

ll query1(int l,int r,int k){

    ll ret=0;

    for(int i=l;i<=r;i+=k)ret+=a[i];

    return ret;
}

ll query2(int l,int r,int k){

    if(bid[l]==bid[r])return query1(l,r,k);

    int lid=bid[l];
    int rid=bid[r];


    ll ret=0;

    ret+=query1(l,brp[lid],k);

    int x=(brp[lid]-l)/k+1;
    l=l+x*k;

    for(int i=lid+1;i<rid;i++){

        ret+=rez[i][k][l-blp[i]];
        x=(brp[i]-l)/k+1;
        l=l+x*k;

    }

    ret+=query1(l,r,k);

    return ret;

}

ll query(int l,int r,int k){

    if(k>=bsize)return query1(l,r,k);
    else return query2(l,r,k);
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }

    make_blocks();


    int q;
    scanf("%d",&q);
    while(q--){

        int l,r,k;

        scanf("%d %d %d",&l,&r,&k);

        printf("%lld\n",query(l,r,k));

    }


    return 0;
}
