/*

    brief explanation:

        try pick vertices at the line intersections, making a rectangle
        then shift the side u can to make it a square
        extra case: when the points go on 2 parallel lines, then
        u can ternary search the optimal position bcs it bitonic
        or u can shift all points of the square to 1 point, and
        then the problem is, given points on a line shift them to
        a 1 point so that it makes them shift minimum distance
        this is just (max+min)/2


*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
typedef map<int,int>::iterator mit;
struct point{
    int x,y;
}p[5],init[5],rp[5];
int rez;
int get_dist(){

    int ret=0;
    for(int i=1;i<=4;i++)
        ret=max(ret,abs(p[i].x-init[i].x)+abs(p[i].y-init[i].y));

    return ret;
}
bool isrec1(){

    for(int i=1;i<=4;i++)
        for(int j=i+1;j<=4;j++)
            if(p[i].x==p[j].x && p[i].y==p[j].y)return false;


    map<int,int>mapax,mapay;
    for(int i=1;i<=4;i++){
        mapax[p[i].x]++;
        mapay[p[i].y]++;
    }

    if(mapax.size()!=2 || mapay.size()!=2)return false;

    for(mit it=mapax.begin();it!=mapax.end();it++)
        if(it->ss!=2)return false;

    for(mit it=mapay.begin();it!=mapay.end();it++)
        if(it->ss!=2)return false;

    return true;
}
bool isrec2(){

    map<int,int>mapax,mapay;
    for(int i=1;i<=4;i++){
        mapax[p[i].x]++;
        mapay[p[i].y]++;
    }

    if((mapax.size()==2 && mapay.size()==1) || (mapax.size()==1 && mapay.size()==2)){
        if(mapax.size()==2){
            for(mit it=mapax.begin();it!=mapax.end();it++)
                if(it->ss!=2)return false;
        }
        else{
            for(mit it=mapay.begin();it!=mapay.end();it++)
                if(it->ss!=2)return false;
        }

        return true;
    }
    else return false;
}
bool issq(){

    if(!isrec1())return false;

    set<int>dd;
    for(int i=1;i<=4;i++){
        for(int j=i+1;j<=4;j++){

            if(p[i].x==p[j].x)dd.insert(abs(p[i].y-p[j].y));
            else if(p[i].y==p[j].y)dd.insert(abs(p[i].x-p[j].x));

        }
    }
    if(dd.size()!=1)return false;
    return true;
}
void upd(){
    if(rez<=get_dist())return;
    rez=get_dist();
    for(int i=1;i<=4;i++)
        rp[i]=p[i];
}
bool is_side(int x,int y){
    if(p[x].x==p[y].x && p[x].y==p[y].y)return false;
    if(p[x].x==p[y].x)return true;
    if(p[x].y==p[y].y)return true;
    return false;
}
void check(){

    if(issq())upd();
    if(!isrec1() && !isrec2())return;

    ///ispis();

    ///return;

    ///check 1 side
    for(int i=1;i<=4;i++){
        for(int j=i+1;j<=4;j++){
            if(!is_side(i,j))continue;

            if(p[i].x==p[j].x){/// vert side
                if(p[i].y!=init[i].y)continue;
                if(p[j].y!=init[j].y)continue;

                int goal=abs(p[i].y-p[j].y);
                vector<int>other;
                for(int k=1;k<=4;k++)
                    if(k!=i && k!=j)other.pb(k);

                int curr=abs(p[i].x-p[other[0]].x);

                if(p[other[0]].x>=p[i].x){
                    p[i].x+=curr-goal;
                    p[j].x+=curr-goal;
                    upd();
                    p[i].x-=curr-goal;
                    p[j].x-=curr-goal;
                }
                else{
                    p[i].x-=curr-goal;
                    p[j].x-=curr-goal;
                    upd();
                    p[i].x+=curr-goal;
                    p[j].x+=curr-goal;
                }
            }
            else{/// horiz side
                if(p[i].x!=init[i].x)continue;
                if(p[j].x!=init[j].x)continue;

                int goal=abs(p[i].x-p[j].x);
                vector<int>other;
                for(int k=1;k<=4;k++)
                    if(k!=i && k!=j)other.pb(k);

                int curr=abs(p[i].y-p[other[0]].y);

                if(p[other[0]].y>=p[i].y){
                    p[i].y+=curr-goal;
                    p[j].y+=curr-goal;
                    upd();
                    p[i].y-=curr-goal;
                    p[j].y-=curr-goal;
                }
                else{
                    p[i].y-=curr-goal;
                    p[j].y-=curr-goal;
                    upd();
                    p[i].y+=curr-goal;
                    p[j].y+=curr-goal;
                }
            }

        }
    }


    /// check 2 side
    for(int i=1;i<=4;i++){
        for(int j=i+1;j<=4;j++){
            if(!is_side(i,j))continue;

            point prvx2[5];
            for(int k=1;k<=4;k++)prvx2[k]=p[k];


            if(p[i].x==p[j].x){/// vert side
                if(p[i].y!=init[i].y)continue;
                if(p[j].y!=init[j].y)continue;

                int goal=abs(p[i].y-p[j].y);
                vector<int>other;
                for(int k=1;k<=4;k++)
                    if(k!=i && k!=j)other.pb(k);

                if(p[other[0]].y!=init[other[0]].y)continue;
                if(p[other[1]].y!=init[other[1]].y)continue;


                p[i]=init[i];
                p[j]=init[j];
                p[other[0]]=init[other[0]];
                p[other[1]]=init[other[1]];

                int coef=(p[other[0]].x>=p[i].x?1:-1);

                p[other[0]].x-=goal*coef;
                p[other[1]].x-=goal*coef;

                int maxx=-1e9;
                int minx=1e9;
                for(int k=1;k<=4;k++){
                    maxx=max(maxx,p[k].x);
                    minx=min(minx,p[k].x);
                }

                int x1=(maxx+minx)/2;
                int x2=x1+goal;


                int inx1=x1;
                int inx2=x2;

                ///try1
                int prvx[5];
                for(int k=1;k<=4;k++)prvx[k]=p[k].x;
                p[i].x=x1;
                p[j].x=x1;
                p[other[0]].x=x2;
                p[other[1]].x=x2;
                upd();
                for(int k=1;k<=4;k++)p[k].x=prvx[k];

                ///try2
                for(int k=1;k<=4;k++)prvx[k]=p[k].x;
                p[i].x=x2;
                p[j].x=x2;
                p[other[0]].x=x1;
                p[other[1]].x=x1;
                upd();
                for(int k=1;k<=4;k++)p[k].x=prvx[k];


                p[i]=init[i];
                p[j]=init[j];
                p[other[0]]=init[other[0]];
                p[other[1]]=init[other[1]];

                coef=(p[other[0]].x>=p[i].x?1:-1)*-1;

                p[other[0]].x-=goal*coef;
                p[other[1]].x-=goal*coef;

                maxx=-1e9;
                minx=1e9;
                for(int k=1;k<=4;k++){
                    maxx=max(maxx,p[k].x);
                    minx=min(minx,p[k].x);
                }


                x1=(maxx+minx)/2;
                x2=x1+goal;


                inx1=x1;
                inx2=x2;

                ///try1
                for(int k=1;k<=4;k++)prvx[k]=p[k].x;
                p[i].x=x1;
                p[j].x=x1;
                p[other[0]].x=x2;
                p[other[1]].x=x2;
                upd();
                for(int k=1;k<=4;k++)p[k].x=prvx[k];

                ///try2
                for(int k=1;k<=4;k++)prvx[k]=p[k].x;
                p[i].x=x2;
                p[j].x=x2;
                p[other[0]].x=x1;
                p[other[1]].x=x1;
                upd();
                for(int k=1;k<=4;k++)p[k].x=prvx[k];

            }
            else{/// horiz side

                if(p[i].x!=init[i].x)continue;
                if(p[j].x!=init[j].x)continue;

                int goal=abs(p[i].x-p[j].x);
                vector<int>other;
                for(int k=1;k<=4;k++)
                    if(k!=i && k!=j)other.pb(k);


                if(p[other[0]].x!=init[other[0]].x)continue;
                if(p[other[1]].x!=init[other[1]].x)continue;

                p[i]=init[i];
                p[j]=init[j];
                p[other[0]]=init[other[0]];
                p[other[1]]=init[other[1]];

                int coef=(p[other[0]].y>=p[i].y?1:-1);

                p[other[0]].y-=goal*coef;
                p[other[1]].y-=goal*coef;

                int maxy=-1e9;
                int miny=1e9;
                for(int k=1;k<=4;k++){
                    maxy=max(maxy,p[k].y);
                    miny=min(miny,p[k].y);
                }


                int y1=(maxy+miny)/2;
                int y2=y1+goal;

                int iny1=y1;
                int iny2=y2;

                ///try1
                int prvy[5];
                for(int k=1;k<=4;k++)prvy[k]=p[k].y;
                p[i].y=y1;
                p[j].y=y1;
                p[other[0]].y=y2;
                p[other[1]].y=y2;
                upd();
                for(int k=1;k<=4;k++)p[k].y=prvy[k];

                ///try2
                for(int k=1;k<=4;k++)prvy[k]=p[k].y;
                p[i].y=y2;
                p[j].y=y2;
                p[other[0]].y=y1;
                p[other[1]].y=y1;
                upd();
                for(int k=1;k<=4;k++)p[k].y=prvy[k];

                p[i]=init[i];
                p[j]=init[j];
                p[other[0]]=init[other[0]];
                p[other[1]]=init[other[1]];

                coef=(p[other[0]].y>=p[i].y?1:-1)*-1;

                p[other[0]].y-=goal*coef;
                p[other[1]].y-=goal*coef;


                maxy=-1e9;
                miny=1e9;
                for(int k=1;k<=4;k++){
                    maxy=max(maxy,p[k].y);
                    miny=min(miny,p[k].y);
                }

                y1=(maxy+miny)/2;
                y2=y1+goal;


                ///try1
                for(int k=1;k<=4;k++)prvy[k]=p[k].y;
                p[i].y=y1;
                p[j].y=y1;
                p[other[0]].y=y2;
                p[other[1]].y=y2;
                upd();
                for(int k=1;k<=4;k++)p[k].y=prvy[k];

                ///try2
                for(int k=1;k<=4;k++)prvy[k]=p[k].y;
                p[i].y=y2;
                p[j].y=y2;
                p[other[0]].y=y1;
                p[other[1]].y=y1;
                upd();
                for(int k=1;k<=4;k++)p[k].y=prvy[k];

            }

            for(int k=1;k<=4;k++)p[k]=prvx2[k];
        }
    }

}
void go(int x){

    if(x>4){
        check();
        return;
    }

    int prv=p[x].x;
    for(int i=1;i<=4;i++){
        p[x].x=init[i].x;
        go(x+1);
    }
    p[x].x=prv;

    prv=p[x].y;
    for(int i=1;i<=4;i++){
        p[x].y=init[i].y;
        go(x+1);
    }
    p[x].y=prv;

}
int main(){

    ///freopen("test.txt","r",stdin);

    int t;
    scanf("%d",&t);
    while(t--){

        for(int i=1;i<=4;i++){
            scanf("%d %d",&p[i].x,&p[i].y);
            init[i]=p[i];
        }
        ///ispis();

        rez=1e9;
        go(1);

        if(rez==1e9)printf("-1\n");
        else{
            printf("%d\n",rez);
            for(int i=1;i<=4;i++)printf("%d %d\n",rp[i].x,rp[i].y);
        }

    }

    return 0;
}
