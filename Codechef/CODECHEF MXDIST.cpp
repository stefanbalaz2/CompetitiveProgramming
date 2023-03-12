/*

    idea:https://discuss.codechef.com/t/mxdist-editorial/21635

*/
#include <bits/stdc++.h>
#define ll long long
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<ll,ll> pii;
mt19937 gen(time(NULL));
ll inf=1e18;
double eps=0.000000001;
double pi=3.1415926;

const int maxn=2e5+10;
const int bsize=300;
int n,br,blp[maxn/bsize+10],brp[maxn/bsize+10],bid[maxn];

bool eq(double a,double b){
    if(abs(a-b)<=eps)return 1;
    return 0;
}

int sgn(ll x){
    if(x==0)return 0;
    if(x>0)return 1;
    if (x<0)return -1;
}

struct point{


    ll x,y;

    point(){}

    point(ll x,ll y){
        this->x=x;
        this->y=y;
    }

    ll cross_product(point c,point b){

        b=b-c;
        point a=(*this);
        a=a-c;

        return a.x*b.y-a.y*b.x;
    }

    ll dot_product(point c,point b){

        b=b-c;
        point a=(*this);
        a=a-c;

        return a.x*b.x+a.y*b.y;

    }

    point operator - (point b){
        return {x-b.x,y-b.y};
    }

    static bool srt(point a,point b){
        return (a.x<b.x)||(a.x==b.x && a.y<b.y);
    }

    ll sq_dist(point b){
        return (this->x-b.x)*(this->x-b.x)+(this->y-b.y)*(this->y-b.y);
    }

    double angle(point b){

        double up=(this->x*b.x+this->y*b.y);
        double down=sqrt((double) this->sq_dist({0,0}) )*sqrt((double) b.sq_dist({0,0}) );

       /// cout<<up<<" "<<down<<" "<<this->x<<" "<<this->y<<" "<<b.x<<" "<<b.y<<"  ANGLE"<<endl;

        ///return acos(up/down)*360.0/2.0/pi;
        return -up/down;
    }

    void invert(){
        x=-x;
        y=-y;
    }

    bool equals(point a){
        if(a.x==this->x && a.y==this->y)return 1;
        return 0;
    }

    bool operator < (const point &a) const{
        return srt(*this,a);
    }

};

point p[maxn];

struct polygon{

    vector<point>points;/// CLOCKWISE !!!!!!!!!!!!!!

    polygon(){}

    polygon(vector<point> &vect){
        this->points=construct_polygon(vect).getPoints();
    }

    vector<point> getPoints(){
        return points;
    }

    void addPoint(point a){

        if(points.size()<=1){
            points.pb(a);
        }
        else{
            while( (points.size()>1 && points.back().equals(a)) || (points.size()>1 &&  points.back().cross_product( points[points.size()-2],a )>=0 ) )
                points.pop_back();

            points.pb(a);
        }

    }

    polygon construct_polygon(vector<point> vect){/// clockwise

        set<point>st;
        for(int i=0;i<vect.size();i++)st.insert(vect[i]);
        vect.clear();
        for(set<point>::iterator it=st.begin();it!=st.end();it++)vect.pb(*it);

        sort(vect.begin(),vect.end(),point::srt);

        polygon ret=*new polygon();
        vector<point>pom;

        for(int i=0;i<vect.size();i++){

            ///cout<<vect[i].x<<" "<<vect[i].y<<" "<<i<<endl;

            while( (pom.size()>1 && pom.back().equals(vect[i])) || (pom.size()>1 && pom.back().cross_product(pom[pom.size()-2],vect[i])>=0) )
                pom.pop_back();

            pom.pb(vect[i]);
        }
        pom.pop_back();

        vector<point>pom2;
        for(int i=vect.size()-1;i>=0;i--){

            while( (pom2.size()>1 && pom2.back().equals(vect[i])) || (pom2.size()>1 &&  pom2.back().cross_product(pom2[pom2.size()-2],vect[i])>=0) )
                pom2.pop_back();

            pom2.pb(vect[i]);
        }
        pom2.pop_back();

        for(int i=0;i<pom2.size();i++){
            pom.pb(pom2[i]);
        }

        if(vect.size()==1)pom.pb(vect[0]);
        ret.points=pom;

        return ret;

    }

