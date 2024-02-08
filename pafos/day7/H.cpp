#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
typedef long long ll;
using namespace std;
using u128=__uint128_t;
typedef pair<int,int> pii;

const int mod=998244353;
inline int add(int x,int y){int ret=x+y;if(ret>=mod)ret-=mod;return ret;}
inline int sub(int x,int y){int ret=x-y;if(ret<0)ret+=mod;return ret;}
inline int mul(int x,int y){return ((ll)x*y)%mod;}
inline int step(int base,int pw){int ret=1;while(pw){if(pw&1)ret=mul(ret,base);base=mul(base,base);pw>>=1;}return ret;}
inline int invv(int x){return step(x,mod-2);}

int n,q;

struct trans{

    char a[8][16];

    trans(){
        for(int i=0;i<16;i++)
            for(int j=0;j<8;j++)a[j][i]=i;
    }



    trans operator *(trans b){
        trans ret=(*this);
        for(int j=0;j<8;j++)
            for(int i=0;i<16;i++){
                ret.a[j][i]=b.a[j][a[j][i]];
            }
        return ret;
    }

    void ispis(){

        for(int i=0;i<8;i++){
            for(int j=0;j<16;j++)printf("%d ",a[i][j]);
            printf("\n");
        }
        printf("ISPIS\n");
    }

};
struct state{

    char a[8];

    state operator *(trans b){

       // printf("OP\n");
        //b.ispis();

        state ret=(*this);
        for(int i=0;i<8;i++)
            ret.a[i]=b.a[i][ret.a[i]];
        return ret;
    }

};
const int maxn=2e4;
struct node{
    int rep;
    vector<trans> vt;
    ll sz,dsz;
}nd[maxn];

int get_integer(string s){

    int cp10=1;
    int ret=0;
    while(s.back()!=' '){
        ret+=cp10*(s.back()-'0');
        cp10*=10;
        s.pop_back();
    }
    return ret;
}
bool bgw(string &s,string p){

    if(p.size()>s.size())return false;
    for(int i=0;i<p.size();i++){
        if(p[i]!=s[i])return false;
    }
    return true;
}
int get_register(string s){
    char c=s[s.size()-2];
    return c-'a';
}
trans get_trans(string s){

    trans ret;

    if(bgw(s,"ori")){
        int imm=get_integer(s);
        while(s.back()!=' ')s.pop_back();
        s.pop_back();
        int reg=get_register(s);

        for(int i=0;i<8;i++){
            char c=((imm&(1<<i))>0);
            for(int j=0;j<16;j++){
                ret.a[i][j]|=(c<<reg);
            }
        }

    }
    else if(bgw(s,"andi")){
        int imm=get_integer(s);
        while(s.back()!=' ')s.pop_back();
        s.pop_back();
        int reg=get_register(s);

        for(int i=0;i<8;i++){
            char c=((imm&(1<<i))>0);
            char c2=15-(1<<reg)+(c<<reg);
            for(int j=0;j<16;j++){
                ret.a[i][j]&=c2;
            }
        }
    }
    else if(bgw(s,"xori")){
        int imm=get_integer(s);
        while(s.back()!=' ')s.pop_back();
        s.pop_back();
        int reg=get_register(s);

        for(int i=0;i<8;i++){
            char c=((imm&(1<<i))>0);
            for(int j=0;j<16;j++){
                ret.a[i][j]^=(c<<reg);
            }
        }
    }
    else if(bgw(s,"or")){
        int reg2=get_register(s);
        while(s.back()!=' ')s.pop_back();
        s.pop_back();
        int reg=get_register(s);

        for(int i=0;i<8;i++){
            for(int j=0;j<16;j++){
                char c=((j&(1<<reg2))>0);
                ret.a[i][j]|=(c<<reg);
            }
        }
    }
    else if(bgw(s,"and")){
        int reg2=get_register(s);
        while(s.back()!=' ')s.pop_back();
        s.pop_back();
        int reg=get_register(s);

        for(int i=0;i<8;i++){
            for(int j=0;j<16;j++){

                char c=((j&(1<<reg2))>0);
                char c2=15-(1<<reg)+(c<<reg);

                ret.a[i][j]&=c2;
            }
        }
    }
    else if(bgw(s,"xor")){
        int reg2=get_register(s);
        while(s.back()!=' ')s.pop_back();
        s.pop_back();
        int reg=get_register(s);

        for(int i=0;i<8;i++){
            for(int j=0;j<16;j++){
                char c=((j&(1<<reg2))>0);
                ret.a[i][j]^=(c<<reg);
            }
        }
    }

    return ret;
}

