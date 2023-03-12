/*

    idea:

        observations: the 2 given operations can be considered this way:

            operation a: cyclic shift in the array(actually doesnt contribute to changing the order of elements)
            operation b: a cyclic shift of any 3 consecutive elements(using the operation a this can be easily done, by just shifting the triplet to the begining of the array)

        we will leave out the shifting using a because it doesnt contribute to actual change of the order of elements, but
        we will consider just the operation b(which cyclic shifts any 3 consecutive elements) and sort our array so that we have
        the right order of elements, which in the end we will shift how we like

            for example:  456123
            this is valid as our solution for our modified problem, because we can shift that one with operation a to make it the real solution

        lets try to construct our order one by one
        so first we have our 1 somewhere
        nothing to do with it
        then we move on to the next element, 2
        we need to see if we can put it right after 1
        with our opB(operation b) we can actually push an element 2 positions to the left, we do this until we reach the wanted position
        if we end up in the wanted position, we r good, or else, we end up in a position that is 1 position to the right of our wanted position
        with opB if we have more than 2 elements undone we can rotate those elements to make our element fit in the wanted position

        so we can solve the order upto n-2 for sure
        what about the rest?

        if n is even we can definately push our element into the wanted position jsut by jumping by 2 position(because we can visit every position with that move
        because n+1(number of positions to fit our element) and 2(length of our jump) are coprime)

        if n is odd then we have 2 cases:
            in this case because the cyclic shift is an even permutation, and opB is an even permutation, by composing those permutation our initial permutation
            cant change parity

            so if our initial permutation is odd in parity then the answer is NO

            else we can definately reach our wanted order, and here is why:
                because our permutation will always be even, and we know that we can solve any permutation upto n-2
                that means that the n-1 and n will be in such an order that it forms even number of inversions, and
                the only way that is possible is with order n-1,n, and thats our wanted order so we will always find our answer
                in that case

        complexity: O(n^2)

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef pair<int,char> pic;
const int maxn=2010;
vector<pic>rez;
int n,cp,a[maxn],pos[maxn];
void rotation3(int x){

    int id[3]={x%n,(x+1)%n,(x+2)%n};

    int pom=a[id[0]];
    int p0=a[id[0]];
    int p1=a[id[1]];
    int p2=a[id[2]];

    a[id[0]]=p2;
    pos[p2]=id[0];

    a[id[2]]=p1;
    pos[p1]=id[2];

    a[id[1]]=p0;
    pos[p0]=id[1];

}
int dist(int x,int y){
    swap(x,y);
    if(x<y)return y-x;
    else return n-x+y;
}
void rot3(int x,int val){
    if(cp!=x){
        rez.pb({dist(cp,x),'a'});
        cp=x;
    }
    rez.pb({val,'b'});
    for(int i=1;i<=val;i++)rotation3(x);
}
int inversions(){

    int ret=0;

    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(a[i]>a[j])ret++;

    return ret;
}
bool isNO(){

    if(n%2==0)return false;

    if(inversions()%2==1)return true;

    return false;
}
int find_num(int x){
    return pos[x];
}
void go(){

    for(int i=2;i<=n;i++){
        if(find_num(i)==(find_num(i-1)+1)%n)continue;

        if(i<=n-2){

            while((pos[i-1]+1)%n!=pos[i] && (pos[i-1]+2)%n!=pos[i])
                rot3((pos[i]-2+n)%n,1);

            if((pos[i-1]+1)%n==pos[i])continue;
            else rot3((pos[i]-1+n)%n,2);
        }
        else{

            if(n%2==0){

                while((pos[i-1]+1)%n!=pos[i])
                    rot3((pos[i]-2+n)%n,1);


            }
            else return;
        }

    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        pos[a[i]]=i;
    }

    if(n==1){
        printf("%d\n",0);
        return 0;
    }
    if(n==2){
        if(a[0]==1)printf("%d\n",0);
        else printf("1\n1a\n");
        return 0;
    }

    if(isNO()){
        printf("NIE DA SIE\n");
        return 0;
    }

    go();

    if(cp!=pos[1])rez.pb({dist(cp,pos[1]),'a'});

    vector<pic>rez2;
    if(rez.size()>0)rez2.pb(rez[0]);
    for(int i=1;i<rez.size();i++)
        if(rez[i].ss==rez2.back().ss)rez2[rez2.size()-1].ff+=rez[i].ff;
        else rez2.pb(rez[i]);

    printf("%d\n",rez2.size());
    for(int i=0;i<rez2.size();i++){
        printf("%d%c ",rez2[i].ff,rez2[i].ss);
    }
    printf("\n");


    return 0;
}
