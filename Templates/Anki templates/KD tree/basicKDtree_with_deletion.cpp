namespace my_kdtree{


    struct my_kdt{

        vector<point>pts;
        vector<pair<pii,int>>tree;

        void build(int x,int l,int r,vector<pair<int,point>>&niz,int dep){

            if(l>r)return;
            if(l==r){
                tree[x].ff.ff=niz[l].ff;
                tree[x].ff.ss=1;
                tree[x].ss=1;
                return;
            }

            int mid=(l+r)/2;

            if(dep==0)sort(niz.begin()+l,niz.begin()+r+1,[](pair<int,point> &a,pair<int,point> &b){
                return a.ss.x<b.ss.x;
            });
            else sort(niz.begin()+l,niz.begin()+r+1,[](pair<int,point> &a,pair<int,point> &b){
                return a.ss.y<b.ss.y;
            });

            tree[x].ff.ff=niz[mid].ff;
            tree[x].ff.ss=1;
            tree[x].ss=1;

            build(x*2,l,mid-1,niz,dep^1);
            build(x*2+1,mid+1,r,niz,dep^1);

            tree[x].ff.ss+=tree[x*2].ff.ss+tree[x*2+1].ff.ss;

        }

        my_kdt(vector<point>&pts){

            this->pts=pts;
            tree.resize(4*pts.size()+1);

            vector<pair<int,point>>niz(pts.size());
            for(int i=0;i<pts.size();i++)niz[i]={i,pts[i]};

            ///cout<<"start build"<<endl;
            build(1,0,pts.size()-1,niz,0);
            ///cout<<"end build"<<endl;

        }

        inline ll get_dist(point &p,point &c){
            return (p.x-(ll)c.x)*(p.x-(ll)c.x)+(p.y-(ll)c.y)*(p.y-(ll)c.y);
        }
        void update_best(point target,int &best,int id){

            if(best==-1){
                best=id;
                return;
            }

            if(get_dist(pts[best],target)>get_dist(target,pts[id]))best=id;

        }
        void nearest_neighbour(int x,point &target,int &best_id,int dep){

            if(tree[x].ff.ss==0)return;

            int id=tree[x].ff.ff;

            int nxt_node,other_node;
            nxt_node=x*2;
            other_node=x*2+1;
            if(dep==0){
                if(target.x<=pts[id].x){}
                else swap(nxt_node,other_node);
            }
            else{
                if(target.y<=pts[id].y){}
                else swap(nxt_node,other_node);
            }

            if(tree[x].ss)update_best(target,best_id,id);

            nearest_neighbour(nxt_node,target,best_id,dep^1);

            ll pom=(target.x-(ll)pts[id].x)*(target.x-(ll)pts[id].x);
            if(dep)pom=(target.y-(ll)pts[id].y)*(target.y-(ll)pts[id].y);

            ///cout<<get_dist(pts[best_id],target)<<" "<<pom<<"  DIST"<<endl;

            if(best_id==-1 || get_dist(pts[best_id],target)>pom){
                nearest_neighbour(other_node,target,best_id,dep^1);
                wrong_cnt++;
            }

        }

        void delete_node(int x,point val,int dep){

            int id=tree[x].ff.ff;

            if(pts[id].x==val.x && pts[id].y==val.y){
                tree[x].ff.ss--;
                tree[x].ss--;
                return;
            }

            if(dep==0){
                if(val.x<=pts[id].x)delete_node(x*2,val,dep^1);
                else delete_node(x*2+1,val,dep^1);
            }
            else{
                if(val.y<=pts[id].y)delete_node(x*2,val,dep^1);
                else delete_node(x*2+1,val,dep^1);
            }

            tree[x].ff.ss=tree[x].ss+tree[x*2].ff.ss+tree[x*2+1].ff.ss;

        }

    };

}
