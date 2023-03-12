/*

  idea: realise that the biggest ludic that will cross out at least 1 number is not bigger than 44 million
  so we can find ludics up to 44mil and just by knowing that, do a query just by taking the next ludic, and
  decreasing the number of numbers it crosses out

*/
#include <cstdio>
#include <cstdlib>
#define v3 134217728
#define v2 67108864
#define v1 33554432
#define vv3 1048576
#define vv2 524288
#define vv1 262144
#define gr 2270000
int ima=4;
int niz[gr+10];
char drvo[v3];
int drvce[vv3];
void postavi(){
    for(int i=1,m;i<=v2;++i)
    {
        drvo[i+v2-1]=
        i%2!=0 &&
        i%6!=3 &&
        i%30!=5 &&
        i%30!=19 ;
    }
    for(int i=v2;i<v2+5;++i)drvo[i]=0;
    for(int i=v2-1;i;--i)drvo[i]=drvo[i+i]+drvo[i+i+1];
    for(int i=vv2;i<vv3;++i)drvce[i]=drvo[i];
    for(int i=vv2-1;i;--i)drvce[i]=drvce[i+i]+drvce[i+i+1];
    niz[0]=1;
    niz[1]=2;
    niz[2]=3;
    niz[3]=5;
}
int nadjiibrisip(){
    int x=1;
    --drvce[1];
    while(x<vv2)
    {
        if(drvce[x<<=1]==0)++x;
        --drvce[x];
    }
    while(x<v2)
    {
        if(drvo[x<<=1]==0)++x;
        --drvo[x];
    }
    niz[ima++]=x-v2+1;
    return x-v2;
}
void nadjiibrisi(int k){
    int br=0;
    int x=1;
    --drvce[1];
    while(x<vv2)
    {
        int dole=drvce[x<<=1];
        if(br+dole<=k)
        {
            br+=dole;
            ++x;
        }
        --drvce[x];
    }
    while(x<v2)
    {
        int dole=drvo[x<<=1];
        if(br+dole<=k)
        {
            br+=dole;
            ++x;
        }
        --drvo[x];
    }
}
void korak(){
    int l=nadjiibrisip();
    for(int k=l;k<drvce[1];k+=l)
        nadjiibrisi(k);
}
int manjih(int n){
    int l=0;
    int d=ima-1;
    int sr;
    while(d-l>1)
    {
        sr=(l+d)>>1;
        if(niz[sr]<=n)l=sr;
        else d=sr;
    }
    return d;
}
int vecih(int n){
    int ost=n-1,dz;
    for(int i=1;i<ima;++i)
    {
        --ost;
        dz=ost/niz[i];
        if(dz==1)
        {
            int l=i;
            int d=ima-1;
            int sr;
            while(d-l>1)
            {
                sr=(l+d)>>1;
                if(niz[sr]<=ost-2*(sr-i))l=sr;
                else d=sr;
            }
            return ost+i+i-d+1;
        }
        ost-=dz;
    }
}
int resi(int n){
    if(n<niz[ima-1])return manjih(n);
    else if(n==niz[ima-1])return ima;
    else return vecih(n);
}
int main(){
    postavi();
    for(int i=3;i<gr;++i)korak();
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        printf("%d\n",resi(n));
    }
    return 0;
}
