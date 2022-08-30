/**



*/
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
#define ull unsigned long long
typedef pair<int,int> pii;

struct pt{

    ll x,y;

    pt(ll x,ll y){
        this->x=x;
        this->y=y;
    }

    pt operator + (const pt &a)const{
        return pt(a.x+this->x,a.y+this->y);
    }
    pt operator - (const pt &a)const{
        return pt(-a.x+this->x,-a.y+this->y);
    }

    ll cross(const pt &a){
        return this->x*a.y-this->y*a.x;
    }

};

int get_min_pos(vector<pt>&a){

    int ret=0;
    for(int i=1;i<a.size();i++){
        if( a[i].y<a[ret].y || ( a[i].y==a[ret].y && a[i].x<a[ret].x ) )
            ret=i;
    }

    return ret;
}

vector<pt>minkowski_sum(vector<pt>a,vector<pt>b){

    int posa=get_min_pos(a);
    int posb=get_min_pos(b);
    rotate(a.begin(),a.begin()+posa,a.end());
    rotate(b.begin(),b.begin()+posa,b.end());

    a.pb(a[0]);
    b.pb(b[0]);
    a.pb(a[1]);
    b.pb(b[1]);

    int pta=0;
    int ptb=0;

    while( !(pta==a.size()-2 && ptb=b.size()-2) ){

        ret.pb(a[pta]+b[pta]);

        if( (a[pta+1]-a[pta]).cross(b[ptb+1]-b[ptb])>=0 )pta++;
        if( (b[ptb+1]-a[ptb]).cross(a[pta+1]-b[pta])>=0 )ptb++;

    }

    return ret;
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);



    return 0;
}
