#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define ff first
#define ss second
using namespace std;
typedef pair<int,int> pii;
const int maxn=1e4+10;
const int col_const=1000;
mt19937 gen(time(NULL));
char mat[maxn][maxn];
int maxx_score,goback,const_goback,spuc_limit,gbc,spcl,spuc_limit2,const_goback2,bio_jedan,spuc2;
float spuc;
ll mod1=1e9+7;
ll mod2=1e9+9;
ll p1=313;
ll p2=317;
pii p_pow[maxn];
int gotov,down_limit,up_limit,minlen,suma_karaktera;
int brmov[maxn],brpoz[maxn];
clock_t pocetak;
string s[maxn];
int t,n,maxlen,minn=1e9,mpos,maxr,vreme;
int dx[4]={0,0,-1,1};
int dy[4]={1,-1,0,0};
/// gore 2
/// dole 3
/// levo 1
/// desno 0
vector<pii>pozicija[maxn],pozicija2[maxn];
vector<int>movement[maxn],movement2[maxn];
vector<pii>pref[maxn];
map<pii,vector<pii> >mapa;
map<pair<pii,pii>,vector<pii> >mapa2;
struct arrangement{
    int ind,fpos,val;
}sortirani[maxn],greedy[maxn];
bool srt(arrangement a,arrangement b){
    return s[a.ind]<s[b.ind];
}
bool srt2(int x,int y){
    return s[x].size()>s[y].size();
}
void arrange1(arrangement sortirani[maxn]){/// sort strings

    sort(sortirani+1,sortirani+n+1,srt);
    for(int i=2;i<=n;i++){
        int lcp=0;

        int id1=sortirani[i].ind;
        int id2=sortirani[i-1].ind;
        while(s[id1].size()>lcp && s[id2].size()>lcp && s[id1][lcp]==s[id2][lcp])lcp++;

        sortirani[i].val=lcp;
        sortirani[i].fpos=1;
    }
}
pii go_z(int id1,int id2){

    string p=s[id2]+'$'+s[id1];
    int z[(int)p.size()+10];
    memset(z,0,sizeof(z));

    int l=0;
    int r=0;
    for(int i=1;i<p.size();i++){

        if(i>r){
            l=i;
            r=l-1;
            while(p[r+1]==p[r-l+1])r++;
            z[i]=r-l+1;
        }
        else{

            if(i+z[i-l]-1<r)z[i]=z[i-l];
            else{

                l=i;
                while(p[r+1]==p[r-l+1])r++;
                z[i]=r-l+1;
            }
        }

    }

    pii ret={-1,-1};
    for(int i=s[id2].size()+1;i<p.size();i++){
        if(ret.ff<=z[i]){
            ret.ff=z[i];
            ret.ss=i-s[id2].size();
        }
    }

    /*cout<<s[id2]<<"$"<<s[id1]<<endl;
    for(int i=0;i<p.size();i++)printf("%d",z[i]);
    printf("\n");*/

    return ret;
}
void arrange2(arrangement niz[maxn]){/// greedy

    int x=mpos;
    niz[1].ind=x;

    bool pos[n+10];
    memset(pos,0,sizeof(pos));
    pos[x]=1;

    ///cout<<s[niz[1].ind]<<endl;
    for(int i=2;i<=n;i++){

        int fp=-1;
        pii maxx{-1,-1};
        for(int j=1;j<=n;j++){
            if(pos[j])continue;

            pii pom=go_z(niz[i-1].ind,j);
            if(pom.ff>maxx.ff){
                maxx=pom;
                fp=j;
            }
        }

        niz[i].ind=fp;
        niz[i].val=maxx.ff;
        niz[i].fpos=maxx.ss;
        pos[fp]=1;

        ///cout<<s[niz[i].ind]<<endl;
    }

}
pii phase1(int id1,int id2,int start,int how_much,int from_where,int &cdone){/// following the previous string

    pii curr=pozicija[id1][from_where-1];

    if(start-2>=0)movement[id2].resize(start-2);
    else movement[id2].resize(start-1);
    pozicija[id2].resize(start-1);
    pozicija[id2].pb(curr);

    for(int i=2;i<=how_much;i++){

        int dir=movement[id1][from_where+i-2-1];
        curr.ff+=dx[dir];
        curr.ss+=dy[dir];

        pozicija[id2].pb(curr);
        movement[id2].pb(dir);
    }

    cdone+=how_much;

    curr={-1,-1};
    while(pozicija[id2].size()){
        int x=pozicija[id2][pozicija[id2].size()-1].ff;
        int y=pozicija[id2][pozicija[id2].size()-1].ss;

        if(mat[x+1][y]=='#'){curr={x,y};break;}
        pozicija[id2].pop_back();
        movement[id2].pop_back();
        cdone--;
    }

    return curr;
}
int phase2(int id,int start,int x,int y,int &prevrow){

    if(start-2>=0)movement[id].resize(start-2);
    else movement[id].resize(start-1);
    pozicija[id].resize(start-1);

    int ret=0;

    ///printf("%d %d %d %d  UFFFF\n",start,s[id].size(),x,prevrow);
    while(start<=s[id].size() && x-1<=prevrow){

        ret++;
        mat[x][y]=s[id][start-1];
        maxlen=max(maxlen,y);

        movement[id].pb(3);
        pozicija[id].pb({x,y});

        ///printf("%d %d %c  jeeebote\n",x,y,s[id][start-1]);

        x++;
        start++;
    }

    if(x>prevrow)prevrow++;

    return ret;
}
void phase3(int id,int start,int x,int y){

    if(start-2>=0)movement[id].resize(start-2);
    else movement[id].resize(start-1);
    pozicija[id].resize(start-1);

    ///if(id==4)printf("%d %d %d AAAJGELSN\n",start,x,y);
    if(start>s[id].size())return;

    mat[x][y]=s[id][start-1];
    maxlen=max(maxlen,y);
    if(pozicija[id].size()>0)movement[id].pb(0);
    pozicija[id].pb({x,y});
    start++;
    int cp=0;

    while(start<=s[id].size()){

        if(cp==1){

            if(mat[x][y+1]==s[id][start-1]){

                y++;
                maxlen=max(maxlen,y);
                if(pozicija[id].size()>0)movement[id].pb(0);
                pozicija[id].pb({x,y});

                start++;
            }
            else{
                x++;
                maxlen=max(maxlen,y);
                if(pozicija[id].size()>0)movement[id].pb(3);
                pozicija[id].pb({x,y});
                mat[x][y]=s[id][start-1];

                start++;
                cp=0;
            }

        }
        else if(mat[x-1][y]==s[id][start-1] && start<s[id].size() && mat[x-1][y+1]==s[id][start]){
            cp=1;
            x--;
            maxlen=max(maxlen,y);
            if(pozicija[id].size()>0)movement[id].pb(2);
            pozicija[id].pb({x,y});

            start++;
        }
        else{
            y++;
            mat[x][y]=s[id][start-1];
            maxlen=max(maxlen,y);
            if(pozicija[id].size()>0)movement[id].pb(0);
            pozicija[id].pb({x,y});

            start++;
        }
    }

}
void ispisi_matricu(){
    for(int i=1;i<=maxr;i++){
        for(int j=1;j<=maxlen;j++)printf("%c",mat[i][j]);
        printf("\n");
    }
}
void finish(arrangement niz[maxn]){

    int prevrow=0;
    for(int i=1;i<=n;i++){


        if(niz[i].val==0){
            prevrow++;
            phase3(niz[i].ind,1,prevrow,1);
            continue;
        }


        int curr_done=0;
        pii tpos=phase1(niz[i-1].ind,niz[i].ind,curr_done+1,niz[i].val,niz[i].fpos,curr_done);



        if(tpos.ff==-1 || (tpos.ff<prevrow && mat[tpos.ff+1][tpos.ss]!='#')){
            prevrow++;
            phase3(niz[i].ind,1,prevrow,1);
            continue;
        }


        if(tpos.ff<=prevrow)
            curr_done+=phase2(niz[i].ind,curr_done+1,tpos.ff+1,tpos.ss,prevrow);



        phase3(niz[i].ind,curr_done+1,prevrow,tpos.ss+1);
    }


}
char get_letter(int x){

    if(x==0)return 'R';
    if(x==1)return 'L';
    if(x==2)return 'U';
    if(x==3)return 'D';
}
void ispis(){

    /// end
    printf("%d %d\n",maxlen,maxr);
    ispisi_matricu();

    for(int i=1;i<=n;i++){
        printf("%d %d ",pozicija[i][0].ss-1,pozicija[i][0].ff-1);
        for(int j=0;j<movement[i].size();j++)printf("%c ",get_letter(movement[i][j]));
        printf("\n");
    }

}
void ispisi_matricu2(int u,int d,int l,int r){
    for(int i=u;i<=d;i++){
        for(int j=l;j<=r;j++)printf("%c",mat[i][j]);
        printf("\n");
    }
}
void ispis2(){


    int u=1e9;
    int d=0;
    int l=1e9;
    int r=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<pozicija[i].size();j++){
            u=min(u,pozicija[i][j].ff);
            d=max(d,pozicija[i][j].ff);

            l=min(l,pozicija[i][j].ss);
            r=max(r,pozicija[i][j].ss);
        }
    }

    /// end
    printf("%d %d\n",r-l+1,d-u+1);
    ispisi_matricu2(u,d,l,r);

    for(int i=1;i<=n;i++){
        printf("%d %d ",pozicija[i][0].ss-l,pozicija[i][0].ff-u);
        for(int j=0;j<movement[i].size();j++)printf("%c ",get_letter(movement[i][j]));
        printf("\n");
    }

}
void go_prefix(){
    arrange1(sortirani);
    arrange2(greedy);
    finish(greedy);

    maxr=n;
}
void go_single(int id,int x,int y){

    int pravac=1;
    for(int i=1;i<s[id].size();i++){

        if(pravac==1){
            if(mat[x][y-1]==s[id][i]){
                movement[id].pb(1);
                y--;
            }
            else if(mat[x][y+1]==s[id][i]){
                movement[id].pb(0);
                y++;
            }
            else if(mat[x][y+1]=='#'){
                movement[id].pb(0);
                y++;
                mat[x][y]=s[id][i];
            }
            else{
                movement[id].pb(3);
                x++;
                mat[x][y]=s[id][i];
                maxr++;
            }
        }
        else if(pravac==0){

            movement[id].pb(3);
            maxr++;
            x++;
            mat[x][y]=s[id][i];

            if(y==col_const)pravac=2;
            else pravac=1;
        }
        else{

            if(mat[x][y-1]==s[id][i]){
                movement[id].pb(1);
                y--;
            }
            else if(mat[x][y+1]==s[id][i]){
                movement[id].pb(0);
                y++;
            }
            else if(mat[x][y-1]=='#'){
                movement[id].pb(1);
                y--;
                mat[x][y]=s[id][i];
            }
            else{
                movement[id].pb(3);
                x++;
                mat[x][y]=s[id][i];
                maxr++;
            }

        }

        maxlen=max(maxlen,y);
        pozicija[id].pb({x,y});
        if(y==1 && pravac==2)pravac=0;
        if(y==col_const && pravac==1)pravac=0;
    }

}
void singles(){

    maxr=0;
    for(int i=1;i<=n;i++){

        pozicija[i].clear();
        movement[i].clear();

        maxr++;
        mat[maxr][1]=s[i][0];
        pozicija[i].pb({maxr,1});

        go_single(i,maxr,1);
    }

}
int degree(int x,int y){
    int ret=0;

    if(mat[x-1][y]!='#')ret++;
    if(mat[x+1][y]!='#')ret++;

    return ret;
}
int place_intersections(int id1,int id2,int row){


    phase3(id1,1,row+2,1);

    int ret=0;

    int x=row+1;
    int y=1;
    pozicija[id2].pb({x,y});
    mat[x][y]=s[id2][0];
    int curr=1;

    while(curr<s[id2].size()){


        if(x==row+1){

            if(mat[x+1][y]==s[id2][curr] && degree(x+1,y)<2){
                x++;
                movement[id2].pb(3);
                ret++;
            }
            else{
                y++;
                movement[id2].pb(0);
            }
        }
        else if(x==row+2){

            if(mat[x][y+1]==s[id2][curr]){
                y++;
                movement[id2].pb(0);
                ret++;
            }
            else{

                if(mat[x-1][y]==s[id2][curr]){
                    x--;
                    movement[id2].pb(2);
                    ret++;
                }
                else if(mat[x+1][y]==s[id2][curr]){
                    x++;
                    movement[id2].pb(3);
                    ret++;
                }
                else if(mat[x-1][y]=='#'){
                    x--;
                    movement[id2].pb(2);
                }
                else if(mat[x+1][y]=='#'){
                    x++;
                    movement[id2].pb(3);
                }
            }

        }
        else{

            if(mat[x-1][y]==s[id2][curr] && degree(x-1,y)<2){
                x--;
                movement[id2].pb(2);
                ret++;
            }
            else{
                y++;
                movement[id2].pb(0);
            }

        }

        curr++;
        pozicija[id2].pb({x,y});
        mat[x][y]=s[id2][curr-1];
        maxlen=max(maxlen,y);
    }


    return ret;
}
void remove_intersections(int x,int y,int row){

    int maxx=max(s[x].size(),s[y].size());
    for(int i=1;i<=maxx;i++){
        mat[row+1][i]='#';
        mat[row+2][i]='#';
        mat[row+3][i]='#';
    }

    pozicija[x].clear();
    pozicija[y].clear();
    movement[x].clear();
    movement[y].clear();
}
void go_pair_and_intersect(){

    bool pos[n+10];
    memset(pos,0,sizeof(pos));

    int cnt=0;
    for(int i=1;i<=n;i++){
        if(pos[i])continue;

        int id=-1;
        int maxx=-1;
        pos[i]=1;
        for(int j=1;j<=n;j++){
            if(pos[j])continue;

            int pom=place_intersections(i,j,cnt*3);
            remove_intersections(i,j,cnt*3);

            if(pom>maxx){
                maxx=pom;
                id=j;
            }
        }

        if(id==-1){
            phase3(i,1,cnt*3+1,1);
            break;
        }
        else{
            place_intersections(i,id,cnt*3);
            cnt++;
            pos[i]=1;
            pos[id]=1;
        }
    }

    maxr=cnt*3+3;
}
int check(){

    for(int i=1;i<=maxr;i++)
        for(int j=1;j<=maxlen;j++)
        if(mat[i][j]!='#' && (mat[i][j]<'a' || mat[i][j]>'z'))return mat[i][j];

    for(int i=1;i<=n;i++){

        int x=pozicija[i][0].ff;
        int y=pozicija[i][0].ss;

        if(s[i][0]!=mat[x][y])return brpoz[i];

        for(int j=0;j<movement[i].size();j++){
            x+=dx[movement[i][j]];
            y+=dy[movement[i][j]];

            if(s[i][j+1]!=mat[x][y])return brpoz[i];
        }

    }
return 0;
}
int range_rand(int l,int r){

    int ret=gen()%(r-l);
    if(ret<0)ret+=(r-l);

    return l+ret;

}
bool time_to_finish(){

    double ctt=4.0;
    if(suma_karaktera>5000)ctt=4.0;

    clock_t kraj=clock();
    if((double)(kraj-pocetak)/CLOCKS_PER_SEC>ctt)return 1;
    return 0;
}
pii get_h(int id,int l,int r){

    ll lp=pref[id][l-1].ff;
    ll rp=pref[id][r].ff;
    ll pp=p_pow[r-l+1].ff;

    ll ret1=(rp-lp*pp)%mod1;
    if(ret1<0)ret1+=mod1;


    lp=pref[id][l-1].ss;
    rp=pref[id][r].ss;
    pp=p_pow[r-l+1].ss;

    ll ret2=(rp-lp*pp)%mod2;
    if(ret2<0)ret2+=mod2;

    return {(int)ret1,(int)ret2};
}
void ubaci(int id){
    int hmc=25;

    if(n==1)return;
    for(int i=1;i<=s[id].size();i++){

        pii pos=pozicija[id][i-1];

        for(int j=i;j<=min(i+hmc,(int)s[id].size());j++){
            mapa[get_h(id,i,j)].pb({id,i});
            mapa2[{get_h(id,i,j),pos}].pb({id,i});
        }
    }

}
void go_rekurzija(int id,int start,int avgx,int avgy,int l,int r,int x,int y,int score){



    if(start>s[id].size()){

        if(time_to_finish())vreme=1;

        bio_jedan=1;
        if(score>maxx_score){
            maxx_score=score;

            for(int j=0;j<s[id].size();j++)pozicija2[id][j]=pozicija[id][j];
            for(int j=0;j<s[id].size()-1;j++)movement2[id][j]=movement[id][j];
        }

        spuc++;
        if((int)spuc==spuc_limit2){
            const_goback+=const_goback2;
            spuc_limit2+=max(1,spuc_limit/gbc);
        }
        goback=const_goback;
        if(spuc>=spuc_limit || vreme)gotov=1;

        return;
    }
    else if(start==1){

        /// best prefix to be found
        for(int i=s[id].size();i>=1;i--){

            pii pom=get_h(id,1,i);

            map<pii,vector<pii> >::iterator it=mapa.find(pom);
            if(it==mapa.end())continue;

            for(int j=0;j<it->ss.size();j++){
                int id2=it->ss[j].ff;
                int start2=it->ss[j].ss;

                if(s[id2][start2-1]!=s[id][0])continue;

                pozicija[id][brpoz[id]++]=pozicija[id2][start2-1];
                int cp=1;
                for(int k=start2;k<s[id2].size();k++){

                    if(cp>=s[id].size())break;
                    if(s[id2][k]!=s[id][cp])break;

                    pozicija[id][brpoz[id]++]=pozicija[id2][k];
                    movement[id][brmov[id]++]=movement[id2][k-1];

                    cp++;
                }

                go_rekurzija(id,cp+1,avgx,avgy,l,r,pozicija[id][brpoz[id]-1].ff,pozicija[id][brpoz[id]-1].ss,cp+1-start);

                brpoz[id]=0;
                brmov[id]=0;

                if(gotov)return;
                if(goback)goback=0;
            }

        }


        /// random point in range
        int spx=-1;
        int spy=-1;
        int slen=s[id].size();
        int deviation=max(1,slen/10);
        ///int deviation=1;

        while(gotov==0){


            for(int i=1;i<=10;i++){
                spx=range_rand(max(up_limit,avgx-deviation),min(down_limit,avgx+deviation));
                spy=range_rand(max(l,avgy-deviation),min(r,avgy+deviation));

                int jeste=(mat[spx][spy]==s[id][start-1]);
                if(mat[spx][spy]=='#' || mat[spx][spy]==s[id][start-1]){
                    pozicija[id][brpoz[id]++]={spx,spy};
                    char prv=mat[spx][spy];
                    mat[spx][spy]=s[id][start-1];
                    go_rekurzija(id,start+1,avgx,avgy,l,r,spx,spy,score+jeste);

                    brpoz[id]--;
                    mat[spx][spy]=prv;

                    if(gotov)break;
                    if(goback)goback=0;
                }
            }

            deviation=min(maxlen,deviation*2);
        }

    }
    else{

        int child=0;

        /// adjacent
        vector<int>taraba;
        for(int i=0;i<4;i++){
            int idx=x+dx[i];
            int idy=y+dy[i];
            if(idx<up_limit || idx>down_limit || idy<l || idy>r)continue;
            if(mat[idx][idy]!='#' && mat[idx][idy]!=s[id][start-1])continue;

            if(mat[idx][idy]==s[id][start-1] /*&& !vreme*/){
                movement[id][brmov[id]++]=i;
                pozicija[id][brpoz[id]++]={idx,idy};
                char prv=mat[idx][idy];
                mat[idx][idy]=s[id][start-1];

                child++;
                go_rekurzija(id,start+1,avgx,avgy,l,r,idx,idy,score+1);

                brpoz[id]--;
                brmov[id]--;
                mat[idx][idy]=prv;

                if(gotov)return;
                if(goback){goback--;return;}
            }
            else taraba.pb(i);
        }


        bool pos[taraba.size()+3];
        memset(pos,0,sizeof(pos));

        for(int i=0;i<taraba.size();i++){

            int minn_dist=1e9;
            int min_pos=-1;
            for(int j=0;j<taraba.size();j++){
                if(pos[j])continue;

                int idx=x+dx[taraba[j]];
                int idy=y+dy[taraba[j]];

                if(abs(avgx-idx)+abs(avgy-idy)<minn_dist){
                    minn_dist=abs(avgx-idx)+abs(avgy-idy);
                    min_pos=j;
                }
            }

            pos[min_pos]=1;

            int idx=x+dx[taraba[min_pos]];
            int idy=y+dy[taraba[min_pos]];
            movement[id][brmov[id]++]=taraba[min_pos];
            pozicija[id][brpoz[id]++]={idx,idy};
            char prv=mat[idx][idy];
            mat[idx][idy]=s[id][start-1];

            child++;
            go_rekurzija(id,start+1,avgx,avgy,l,r,idx,idy,score);

            brpoz[id]--;
            brmov[id]--;
            mat[idx][idy]=prv;

            if(gotov)return;
            if(goback){goback--;return;}

        }

        if(child==0){

            if(time_to_finish())vreme=1;

            spuc+=0.25;
            if((int)spuc==spuc_limit2){
                const_goback+=const_goback2;
                spuc_limit2+=max(1,spuc_limit/gbc);
            }
            if((int)spuc>=spuc_limit && bio_jedan)gotov=1;

        }
    }

}
void prek_hash(){

    for(int i=1;i<=n;i++){

        pref[i].resize(s[i].size()+1);
        for(int j=1;j<=s[i].size();j++){
            pref[i][j].ff=(int)(((ll)pref[i][j-1].ff*p1+s[i][j-1])%(ll)mod1);
            pref[i][j].ss=(int)(((ll)pref[i][j-1].ss*p2+s[i][j-1])%(ll)mod2);
        }
    }

    p_pow[0]={1,1};
    for(int i=1;i<=maxn-3;i++){
        p_pow[i].ff=(int)(((ll)p_pow[i-1].ff*p1)%mod1);
        p_pow[i].ss=(int)(((ll)p_pow[i-1].ss*p2)%mod2);
    }
}
void set_constants(int x){

    /// 1e7=splc*x*1e4/x

    if(x<=10){gbc=2;spcl=3e6/suma_karaktera;}
    else if(x<=50){gbc=2;spcl=3e6/suma_karaktera;}
    else if(x<=100){gbc=2;spcl=3e6/suma_karaktera;}
    else if(x<=300){gbc=2;spcl=3e6/suma_karaktera;}
    else if(x<=500){gbc=2;spcl=3e6/suma_karaktera;}
    else if(x<=1000){gbc=2;spcl=2e6/suma_karaktera;}
    else if(x<=2000){gbc=2;spcl=2e5/suma_karaktera;}
    else if(x<=3000){gbc=2;spcl=3e5/suma_karaktera;}
    else if(x<=5000){gbc=2;spcl=3e5/suma_karaktera;}
    else if(x<=7000){gbc=2;spcl=3e5/suma_karaktera;}
    else if(x<=10000){gbc=2;spcl=3e5/suma_karaktera;}

    gbc=5;
}
void rekurzija(){

    minlen=1;
    maxlen=800;

    int blok=800;
    int granica=suma_karaktera/1+(maxlen/blok+1);

    for(int i=1;i<=n;i++){
        int pom=s[i].size();

        pozicija[i].resize(pom);
        movement[i].resize(pom-1);

        pozicija2[i].resize(pom);
        movement2[i].resize(pom-1);
    }

    prek_hash();

    int niz[n+10];
    for(int i=1;i<=n;i++)niz[i]=i;
    sort(niz+1,niz+n+1,srt2);


    up_limit=1;
    down_limit=800;
    maxr=down_limit;

    int l=1;
    int r=blok;
    int curr_string=1;
    while(1){
        if(curr_string>n)break;
        if(l>maxlen)break;
        if(r>maxlen)r=maxlen;


        int curr_sum=0;
        int sumx=(up_limit+down_limit)/2;
        int sumy=(l+r)/2;
        int cnt=1;
        curr_sum=0;
        while(curr_sum<granica && curr_string<=n){

            set_constants(s[niz[curr_string]].size());

            gotov=0;
            spuc=0;
            goback=0;
            const_goback=max((int)s[niz[curr_string]].size()/gbc,1);
            const_goback2=max((int)s[niz[curr_string]].size()/gbc,1);
            spuc_limit2=max(spcl/gbc,1);
            spuc_limit=spcl;
            maxx_score=-1;
            bio_jedan=0;
            spuc2=0;
            go_rekurzija(niz[curr_string],1,sumx/cnt,sumy/cnt,l,r,-1,-1,0);


            for(int i=0;i<pozicija[niz[curr_string]].size();i++){
                pozicija[niz[curr_string]][i]=pozicija2[niz[curr_string]][i];
                mat[pozicija[niz[curr_string]][i].ff][pozicija[niz[curr_string]][i].ss]=s[niz[curr_string]][i];
            }
            for(int i=0;i<pozicija[niz[curr_string]].size()-1;i++)
                movement[niz[curr_string]][i]=movement2[niz[curr_string]][i];

            for(int i=0;i<pozicija[niz[curr_string]].size();i++){
                sumx+=pozicija[niz[curr_string]][i].ff;
                sumy+=pozicija[niz[curr_string]][i].ss;
                cnt++;
            }

            ubaci(niz[curr_string]);
            curr_sum+=s[niz[curr_string]].size();
            curr_string++;
        }


        l+=blok;
        r+=blok;
    }

}
void jedna(){

    int grupe=sqrt(suma_karaktera);

    int dir=0;
    int x=1;
    int y=1;
    mat[x][y]=s[n][0];
    pozicija[n].pb({x,y});
    int cr=1;
    for(int i=1;i<s[n].size();i++){


        if(x<cr && (y==grupe || y==1)){
            movement[n].pb(3);
            x++;
            pozicija[n].pb({x,y});
            mat[x][y]=s[n][i];

            if(x==cr)dir^=1;
        }
        else{

            if(x==cr){

                if(y!=1 && y!=grupe && mat[x-1][y]==s[n][i] && i<s[n].size()-1 && (mat[x-1][y+dy[dir]]=='#' || mat[x-1][y+dy[dir]]==s[n][i+1])){
                    x--;
                    movement[n].pb(2);
                    pozicija[n].pb({x,y});
                    mat[x][y]=s[n][i];
                }
                else{
                    y+=dy[dir];
                    movement[n].pb(dir);
                    pozicija[n].pb({x,y});
                    mat[x][y]=s[n][i];

                    if(y==grupe || y==1)cr++;
                }

            }
            else{
                if(mat[x][y+dy[dir]]=='#' || mat[x][y+dy[dir]]==s[n][i]){
                    y+=dy[dir];
                    movement[n].pb(dir);
                    pozicija[n].pb({x,y});
                    mat[x][y]=s[n][i];

                    if(y==grupe || y==1)cr++;
                }
                else{
                    movement[n].pb(3);
                    x++;
                    pozicija[n].pb({x,y});
                    mat[x][y]=s[n][i];
                }
            }

        }

    }
}
int main(){


    pocetak=clock();

    freopen("crossword.in","r",stdin);
    freopen("crossword.out","w",stdout);

    for(int i=0;i<=maxn-5;i++)
    for(int j=0;j<=maxn-5;j++)mat[i][j]='#';

    scanf("%d %d",&t,&n);

    for(int i=1;i<=n;i++){
        cin>>s[i];
        suma_karaktera+=s[i].size();
        if(minn>s[i].size()){
            minn=s[i].size();
            mpos=i;
        }
        sortirani[i].ind=i;
    }

    rekurzija();
    ispis2();


return 0;
}
