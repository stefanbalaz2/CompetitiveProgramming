
struct sat2{

    int n;
    vector<vector<int> >vect,rvect;
    vector<int>stek,pos,niz,val;
    int br,color,ne_moze;

    sat2(int n){
        this->n=n;

        vect.resize(n*2+1);
        rvect.resize(n*2+1);

        pos.resize(2*n+1);
        niz.resize(2*n+1);
        val.resize(2*n+1);

        ne_moze=0;
    }

    int neg(int x){
        if(x>n)return x-n;
        return x+n;
    }

    void add_or(int x,int y){
        vect[neg(x)].pb(y);
        vect[neg(y)].pb(x);
    }

    void add_xor(int x,int y){
        add_or(x,y);
        add_or(neg(x),neg(y));
    }


    void dfs1(int x){

        pos[x]=1;
        for(int i=0;i<vect[x].size();i++){
            int id=vect[x][i];
            if(pos[id])continue;
            dfs1(id);
        }
        stek.pb(x);
    }

    void dfs2(int x){

        pos[x]=color;
        niz[x]=++br;
        for(int i=0;i<rvect[x].size();i++){
            int id=rvect[x][i];
            if(pos[id])continue;
            dfs2(id);
        }
    }

    void solve(){

        stek.clear();
        for(int i=1;i<=2*n;i++){
            if(pos[i])continue;
            dfs1(i);
        }


        for(int i=1;i<=2*n;i++)
            for(int j=0;j<vect[i].size();j++)
                rvect[vect[i][j]].pb(i);



        br=0;
        color=0;
        for(int i=1;i<=2*n;i++)pos[i]=0;
        while(stek.size()){

            int id=stek.back();
            if(pos[id]){
                stek.pop_back();
                continue;
            }

            color++;
            dfs2(id);
            stek.pop_back();
        }


        for(int i=1;i<=n;i++)
            if(pos[i]==pos[neg(i)])ne_moze=1;


        for(int i=1;i<=n;i++){
            if(niz[i]<=niz[neg(i)])val[i]=0;
            else val[i]=1;
        }
    }

};
