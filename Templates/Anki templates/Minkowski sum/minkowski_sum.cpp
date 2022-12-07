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

    pt operator +(pt &a){
        return pt(x+a.x,y+a.y);
    }
    pt operator -(pt &a){
        return pt(x-a.x,y-a.y);
    }
    ll cross(pt &a){
        return x*a.y-y*a.x;
    }

};

int get_pt(vector<pt>&a){

    int ret=0;
    for(int i=1;i<a.size();i++)
        if( a[i].y<a[ret].y || (a[i].y==a[ret].y && a[i].x<a[ret].x) )ret=i;
    return ret;
}

vector<pt> minkowski(vector<pt>a,vector<pt>b){

    int posa=0,posb=0;
    posa=get_pt(a);
    posb=get_pt(b);
    rotate(a.begin(),a.begin()+posa,a.end());
    rotate(b.begin(),b.begin()+posb,b.end());

    a.pb(a[0]);
    a.pb(a[1]);
    b.pb(b[0]);
    b.pb(b[1]);

    int pa=0;
    int pb=0;
    while( !(pa==a.size()-2 && pb==b.size()-2) ){

        ret.pb(a[pa]+b[pb]);
        int p2=(b[pb+1]-b[pb]).cross(a[pa+1]-a[pa]);
        if( (a[pa+1]-a[pa]).cross(b[pb+1]-b[pb])>=0)pa++;
        if( p2>=0)pb++;
    }

    return ret;
}

int main() {

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);



    return 0;
}