    ll max_distance(){

        if(points.size()==1)return 0;

        int id1=-1,id2=-1;
        point maxx1={-inf,-inf};///max Y, max X
        point minn2={inf,inf};///min Y, min X

        for(int i=0;i<points.size();i++){

            ll xx=points[i].x;
            ll yy=points[i].y;

            if(yy>maxx1.y)maxx1={xx,yy},id1=i;
            else if(yy==maxx1.y && xx>maxx1.x)maxx1={xx,yy},id1=i;

            if(yy<minn2.y)minn2={xx,yy},id2=i;
            else if(yy==minn2.y && xx<minn2.x)minn2={xx,yy},id2=i;
        }


        ll ret=0;
        ret=max(ret,maxx1.sq_dist(minn2));

        point dir={1,0};/// drugi direction je -dir
        int p1=id1;
        int p2=id2;
        int cnt1=0;
        int cnt2=0;


        while(1){

            if(cnt1==points.size() && cnt2==points.size())break;

            int nxt1=(p1+1)%points.size();
            int nxt2=(p2+1)%points.size();

            double angle1=dir.angle(points[nxt1]-points[p1]);
            point dir2=dir;
            dir2.invert();
            double angle2=dir2.angle(points[nxt2]-points[p2]);

            ///printf("%d %d %d ADSAF\n",cnt1,cnt2,points.size());
            ///cout<<angle1<<" "<<angle2<<" "<<p1<<" "<<p2<<" "<<nxt1<<" "<<nxt2<</*" "<<dir.x<<" "<<dir.y<<" "<<dir2.x<<" "<<dir2.y<<*/endl;

            if(eq(angle1,angle2)){
                ret=max(ret,points[p1].sq_dist( points[nxt2] ));
                ret=max(ret,points[p2].sq_dist( points[nxt1] ));
                ret=max(ret,points[nxt1].sq_dist( points[nxt2] ));

                dir=points[nxt1]-points[p1];

                p1=nxt1;
                p2=nxt2;

                cnt1++;
                cnt2++;
            }
            else{

                if(angle1<angle2){/// gornji pomeras

                    ret=max(ret,points[nxt1].sq_dist(points[p2]) );

                    dir=points[nxt1]-points[p1];

                    p1=nxt1;
                    cnt1++;
                }
                else{

                    ret=max(ret,points[nxt2].sq_dist(points[p1]) );

                    dir=points[nxt2]-points[p2];
                    dir.invert();

                    p2=nxt2;
                    cnt2++;
                }

            }

        }

        return ret;
    }

    point getPoint(int id){
        id%=points.size();
        if(id<0)id+=points.size();
        return points[id];
    }

    static vector<point> filter_points(vector<point> vect,point dir){

        ll maxx=-inf;
        for(int i=0;i<vect.size();i++)
            maxx=max(maxx,dir.cross_product({0,0},vect[i]));


        vector<point>vect2;
        for(int i=0;i<vect.size();i++)
            if(dir.cross_product({0,0},vect[i])!=maxx){}
            else vect2.pb(vect[i]);

        vector<pii>pom;
        for(int i=0;i<vect2.size();i++){
            pom.pb({dir.dot_product({0,0},vect2[i]),i});
        }
        sort(pom.begin(),pom.end());

        vector<point>ret;
        for(int i=0;i<pom.size();i++){
            ret.pb(vect2[pom[i].ss]);
        }

        while(ret.size()>1)ret.pop_back();

        return ret;
    }

