#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;


int n,m;
const int maxn=210;
double dist[maxn][maxn];
double inf=1e9;

struct pt{

    int x,y;

    pt(int x,int y){
        this->x=x;
        this->y=y;
    }
    pt(){}

    pt operator -(pt b){
        return pt(x-b.x,y-b.y);
    }

    pt operator +(pt b){
        return pt(x+b.x,y+b.y);
    }

    int cross(pt b){
        return x*b.y-y*b.x;
    }

    bool operator ==(pt b){
        return (x==b.x && y==b.y);
    }

    bool operator !=(pt b){
        return !(x==b.x && y==b.y);
    }

    double dist(pt b){
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }

};

vector<pt>polpts,goalpts;

bool is_on_line(pt ppt,pt a,pt b){

    if(a.x>b.x || (a.x==b.x && a.y>b.y) )swap(a,b);

    if(a.x!=b.x){
        if(ppt.x<a.x || ppt.x>b.x)return false;
    }
    else{
        if(ppt.y<a.y || ppt.y>b.y)return false;
    }

    b=b-a;
    ppt=ppt-a;

    if(b.cross(ppt)!=0)return false;
    return true;
}
bool lines_intersect(pt a,pt b,pt p,pt q){

    b=b-a;
    p=p-a;
    q=q-a;

    int c1=b.cross(p);
    int c2=b.cross(q);

    if(c1>=0 && c2<=0)return true;
    swap(c1,c2);
    if(c1>=0 && c2<=0)return true;
    return false;
}
bool lines_intersect2(pt a,pt b,pt p,pt q){

    b=b-p;
    a=a-p;
    q=q-p;

    int c1=q.cross(b);
    int c2=q.cross(a);

    if(c1>0 || c2>0)return true;
    return false;
}
bool sece_poligon(pt a,pt b){

    for(int i=1;i<=n;i++){
        if(lines_intersect(a,b,polpts[i],polpts[i-1]) && lines_intersect(polpts[i],polpts[i-1],a,b) && a!=polpts[i] && a!=polpts[i-1] && b!=polpts[i] && b!=polpts[i-1] ){
            if(lines_intersect2(a,b,polpts[i],polpts[i-1]) )return true;
        }
    }

    for(int i=1;i<=n;i++){

        pt p=polpts[i-1];
        pt q=polpts[i];
        pt r=polpts[i+1];

        if(!is_on_line(q,a,b))continue;

        if( (r-q).cross(p-q)>0 ){

            pt pom=a;
            if((r-q).cross(pom-q)>=0){}
            else return true;
            if((pom-q).cross(p-q)>=0){}
            else return true;

            pom=b;
            if((r-q).cross(pom-q)>=0){}
            else return true;
            if((pom-q).cross(p-q)>=0){}
            else return true;
        }
        else{

            pt pom=a;
            if((p-q).cross(pom-q)>0 && (pom-q).cross(r-q)>0)return true;

            pom=b;
            if((p-q).cross(pom-q)>0 && (pom-q).cross(r-q)>0)return true;

        }

    }

    return false;
}
void get_adj(vector<pt>v){

    for(int i=0;i<v.size();i++){

        for(int j=0;j<v.size();j++){
            dist[i][j]=inf;
            if(v[i]==v[j]){dist[i][j]=0;continue;}

            if(sece_poligon(v[i],v[j]))continue;

            dist[i][j]=v[i].dist(v[j]);

        }

    }

}
void floyd(vector<pt>v){

    for(int k=0;k<v.size();k++)
        for(int i=0;i<v.size();i++)
            for(int j=0;j<v.size();j++)
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
}
pair<int,double> get_pt_val(pt a){

    for(int i=0;i<n-1;i++){
        if(is_on_line(a,polpts[i],polpts[i+1])){
            return {i,polpts[i].dist(a)};
        }
    }
    return {n-1,polpts[n-1].dist(a)};
}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&m);
    polpts.resize(n);
    goalpts.resize(m);
    vector<pt>v;
    for(int i=0;i<n;i++){
        scanf("%d %d",&polpts[i].x,&polpts[i].y);
        v.pb(polpts[i]);
    }
    polpts.pb(polpts[0]);
    polpts.pb(polpts[1]);
    vector< pair<pair<int,double>,int>>cand;
    for(int i=0;i<m;i++){
        scanf("%d %d",&goalpts[i].x,&goalpts[i].y);
        v.pb(goalpts[i]);

        pair<int,double> pom=get_pt_val(goalpts[i]);
        cand.pb({pom,i});
    }
    sort(cand.begin(),cand.end());

    //printf("%d AA\n",sece_poligon({0,4},{1,3}));
    //return 0;
    get_adj(v);
    floyd(v);

    double rez=0;
    cand.pb(cand[0]);
    for(int i=0;i<=m-1;i++){
        rez+=dist[cand[i].ss+n][cand[i+1].ss+n];
       /// printf("%d %d | %lf AA\n",cand[i].ss,cand[i+1].ss,dist[cand[i].ss+n][cand[i+1].ss+n]);
    }

    cout<<fixed<<setprecision(10)<<rez<<endl;

    return 0;
}
