struct cd{

    double x,y;

    cd(double a,double b){x=a;y=b;}
    cd(double a){x=a;y=0;}
    cd(){x=0,y=0;}

    void real(double a){x=a;}
    void imag(double a){y=a;}

    double real(){return x;}
    double imag(){return y;}


    void operator *= (const cd &b){double pom=x;x=x*b.x-y*b.y;y=pom*b.y+y*b.x;}
    cd operator *(const cd &b){return cd(x*b.x-y*b.y,x*b.y+y*b.x);}

    void operator /= (const double &b){x/=b;y/=b;}
    cd operator / (double b){return cd(x/b,y/b);}

    void operator -=(const cd &b){x-=b.x;y-=b.y;}
    cd operator -(const cd &b){return cd(x-b.x,y-b.y);}

    void operator +=(const cd &b){x+=b.x;y+=b.y;}
    cd operator +(const cd &b){return cd(x+b.x,y+b.y);}

    cd conj(){return cd(x,-y);}
};
