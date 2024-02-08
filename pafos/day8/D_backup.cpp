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

using int128=__int128_t;
int128 get_int128(string s){
    int128 ret=0;
    for(int i=0;i<s.size();i++){
        ret=ret*2+s[i]-'0';
    }
    return ret;
}


const int maxfact=10;
int fact[maxfact],inv[maxfact];
void prek_fact(){
    fact[0]=1;
    for(int i=1;i<maxfact;i++)fact[i]=mul(fact[i-1],i);
    inv[maxfact-1]=invv(fact[maxfact-1]);
    for(int i=maxfact-1;i>0;i--)
        inv[i-1]=mul(inv[i],i);
}
int nCk(int n,int k){
    if(n<k || n<0 || k<0)return 0;
    return mul(fact[n],mul(inv[k],inv[n-k]));
}

struct polyn{

    vector<int>a;

    int size(){return a.size();}

    int& operator [](int x){
        if(x>=a.size())a.resize(x+1);
        return a[x];
    }

    polyn operator *(polyn b){

        polyn ret;
        for(int i=0;i<a.size();i++)
            for(int j=0;j<b.size();j++)
            ret[i+j]=add(ret[i+j],mul(a[i],b[j]));

        return ret;
    }

    polyn operator -(polyn b){
        polyn ret=(*this);
        for(int i=0;i<b.size();i++)
            ret[i]=sub(ret[i],b[i]);
        return ret;
    }
    polyn operator +(polyn b){
        polyn ret=(*this);
        for(int i=0;i<b.size();i++)
            ret[i]=add(ret[i],b[i]);
        return ret;
    }

    int eval(int x){
        int ret=0;
        int pom=1;
        for(int i=0;i<a.size();i++){
            ret=add(ret,mul(a[i],pom));
            pom=mul(pom,x);
        }
        return ret;
    }

    polyn taylor_shift(int c){

        int prekc[a.size()];
        int pom=1;
        for(int i=0;i<a.size();i++){
            prekc[i]=pom;
            pom=mul(pom,c);
        }

        polyn ret;
        int n=a.size();
        for(int k=0;k<n;k++){
            int sum=0;
            for(int i=k;i<n;i++)
                sum=add(sum,mul(a[i],mul(prekc[i-k],nCk(i,k))));
            ret[k]=sum;
        }

        return ret;
    }

    void ispis(){
       for(int i=0;i<a.size();i++)printf("%d ",a[i]);
       printf(" ISPIS\n");
    }

};


const int maxn=110;
int n,q;
int a[maxn],inva[maxn];
int inv2=invv(2);
int inv3=invv(3);


polyn prek_pw[maxn][4];
int pos[maxn],pos_cnt=0;
int pw2[maxn];

void ubaci(int x){
    pos[x]++;
    if(pos[x]==1)pos_cnt++;
}
void izbaci(int x){
    pos[x]--;
    if(pos[x]==0)pos_cnt--;
}

void prek_step2(){
    pw2[0]=1;
    for(int i=1;i<maxn;i++)pw2[i]=mul(pw2[i-1],2);
}
void prek_0_pw(){
    for(int i=n;i>=0;i--)
        prek_pw[i][0][0]=step(2,i);
}
void prek_1_pw(){

    for(int i=n;i>=0;i--){

        int pwx=0;
        int c=1;
        for(int k=0;k<=i;k++){

            if(k==i)pwx++;
            else{
                c=mul(c,a[k]);
                ubaci(k);
            }


            prek_pw[i][1][pwx]=add(prek_pw[i][1][pwx],mul(c,pw2[i-pos_cnt]));


            if(k==i)pwx--;
            else{
                c=mul(c,inva[k]);
                izbaci(k);
            }
        }

    }

}
void prek_2_pw(){

    for(int i=n;i>=0;i--){

        int pwx=0;
        int c=1;
        for(int j=0;j<=i;j++){

            if(j==i)pwx++;
            else{
                c=mul(c,a[j]);
                ubaci(j);
            }

            for(int k=0;k<=i;k++){

                if(k==i)pwx++;
                else{
                    c=mul(c,a[k]);
                    ubaci(k);
                }


                prek_pw[i][2][pwx]=add(prek_pw[i][2][pwx],mul(c,pw2[i-pos_cnt]));


                if(k==i)pwx--;
                else{
                    c=mul(c,inva[k]);
                    izbaci(k);
                }
            }


            if(j==i)pwx--;
            else{
                c=mul(c,inva[j]);
                izbaci(j);
            }

        }

    }

}

