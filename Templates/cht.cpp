int Q=0;
struct line{

    mutable pii p;
    mutable ll x;

    bool operator <(const line &b)const {
        if(Q==0)return (*this).p<b.p;
        else return (*this).x<b.x;
    }

};
typedef multiset<line>::iterator spit;
struct cht {

    multiset<line>lines;

    void build(){
        lines.clear();
    }

    spit get_prv(spit it){
        if(it==lines.begin())return lines.end();
        it--;
        return it;
    }

    spit get_nxt(spit it){
        it++;
        return it;
    }

    bool ostaje(spit it){

        spit prv,nxt;

        prv=get_prv(it);
        nxt=get_nxt(it);

        if(nxt!=lines.end()){
            if((*nxt).p.ff==(*it).p.ff)return (*it).p.ss<(*nxt).p.ss;
        }
        if(prv!=lines.end()){
            if((*prv).p.ff==(*it).p.ff)return (*it).p.ss<(*prv).p.ss;
        }
        if(prv==lines.end() || nxt==lines.end())return true;

        if(intersection((*prv).p,(*it).p)<intersection((*prv).p,(*nxt).p))return true;
        return false;
    }

    void erase_line(spit it){

        if(it==lines.end())return;

        spit prv=get_prv(it);

        if(prv!=lines.end())intersection(prv,get_nxt(it));

        lines.erase(it);
    }

    void erase_line(pii x){
        erase_line(lines.find({x,0}));
    }

    spit ins_line(pii x){

        spit it=(lines.insert({x,0}));
        spit prv=get_prv(it);

        if(prv!=lines.end())intersection(prv);

        intersection(it);

        return it;
    }

    ll intersection(pii a,pii b){
        if(a.ff==b.ff)return 2*inf;
        return (b.ss-a.ss)/(a.ff-b.ff);
    }
    ll intersection(spit it){
        spit nxt=get_nxt(it);

        if(nxt==lines.end()){
            (*it).x=inf;
            return inf;
        }
        return intersection((*it).p,(*nxt).p);
    }
    ll intersection(spit it,spit it2){
        if(it2==lines.end()){
            (*it).x=inf;
            return inf;
        }
        ll pom=intersection((*it).p,(*it2).p);
        (*it).x=pom;
        return pom;
    }

    void add_line(pii x){

        spit it=ins_line(x);

        if(ostaje(it)){

            while(1){
                spit it2=it;
                it2++;
                if(it2==lines.end())break;
                if(ostaje(it2))break;
                erase_line(it2);
            }

            while(1){
                spit it2=it;
                if(it2==lines.begin())break;
                it2--;
                if(ostaje(it2))break;
                erase_line(it2);
            }
        }
        else erase_line(it);
    }


    ll query(ll x){
        if(lines.size()==0)return -inf;

        Q=1;
        spit it=lines.lower_bound({{-inf,-inf},x});
        Q=0;

        return (*it).p.ff*x+(*it).p.ss;
    }

}
