/*

    idea:https://codeforces.com/blog/entry/1598
*/
#include<bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10;
struct point{

    double x,y;

    point operator -(point b){
        point a=*this;
        return {a.x-b.x,a.y-b.y};
    }

    double dist(){
        return sqrt((double)x*x+y*y);
    }

    double dot(point b){
        point a=*this;
        return a.x*b.x+a.y*b.y;
    }

    double cross(point b){
        point a=*this;
        return a.x*b.y-a.y*b.x;
    }

    double cross(point c,point b){

        point a=*this;
        a=a-c;
        b=b-c;
        return a.cross(b);

    }

    void ispis(){
        printf("TACKA ");
        cout<<x<<" "<<y<<endl;
    }

};
int sgn(double a){
    if(a>0)return 1;
    if(a==0)return 0;
    return -1;
}

struct polygon{

    point center;
    map<double,point>hull;
    typedef map<double,point>::iterator mit;

    polygon(point center,vector<point> &p){

        this->center={0,0};
        for(int i=0;i<p.size();i++)this->center.x+=p[i].x,this->center.y+=p[i].y;
        this->center.x/=(double)p.size();
        this->center.y/=(double)p.size();

        for(int i=0;i<p.size();i++){
            hull[getAngle(this->center,p[i])]=p[i];
        }

    }

    static double getAngle(point c,point a){

        a=a-c;
        point b={1,0};


        double up=a.dot(b);
        double down=a.dist()*b.dist();

        return acos(up/down)*(sgn(b.cross(a))>=0?1:-1);
    }

    mit getLesser(double angle){

        mit it=hull.lower_bound(angle);
        if(it==hull.end())it=hull.begin();
        mit it2=pme(it);

        return it2;
    }

    mit getBigger(double angle){

        mit it=hull.lower_bound(angle);
        if(it==hull.end())it=hull.begin();

        return it;
    }

    bool takeDownLesser(point a){

        mit it=getLesser(getAngle(center,a));
        mit c=pme(it);

        if(it->ss.cross(c->ss,a)<=0){hull.erase(it);return true;}
        return false;
    }

    bool takeDownBigger(point a){

        mit it=getBigger(getAngle(center,a));
        mit c=nme(it);

        if(c->ss.cross(it->ss,a)<=0){hull.erase(it);return true;}
        return false;
    }

    void addPoint(point a){

        if(isInside(a))return;

        while(takeDownLesser(a)){}
        while(takeDownBigger(a)){}

        hull[getAngle(center,a)]=a;
    }

    mit pme(mit it){

        mit ret;

        if(it==hull.begin()){
            ret=hull.end();
            ret--;
        }
        else{
            ret=it;
            ret--;
        }

        return ret;
    }

    mit nme(mit it){

        mit ret;

        if(it==hull.end())ret=hull.begin();
        else {ret=it;ret++;}

        if(ret==hull.end())ret=hull.begin();

        return ret;

    }

    bool isInside(point a){

        double angle=getAngle(center,a);
        mit it=getBigger(angle);
        mit it2=getLesser(angle);

        point p1=it->ss;
        point p2=it2->ss;

        if(p1.cross(p2,a)>=0)return true;
        return false;

    }

    void ispis(){
        printf("POLYGON ");
        for(mit it=hull.begin();it!=hull.end();it++){
            cout<<it->ff<<" "<<it->ss.x<<" "<<it->ss.y<<" |";
        }
        printf("\n");
    }

};

int main(){

    ///freopen("test.txt","r",stdin);


    int q;
    scanf("%d",&q);
    q-=3;

    int t;
    point p1,p2,p3;
    scanf("%d %lf %lf",&t,&p1.x,&p1.y);
    scanf("%d %lf %lf",&t,&p2.x,&p2.y);
    scanf("%d %lf %lf",&t,&p3.x,&p3.y);

    vector<point>pom;
    pom.pb(p1);
    pom.pb(p2);
    pom.pb(p3);

    polygon p=*new polygon(p1,pom);



    while(q--){

        scanf("%d %lf %lf",&t,&p1.x,&p1.y);

        if(t==1)p.addPoint(p1);
        else{
            if(p.isInside(p1))printf("YES\n");
            else printf("NO\n");
        }

    }


    return 0;
}