void prek_3_pw(){

    for(int i=n;i>=0;i--){

        int pwx=0;
        int c=1;
        for(int j=0;j<=i;j++){

            if(j==i)pwx++;
            else{
                c=mul(c,a[j]);
                ubaci(j);
            }

            for(int k=0;k<=i;k++){

                if(k==i)pwx++;
                else{
                    c=mul(c,a[k]);
                    ubaci(k);
                }


                for(int p=0;p<=i;p++){

                    if(p==i)pwx++;
                    else{
                        c=mul(c,a[p]);
                        ubaci(p);
                    }


                    prek_pw[i][3][pwx]=add(prek_pw[i][3][pwx],mul(c,pw2[i-pos_cnt]));


                    if(p==i)pwx--;
                    else{
                        c=mul(c,inva[p]);
                        izbaci(p);
                    }

                }


                if(k==i)pwx--;
                else{
                    c=mul(c,inva[k]);
                    izbaci(k);
                }
            }


            if(j==i)pwx--;
            else{
                c=mul(c,inva[j]);
                izbaci(j);
            }

        }

    }

}

struct polyset{
    polyn p[4];

    polyn& operator [](int x){
        return p[x];
    }

    polyset operator *(polyset b){

        polyset ret;

        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++){
                if(i+j>=4)continue;
                ret[i+j]=ret[i+j]+p[i]*b[j];
            }

        return ret;
    }

    polyset taylor_shift(int c){
        polyset ret=(*this);
        for(int i=0;i<4;i++)ret[i]=ret[i].taylor_shift(c);
        return ret;
    }

};

polyset get_polyset(int x,int k){

    polyset ret;

    polyn tuple1,tuple2,tuple3;
    tuple1[0]=prek_pw[k][1].eval(x);
    tuple1[1]=prek_pw[k][0].eval(x);

    tuple2[0]=prek_pw[k][2].eval(x);
    tuple2[1]=mul(2,prek_pw[k][1].eval(x));
    tuple2[2]=prek_pw[k][0].eval(x);

    tuple3[0]=prek_pw[k][3].eval(x);
    tuple3[1]=mul(3,prek_pw[k][2].eval(x));
    tuple3[2]=mul(3,prek_pw[k][1].eval(x));
    tuple3[3]=prek_pw[k][0].eval(x);


    ret[0][0]=1;

    ret[1]=tuple1;

    ret[2]=ret[1]*ret[1];
    ret[2]=ret[2]-tuple2;
    assert(ret[2].size()==3);
    ret[2][0]=mul(ret[2][0],inv2);
    ret[2][1]=mul(ret[2][1],inv2);
    ret[2][2]=mul(ret[2][2],inv2);


    ret[3]=ret[2]*ret[1];
    ret[3]=ret[3]-(tuple2*tuple1);
    ret[3]=ret[3]+tuple3;
    for(int i=0;i<ret[3].size();i++)ret[3][i]=mul(ret[3][i],inv3);


    return ret;
}

const int maxq=5e4+10;
struct node{

    int l=0,r=0;
    int lazy=0;
    polyset ps;

}nodes[maxq*150];
int root=0;
int cnt=1;

int get_new_node(int x,int k){
    node c;
    c.ps=get_polyset(x,k);
    nodes[cnt++]=c;
    ///cout<<cnt-1<<" "<<maxq*150<<endl;
    assert(cnt-1<maxq*150);
    return cnt-1;
}

