namespace fwht{

    struct xorpoly{

        vector<int>a;
        int n;

        xorpoly(int n){
            this->n=n;
            a.resize(n);
        }
        xorpoly(vector<int>v){
            a=v;
            n=a.size();
        }

        void resize(int n){
            this->n=n;
            a.resize(n);
        }

        void fft(vector<int>&a,bool invert){

            int n=a.size();

            for(int len=2;len<=n;len<<=1){
                int hlen=len/2;

                for(int i=0;i<n;i+=len){
                    for(int j=0;j<hlen;j++){

                        int pom1=a[i+j];
                        int pom2=a[i+j+hlen];

                        a[i+j]=add(pom1,pom2);
                        a[i+j+hlen]=sub(pom1,pom2);

                    }
                }

            }

            if(invert){
                int invn=invv(n);
                for(int i=0;i<a.size();i++)a[i]=mul(a[i],invn);
            }
        }

        vector<int>xorconv(vector<int>a,vector<int>b){
            fft(a,0);
            fft(b,0);
            for(int i=0;i<a.size();i++)a[i]=mul(a[i],b[i]);
            fft(a,1);
            return a;
        }


        xorpoly operator *(xorpoly b){
            return xorpoly(xorconv(a,b.a));
        }

        xorpoly operator +(xorpoly b){
            xorpoly ret(n);
            for(int i=0;i<n;i++)ret[i]=add(a[i],b[i]);
            return ret;
        }

        int& operator [](int x){
            assert(x<n);
            return a[x];
        }


    };

}
