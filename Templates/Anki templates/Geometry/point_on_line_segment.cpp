struct pt{

    int x,y;

    pt(int x,int y){
        this->x=x;
        this->y=y;
    }
    pt(){}

    pt operator -(pt b){
        return pt(x-b.x,y-b.y);
    }

    pt operator +(pt b){
        return pt(x+b.x,y+b.y);
    }

    int cross(pt b){
        return x*b.y-y*b.x;
    }

    bool operator ==(pt b){
        return (x==b.x && y==b.y);
    }

    bool operator !=(pt b){
        return !(x==b.x && y==b.y);
    }

    double dist(pt b){
        return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
    }

};

bool is_on_line(pt ppt,pt a,pt b){

    if(a.x>b.x || (a.x==b.x && a.y>b.y) )swap(a,b);

    if(a.x!=b.x){
        if(ppt.x<a.x || ppt.x>b.x)return false;
    }
    else{
        if(ppt.y<a.y || ppt.y>b.y)return false;
    }

    b=b-a;
    ppt=ppt-a;

    if(b.cross(ppt)!=0)return false;
    return true;
}
