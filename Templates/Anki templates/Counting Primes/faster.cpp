/**

  O(n^(2/3)*logn)
  

*/

struct cps{

    vector<pair<pair<ll,ll>,int>>cand;
    vector<ll>primes;
    ll ny;

    ll calc_primes(ll n){

        ny=pow(n,0.64);
        if(n<100)ny=min(n,100ll);
        ll y=n/ny;
        primes.clear();
        vector<ll>mn(ny+1);
        for(ll p=2;p<=ny;p++){
            if(mn[p]!=0)continue;
            primes.pb(p);
            for(int j=p;j<=ny;j+=p)
                if(mn[j]==0)mn[j]=primes.size();
        }
        if(n<100)return primes.size();

        ll piy=0;
        for(int i=0;i<primes.size();i++){
            if(primes[i]>y)break;
            piy++;
        }

        //printf("%lld %lld %lld AA\n",ny,y,piy);

        int rp=primes.size()-1;
        ll F=0;
        for(int i=0;i<primes.size();i++){
            if(i>rp)break;
            if(primes[i]<=y)continue;
            ll pom=n/primes[i];
            while(primes[rp]>pom)rp--;
            F+=rp-i+1;
        }

        cand.clear();

        ll ret=phi(n,piy,1);
        ret=ret-1+piy-F;

        sort(cand.begin(),cand.end());
        fenwick ds(primes.size());
        int pt=2;
        for(auto q:cand){

            while(pt<=q.ff.ff){
                ds.add(primes.size()-mn[pt]+1,1);
                pt++;
            }

            ret+=q.ss*(ds.get(primes.size()-q.ff.ss)+1);
        }

        return ret;
    }

    ll phi(ll n,ll a,int sgn){

        if(a==0)return n;
        if(n==0)return 0;

        if(n<=ny){
            cand.pb({ {n,a},sgn });
            return 0;
        }
        return phi(n,a-1,sgn)-phi(n/primes[a-1],a-1,sgn*-1);
    }

    struct fenwick{

        vector<ll>bit;
        int n;

        fenwick(int n){
            bit.resize(n+1);
            this->n=n;
        }

        void add(int x,ll val){
            while(x<=n){
                bit[x]+=val;
                x+=(x&(-x));
            }
        }
        ll get(int x){
            ll ret=0;
            while(x){
                ret+=bit[x];
                x-=(x&(-x));
            }
            return ret;
        }

    };

};
