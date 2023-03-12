/*

    idea:   canddiates for the radius are the distances of different colored radars/2
            when fiexed a radius, make a graph where if the 2 circles intersect, they have and edge
            when fixed a radius, we have to find size of the biggest independent subset of that graph
            its equal to no. of nodes-matching

*/
#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
using namespace std;
typedef pair<int,int>pii;

class HouseProtection{

    const static int maxn=55;
    int n,m,pos[maxn*2],mt[maxn*2];
    vector<int>vect[maxn*2];
    const double pi=3.14159265359;
    const double eps=1e-5;

    int dist(int x1,int y1,int x2,int y2){
        return abs(x1-x2)*abs(x1-x2)+abs(y1-y2)*abs(y1-y2);
    }

    int go(int x){

        pos[x]=1;

        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(pos[id])continue;
            pos[id]=1;

            if(mt[id]==-1){
                mt[id]=x;
                mt[x]=id;
                return 1;
            }
            else{
                if(pos[mt[id]])continue;

                int pom=go(mt[id]);
                if(pom){
                    mt[id]=x;
                    mt[x]=id;
                    return 1;
                }
            }
        }

        return 0;
    }

    int matching(){

        int ret=0;
        while(1){

            int e=0;
            memset(pos,0,sizeof(pos));

            for(int i=0;i<n;i++){
                if(mt[i]!=-1)continue;
                e=go(i);
                if(e){
                    ret+=e;
                    break;
                }
            }


            if(e==0)break;
        }

        return ret;
    }


    double probaj(double r,vector<int> &possibleXForBlue, vector<int> &possibleYForBlue, vector<int> &possibleXForRed, vector<int> &possibleYForRed){

        for(int i=0;i<n+m;i++)vect[i].clear();
        memset(mt,-1,sizeof(mt));

        for(int i=0;i<possibleXForBlue.size();i++){

            for(int j=0;j<possibleXForRed.size();j++){

                double pom=dist(possibleXForBlue[i],possibleYForBlue[i],possibleXForRed[j],possibleYForRed[j])/4.0;
                if(pom<r){
                    vect[i].pb(j+n);
                    vect[j+n].pb(i);

				}

            }

        }

        int pom=matching();

        return ((double)n+m-pom)*r*pi;

    }

    public: double safetyFactor(vector<int> possibleXForBlue, vector<int> possibleYForBlue, vector<int> possibleXForRed, vector<int> possibleYForRed, int R){

        n=possibleXForBlue.size();
        m=possibleXForRed.size();

        double ret=0;
        for(int i=0;i<possibleXForBlue.size();i++){

            for(int j=0;j<possibleXForRed.size();j++){

                double pom=dist(possibleXForBlue[i],possibleYForBlue[i],possibleXForRed[j],possibleYForRed[j])/4.0;

                if(pom>(double)R*R)continue;

                ret=max(ret,probaj(pom,possibleXForBlue,possibleYForBlue,possibleXForRed,possibleYForRed));

            }

        }

        ret=max(ret,probaj(R*R,possibleXForBlue,possibleYForBlue,possibleXForRed,possibleYForRed));

        return ret;
    }

};

