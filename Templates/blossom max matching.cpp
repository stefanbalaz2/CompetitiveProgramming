struct blossom{

    int n,m;
    vector<int>mate;
    vector<vector<int> >b;
    vector<int>bl,p,d;
    vector<vector<int> >g;

    blossom(int n){

        this->n=n;
        m=n+n/2;
        mate.assign(n,-1);
        bl.resize(m);
        p.resize(m);
        d.resize(m);
        g.assign(m,vector<int>(m,-1));
        b.resize(m);

    }

    void add_edge(int u,int v){
        g[u][v]=u;
        g[v][u]=v;
    }

    void match(int u,int v){
        g[u][v]=-1;
        g[v][u]=-1;
        mate[u]=v;
        mate[v]=u;
    }


    vector<int>trace(int x){

        vector<int>vx;

        while(1){

            while(bl[x]!=x)x=bl[x];
            if(vx.size() && vx.back()==x)break;

            vx.pb(x);
            x=p[x];

        }

        return vx;
    }


    void contract(int c,int x,int y,vector<int>&vx,vector<int>&vy){

        b[c].clear();
        int r=vx.back();
        while(vx.size() && vy.size() && vx.back()==vy.back()){
            r=vx.back();
            vx.pop_back();
            vy.pop_back();
        }

        b[c].pb(r);
        b[c].insert(b[c].end(),vx.rbegin(),vx.rend());
        b[c].insert(b[c].end(),vy.begin(),vy.end());

        for(int i=0;i<=c;i++){
            g[c][i]=-1;
            g[i][c]=-1;
        }

        for(int z:b[c]){

            bl[z]=c;

            for(int i=0;i<c;i++){

                if(g[z][i]!=-1){
                    g[c][i]=z;
                    g[i][c]=g[i][z];
                }

            }

        }

    }



    vector<int> lift(vector<int> &vx){

        vector<int>A;

        while(vx.size()>=2){

            int z=vx.back();
            vx.pop_back();
            if(z<n){
                A.pb(z);
                continue;
            }

            int w=vx.back();

            int i=( A.size()%2==0? find(b[z].begin(),b[z].end(),g[z][w]) - b[z].begin() : 0 );
            int j=(A.size()%2==1?find(b[z].begin(),b[z].end(),g[z][A.back()])-b[z].begin():0);

            int k=b[z].size();
            int dif=( A.size()%2==0? i%2==1 : j%2==0 )?1:k-1 ;

            while(i!=j){
                vx.pb(b[z][i]);
                i=(i+dif)%k;
            }
            vx.pb(b[z][i]);

        }

        return A;
    }


    int solve(){

        int ret=0;
        while(1){


            fill(d.begin(),d.end(),0);
            queue<int>q;
            for(int i=0;i<m;i++)bl[i]=i;
            for(int i=0;i<n;i++)
                if(mate[i]==-1){
                    p[i]=i;
                    q.push(i);
                    d[i]=1;
                }

            bool aug=false;
            int c=n;
            while(q.size() && !aug){



                int x=q.front();
                q.pop();
                if(bl[x]!=x)continue;

                for(int y=0;y<c;y++){

                    if(bl[y]==y && g[x][y]!=-1){


                        if(d[y]==0){

                            p[y]=x;
                            d[y]=2;
                            p[mate[y]]=y;
                            d[mate[y]]=1;

                            q.push(mate[y]);
                        }
                        else if(d[y]==1){

                            vector<int>vx=trace(x);
                            vector<int>vy=trace(y);

                            if(vx.back()==vy.back()){

                                contract(c,x,y,vx,vy);
                                q.push(c);
                                p[c]=p[b[c][0]];
                                d[c]=1;
                                c++;
                            }
                            else{

                                aug=true;

                                vx.insert(vx.begin(),y);
                                vy.insert(vy.begin(),x);

                                vector<int>A=lift(vx);
                                vector<int>B=lift(vy);

                                A.insert(A.end(),B.rbegin(),B.rend());

                                for(int i=0;i<A.size();i+=2){

                                    match(A[i],A[i+1]);
                                    if(i+2<A.size())add_edge(A[i+1],A[i+2]);

                                }

                            }

                            break;
                        }


                    }

                }

            }

            if(!aug)break;

            ret++;
        }

        return ret;
    }

};

vector<pii> get_matching(vector<pii> edges){

    int n=0;
    for(int i=0;i<edges.size();i++)
        n=max(n,max(edges[i].ff,edges[i].ss));
    n++;

    blossom b(n);

    for(int i=0;i<edges.size();i++){
        b.add_edge(edges[i].ff,edges[i].ss);
    }

    vector<pii>ret;
    b.solve();
    for(int i=0;i<n;i++){
        if(b.mate[i]==-1)continue;

        ret.pb({i,b.mate[i]});

        b.mate[b.mate[i]]=-1;
        b.mate[i]=-1;

    }

    return ret;
}