    static polygon merge_polygons(polygon &a,polygon &b){

        if(a.points.size()<=2 || b.points.size()<=2){

            vector<point> vect;
            for(int i=0;i<a.points.size();i++)vect.pb(a.points[i]);
            for(int i=0;i<b.points.size();i++)vect.pb(b.points[i]);

            return *new polygon(vect);
        }

        int id1=-1,id2=-1;
        point maxx1={-inf,-inf};///max Y, max X
        point maxx2={-inf,-inf};///min Y, min X

        for(int i=0;i<a.points.size();i++){

            ll xx=a.points[i].x;
            ll yy=a.points[i].y;

            if(yy>maxx1.y)maxx1={xx,yy},id1=i;
            else if(yy==maxx1.y && xx>maxx1.x)maxx1={xx,yy},id1=i;
        }

        for(int i=0;i<b.points.size();i++){
            ll xx=b.points[i].x;
            ll yy=b.points[i].y;

            if(yy>maxx2.y)maxx2={xx,yy},id2=i;
            else if(yy==maxx2.y && xx>maxx2.x)maxx2={xx,yy},id2=i;
        }

        polygon ret;


        point dir={1,0};
        int p1=id1;
        int p2=id2;
        int cnt1=0;
        int cnt2=0;

        vector<point>vect2;
        vect2.pb(a.points[id1]);
        vect2.pb(b.points[id2]);
        vect2=filter_points(vect2,dir);
        for(int i=0;i<vect2.size();i++){

            ///printf("%lld %lld 111\n",vect[i].x,vect[i].y);
            ret.addPoint(vect2[i]);
        }
        while(1){


            ///printf("%d %d %d %d ADSAF\n",cnt1,cnt2,a.points.size(),b.points.size());
            if(cnt1==a.points.size() && cnt2==b.points.size())break;

            int nxt1=(p1+1)%a.points.size();
            int nxt2=(p2+1)%b.points.size();

            double angle1=dir.angle(a.points[nxt1]-a.points[p1]);
            double angle2=dir.angle(b.points[nxt2]-b.points[p2]);


            ///cout<<angle1<<" "<<angle2<<" "<<p1<<" "<<p2<<" "<<dir.x<<" "<<dir.y<<endl;

            if(eq(angle1,angle2)){


                dir=a.points[nxt1]-a.points[p1];

                vector<point>vect;
                vect.pb(a.points[p1]);
                vect.pb(b.points[p2]);

                /*for(int i=0;i<vect.size();i++)
                printf("%lld %lld 111\n",vect[i].x,vect[i].y);*/

                vect=filter_points(vect,dir);
                for(int i=0;i<vect.size();i++){

                    ///printf("%lld %lld 111\n",vect[i].x,vect[i].y);
                    ret.addPoint(vect[i]);
                }

                vect.clear();
                vect.pb(a.points[nxt1]);
                vect.pb(b.points[nxt2]);

                /*for(int i=0;i<vect.size();i++)
                printf("%lld %lld 111\n",vect[i].x,vect[i].y);*/

                vect=filter_points(vect,dir);
                for(int i=0;i<vect.size();i++){

                    ///printf("%lld %lld 111\n",vect[i].x,vect[i].y);
                    ret.addPoint(vect[i]);
                }


                p1=nxt1;
                p2=nxt2;

                cnt1++;
                cnt2++;
            }
            else{

                if(angle1<angle2){

                    dir=a.points[nxt1]-a.points[p1];

                    vector<point>vect;
                    vect.pb(b.points[p2]);
                    vect.pb(a.points[p1]);
                    /*for(int i=0;i<vect.size();i++)
                        printf("%lld %lld 111\n",vect[i].x,vect[i].y);*/
                    vect=filter_points(vect,dir);
                    for(int i=0;i<vect.size();i++){
                        ///printf("%lld %lld 222\n",vect[i].x,vect[i].y);
                        ret.addPoint(vect[i]);
                    }

                    vect.clear();
                    vect.pb(b.points[p2]);
                    vect.pb(a.points[nxt1]);
                    /*for(int i=0;i<vect.size();i++)
                        printf("%lld %lld 111\n",vect[i].x,vect[i].y);*/
                    vect=filter_points(vect,dir);
                    for(int i=0;i<vect.size();i++){
                        ///printf("%lld %lld 222\n",vect[i].x,vect[i].y);
                        ret.addPoint(vect[i]);
                    }



                    p1=nxt1;

                    cnt1++;

                }
                else{

                    dir=b.points[nxt2]-b.points[p2];

                    vector<point>vect;
                    vect.pb(b.points[p2]);
                    vect.pb(a.points[p1]);
                    /*for(int i=0;i<vect.size();i++)
                        printf("%lld %lld 111\n",vect[i].x,vect[i].y);*/
                    vect=filter_points(vect,dir);
                    for(int i=0;i<vect.size();i++){
                       /// printf("%lld %lld 333\n",vect[i].x,vect[i].y);
                        ret.addPoint(vect[i]);
                    }

                    vect.clear();
                    vect.pb(b.points[nxt2]);
                    vect.pb(a.points[p1]);
                    /*for(int i=0;i<vect.size();i++)
                        printf("%lld %lld 111\n",vect[i].x,vect[i].y);*/
                    vect=filter_points(vect,dir);
                    for(int i=0;i<vect.size();i++){
                       /// printf("%lld %lld 333\n",vect[i].x,vect[i].y);
                        ret.addPoint(vect[i]);
                    }


                    p2=nxt2;

                    cnt2++;

                }

            }

        }

        ret.addPoint(ret.points[0]);
        if(ret.points.size()>1)ret.points.pop_back();

        if(ret.points.size()>=2 && ret.points[0].cross_product(ret.points.back(),ret.points[1])==0 )ret.points.erase(ret.points.begin());

        return ret;

    }

    static polygon generate_pointset(int n,int maxn){

        vector<point>pom;

        for(int i=0;i<n;i++){
            pom.pb({gen()%maxn,gen()%maxn});
        }

        return *new polygon(pom);
    }

    bool equals(polygon b){

        vector<point>vect1=this->points;
        vector<point>vect2=b.points;

        sort(vect1.begin(),vect1.end(),point::srt);
        sort(vect2.begin(),vect2.end(),point::srt);

        if(points.size()!=b.points.size())return false;

        for(int i=0;i<b.points.size();i++){

            if(!vect1[i].equals(vect2[i]))return false;
        }

        return true;
    }

    void ispis(){

        printf("ISPIS POLIGONA\n");
        for(int i=0;i<points.size();i++)printf("(%lld,%lld)\n",points[i].x,points[i].y);
        printf("\n");

    }

