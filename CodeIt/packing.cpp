#include<bits/stdc++.h>
#define pb push_back
#define ss second
#define ff first
using namespace std;
typedef pair<int,int> pii;
const double eps=1e-6;/// calculation eps
clock_t start_time;
int cc2_const=1000;
int cc_const=30;
int aaa,aaa2;
int maxset,neki_cnt,ret_pcnt,ret_p2;
double eps2,ac;/// output eps
const double inf=1e18;
const double pi=3.14159265359;
const double rt_const=57.2957795;/// radian to degrees
const double dtr=2*pi/360;
const int cnt_const=1400;/// match lines coefficient
const int const_cnt2=30;
int n,trez[510],e=0,ch_tests=1;
int pos[510],isch[510];
double mostx[510],time2;
struct point{
   double x,y;
};
typedef pair<int,point> pip;
bool eq(double x,double y){
    if(abs(x-y)<=eps)return 1;
    return 0;
}
point operator -(point a,point b){
   return {a.x-b.x,a.y-b.y};
}
bool operator ==(point &a,point &b){
   if(eq(a.x,b.x) && eq(a.y,b.y))return 1;
   return 0;
}
bool time_to_end(){
    clock_t ctime=clock();
    if((double)((double)ctime-start_time)/CLOCKS_PER_SEC>4.7)return true;
    return false;
}
bool time_to_end2(){
    clock_t ctime=clock();
    if((double)((double)ctime-start_time)/CLOCKS_PER_SEC>time2)return true;
    return false;
}
struct polygon{
   vector<point>pt;
   vector<vector<int> >ch;
   vector<pii>sch;
   vector<int>spt;
   point center;
   int id,type;
   double surface,h;
}p[510],pocp[510];
struct trans{/// transformation(rotation and translation)
   double angle,dx,dy;
}rez[510];
struct line{/// line with its coefficients and 2 points which define her
   double k,b;
   point pt1,pt2;
};
struct pls{
    point pt;
    line ln;
    int pid;
};
pii event[20000];
pls stek[20000];
int brstek,brevent;
point get_center(polygon &x){
    point ret={0,0};
    for(int i=0;i<x.spt.size();i++){
        ret.x+=x.pt[x.spt[i]].x;
        ret.y+=x.pt[x.spt[i]].y;
    }
    ret.x/=(long double)x.spt.size();
    ret.y/=(long double)x.spt.size();
    return ret;
}
void handle_angle_movement(){
    if(ch_tests){
        if(ret_pcnt<1000)ac=1;
        else if(ret_pcnt<1600)ac=2;
        else if(ret_pcnt<2300)ac=3;
        else if(ret_pcnt<2900)ac=4;
        else if(ret_pcnt<3500)ac=5;
        else if(ret_pcnt<4000)ac=6;
        else ac=8;
    }
    else{
        if(ret_pcnt<700)ac=1;
        else if(ret_pcnt<1500)ac=2;
        else if(ret_pcnt<2300)ac=3;
        else if(ret_pcnt<2900)ac=4;
        else if(ret_pcnt<3500)ac=5;
        else if(ret_pcnt<4000)ac=6;
        else ac=8;

        if(ret_pcnt<=320){cc2_const=2200;cc_const=46;time2=4.5;}
        else if(ret_pcnt<=500){cc2_const=1500;cc_const=38;time2=4.4;}
        else if(ret_pcnt<=700){cc2_const=900;cc_const=30;time2=3.9;}
        else if(ret_pcnt<=1000){cc2_const=500;cc_const=22;time2=3.9;}
        else if(ret_pcnt<=1300){cc2_const=350;cc_const=18;time2=3.9;}
        else if(ret_pcnt<=1500){cc2_const=300;cc_const=18;time2=3.9;}
        else if(ret_pcnt<=2000){cc2_const=100;cc_const=15;time2=3.9;}
        else if(ret_pcnt<=3000){cc2_const=75;cc_const=9;time2=3.7;}
        else if(ret_pcnt<=4000){cc2_const=60;cc_const=8;time2=3.5;}
        else if(ret_pcnt<=5000){cc2_const=60;cc_const=8;time2=3.5;}
    }
}
bool srt_event(pii a,pii b){
    double y1,y2;

    if(a.ss==2)y1=stek[a.ff].pt.y;
    else if(a.ss==1)y1=stek[a.ff].ln.pt1.y;
    else y1=stek[a.ff].ln.pt2.y;

    if(b.ss==2)y2=stek[b.ff].pt.y;
    else if(b.ss==1)y2=stek[b.ff].ln.pt1.y;
    else y2=stek[b.ff].ln.pt2.y;

    if(eq(y1,y2))return a.ss<b.ss;
    else return y1<y2;
}
bool srt_ch(point a,point b){/// sorts points for convex hull building
   return (a.x<b.x)||(a.x==b.x && a.y<b.y);
}
bool srt_pol(polygon a,polygon b){/// sorts polygons by surface
   return a.surface>b.surface;
}
bool srt_h(polygon a,polygon b){/// sorts polygons by surface
   return a.h>b.h;
}
int next(int sz,int x){/// gets the next index in vector of size sz
    x++;
    x%=sz;
    return x;
}
int mex(int x,int y){/// gets mex of 2 values
   if(x>y)swap(x,y);
   if(x==0 && y==1)return 2;
   if(x==0)return 1;
   return 0;
}
double dist(point a,point b){
   return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}
