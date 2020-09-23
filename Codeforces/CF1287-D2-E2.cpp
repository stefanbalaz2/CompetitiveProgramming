/*

    idea: we can solve a n/2 prefix with 2 queries({1,n/2},{2,n/2})

        solve the rest by querying {1,n}
        and solving each i from n to n/2

        lets solve for i=n
        to solve it we can make use of the 2 substring of size n-1
        take their difference and its trivial what the nth character is
        then remove all the n/2 strings which are of type {i,n} i<=n/2(this can be done by going from the biggest string,deleting it, and moving on to the next
        by removing the 1st letter and deleting that string, then 2nd,3rd and so on)
        and then we are left with the same task with n-1 size string


*/
#include<bits/stdc++.h>
#define pb push_back
#define ff first
#define ss second
#define ll long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=110;
char rez[maxn];
int lim,n;
bool srt(string a,string b){
    return a.size()<b.size();
}
vector<string> query(int l,int r){

    printf("? %d %d\n",l,r);
    fflush(stdout);

    vector<string>ret;
    for(int i=l;i<=r;i++)
    for(int j=i;j<=r;j++){
        string s;
        cin>>s;
        ret.pb(s);
    }

    return ret;
}
void popuni(int a[26],string s){
    for(int i=0;i<s.size();i++)
        a[s[i]-'a']++;
}
void oduzmi(int a[26],int b[26]){
    for(int i=0;i<26;i++)a[i]-=b[i];
}
void absolut(int a[26]){
    for(int i=0;i<26;i++){
        a[i]=abs(a[i]);
    }
}
char nadji(int a[26],int x){
    for(int i=0;i<26;i++){
        if(a[i]==x)return i+'a';
    }
}
void solve1(){

    map<string,int>mapa;

    vector<string>v=query(1,lim);
    for(int i=0;i<v.size();i++){
        sort(v[i].begin(),v[i].end());
        mapa[v[i]]++;
    }

    if(lim==1){
        rez[1]=v[0][0];
        return;
    }


    v=query(2,lim);
    for(int i=0;i<v.size();i++){
        sort(v[i].begin(),v[i].end());
        mapa[v[i]]--;
    }

    v.clear();
    for(map<string,int>::iterator it=mapa.begin();it!=mapa.end();it++){
        if(it->ss==0)continue;
        v.pb(it->ff);
    }

    sort(v.begin(),v.end(),srt);

    int curr[26];
    memset(curr,0,sizeof(curr));
    for(int i=0;i<v.size();i++){

        int pom[26];
        memset(pom,0,sizeof(pom));
        popuni(pom,v[i]);
        oduzmi(pom,curr);
        rez[i+1]=nadji(pom,1);

        curr[rez[i+1]-'a']++;
    }
}
string bildaj(int a[26]){
    string ret;

    for(int i=0;i<26;i++)
        for(int j=1;j<=a[i];j++)
            ret.pb(i+'a');

    return ret;
}
void solve2(){

    map<string,int>mapa[maxn];

    vector<string>v=query(1,n);
    for(int i=0;i<v.size();i++){
        sort(v[i].begin(),v[i].end());
        mapa[v[i].size()][v[i]]++;
    }

    for(int i=n;i>lim;i--){

        int curr1[26],curr2[26];
        memset(curr1,0,sizeof(curr1));
        memset(curr2,0,sizeof(curr2));

        popuni(curr1,mapa[i-1].begin()->ff);
        popuni(curr2,mapa[i-1].rbegin()->ff);

        oduzmi(curr1,curr2);
        absolut(curr1);


        if(curr1[rez[1]-'a']==0){
            rez[i]=rez[1];
        }
        else{
            curr1[rez[1]-'a']--;
            rez[i]=nadji(curr1,1);
        }


        memset(curr1,0,sizeof(curr1));
        popuni(curr1,mapa[i].begin()->ff);
        for(int j=1;j<=lim;j++){

            string s=bildaj(curr1);
            mapa[s.size()][s]--;
            if(mapa[s.size()][s]==0)mapa[s.size()].erase(s);

            curr1[rez[j]-'a']--;
        }

    }

}
int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d",&n);

    lim=n/2+1;
    solve1();
    solve2();

    printf("! ");
    for(int i=1;i<=n;i++)printf("%c",rez[i]);
    printf("\n");
    fflush(stdout);

    return 0;
}
