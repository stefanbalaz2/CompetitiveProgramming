struct FFT{


    /// set max power of 2

    /// mul is faster than mul_more_precision, but cant handle bigger numbers

    /// online fft supports anything, u might have to change the type of multiplication it does from mul_more_precision to mul
    /// mul supports (max_element^2)*n<1e18, types: primitive types, complex(struct cd)
    /// mul_more_precision supports the rest, types: primitive types



    const static int max_power_of_2=19;/// set this
    const static int max_polynomial_sz=(1<<max_power_of_2);

    bool done_precalculation=false;

    template<class base,class T>
    inline bool instanceof(){
        return is_base_of<base,T>::value;
    }

    struct cd{

        double x,y;

        cd(double a,double b){x=a;y=b;}
        cd(double a){x=a;y=0;}
        cd(){x=0,y=0;}

        operator long long(){return (long long)x;}

        void real(double a){x=a;}
        void imag(double a){y=a;}

        double real(){return x;}
        double imag(){return y;}


        void operator *= (const cd &b){double pom=x;x=x*b.x-y*b.y;y=pom*b.y+y*b.x;}
        cd operator *(const cd &b){return cd(x*b.x-y*b.y,x*b.y+y*b.x);}

        void operator *= (const double &b){x*=b;y*=b;}
        cd operator *(const double &b){return cd(x*b,y*b);}

        void operator *= (const long long &b){x*=b;y*=b;}
        cd operator *(const long long &b){return cd(x*b,y*b);}


        void operator /= (const double &b){x/=b;y/=b;}
        cd operator / (double b){return cd(x/b,y/b);}

        void operator -=(const cd &b){x-=b.x;y-=b.y;}
        cd operator -(const cd &b){return cd(x-b.x,y-b.y);}

        void operator +=(const cd &b){x+=b.x;y+=b.y;}
        cd operator +(const cd &b){return cd(x+b.x,y+b.y);}

        cd conj(){return cd(x,-y);}
        static cd round(cd a){return cd(std::round(a.x),std::round(a.y));}
        static double round(double a){return std::round(a);}
    };

    struct cd2{

        cd x,y;

        cd2(cd a,cd b){x=a;y=b;}
        cd2(cd a){x=a;y=cd(0,0);}
        cd2(){x=cd(0,0),y=cd(0,0);}

        void real(cd a){x=a;}
        void imag(cd a){y=a;}

        cd real(){return x;}
        cd imag(){return y;}


        void operator *= (const cd2 &b){cd pom=x;x=x*b.x-y*b.y;y=pom*b.y+y*b.x;}
        cd2 operator *(const cd2 &b){return cd2(x*b.x-y*b.y,x*b.y+y*b.x);}

        void operator *= (const cd &b){cd pom=x;x=x*b.x-y*b.y;y=pom*b.y+y*b.x;}
        cd2 operator *(const cd &b){return cd2(x*b.x-y*b.y,x*b.y+y*b.x);}


        void operator /= (const double &b){x/=b;y/=b;}
        cd2 operator / (double b){return cd2(x/b,y/b);}

        void operator -=(const cd2 &b){x-=b.x;y-=b.y;}
        cd2 operator -(const cd2 &b){return cd2(x-b.x,y-b.y);}

        void operator +=(const cd2 &b){x+=b.x;y+=b.y;}
        cd2 operator +(const cd2 &b){return cd2(x+b.x,y+b.y);}

        cd2 conj(){return cd2(x,cd()-y);}
    };


    cd prekw[max_polynomial_sz+10];
    const double PI=acos(-1);
    void prek_w(){

        for(int i=0;i<max_polynomial_sz;i++){
            double angle=2*PI*i/max_polynomial_sz;
            cd wlen(cos(angle),sin(angle));
            prekw[i]=wlen;
        }
    }

    template<class T>
    void fft(vector<T> &a,bool invert){

        int n=a.size();

        for(int i=1,j=0;i<n;i++){

            int bit=n>>1;
            for(;bit&j;bit>>=1)j^=bit;
            j^=bit;

            if(i<j)swap(a[i],a[j]);

        }

        for(int len=2;len<=n;len<<=1){

            int hlen=len/2;
            int angle=(max_polynomial_sz/len)*(invert?-1:1);

            for(int i=0;i<n;i+=len){
                int w=0;
                for(int j=0;j<hlen;j++){


                    T pom1=a[i+j];
                    T pom2=a[i+j+hlen]*prekw[w];

                    a[i+j]=pom1+pom2;
                    a[i+j+hlen]=pom1-pom2;

                    w+=angle;
                    if(w<0)w+=max_polynomial_sz;
                }
            }

        }


    }


    template<typename Q1,typename Q2,typename Q3>
    vector<Q1> mul(vector<Q1> &a,vector<Q1> &b,long long mod_selected,bool round_selected,Q2 qtp2,Q3 qtp3){

        if(!done_precalculation){
            prek_w();
            done_precalculation=1;
        }

        vector<Q2>fa;

        int n=1;
        while(n<a.size()+b.size())n<<=1;

        fa.resize(n);
        for(int i=0;i<n;i++){
            fa[i].real((i<a.size())?a[i]:Q1());
            fa[i].imag((i<b.size())?b[i]:Q1());
        }

        vector<Q2>fa2(n);

        fft(fa,0);
        Q2 pom1,pom2,A,B;
        for(int i=0;i<n;i++){

            pom1=fa[i];
            pom2=fa[(n-i)%n].conj();

            A=(pom1+pom2)*cd(0.5,0)/(double)n;
            B=(pom1-pom2)*cd(0,-0.5);

            fa2[i]=A*B;
        }
        fa=fa2;

        fft(fa,1);

        vector<Q1>ret(n);
        for(int i=0;i<n;i++){
            if(round_selected){

                Q3 rq=cd::round(fa[i].real());

                if(mod_selected){
                    ret[i]=((long long)rq)%mod_selected;
                }
                else ret[i]=rq;
            }
            else{
                Q3 rq=fa[i].real();

                if(mod_selected)ret[i]=((long long)rq)%mod_selected;
                else ret[i]=rq;
            }
        }

        return ret;

    }

    template<typename Q1>
    vector<Q1> mul(vector<Q1> &a,vector<Q1> &b,long long mod_selected,bool round_selected){

        if(instanceof<cd,Q1>()){
            cd qtp3=cd();
            cd2 qtp2=cd2();
            return mul(a,b,mod_selected,round_selected,qtp2,qtp3);
        }
        else{
            double qtp3=double();
            cd qtp2=cd();
            return mul(a,b,mod_selected,round_selected,qtp2,qtp3);
        }
    }



    template<typename Q1,typename Q2,typename Q3>
    vector<Q1> mul_more_precision(vector<Q1> &a,vector<Q1> &b,long long max_el,long long mod_selected,bool round_selected,Q2 qtp2,Q3 qtp3){

        if(!done_precalculation){
            prek_w();
            done_precalculation=1;
        }

        vector<Q2>fa(a.size()),fb(b.size());

        int n=1;
        while(n<a.size()+b.size())n<<=1;

        const long long m=sqrt(max_el);
        const long long m2=m*m;

        for(int i=0;i<a.size();i++)fa[i]=Q2(a[i]%m,a[i]/m);
        for(int i=0;i<b.size();i++)fb[i]=Q2(b[i]%m,b[i]/m);
        fa.resize(n);
        fb.resize(n);

        fft(fa,0);
        fft(fb,0);

        Q2 pom1,pom2,A1,A2,B1,B2;
        for(int i=0;i<=n-i;i++){

            int op=(n-i)%n;

            pom1=fa[i];
            pom2=fa[op].conj();
            A1=(pom1+pom2)*cd(0.5,0)/n;
            A2=(pom1-pom2)*cd(0,-0.5)/n;

            pom1=fb[i];
            pom2=fb[(n-i)%n].conj();
            B1=(pom1+pom2)*cd(0.5,0);
            B2=(pom1-pom2)*cd(0,-0.5);

            fa[i]=A1*B1+A2*B2*cd(0,1);
            fb[i]=A1*B2+A2*B1;

            A1=A1.conj();
            A2=A2.conj();
            B1=B1.conj();
            B2=B2.conj();
            fa[op]=A1*B1+A2*B2*cd(0,1);
            fb[op]=A1*B2+A2*B1;
        }

        fft(fa,1);
        fft(fb,1);

        vector<Q1>ret(n);
        for(int i=0;i<n;i++){

            if(round_selected){
                Q3 x=cd::round(fa[i].real());
                Q3 y=cd::round(fa[i].imag());
                Q3 z=cd::round(fb[i].real());

                if(mod_selected){

                    ret[i]=((((ll)x)%mod_selected)+
                            ((((ll)z)%mod_selected)*m)%mod_selected+
                            ((((ll)y)%mod_selected)*m2)%mod_selected)%mod_selected;
                }
                else ret[i]=x+
                    z*m+y*m2;
            }
            else{
                Q3 x=cd::round(fa[i].real());
                Q3 y=cd::round(fa[i].imag());
                Q3 z=cd::round(fb[i].real());

                ret[i]=x+z*m+y*m2;
            }
        }


        return ret;
    }

    template<typename Q1>
    vector<Q1> mul_more_precision(vector<Q1> &a,vector<Q1> &b,long long max_el,long long mod_selected,bool round_selected){

        if(instanceof<cd,Q1>()){
            cd qtp3=cd();
            cd2 qtp2=cd2();
            return mul_more_precision(a,b,max_el,mod_selected,round_selected,qtp2,qtp3);
        }
        else{
            double qtp3=double();
            cd qtp2=cd();
            return mul_more_precision(a,b,max_el,mod_selected,round_selected,qtp2,qtp3);
        }
    }


    /// Modular arithmnetics
    template<typename Q,typename Q2>
    inline Q2 add(Q2 a,Q2 b,Q &mod){long long ret=a+b;if(mod==0)return ret;if(ret>=mod)ret-=mod;return ret;}
    template<typename Q,typename Q2>
    inline Q2 mul(Q2 a,Q2 b,Q &mod){if(mod==0)return a*b;return (a*1ll*b)%mod;}
    template<typename Q,typename Q2>
    inline Q2 step(Q2 base,long long pw,Q &mod){Q2 ret=1;while(pw){if(pw&1)ret=mul(ret,base,mod);base=mul(base,base,mod);pw/=2;}return ret;}
    template<typename Q,typename Q2>
    inline Q2 inv(Q2 x,Q &mod){return step(x,mod-2,mod);}


    template<typename Q,typename Q2>
    void convolve(int l1,int r1,int l2,int r2,vector<Q> &f,vector<Q> &b,Q2 mod){

        if(l2>r2)return;

        vector<Q>ff(f.begin()+l1,f.begin()+r1+1),fb(b.begin()+l2,b.begin()+r2+1);

        vector<Q>ret=mul_more_precision(ff,fb,mod,mod,true);

        for(int i=0;i<ret.size();i++)
            if(l1+l2+i<f.size())f[l1+l2+i]=add(f[l1+l2+i],ret[i],mod);

    }

    template<typename Q>
    vector<Q> online_fft(vector<Q> f,vector<Q> &b,Q mod){

        int n=f.size();
        for(int i=0;i<n-1;i++){

            f[i+1]=add(f[i+1],mul(f[i],b[1],mod),mod);
            for(int pw=2;pw<=i+1 && (i+1)%pw==0;pw<<=1)
                convolve(i-pw+1,i,pw,min(pw*2-1,n),f,b,mod);
        }

        return f;
    }


}fff;
