/*

meet in middle 3^(n/2)
3 options to exclude per mission
debugged for long time because i didnt take care of applying max() on some newly defined values
not so clean and efficient code, wanted to experiment with maps and structs

*/
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair< int,int> pii;
struct ss{
    int a,b,c;
}p[30];
int n,pw3[30],maxxrez,m1,m2,fin[30];
struct op{
    bool operator()(ss a,ss b){
        if(a.a!=b.a)return a.a<b.a;
        if(a.b!=b.b)return a.b<b.b;
        if(a.c!=b.c)return a.c<b.c;
        return 0;
    }
};
map<ss,pii,op>mapa;
ss operator +(ss a,ss b){
    return {a.a+b.a,a.b+b.b,a.c+b.c};
}
void trans(ss &a){
    int minn=min(a.a,min(a.b,a.c));
    a.a-=minn;
    a.b-=minn;
    a.c-=minn;
}
void trans2(ss &a){
    int minn=max(a.a,max(a.b,a.c));
    a.a=minn-a.a;
    a.b=minn-a.b;
    a.c=minn-a.c;
}
int main(){

    ///freopen("test.txt","r",stdin);

    pw3[0]=1;
    for(int i=1;i<=16;i++)pw3[i]=pw3[i-1]*3;

    scanf("%d",&n);

    for(int i=0;i<n;i++)scanf("%d %d %d",&p[i].a,&p[i].b,&p[i].c);

    int pom=(n+1)/2;
    int pom22=n-pom;

    for(int i=0;i<pw3[pom];i++){


        ss a={0,0,0};

        int pom2=i;
        for(int j=0;j<pom;j++){
            int id=pom2%3;
            pom2/=3;

            if(id==0){
                a=a+p[pom22+j];
                a.a-=p[pom22+j].a;
            }
            else if(id==1){
                a=a+p[pom22+j];
                a.b-=p[pom22+j].b;
            }
            else{
                a=a+p[pom22+j];
                a.c-=p[pom22+j].c;
            }
        }


        int blabla=min(min(a.a,a.b),a.c);
        trans(a);
        if(mapa.find(a)!=mapa.end())mapa[a]=max(mapa[a],(pii){blabla,i});
        else mapa[a]=(pii){blabla,i};
    }


    maxxrez=-2e9;
    for(int i=0;i<pw3[pom22];i++){


        ss a={0,0,0};

        int pom2=i;
        for(int j=0;j<pom22;j++){
            int id=pom2%3;
            pom2/=3;

            if(id==0){
                a=a+p[j];
                a.a-=p[j].a;
            }
            else if(id==1){
                a=a+p[j];
                a.b-=p[j].b;
            }
            else{
                a=a+p[j];
                a.c-=p[j].c;
            }
        }


        int blabla=max(max(a.a,a.b),a.c);
        trans2(a);

        if(mapa.find(a)==mapa.end())continue;
        pii ret=mapa[a];

        if(ret.ff+blabla>maxxrez){
            maxxrez=ret.ff+blabla;
            m1=i;
            m2=ret.ss;
        }
    }

    for(int i=0;i<pom22;i++){
        fin[i]=m1%3;
        m1/=3;
    }
    for(int i=0;i<pom;i++){
        fin[i+pom22]=m2%3;
        m2/=3;
    }

    if(maxxrez==-2e9){
        printf("Impossible\n");
        return 0;
    }
    for(int i=0;i<n;i++){
        if(fin[i]==0)printf("MW\n");
        else if(fin[i]==1)printf("LW\n");
        else if(fin[i]==2)printf("LM\n");
    }

    return 0;
}