    ll ac(){

        ll ret=0;

        for(int i=0;i<points.size();i++)
        for(int j=0;j<i;j++){
            ret=max(ret,points[i].sq_dist(points[j]));
        }

        return ret;
    }

}dp[20][maxn/bsize+10];

void make_blocks(){

    int l=1;
    int r=min(bsize,n);
    while(1){

        blp[++br]=l;
        brp[br]=r;

        l+=bsize;
        r+=bsize;

        if(l>n)break;
        if(r>n)r=n;
    }

    for(int i=1;i<=br;i++){

        vector<point>vect;
        for(int j=blp[i];j<=brp[i];j++){
            vect.pb(p[j]);
            bid[j]=i;
        }

        dp[0][i]=*new polygon(vect);
    }

    int h=log2(br);
    for(int i=1;i<=h;i++)
        for(int j=1;j<=br;j++)
        dp[i][j]=polygon::merge_polygons(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);

}

polygon query(int l,int r){

    polygon ret;
    ret.points.clear();

    if(l>r)return ret;

    int h=log2(r-l+1);

    return polygon::merge_polygons(dp[h][l],dp[h][r-(1<<h)+1]);
}

ll bq(int l,int r){

    int lid=bid[l];
    int rid=bid[r];

    polygon p1=query(lid+1,rid-1);

    vector<point>vect;
    for(int i=l;i<=min(brp[lid],r);i++)vect.pb(p[i]);
    for(int i=max(l,blp[rid]);i<=r;i++)vect.pb(p[i]);
    polygon p2=*new polygon(vect);

    return (polygon::merge_polygons(p1,p2)).max_distance();
}

int main(){

    ///freopen("test.txt","r",stdin);


    scanf("%d",&n);

    for(int i=1;i<=n;i++){
        scanf("%d %d",&p[i].x,&p[i].y);
    }



    make_blocks();

    int q;
    scanf("%d",&q);
    while(q--){

        int l,r;
        scanf("%d %d",&l,&r);

        printf("%lld\n",bq(l,r));

    }



    /*vector<point>vect;
    vect.pb({1,1});
    vect.pb({2,1});
    vect.pb({1,0});
    vect.pb({3,0});
    vect.pb({2,3});
    vect.pb({2,3});
    vect.pb({3,3});
    vect.pb({4,2});

    polygon p=*new polygon(vect);

    vect.clear();
    vect.pb({-4,5});
    vect.pb({-5,5});
    vect.pb({-5,4});
    vect.pb({-4,3});

    polygon p2=*new polygon(vect);

    polygon p3=polygon::merge_polygons(p,p2);

    for(int i=0;i<p3.points.size();i++)printf("%lld %lld\n",p3.points[i].x,p3.points[i].y);*/
    ///printf("%lld\n",p3.max_distance());

    /*
    int maxn=10;
    for(int i=1;i<=1000000;i++){

        int n1=gen()%maxn;
        if(n1<0)n1+=maxn;
        n1++;

        int n2=gen()%maxn;
        if(n2<0)n2+=maxn;
        n2++;

        polygon p1=polygon::generate_pointset(n1,maxn);
        polygon p2=polygon::generate_pointset(n2,maxn);
        polygon p3=polygon::merge_polygons(p1,p2);

        p1.ispis();
        p2.ispis();
        ///p3.ispis();

        vector<point>pom;
        for(int i=0;i<p1.points.size();i++)pom.pb(p1.points[i]);
        for(int i=0;i<p2.points.size();i++)pom.pb(p2.points[i]);
        polygon pd3=*new polygon(pom);

        ///pd3.ispis();

        if(!p3.equals(pd3)){printf("NE RADI %d\n",i);return 0;}
        else printf("RADI %d\n",i);

        if(pd3.max_distance()!=pd3.ac()){printf("NE RADI MAX %d\n",i);return 0;}
        else printf("RADI %d\n",i);
    }*/

/*
    int n1;
    scanf("%d",&n1);
    vector<point>pom;
    for(int i=1;i<=n1;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        pom.pb({x,y});
    }
    polygon p1=*new polygon(pom);

    int n2;
    scanf("%d",&n2);
    vector<point>pom2;
    for(int i=1;i<=n2;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        pom2.pb({x,y});
    }
    polygon p2=*new polygon(pom2);

    polygon p3=polygon::merge_polygons(p1,p2);

    pom.clear();
    for(int i=0;i<p1.points.size();i++)pom.pb(p1.points[i]);
    for(int i=0;i<p2.points.size();i++)pom.pb(p2.points[i]);
    polygon pd3=*new polygon(pom);

    pd3.ispis();

    if(!p3.equals(pd3)){printf("NE RADI \n");}
    else printf("RADI \n");

    p3.ispis();
    p3.max_distance();
*/

    return 0;
}
