ll gilbertOrder(int x, int y, int pow) {

	if(pow==0){
        return 0;
	}

	int bsize=(1<<(pow-1));
    int upb=bsize-1;

	int bx=x/bsize;
	int by=y/bsize;

	x%=bsize;
	y%=bsize;

	if(bx==0 && by==0)return gilbertOrder(y,x,pow-1);
	if(bx==1 && by==0)return (ll)bsize*bsize+gilbertOrder(x,y,pow-1);
	if(bx==1 && by==1)return 2*(ll)bsize*bsize+gilbertOrder(x,y,pow-1);
	if(bx==0 && by==1)return 3*(ll)bsize*bsize+gilbertOrder(upb-y,upb-x,pow-1);

}