line make_line(point a,point b){/// makes a line out of 2 points
   line ret;
   if(eq(a.x-b.x,0)){ret.k=inf;ret.b=a.x;}
   else{
        ret.k=(a.y-b.y)/(a.x-b.x);
        ret.b=a.y-ret.k*a.x;
   }
   ret.pt1=a;
   ret.pt2=b;
   return ret;
}
int sign(point c,point a,point b){/// sign of vector product
    a=a-c;
    b=b-c;
    double ret=a.x*b.y-b.x*a.y;
    if(eq(ret,0))return 0;
    return ret>0?1:-1;
}
double v_product(point c,point a,point b){/// vector product
    a=a-c;
    b=b-c;
    double ret=a.x*b.y-b.x*a.y;
    return ret;
}
double raw_surface(vector<point> &vect){/// oriented surface
    double ret=0;
    for(int i=0;i<vect.size();i++)
        ret+=v_product({0,0},vect[i],vect[next(vect.size(),i)]);
    return ret/2.0;
}
double actual_surface(vector<point> &vect){/// surface
   return abs(raw_surface(vect));
}
double get_miny(polygon &x){
   double ret=inf;
   for(int i=0;i<x.spt.size();i++)ret=min(ret,x.pt[x.spt[i]].y);
   return ret;
}
double get_minx(polygon &x){
   double ret=inf;
   for(int i=0;i<x.spt.size();i++)ret=min(ret,x.pt[x.spt[i]].x);
   return ret;
}
double get_maxx(polygon &x){
   double ret=-inf;
   for(int i=0;i<x.spt.size();i++)ret=max(ret,x.pt[x.spt[i]].x);
   return ret;
}
double get_maxy(polygon &x){
   double ret=-inf;
   for(int i=0;i<x.spt.size();i++)ret=max(ret,x.pt[x.spt[i]].y);
   return ret;
}
double get_minx_ch(polygon &x,int id){
   double ret=inf;
   for(int i=0;i<x.ch[id].size();i++)ret=min(ret,x.pt[x.ch[id][i]].x);
   return ret;
}
double get_maxx_ch(polygon &x,int id){
   double ret=-inf;
   for(int i=0;i<x.ch[id].size();i++)ret=max(ret,x.pt[x.ch[id][i]].x);
   return ret;
}
double get_miny_ch(polygon &x,int id){
   double ret=inf;
   for(int i=0;i<x.ch[id].size();i++)ret=min(ret,x.pt[x.ch[id][i]].y);
   return ret;
}
double get_maxy_ch(polygon &x,int id){
   double ret=-inf;
   for(int i=0;i<x.ch[id].size();i++)ret=max(ret,x.pt[x.ch[id][i]].y);
   return ret;
}
line get_any_line(polygon &x){
   return make_line(x.pt[x.ch[0][0]],x.pt[x.ch[0][1]]);
}
bool intersect(line a,line b){

    ///if(max(a.pt1.x,a.pt2.x)<min(b.pt1.x,b.pt2.x) || min(a.pt1.x,a.pt2.x)>max(b.pt1.x,b.pt2.x) || max(a.pt1.y,a.pt2.y)<min(b.pt1.y,b.pt2.y) || min(a.pt1.y,a.pt2.y)>max(b.pt1.y,b.pt2.y))return false;

    int p1=sign(a.pt1,a.pt2,b.pt1);
    int p2=sign(a.pt1,a.pt2,b.pt2);
    if(p1==0 && p2==0)return 1;

    if(p1!=p2 && sign(b.pt1,b.pt2,a.pt1)!=sign(b.pt1,b.pt2,a.pt2))return true;
    return false;
}
bool clockwise(vector<point> &vect){/// checks whether the polygon is sorted clockwise
    if(raw_surface(vect)<0)return 1;
    return 0;
}
void regulate_angle(double &x){/// mods the angle to fit into 2pi
    if(x<0)x+=2*pi;
    else if(x>2*pi)x-=2*pi;
}
void calibrate_cc(int prod){

    if(prod<=2500){cc2_const=1600;cc_const=46;}
    else if(prod<=9000){cc2_const=500;cc_const=23;}
    else if(prod<=10000){cc2_const=400;cc_const=20;}
    else if(prod<=20000){cc2_const=350;cc_const=22;}
    else if(prod<=30000){cc2_const=300;cc_const=22;}
    else if(prod<=40000){cc2_const=250;cc_const=18;}
    else if(prod<=50000){cc2_const=200;cc_const=17;}
    else if(prod<=60000){cc2_const=150;cc_const=13;}
    else if(prod<=70000){cc2_const=100;cc_const=10;}
    else if(prod<=80000){cc2_const=50;cc_const=13;}
    else if(prod<=90000){cc2_const=50;cc_const=13;}
    else if(prod<=100000){cc2_const=40;cc_const=12;}
    else{cc2_const=10;cc_const=8;}

}
double get_angle(line a){/// gets angle of the line in radians

    a.pt2=a.pt2-a.pt1;

    if(eq(a.pt2.x,0)){
        if(a.pt2.y>0)return pi/2;
        else return pi+pi/2;
    }

    double ret=atan(a.k);
    if(a.pt2.x<0)ret+=pi;

    return ret;
}
void rotate(point &p,double angle,point origin){/// rotates a point around the origin by angle
   p=p-origin;

   double s=sin(angle);
   double c=cos(angle);

   point ret;
   ret.x=p.x*c-p.y*s;
   ret.y=p.x*s+p.y*c;

   p.x=ret.x+origin.x;
   p.y=ret.y+origin.y;
}
void transform(polygon &x,trans tt,point origin,int id){/// transforms a polygon by transformation pattern tt aroung origin

    for(int i=0;i<x.pt.size();i++){
        if(!eq(tt.angle,0))rotate(x.pt[i],tt.angle,origin);
        x.pt[i].x+=tt.dx;
        x.pt[i].y+=tt.dy;
    }
    rotate(x.center,tt.angle,origin);
    x.center.x+=tt.dx;
    x.center.y+=tt.dy;

    rez[id].dx+=tt.dx;
    rez[id].dy+=tt.dy;
    rez[id].angle+=tt.angle;
    regulate_angle(rez[id].angle);
}
trans transformation(line a,line b){/// calculate the transformation needed to make a parallel to b

   double angle1=get_angle(a);
   double angle2=get_angle(b);

   double diff=angle2-angle1;

   regulate_angle(diff);

   rotate(a.pt1,diff,{0,0});
   rotate(a.pt2,diff,{0,0});

   return {diff,b.pt1.x-a.pt1.x,b.pt1.y-a.pt1.y};
}
void get_convex_hull(polygon &x,vector<point> &vect){/// given points, calculates convex hull

    vector<point>ret(x.spt.size());
    for(int i=0;i<x.spt.size();i++)ret[i]=x.pt[x.spt[i]];

   sort(ret.begin(),ret.end(),srt_ch);

   point stek[ret.size()+10];
   int br=0;

   for(int i=0;i<ret.size();i++){
    while(br>1 && v_product(ret[i],stek[br],stek[br-1])<=0)br--;
    stek[++br]=ret[i];
   }
   br--;
   int brg=br;
   for(int i=ret.size()-1;i>=0;i--){
    while(br>brg+1 && v_product(ret[i],stek[br],stek[br-1])<=0)br--;
    stek[++br]=ret[i];
   }
   br--;

   vect.resize(br);
   vect[0]=stek[1];
   int br2=1;
   for(int i=2;i<=br;i++){
    if(vect[vect.size()-1]==stek[i])continue;
    vect[br2++]=stek[i];
   }
   vect.resize(br2);
}
void get_convex_hull2(polygon &x,polygon &y,vector<point> &vect){/// given points, calculates convex hull

    vector<point>ret(x.spt.size()+y.spt.size());
    for(int i=0;i<x.spt.size();i++)ret[i]=x.pt[x.spt[i]];
    for(int i=0;i<y.spt.size();i++)ret[i+x.spt.size()]=y.pt[y.spt[i]];

   sort(ret.begin(),ret.end(),srt_ch);

   point stek[ret.size()+10];
   int br=0;

   for(int i=0;i<ret.size();i++){
    while(br>1 && v_product(ret[i],stek[br],stek[br-1])<=0)br--;
    stek[++br]=ret[i];
   }
   br--;
   int brg=br;
   for(int i=ret.size()-1;i>=0;i--){
    while(br>brg+1 && v_product(ret[i],stek[br],stek[br-1])<=0)br--;
    stek[++br]=ret[i];
   }
   br--;

   vect.resize(br);
   vect[0]=stek[1];
   int br2=1;
   for(int i=2;i<=br;i++){
    if(vect[vect.size()-1]==stek[i])continue;
    vect[br2++]=stek[i];
   }
   vect.resize(br2);
}
void read_and_formulate_figure(polygon &x){/// forms input


    /// read point included in the whole figure
    int np;
    scanf("%d",&np);
    for(int i=0;i<np;i++){
        point pom;
        scanf("%lf %lf",&pom.x,&pom.y);
        x.pt.pb(pom);
    }

    map<pii,int>mapa;

    /// read points for every subpolygon
    scanf("%d",&np);
    for(int i=0;i<np;i++){
        int dots;
        scanf("%d",&dots);
        if(dots!=4)e=1;
        vector<int>pom;
        vector<point>pom2;
        for(int j=0;j<dots;j++){
            int pp;
            scanf("%d",&pp);
            pom.pb(pp);
            pom2.pb(x.pt[pp]);

            if(j>0){
                if(!eq(dist(pom2[j],pom2[j-1]),1))e=1;
            }
        }
        x.ch.pb(pom);
        x.surface+=actual_surface(pom2);
        if(!eq(actual_surface(pom2),1))e=1;

        for(int j=0;j<dots;j++){
            int pp=pom[j];
            int nxt=next(dots,j);
            mapa[{min(pom[j],pom[nxt]),max(pom[j],pom[nxt])}]++;
        }
    }
    if(np!=4)e=1;

    if(np>1)ch_tests=0;

    set<int>st;
    for(map<pii,int>::iterator it=mapa.begin();it!=mapa.end();it++){
        if(it->ss>1)continue;
        x.sch.pb(it->ff);
        st.insert(it->ff.ff);
        st.insert(it->ff.ss);
    }

    for(set<int>::iterator it=st.begin();it!=st.end();it++)
        x.spt.pb(*it);

    ret_p2+=x.pt.size();
    ret_pcnt+=x.sch.size();
}
void read_input(){/// input

   scanf("%d",&n);
   for(int i=1;i<=n;i++){
        read_and_formulate_figure(p[i]);
        p[i].id=i;

        pocp[i]=p[i];
        p[i].center=get_center(p[i]);
   }
   if(e)eps2=1;
   else eps2=0.0001;

   handle_angle_movement();
}
bool point_in_ch(point p,polygon &x,int id){

    for(int i=0;i<x.ch[id].size();i++){
        int nxt=next(x.ch[id].size(),i);
        if(sign(x.pt[x.ch[id][i]],x.pt[x.ch[id][nxt]],p)<0)return false;
    }
return true;
}
bool point_in_polygon(point p,polygon &x){

   for(int i=0;i<x.ch.size();i++)
    if(point_in_ch(p,x,i))return true;

   return false;
}
int find_next(int sz,int f,int s){
   for(int i=0;i<sz;i++){
    if(i==f || i==s)continue;
    return i;
   }
}
bool hplch_check(polygon &x,int id,polygon &y,int id2){

    for(int i=0;i<x.ch[id].size();i++){
        int pid=next(x.ch[id].size(),i);
        int pom=find_next(x.ch[id].size(),i,pid);
        int psign=sign(x.pt[x.ch[id][i]],x.pt[x.ch[id][pid]],x.pt[x.ch[id][pom]]);

        int e=0;
        for(int j=0;j<y.ch[id2].size();j++){
            point pp;
            pp=y.pt[y.ch[id2][j]];

            if(sign(x.pt[x.ch[id][i]],x.pt[x.ch[id][pid]],pp)==psign){
                e=1;
                break;
            }
        }

        if(!e)return true;
    }
return false;
}
bool polygon_intersect(polygon &x,polygon &y){

    if(point_in_polygon(y.pt[0],x))return true;

    for(int i=0;i<x.sch.size();i++){
        line p1=make_line(x.pt[x.sch[i].ff],x.pt[x.sch[i].ss]);
        p1.pt1=x.pt[x.sch[i].ff];
        p1.pt2=x.pt[x.sch[i].ss];
        for(int j=0;j<y.sch.size();j++){

            line p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
            p2.pt1=y.pt[y.sch[j].ff];
            p2.pt2=y.pt[y.sch[j].ss];
            if(intersect(p1,p2))return true;
        }
    }

return false;
}
bool check(polygon &x,int last,double xcord){/// returns true if x doesnt intersect with and polygon

    for(int i=last;i>=1 && xcord<=mostx[i];i--){
        if(polygon_intersect(x,p[i]))return false;
    }

return true;
}
double point_to_line(point x,line y){
    if(y.pt1.y>y.pt2.y)swap(y.pt1,y.pt2);

    if(x.y>y.pt2.y || x.y<y.pt1.y)return inf;

    if(eq(y.k,inf))return abs(x.x-y.b);

    double cx;
    if(eq(y.k,0))return min(abs(x.x-y.pt1.x),abs(x.x-y.pt2.x));
    else cx=(x.y-y.b)/y.k;

    return abs(cx-x.x);
}
double how_close(polygon &l,polygon &r){

    double ret=inf;

    brstek=0;
    brevent=0;

    for(int i=0;i<l.spt.size();i++){
        int id=l.spt[i];
        pls pom;
        pom.pt=l.pt[id];
        pom.pid=0;
        stek[brstek++]=pom;
        event[brevent++]={brstek-1,2};
    }
    for(int i=0;i<r.spt.size();i++){
        int id=r.spt[i];
        pls pom;
        pom.pt=r.pt[id];
        pom.pid=1;
        stek[brstek++]=pom;
        event[brevent++]={brstek-1,2};
    }
    for(int i=0;i<l.sch.size();i++){
        int id=l.sch[i].ff;
        int nxt=l.sch[i].ss;
        line pom=make_line(l.pt[id],l.pt[nxt]);
        if(pom.pt1.y>pom.pt2.y)swap(pom.pt1,pom.pt2);
        pls ppom;
        ppom.ln=pom;
        ppom.pid=0;
        stek[brstek++]=ppom;
        event[brevent++]={brstek-1,1};
        event[brevent++]={brstek-1,3};
    }
    for(int i=0;i<r.sch.size();i++){
        int id=r.sch[i].ff;
        int nxt=r.sch[i].ss;
        line pom=make_line(r.pt[id],r.pt[nxt]);
        if(pom.pt1.y>pom.pt2.y)swap(pom.pt1,pom.pt2);
        pls ppom;
        ppom.ln=pom;
        ppom.pid=1;
        stek[brstek++]=ppom;
        event[brevent++]={brstek-1,1};
        event[brevent++]={brstek-1,3};
    }
    sort(event,event+brevent,srt_event);

    unordered_set<int>st[2];

    for(int i=0;i<brevent;i++){

        maxset=max(maxset,(int)st[1].size());
        maxset=max(maxset,(int)st[0].size());

        if(event[i].ss==2){/// point query

            int wp=(stek[event[i].ff].pid^1);
            point pom=stek[event[i].ff].pt;
            for(unordered_set<int>::iterator it=st[wp].begin();it!=st[wp].end();it++){
                ret=min(ret,point_to_line(pom,stek[*it].ln));

                neki_cnt++;
            }

        }
        else if(event[i].ss==1)st[stek[event[i].ff].pid].insert(event[i].ff);
        else st[stek[event[i].ff].pid].erase(event[i].ff);

    }

    return ret;
}
void tryout(polygon &x,int last){/// closen 2 polygons

    transform(x,(trans){0,mostx[last]+1-get_minx(x),-get_miny(x)},(point){0,0},x.id);

    double ret=how_close(p[last],x);
    if(last-1>0)ret=min(how_close(p[last-1],x),ret);

    transform(x,(trans){0,-ret+eps2,0},(point){0,0},x.id);

    mostx[last+1]=max(get_maxx(x),mostx[last]);
}
point get_hpoint(polygon &x){
    point ret={-inf,-inf};
   for(int i=0;i<x.pt.size();i++){
        if(x.pt[i].y>ret.y){
            ret=x.pt[i];
        }
        else if(x.pt[i].y==ret.y){
            if(x.pt[i].x>ret.x)ret=x.pt[i];
        }
   }
   return ret;
}
void write_ch(){
   memset(isch,0,sizeof(isch));

   int br=0;
   pair<int,point>stek[n+10];
   for(int i=1;i<=n;i++){
    point pom=get_hpoint(p[i]);
    while(sign(stek[br-1].ss,stek[br].ss,pom)>=0 && br>1)br--;
    stek[++br]={i,pom};
   }
   for(int i=1;i<=br;i++)isch[stek[i].ff]=1;
}
int get_first(){

   for(int i=1;i<=n;i++){
        if(pos[i])continue;
        if(isch[i])continue;
        return i;
   }
   return -1;
}
pip get_l(int x){
   for(int i=x;i>=1;i--){
    if(!isch[i])continue;
    return {i,get_hpoint(p[i])};
   }
}
pip get_r(int x){
   for(int i=x;i<=n;i++){
    if(!isch[i])continue;
    return {i,get_hpoint(p[i])};
   }
}
void handle(polygon &x,int last,pip l,pip r){

    int dokle=min(last+2,n);

    double mindiff=inf;
    double minangle;

    double sp=get_maxx(p[dokle]);
    for(int i=1;i<=360/(int)ac;i++){

        transform(x,(trans){dtr*ac,0,0},(point){0,0},x.id);
        transform(x,(trans){0,0,-get_miny(x)},(point){0,0},x.id);

        for(int j=last;j<=dokle;j++)tryout(p[j],j-1);

        double tren=get_maxx(p[dokle]);
        double diff=tren-sp;

        pip pom=r;
        pom.ss.x+=diff;

        if(sign(pom.ss,l.ss,get_hpoint(x))>=0){
            if(diff<mindiff){
                mindiff=diff;
                minangle=i;
            }
        }
    }

    transform(x,(trans){dtr*minangle*ac,0,0},(point){0,0},x.id);
    transform(x,(trans){0,0,-get_miny(x)},(point){0,0},x.id);
    for(int j=last;j<=dokle;j++)tryout(p[j],j-1);

    for(int i=dokle+1;i<=n;i++){
        transform(p[i],(trans){0,mindiff,0},(point){0,0},p[i].id);
        mostx[i]=max(mostx[i-1],get_maxx(p[i]));
    }

}
void sort_sch(polygon &x){
    vector<pair<double,pii> >stk(x.sch.size());
    for(int i=0;i<x.sch.size();i++){
        stk[i].ff=dist(x.pt[x.sch[i].ff],x.pt[x.sch[i].ss]);
        stk[i].ss=x.sch[i];
    }
    sort(stk.begin(),stk.end());
    for(int i=0;i<x.sch.size();i++)x.sch[i]=stk[x.sch.size()-i-1].ss;
}
point get_a_from_b(point a,point b){

    point ret;
    if(a.x>b.x)ret.x=eps2/2;
    else ret.x=-eps2/2;

    if(a.y>b.y)ret.y=eps2/2;
    else ret.y=-eps2/2;

    return ret;
}
trans fix_to_fit(line a,point ca,line b,point cb){

    if(b.pt1.x==b.pt2.x){
        if(b.pt1.y>b.pt2.y)swap(b.pt1,b.pt2);
        if(a.pt1.y>a.pt2.y)swap(a.pt1,a.pt2);
        return {0,b.pt1.x-a.pt1.x,b.pt1.y-a.pt1.y};
    }
    if(b.pt1.x>b.pt2.x)swap(b.pt1,b.pt2);
    if(a.pt1.x>a.pt2.x)swap(a.pt1,a.pt2);

    point pom=get_a_from_b({ca.x+b.pt1.x-a.pt1.x,ca.y+b.pt1.y-a.pt1.y},cb);

    return {0,b.pt1.x-a.pt1.x+pom.x,b.pt1.y-a.pt1.y+pom.y};
}
void apply_changes(polygon &x,polygon &y,int i,int j){
    line p1=make_line(x.pt[x.sch[i].ff],x.pt[x.sch[i].ss]);
    line p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
    trans pom=transformation(p2,p1);
    transform(y,{pom.angle,0,0},{0,0},y.id);
    p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
    pom=fix_to_fit(p2,y.center,p1,x.center);
    transform(y,pom,{0,0},y.id);

    if(!polygon_intersect(x,y))return;

    /// rotate by 180 and try again
    transform(y,{180*dtr,0,0},{0,0},y.id);
    p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
    pom=fix_to_fit(p2,y.center,p1,x.center);
    transform(y,pom,{0,0},y.id);
    if(!polygon_intersect(x,y))return;
}
void insert_x_to_y(polygon &x,polygon &y){

    for(int i=0;i<x.ch.size();i++){
        y.ch.pb(x.ch[i]);
        for(int j=0;j<x.ch[i].size();j++)y.ch[y.ch.size()-1][j]+=y.pt.size();
    }
    for(int i=0;i<x.sch.size();i++){
        y.sch.pb(x.sch[i]);
        y.sch[y.sch.size()-1].ff+=y.pt.size();
        y.sch[y.sch.size()-1].ss+=y.pt.size();
    }
    for(int i=0;i<x.spt.size();i++){
        y.spt.pb(x.spt[i]);
        y.spt[y.spt.size()-1]+=y.pt.size();
    }
    for(int i=0;i<x.pt.size();i++){
        y.pt.pb(x.pt[i]);
    }
    sort_sch(y);
    y.center=get_center(y);
}
void match_lines(polygon &x,polygon &y){

   double minsur=inf;
   int id1=-1,id2;

   int cc2=0;
   suff:;
   for(int i=0;i<x.sch.size();i++){/// probam prvi ugao, pa onda za 180 vise, i koji se ne sece uzmem

        if(time_to_end2())cc2_const=0;

        line p1=make_line(x.pt[x.sch[i].ff],x.pt[x.sch[i].ss]);

        int cc=0;
        if(cc2>cc2_const && id1!=-1)break;

        for(int j=0;j<y.sch.size();j++){

            if(time_to_end2())cc2_const=0;
            cc++;
            cc2++;
            if(cc2_const==0){
                if(id1!=-1)break;
            }
            else if(cc>cc_const)break;

            line p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
            trans pom=transformation(p2,p1);
            transform(y,{pom.angle,0,0},{0,0},y.id);
            p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
            pom=fix_to_fit(p2,y.center,p1,x.center);
            transform(y,pom,{0,0},y.id);

            if(!polygon_intersect(x,y)){
                vector<point>convex;
                get_convex_hull2(x,y,convex);
                double acsf=actual_surface(convex);

                if(acsf<minsur){
                    minsur=acsf;
                    id1=i;
                    id2=j;
                }

                continue;
            }

            /// rotate by 180 and try again
            transform(y,{180*dtr,0,0},{0,0},y.id);
            p2=make_line(y.pt[y.sch[j].ff],y.pt[y.sch[j].ss]);
            pom=fix_to_fit(p2,y.center,p1,x.center);
            transform(y,pom,{0,0},y.id);
            if(!polygon_intersect(x,y)){

                vector<point>convex;
                get_convex_hull2(x,y,convex);
                double acsf=actual_surface(convex);

                if(acsf<minsur){
                    minsur=acsf;
                    id1=i;
                    id2=j;
                }

                continue;
            }

        }

   }
   int prvcc=cc2_const;
   if(id1==-1){cc2_const=0;goto suff;}

   cc2_const=prvcc;

    apply_changes(x,y,id1,id2);
    insert_x_to_y(y,x);
}
void go(){/// line to line

    polygon pom=p[1];
    trez[p[1].id]=1;
    sort_sch(pom);

    for(int i=2;i<=n;i++){
        trez[p[i].id]=1;
        match_lines(pom,p[i]);    }
}
void try_merging(){/// merging convex hulls

    for(int i=1;i<=n;i++){

        double currangle=0;
        double minn=inf;
        double bestangle;

        for(int j=1;j<=360;j++){/// find angle with lowest h
            currangle+=dtr;
            transform(p[i],(trans){dtr,0,0},(point){0,0},p[i].id);
            double miny=get_miny(p[i]);
            double maxy=get_maxy(p[i]);

            if(maxy-miny<=minn){
                minn=maxy-miny;
                bestangle=currangle;
            }
        }

        transform(p[i],(trans){bestangle,0,0},(point){0,0},p[i].id);
        p[i].h=minn;
    }

    sort(p+1,p+n+1,srt_h);/// sort polygons by h

    if(!ch_tests){go();return;}

    trez[p[1].id]=1;
    double minx=get_minx(p[1]);
    double miny=get_miny(p[1]);

    trans tp;
    tp.angle=0;
    tp.dx=-minx;
    tp.dy=-miny;
    transform(p[1],tp,(point){0,0},p[1].id);

    mostx[1]=get_maxx(p[1]);
    double maxy=get_maxy(p[1]);

    for(int i=2;i<=n;i++){
        tryout(p[i],i-1);
        trez[p[i].id]=1;
    }

    /// optimise solution

    /// nadjem ch najvisih tacaka
    /// nadjem prvu nestelovanu koje nema u ch i odradim
    /// update mostx i kordinate svih poligona


    for(int i=1;i<=n;i++){

        if(time_to_end())break;

        write_ch();
        int fst=get_first();
        if(fst==-1)break;
        pip pom2=get_l(fst);
        pip pom3=get_r(fst);

        pos[fst]=1;
        handle(p[fst],fst,pom2,pom3);
    }

}
int cube_angle(polygon &x,int a,int b){

    set<int>mapa;
    for(int i=0;i<4;i++)mapa.insert(x.ch[a][i]);
    for(int i=0;i<4;i++)if(mapa.find(x.ch[b][i])!=mapa.end())return 90;

    return 180;
}
point center(polygon &x,int id){
    double retx=0;
    double rety=0;

    for(int i=0;i<4;i++){
        retx+=x.pt[x.ch[id][i]].x;
        rety+=x.pt[x.ch[id][i]].y;
    }

    return {retx/4,rety/4};
}
int sub_type5(polygon &x,vector<int> vect[4]){

    int curr;
    for(int i=0;i<4;i++)
    if(vect[i].size()==1){
        curr=i;
        break;
    }


    int prv=-1;
    int stek[3],br=-1;
    while(1){

        int child=0;
        for(int i=0;i<vect[curr].size();i++){
            int id=vect[curr][i];
            if(id==prv)continue;

            child++;
            if(prv!=-1)stek[++br]=sign(center(x,prv),center(x,curr),center(x,id));
            else stek[++br]=0;
            prv=curr;
            curr=id;
        }
        if(child==0)break;
    }

    if(stek[1]==1)return 5;
    else return 7;
}
int sub_type4(polygon &x,vector<int> vect[4]){

    int curr;
    for(int i=0;i<4;i++){
    if(vect[i].size()==1){
        curr=i;
        break;
    }
    }


    int prv=-1;
    int stek[3],br=-1;
    while(1){
        int child=0;
        for(int i=0;i<vect[curr].size();i++){
            int id=vect[curr][i];
            if(id==prv)continue;

            child++;
            if(prv!=-1)stek[++br]=sign(center(x,prv),center(x,curr),center(x,id));
            else stek[++br]=0;
            prv=curr;
            curr=id;
        }
        if(child==0)break;
    }

    if((stek[0]==0 && stek[1]==0 && stek[2]==1)||(stek[0]==0 && stek[1]==-1 && stek[2]==0))return 4;
    else return 6;
}
int type(polygon &x){/// determine type of tetromino

    vector<int>vect[4];
    for(int i=0;i<4;i++){/// get graph
        set<pii>mapa;
        for(int j=0;j<4;j++){
            int id=next(4,j);
            mapa.insert({min(x.ch[i][j],x.ch[i][id]),max(x.ch[i][j],x.ch[i][id])});
        }

        for(int j=i+1;j<4;j++)
            for(int k=0;k<4;k++)
                if(mapa.find({min(x.ch[j][k],x.ch[j][next(4,k)]),max(x.ch[j][k],x.ch[j][next(4,k)])})!=mapa.end()){
                    vect[i].pb(j);
                    vect[j].pb(i);
                    break;
                }
    }

    int cnt[4];
    int cnt90=0;
    int cnt180=0;
    memset(cnt,0,sizeof(cnt));
    for(int i=0;i<4;i++){
        cnt[vect[i].size()]++;
        if(vect[i].size()==2){
            if(cube_angle(x,vect[i][0],vect[i][1])==90)cnt90++;
            else cnt180++;
        }
    }

    if(cnt[2]==4)return 1;
    if(cnt[1]==3)return 2;
    if(cnt180==2)return 3;
    if(cnt90==2)return sub_type5(x,vect);
    return sub_type4(x,vect);

}
void make_parallel_and_get_to_origin(polygon &x){
    line l1=get_any_line(x);
    line l2=make_line({0,0},{1,0});
    trans pom=transformation(l1,l2);
    pom.dx=0;
    pom.dy=0;
    transform(x,pom,(point){0,0},x.id);

    double minx=get_minx(x);
    double miny=get_miny(x);
    transform(x,(trans){0,-minx,-miny},(point){0,0},x.id);
}
void count_points_per_line(polygon &x,vector<int> &ret){
   for(int i=0;i<x.pt.size();i++){
    double pom=x.pt[i].x;
    pom=round(pom);
    int pom2=pom;
    ret[pom2]++;
   }
}
void count_points_per_line_y(polygon &x,vector<int> &ret){
   for(int i=0;i<x.pt.size();i++){
    double pom=x.pt[i].y;
    pom=round(pom);
    int pom2=pom;
    ret[pom2]++;
   }
}
void get_to_x0(polygon &x){
   double minx=get_minx(x);
   transform(x,(trans){0,-minx,0},(point){0,0},x.id);
}
void get_to_y0(polygon &x){
   double miny=get_miny(x);
   transform(x,(trans){0,0,-miny},(point){0,0},x.id);
}
void regulate_tetromino_1(polygon &x){
    make_parallel_and_get_to_origin(x);
}
void regulate_tetromino_2(polygon &x){

    make_parallel_and_get_to_origin(x);
    vector<int>cnt(5,0);
    count_points_per_line(x,cnt);
    vector<int>cnt2(5,0);
    count_points_per_line_y(x,cnt);

    if(cnt[0]==4 && cnt[1]==4 && cnt[2]==2){
        transform(x,(trans){dtr*90,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==2 && cnt[1]==3 && cnt[2]==3 && cnt[3]==2 && cnt2[0]==2){
        transform(x,(trans){dtr*180,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==2 && cnt[1]==4 && cnt[2]==4){
        transform(x,(trans){dtr*270,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
}
void regulate_tetromino_3(polygon &x){

    make_parallel_and_get_to_origin(x);
    vector<int>cnt(5,0);
    count_points_per_line(x,cnt);

    if(cnt[0]==5){
        transform(x,(trans){dtr*90,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
}
void regulate_tetromino_4(polygon &x){

    make_parallel_and_get_to_origin(x);
    vector<int>cnt(5,0);
    count_points_per_line(x,cnt);

    if(cnt[0]==2 && cnt[1]==4 && cnt[2]==4){
        transform(x,(trans){dtr*90,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==2 && cnt[1]==2 && cnt[2]==3 && cnt[3]==3){
        transform(x,(trans){dtr*180,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==4 && cnt[1]==4 && cnt[2]==2){
        transform(x,(trans){dtr*270,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
}
void regulate_tetromino_5(polygon &x){

    make_parallel_and_get_to_origin(x);
    vector<int>cnt(5,0);
    count_points_per_line(x,cnt);

    if(cnt[0]==3 && cnt[1]==4 && cnt[2]==3){
        transform(x,(trans){dtr*90,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==2 && cnt[1]==3 && cnt[2]==3 && cnt[3]==2){
        transform(x,(trans){dtr*180,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==3 && cnt[1]==4 && cnt[2]==3){
        transform(x,(trans){dtr*270,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
}
void regulate_tetromino_6(polygon &x){

    make_parallel_and_get_to_origin(x);
    vector<int>cnt(5,0);
    count_points_per_line(x,cnt);

    if(cnt[0]==2 && cnt[1]==4 && cnt[2]==4){
        transform(x,(trans){dtr*90,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==3 && cnt[1]==3 && cnt[2]==2 && cnt[3]==2){
        transform(x,(trans){dtr*180,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==4 && cnt[1]==4 && cnt[2]==2){
        transform(x,(trans){dtr*270,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
}
void regulate_tetromino_7(polygon &x){

    make_parallel_and_get_to_origin(x);
    vector<int>cnt(5,0);
    count_points_per_line(x,cnt);

    if(cnt[0]==3 && cnt[1]==4 && cnt[2]==3){
        transform(x,(trans){dtr*90,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==2 && cnt[1]==3 && cnt[2]==3 && cnt[3]==2){
        transform(x,(trans){dtr*180,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
    else if(cnt[0]==3 && cnt[1]==4 && cnt[2]==3){
        transform(x,(trans){dtr*270,0,0},(point){0,0},x.id);
        get_to_x0(x);
        get_to_y0(x);
    }
}
void tetromino(){/// solve tetromino

    /// determine type
    for(int i=1;i<=n;i++)p[i].type=type(p[i]);

    /// regulate tetrominos
    for(int i=1;i<=n;i++){
        if(p[i].type==1)regulate_tetromino_1(p[i]);
        else if(p[i].type==2)regulate_tetromino_2(p[i]);
        else if(p[i].type==3)regulate_tetromino_3(p[i]);
        else if(p[i].type==4)regulate_tetromino_4(p[i]);
        else if(p[i].type==5)regulate_tetromino_5(p[i]);
        else if(p[i].type==6)regulate_tetromino_6(p[i]);
        else if(p[i].type==7)regulate_tetromino_7(p[i]);

        trez[i]=1;
    }

    vector<int>tpt[8];
    for(int i=1;i<=n;i++)tpt[p[i].type].pb(i);

    /// solve


    double lastx=0+eps2;
    int luft=0;
    int koji_luft=0;

    for(int i=0;i<tpt[1].size();i++){/// postavljaj 1
        int id=tpt[1][i];
        transform(p[id],(trans){0,lastx-get_minx(p[id]),0},(point){0,0},p[id].id);
        lastx+=2+eps2;
    }

    for(int i=0;i<tpt[3].size();i++){/// postavljaj 3
        int id=tpt[3][i];
        if(luft==0){
            transform(p[id],(trans){0,lastx-get_minx(p[id]),0},(point){0,0},p[id].id);
            luft=4;
            lastx+=4+eps2;
            koji_luft=2;
        }
        else{
            transform(p[id],(trans){0,lastx-4-get_minx(p[id]),1},(point){0,0},p[id].id);
            luft=0;
            koji_luft=0;
        }
    }

    int start=0;
    /// case fill
    if(luft>0){
        if(tpt[6].size()>0){
            start++;
            int id=tpt[6][0];
            transform(p[id],(trans){0,lastx-2-get_minx(p[id]),0},(point){0,0},p[id].id);
            luft=0;
            lastx+=1+eps2;
            koji_luft=0;
        }
    }

    for(int i=start;i<tpt[6].size();i++){/// stavljaj 6
        int id=tpt[6][i];

        if(luft==0){
            transform(p[id],(trans){dtr*180,0,0},(point){0,0},p[id].id);
            transform(p[id],(trans){0,lastx-get_minx(p[id]),-get_miny(p[id])},(point){0,0},p[id].id);
            lastx+=3+eps2;
            luft=2;
            koji_luft=2;
        }
        else{
            transform(p[id],(trans){0,lastx-2-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=1+eps2;
            luft=0;
            koji_luft=0;
        }
    }

    for(int i=0;i<tpt[7].size();i++){/// stavljaj 7
        int id=tpt[7][i];

        if(luft==0){
            transform(p[id],(trans){0,lastx-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=3+eps2;
            luft=1;
            koji_luft=2;
        }
        else{
            transform(p[id],(trans){0,lastx-1-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=2+eps2;
            luft=1;
            koji_luft=2;
        }
    }

    if(tpt[2].size()>=1){
        start=1;
        if(luft>0 && koji_luft==2){
            int id=tpt[2][0];
            transform(p[id],(trans){180*dtr,0,0},(point){0,0},p[id].id);
            transform(p[id],(trans){0,lastx-1-get_minx(p[id]),-get_miny(p[id])},(point){0,0},p[id].id);
            lastx+=2+eps2;
            luft=1;
            koji_luft=1;
        }
    }

    for(int i=0;i<tpt[5].size();i++){
        int id=tpt[5][i];

        if(luft>=1 && koji_luft==1){
            transform(p[id],(trans){0,lastx-1-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=2+eps2;
            luft=1;
            koji_luft=1;
        }
        else{
            transform(p[id],(trans){0,lastx-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=3+eps2;
            luft=1;
            koji_luft=1;
        }
    }

    for(int i=start;i<tpt[2].size();i++){
        int id=tpt[2][i];

        if(luft==0){
            transform(p[id],(trans){0,lastx-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=3+eps2;
            luft=1;
            koji_luft=2;
        }
        else if(luft>=1 && koji_luft==1){
            transform(p[id],(trans){0,lastx-1-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=2+eps2;
            luft=1;
            koji_luft=2;
        }
        else{
            transform(p[id],(trans){180*dtr,0,0},(point){0,0},p[id].id);
            transform(p[id],(trans){0,lastx-1-get_minx(p[id]),-get_miny(p[id])},(point){0,0},p[id].id);
            lastx+=2+eps2;
            luft=1;
            koji_luft=1;
        }
    }

    for(int i=0;i<tpt[4].size();i++){
        int id=tpt[4][i];

        if(i%2){
            transform(p[id],(trans){dtr*180,0,0},(point){0,0},p[id].id);
            transform(p[id],(trans){0,lastx-2-get_minx(p[id]),-get_miny(p[id])},(point){0,0},p[id].id);
            lastx+=1+eps2;
            luft=0;
            koji_luft=0;
        }
        else{
            transform(p[id],(trans){0,lastx-get_minx(p[id]),0},(point){0,0},p[id].id);
            lastx+=3+eps2;
            luft=2;
            koji_luft=1;
        }
    }
}
void output(){

    for(int i=1;i<=n;i++){
        int id=p[i].id;

        transform(pocp[id],(trans){rez[id].angle,0,0},(point){0,0},0);
        rez[id].dx=get_minx(p[i])-get_minx(pocp[id]);
        rez[id].dy=get_miny(p[i])-get_miny(pocp[id]);
    }

   for(int i=1;i<=n;i++){
    if(trez[i]==0)printf("0\n");
    else{

        cout<<1<<" "<<rez[i].angle*rt_const<<" "<<rez[i].dx<<" "<<rez[i].dy<<endl;
    }
   }

}
void fopens(){

   freopen("packing.in","r",stdin);
   freopen("packing.out","w",stdout);

}
int main(){

    start_time=clock();

    fopens();
    read_input();
    if(e)try_merging();
    else tetromino();
    output();

return 0;
}
/// tetromino
/// 1 - kvadrat
/// 2 - kita
/// 3 - stapic
/// 4,6 - kuka
/// 5,7 - Z
