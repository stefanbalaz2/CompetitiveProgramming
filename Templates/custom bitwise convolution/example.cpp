#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define ll long long
using namespace std;
typedef pair<int,int> pii;

const int maxn=18;

int n;
int A[maxn][2][2],B[maxn][2][2],C[maxn][2][2];
ll a[(1<<maxn)],b[(1<<maxn)];

void ispis(int a[2][2]){
    printf("%d %d\n%d %d  MAT\n",a[0][0],a[0][1],a[1][0],a[1][1]);
}

int det(int A[2][2]){
    return A[0][0]*A[1][1]-A[0][1]*A[1][0];
}
bool unit_holds(int f[2][2],int A[2][2],int B[2][2],int C[2][2]){

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)
                if(A[i][j]*B[i][k]!=C[i][f[j][k]])return false;

    return true;
}
void invert_matrix(int A[2][2]){/// inverses the matrix, but multiplies coefficients by 2, 
                                /// so we can kepp using int, take care to divide by 2 when doing the fft

    int ret[2][2];
    int d=det(A);

    ret[0][0]=(A[1][1]*2)/d;
    ret[0][1]=-(A[0][1]*2)/d;
    ret[1][0]=-(A[1][0]*2)/d;
    ret[1][1]=(A[0][0]*2)/d;

    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            A[i][j]=ret[i][j];
}

void make_convolution_matrices(int f[2][2],int A[2][2],int B[2][2],int C[2][2]){

    int n=1;
    for(int i=1;i<=12;i++)n*=3;

    for(int mask=0;mask<n;mask++){

        int pmask=mask;
        int cx=0;
        int cy=0;
        for(int i=0;i<12;i++){
            int x=pmask%3-1;
            pmask/=3;

            if(i<4)A[cx][cy]=x;
            else if(i<8)B[cx][cy]=x;
            else C[cx][cy]=x;

            cy++;
            if(cy>1){cy=0;cx++;}
            if(cx>1)cx=0;
        }

        int d=det(C);
        if(d==0)continue;

        if(unit_holds(f,A,B,C))break;
    }

    invert_matrix(C);
}

void fft(ll a[],int T[][2][2],int bit,bool inverse){

    int n=(1<<(bit+1));

    for(int len=n;len>1;len>>=1,bit--){

        int hlen=(len/2);

        for(int i=0;i<n;i+=len){

            for(int j=0;j<hlen;j++){

                ll pom1=a[i+j];
                ll pom2=a[i+j+hlen];

                a[i+j]=pom1*T[bit][0][0]+pom2*T[bit][0][1];
                a[i+j+hlen]=pom1*T[bit][1][0]+pom2*T[bit][1][1];

                if(inverse){
                    a[i+j]/=2;
                    a[i+j+hlen]/=2;
                }
            }

        }

    }

}

void mul(ll a[],ll b[],ll m){
    int n=(1<<m);
    fft(a,A,m-1,0);
    fft(b,B,m-1,0);
    for(int i=0;i<n;i++)a[i]*=b[i];
    fft(a,C,m-1,1);
}


int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);

    for(int i=0;i<n;i++){
        string s;
        cin>>s;
        int niz[2][2];

        niz[0][0]=s[0]-48;
        niz[0][1]=s[1]-48;
        niz[1][0]=s[2]-48;
        niz[1][1]=s[3]-48;

        make_convolution_matrices(niz,A[i],B[i],C[i]);
    }

    for(int i=0;i<(1<<n);i++)
        scanf("%lld",&a[i]);
    for(int i=0;i<(1<<n);i++)
        scanf("%lld",&b[i]);

    mul(a,b,n);

    for(int i=0;i<(1<<n);i++){
        printf("%lld ",a[i]);
    }

return 0;
}
