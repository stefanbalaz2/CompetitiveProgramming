/*


    idea: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/ZOJ/ZOJ_2318.txt

*/
#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define ll long long
#define pb push_back
typedef pair<int,int> pii;

const int maxn=310;
int pos[maxn],n,e;
double a[maxn];

bool eq(double a,double b){
    if(abs(a-b)<1e-7)return true;
    return false;
}

struct circle{
    double x,y,r;
}c[maxn],s;

vector<int>vect[maxn];

double sq_dist(circle a,circle b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

bool intersect(circle a,circle b){
    if(sq_dist(a,b)<(a.r+b.r)*(a.r+b.r))return true;
    return false;
}

double sgn(double x){
    if(x>0)return 1;
    if(x==0)return 0;
    if(x<0)return -1;
}

double getCos(int a,int b){

    circle p1=c[a];
    circle p2=c[b];

    p1.x-=s.x;
    p2.x-=s.x;
    p1.y-=s.y;
    p2.y-=s.y;

    double up=p1.x*p2.x+p1.y*p2.y;
    double down=sqrt(sq_dist(c[a],s))*sqrt(sq_dist(c[b],s));

    return up/down;
}

double getCross(int a,int b){

    circle p1=c[a];
    circle p2=c[b];

    p1.x-=s.x;
    p2.x-=s.x;
    p1.y-=s.y;
    p2.y-=s.y;

    return p1.x*p2.y-p1.y*p2.x;

}

double getAngle(int a,int b){
    return acos(getCos(a,b))*sgn(getCross(a,b));
}

void dfs(int x,double angle){

    pos[x]=1;
    a[x]=angle;

    cout<<x<<" "<<angle<<endl;

    for(int i=0;i<vect[x].size();i++){

        int id=vect[x][i];

        if(pos[id]){
            double na=angle+getAngle(x,id);
            if(!eq(a[id],na))e=1;
        }
        else{
            dfs(id,angle+getAngle(x,id));
        }

    }

}

int main(){


    int t;
    scanf("%d",&t);
    while(t--){

        scanf("%d",&n);

        e=0;
        for(int i=1;i<=n;i++){
            vect[i].clear();
            cin>>c[i].x>>c[i].y>>c[i].r;
        }

        cin>>s.x>>s.y>>s.r;

        for(int i=1;i<=n;i++)
            c[i].r+=s.r;


        for(int i=1;i<=n;i++)
            for(int j=1;j<i;j++)
                if(intersect(c[i],c[j]))vect[i].pb(j),vect[j].pb(i);

        memset(pos,0,sizeof(pos));
        for(int i=1;i<=n;i++){
            if(pos[i])continue;
            dfs(i,0);
        }

        if(e)printf("NO\n\n");
        else printf("YES\n\n");

    }

    return 0;
}
