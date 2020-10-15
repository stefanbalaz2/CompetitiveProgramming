/*

    idea:    https://codeforces.com/blog/entry/66878

*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e5+10;
int qq,n,eq[maxn],p[maxn],color[maxn];
vector<pii>qv[10],diff[maxn];
vector<int>vect;
string ask(){

    string s;

    if(qv[qq+1].size()==0)return s;

    printf("Q ");
    printf("%d ",qv[++qq].size());
    for(int i=0;i<qv[qq].size();i++)printf("%d %d ",qv[qq][i].ff,qv[qq][i].ss);
    printf("\n");
    fflush(stdout);

    cin>>s;

    return s;
}
void conseq(){

    for(int i=2;i<=n;i+=2)qv[1].pb({i-1,i});
    string s=ask();
    for(int i=1;i<=s.size();i++)eq[i*2-1]=s[i-1]-'0';

    for(int i=3;i<=n;i+=2)qv[2].pb({i-1,i});
    s=ask();
    for(int i=1;i<=s.size();i++)eq[i*2]=s[i-1]-'0';


    p[1]=1;
    vect.clear();
    vect.pb(1);
    for(int i=1;i<n;i++){
        if(eq[i])p[i+1]=p[i];
        else{
            vect.pb(i+1);
            p[i+1]=i+1;
        }
    }

}
void blocks(){

    memset(color,-1,sizeof(color));
    for(int i=0;i<min((int)vect.size(),2);i++){
        color[vect[i]]=i;
    }

    if(vect.size()<3)return;

    /// parni
    for(int i=2;i<vect.size();i+=4){

        qv[3].pb({vect[i],vect[i-2]});
        if(i+1<vect.size())qv[3].pb({vect[i+1],vect[i-1]});

        qv[4].pb({vect[i],vect[i-1]});
        if(i+1<vect.size())qv[4].pb({vect[i+1],vect[i-2]});
    }

    string s=ask();
    for(int i=0;i<s.size();i++)
        diff[qv[3][i].ff].pb({qv[3][i].ss,s[i]-'0'});


    s=ask();
    for(int i=0;i<s.size();i++)
        diff[qv[4][i].ff].pb({qv[4][i].ss,s[i]-'0'});


    /// neparni
    for(int i=4;i<vect.size();i+=4){

        qv[5].pb({vect[i],vect[i-2]});
        if(i+1<vect.size())qv[5].pb({vect[i+1],vect[i-1]});

        qv[6].pb({vect[i],vect[i-1]});
        if(i+1<vect.size())qv[6].pb({vect[i+1],vect[i-2]});
    }

    s=ask();
    for(int i=0;i<s.size();i++)
        diff[qv[5][i].ff].pb({qv[5][i].ss,s[i]-'0'});

    s=ask();
    for(int i=0;i<s.size();i++)
        diff[qv[6][i].ff].pb({qv[6][i].ss,s[i]-'0'});

}
void answer(){

    vector<int>ret[3];
    for(int i=1;i<=n;i++)
        ret[color[p[i]]].pb(i);


    printf("A %d %d %d\n",ret[0].size(),ret[1].size(),ret[2].size());
    for(int i=0;i<3;i++){
        for(int j=0;j<ret[i].size();j++)printf("%d ",ret[i][j]);
        printf("\n");
    }

    fflush(stdout);
}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("moj.txt","w",stdout);

    int t;
    scanf("%d",&t);

    while(t--){

        qq=0;
        for(int i=1;i<=7;i++)qv[i].clear();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)diff[i].clear();

        conseq();
        blocks();

        for(int i=2;i<vect.size();i++){
            int id=vect[i];

            if(diff[id][0].ss==1)color[id]=color[diff[id][0].ff];
            else if(diff[id][1].ss==1)color[id]=color[diff[id][1].ff];
            else {
                if(0!=color[diff[id][0].ff] && 0!=color[diff[id][1].ff])color[id]=0;
                else if(1!=color[diff[id][0].ff] && 1!=color[diff[id][1].ff])color[id]=1;
                else color[id]=2;
            }
        }

        answer();

    }

    return 0;
}
