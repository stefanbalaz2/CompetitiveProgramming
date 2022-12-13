#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define ll long long
typedef pair<int,int> pii;

struct pt{
    int x,y;
    pt(int x,int y){
        this->x=x;
        this->y=y;
    }
    ll cross(pt a){
        return (ll)x*a.y-(ll)y*a.x;
    }
    pt operator -(pt &a){
        return pt(x-a.x,y-a.y);
    }
    pt operator +(pt &a){
        return pt(x+a.x,y+a.y);
    }
};
int get_mp(vector<pt>&a){

    int id=0;
    for(int i=1;i<a.size();i++){
        if(a[i].x<a[id].x)id=i;
        else if(a[i].x==a[id].x && a[i].y<a[id].y)id=i;
    }
    return id;
}
vector<pt> minkowski(vector<pt>a,vector<pt>b){

    int id=get_mp(a);
    rotate(a.begin(),a.begin()+id,a.end());
    id=get_mp(b);
    rotate(b.begin(),b.begin()+id,b.end());

    a.pb(a[0]);
    a.pb(a[1]);
    b.pb(b[0]);
    b.pb(b[1]);

    int pt1=0;
    int pt2=0;
    vector<pt>ret;
    while( !( pt1==a.size()-2 && pt2==b.size()-2 ) ){
        ret.pb(a[pt1]+b[pt2]);
        ll cs=(a[pt1+1]-a[pt1]).cross(b[pt2+1]-b[pt2]);
        if(cs>=0)pt1++;
        if(cs<=0)pt2++;
    }
    return ret;
}

int main() {

    ///freopen("test.txt","r",stdin);




    return 0;
}