int cnt;
vector<int>vect[maxn];
int par[maxn];

ll inf=2e9;
void prek(int x){

    nd[x].vt.resize(2);

    nd[x].sz=0;
    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        prek(id);
        nd[x].vt[1]=nd[x].vt[1]*nd[id].vt.back();
        nd[x].sz+=nd[id].sz;
        nd[x].sz=min(inf,nd[x].sz);
    }

    for(int i=2;i<=nd[x].rep;i++)
        nd[x].vt.pb(nd[x].vt.back()*nd[x].vt[1]);

    nd[x].dsz=nd[x].sz;
    nd[x].sz*=nd[x].rep;
    if(nd[x].rep==0){
        nd[x].sz=1;
        nd[x].dsz=1;
        swap(nd[x].vt[0],nd[x].vt[1]);
    }
    nd[x].sz=min(inf,nd[x].sz);
    nd[x].dsz=min(inf,nd[x].dsz);

    //printf("%d %lld %d AAA\n",x,nd[x].sz,par[x]);
    //nd[x].vt.back().ispis();
}

void go(int x,ll &k,state &s){

    if(k==0)return;
    if(k>=nd[x].sz){
        k-=nd[x].sz;
        s=s*nd[x].vt.back();
        return ;
    }

    s=s*nd[x].vt[k/nd[x].dsz];
    k%=nd[x].dsz;

    for(int i=0;i<vect[x].size();i++){
        int id=vect[x][i];
        go(id,k,s);
    }
}

int main(){

    ///freopen("test.txt","r",stdin);

    scanf("%d %d",&n,&q);
    int curr=1;
    cnt=2;
    nd[curr].rep=1;
    string s;
    getline(cin,s);
    for(int i=1;i<=n;i++){

        getline(cin,s);

        ///cout<<s<<" "<<i<<" "<<n<<endl;

        if(s[0]=='r'){// repeat
            vect[curr].pb(cnt);
            par[cnt]=curr;
            curr=cnt++;
            nd[curr].rep=get_integer(s);
            ///printf("%d CURR\n",curr);
        }
        else if(s[0]=='e'){
            curr=par[curr];
        }
        else{

            vect[curr].pb(cnt);
            par[cnt]=curr;
            curr=cnt++;
            nd[curr].rep=0;

            nd[curr].vt.pb(get_trans(s));

           /// nd[curr].vt.back().ispis();
            curr=par[curr];
        }

    }

    prek(1);

    while(q--){

        ll k;
        int c[4];
        scanf("%lld %d %d %d %d",&k,&c[0],&c[1],&c[2],&c[3]);

        state s;
        for(int i=0;i<8;i++){
            s.a[i]=0;
            for(int j=0;j<4;j++)
                s.a[i]|=(((c[j]&(1<<i))>0)<<j);
        }

        go(1,k,s);

        assert(k==0);

        memset(c,0,sizeof(c));

        for(int i=0;i<8;i++){
            for(int j=0;j<4;j++){
                int cc=((s.a[i]&(1<<j))>0);
                c[j]|=(cc<<i);
            }
        }

        for(int i=0;i<4;i++)printf("%d ",c[i]);
        printf("\n");

    }

    return 0;
}
