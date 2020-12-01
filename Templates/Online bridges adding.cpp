struct dsu{

    int p1[maxn],p2[maxn],p[maxn];
    int sz1[maxn],sz2[maxn];
    int bridge=0;
    int pos[maxn];

    void init(){

        for(int i=1;i<maxn;i++){
            p1[i]=i;
            p2[i]=i;
            p[i]=0;
            sz1[i]=1;
            sz2[i]=1;
            bridge=0;
            pos[i]=0;
        }

    }


    int root1(int x){
        if(p1[x]==x)return x;
        else return p1[x]=root1(p1[x]);
    }

    int root2(int x){
        if(p2[x]==x)return x;
        else return p2[x]=root2(p2[x]);
    }

    void reroot(int x,int y){/// reroot tree x into y

        y=root2(y);
        sz1[y]=sz1[x];
        p1[y]=y;
        p1[x]=y;
        int prv=0;
        while(y!=0){

            int pp=root2(p[y]);

            p[y]=prv;
            prv=y;

            y=pp;
        }

    }

    int get_lca(int x,int y){

        int ret=-1;
        vector<int>rbp;
        while(1){

            if(pos[x] && x!=0){
                ret=x;
                break;
            }
            pos[x]=1;
            rbp.pb(x);
            if(pos[y] && y!=0){
                ret=y;
                break;
            }
            pos[y]=1;
            rbp.pb(y);

            x=root2(p[x]);
            y=root2(p[y]);
        }

        for(int i=0;i<rbp.size();i++)pos[rbp[i]]=0;

        return ret;
    }

    int merge_cycle(int x,int y){

        int ret=0;
        x=root2(x);
        y=root2(y);

        if(x==y)return 0;

        int lca=get_lca(x,y);

        while(x!=lca){

            int pp=root2(p[x]);
            p2[x]=pp;

            x=pp;

            ret++;
        }

        while(y!=lca){

            int pp=root2(p[y]);
            p2[y]=pp;

            y=pp;

            ret++;
        }

        return ret;
    }

    void join(int x,int y){

        x=root2(x);
        y=root2(y);

        int xr1=root1(x);
        int yr1=root1(y);

        if(xr1!=yr1){

            bridge++;

            if(sz1[xr1]<sz1[yr1]){
                swap(xr1,yr1);
                swap(x,y);
            }

            reroot(yr1,y);

            sz1[xr1]+=sz1[y];
            p1[y]=xr1;
            p[y]=x;
        }
        else{

            if(x==y)return;
            bridge-=merge_cycle(x,y);
        }

    }

}d;
