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

const int maxn=2e5+10;
int n,a[maxn],b[maxn];

double eps=1e-7;
bool eq(double a,double b){
    if(abs(a-b)<eps)return true;
    return false;
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);

    double suma=0;
    double sumb=0;
    for(int i=1;i<=n;i++){
        scanf("%d %d",&a[i],&b[i]);
        suma+=a[i];
        sumb+=b[i];
    }

    ///if(n>=2 && a[1]!=1)return 10;

    suma/=2;
    sumb/=2;

    int l=1;
    int r=1;
    double ld=0;
    double rd=0;
    double curr=0;
    double currb=0;
    for(;curr<suma;r++){
        curr+=a[r];
        currb+=b[r];
        if(curr>=suma){
            curr-=a[r];
            currb-=b[r];
            rd=(suma-curr)/(double)a[r];
            currb+=rd*b[r];
            break;
        }
    }

   if(eq(currb,sumb)){
        printf("1\n");
        cout<<r<<" "<<rd<<endl;
        printf("%d\n",r);
        for(int i=1;i<=r;i++)printf("%d ",i);
        printf("\n");
        ///ispisi resenje
        return 0;
    }


    cout<<fixed<<setprecision(10);
    ///cout<<l<<" "<<r<<" "<<ld<<" "<<rd<<endl;

    while(1){

        double d1=1-ld;
        double d2=1-rd;


        double nxtcurrb=currb;


        double pom=0;
        //for(int j=l;j<=r;j++){
        //    pom+=a[j];
        //}
        pom-=a[l]*ld;
        pom-=a[r]*(1-rd);

        //cout<<l<<" "<<r<<" "<<ld<<" "<<rd<<" | "<<currb<<" "<<sumb<<"  pom="<<pom<<endl;

        if( eq((d1*a[l])/((double)a[r]),d2) ){
            nxtcurrb-=d1*b[l];
            nxtcurrb+=d2*b[r];

            if(!((nxtcurrb>=sumb && currb<=sumb)||(nxtcurrb<=sumb && currb>=sumb))){
                l++;
                r++;
                ld=0;
                rd=0;
                currb=nxtcurrb;
                continue;
            }
        }
        else if((d1*a[l])/((double)a[r])<d2){
            nxtcurrb-=d1*b[l];
            nxtcurrb+=((d1*a[l])/((double)a[r]))*b[r];
            if(!((nxtcurrb>=sumb && currb<=sumb)||(nxtcurrb<=sumb && currb>=sumb))){
                rd+=((d1*a[l])/((double)a[r]));
                l++;
                ld=0;
                currb=nxtcurrb;
                continue;
            }
        }
        else{
            nxtcurrb-=((d2*a[r])/((double)a[l]))*b[l];
            nxtcurrb+=d2*b[r];
            if(!((nxtcurrb>=sumb && currb<=sumb)||(nxtcurrb<=sumb && currb>=sumb))){
                ld+=((d2*a[r])/((double)a[l]));
                r++;
                rd=0;
                currb=nxtcurrb;
                continue;
            }
        }

        if((nxtcurrb>=sumb && currb<=sumb)||(nxtcurrb<=sumb && currb>=sumb)){

            if(l==r){
                ld=suma/a[l];
                printf("1\n");
                cout<<l<<" "<<ld<<endl;
                printf("1\n%d\n",n+1);
                return 0;
            }

            d2=(sumb-currb)/(b[r]-b[l]*(a[r]/(double)(a[l]) ) );
            d1=(d2*a[r])/(double)a[l];

            ///cout<<d2<<" "<<b[r]-b[l]*(a[r]/(double)(a[l]) )<<" AA"<<endl;

            ///d1 i d2 je kolko jos treba dodati na dl i dr

            printf("2\n");
            cout<<l<<" "<<ld+d1<<endl;
            cout<<r<<" "<<rd+d2<<endl;

            vector<int>pom;
            for(int j=l+1;j<=r;j++)pom.pb(j);
            pom.pb(n+1);

            printf("%d\n",pom.size());
            for(int j=0;j<pom.size();j++)printf("%d ",pom[j]);
            printf("\n");

            break;

        }

    }


    return 0;
}