void push(int x,int k,int nd){

    if(nodes[nd].lazy==0)return;

    if(nodes[nd].l==0)nodes[nd].l=get_new_node(x,k-1);
    if(nodes[nd].r==0)nodes[nd].r=get_new_node(add(x,a[k-1]),k-1);

    nodes[nodes[nd].l].lazy+=nodes[nd].lazy;
    nodes[nodes[nd].r].lazy+=nodes[nd].lazy;

    nodes[nodes[nd].l].ps=nodes[nodes[nd].l].ps.taylor_shift(nodes[nd].lazy);
    nodes[nodes[nd].r].ps=nodes[nodes[nd].r].ps.taylor_shift(nodes[nd].lazy);

    nodes[nd].lazy=0;
}
void upd(int x,int k,int &nd,int128 lp,int128 rp,int128 l,int128 r,int val){

    if(l>rp || r<lp)return;

    if(nd==0)nd=get_new_node(x,k);

    if(l>=lp && r<=rp){
        nodes[nd].lazy+=val;
        //nodes[nd].ps[1].ispis();
        nodes[nd].ps=nodes[nd].ps.taylor_shift(val);
        ///nodes[nd].ps[1].ispis();
        ///printf("%d  TO NODE\n",nd);
        return;
    }
    int128 mid=(l+r)/2;
    push(x,k,nd);

    upd(x,k-1,nodes[nd].l,lp,rp,l,mid,val);
    upd(add(x,a[k-1]),k-1,nodes[nd].r,lp,rp,mid+1,r,val);


    if(nodes[nd].l==0)nodes[nd].l=get_new_node(x,k-1);
    if(nodes[nd].r==0)nodes[nd].r=get_new_node(add(x,a[k-1]),k-1);

    nodes[nd].ps=nodes[nodes[nd].l].ps*nodes[nodes[nd].r].ps;

    /*cout<<(int)l<<" "<<(int)r<<"   INTER "<<nodes[nd].l<<" "<<nodes[nd].r<<endl;
    nodes[nd].ps[1].ispis();
    nodes[nodes[nd].l].ps[1].ispis();
    nodes[nodes[nd].r].ps[1].ispis();*/

}
void qry(int x,int k,int &nd,int128 lp,int128 rp,int128 l,int128 r,polyset &ret){

    if(l>rp || r<lp)return;

    if(nd==0)nd=get_new_node(x,k);

    if(l>=lp && r<=rp){
        ///cout<<(int)l<<" "<<(int)r<<endl;
        ///nodes[nd].ps[1].ispis();
        ret=ret*nodes[nd].ps;
        return;
    }
    int128 mid=(l+r)/2;
    push(x,k,nd);

    qry(x,k-1,nodes[nd].l,lp,rp,l,mid,ret);
    qry(add(x,a[k-1]),k-1,nodes[nd].r,lp,rp,mid+1,r,ret);

}


int main(){

    ///freopen("test.txt","r",stdin);

    prek_fact();

    scanf("%d %d",&n,&q);

    string minpts,maxpts;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        a[i]%=mod;
        inva[i]=invv(a[i]);
        minpts.pb('0');
        maxpts.pb('1');
    }
    int128 minpt,maxpt;
    minpt=get_int128(minpts);
    maxpt=get_int128(maxpts);


    prek_step2();
    prek_0_pw();
    prek_1_pw();
    prek_2_pw();
    prek_3_pw();

    ///printf("%d %d %d %d AAAA\n",prek_pw[n-1][0].eval(1),prek_pw[n-1][1].eval(1),prek_pw[n-1][2].eval(1),prek_pw[n-1][3].eval(1));

    root=0;

    while(q--){

        int tip;
        scanf("%d",&tip);
        if(tip==1){

            int x;
            string ls,rs;
            cin>>ls>>rs;
            scanf("%d",&x);
            x%=mod;

            int128 l,r;
            l=get_int128(ls);
            r=get_int128(rs);

            upd(0,n,root,l,r,minpt,maxpt,x);

        }
        else{

            string ls,rs;
            cin>>ls>>rs;

            int128 l,r;
            l=get_int128(ls);
            r=get_int128(rs);

            polyset ret;
            ///cout<<"AAAFA"<<endl;
            ret[0][0]=1;
            ///cout<<"AAAFA"<<endl;
            qry(0,n,root,l,r,minpt,maxpt,ret);

            printf("%d\n",ret[3].eval(0));
            ///ret[3].ispis();

        }

    }


    ///nodes[root].ps[1].ispis();


    return 0;
}
