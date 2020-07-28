/*

    link: https://szkopul.edu.pl/problemset/problem/Hhip15j-8Ro2dOb_4oB98C-G/site/?key=statement

    idea and thinking path:


        it is obvious to see that we can make every a[i]=(a[i]+1)%s

        we will consider every i from 0 to s-1 as a node, and adding
        an element with value x to our current state(or sum, however u wanna call it)
        will get us to a node (i+x)mod s
        i considered it as a graph so i could explain more easily

        now, we have to construct a permutation of a[] which yields minimum
        number of times of stepping onto s-1

        first thought: can we somehow build our permutation element by element? and if we can, can we somehow try to get the result to be zero?
        lets see, when we want to add our element to the end of our current permutation
        we have to know whats the sum modulo s of our elements in our current permutation
        and we also have to know which elements were taken, in order not to overtake something
        this would yield a too big complexity

        can we somehow get rid of needing to know what elements were taken?
        if we take them in some order then we dont have to worry about it, lets take them in some arbitrary order
        when we wanna put them in our permutation, we can put the between any two elements(but this wont be important in the rest of the editorial)

        how do we get rid of our need to know the sum?
        actually, only thing we wanna evade is stepping on s-1,so when we are about to step on it by placing our ith element
        we can just place i+1th element and then place the ith element(of course, if those 2 are different and if the i+1th is different from 0)
        so in our 2nd subtask, we can just try to put any element on the its position in the permutation
        and if it will make us step on s-1, then we pick any other element, and if we dont have any other, than it is okay to step
        on s-1, that means that if a[] has all distinct elements, our solution is always 0

        how do we build our solution on this observatoin?
        lets say that we have just 1 group of same elements that has more than one element, and the rest of the groups have 1 element
        lets call that group P
        so if we solve P group somehow, then we definately have an answer 0 because we are left with an array of distinct elements
        how do we solve P?
        we can greedily take from P as long as we can(as long as we dont step on s-1) and when we cant take anymore
        then we take some other element, which gives us some bonus steps until the next time we reach s-1 by adding elements from P
        why is this correct?
        lets call elements of P as p
        some element of different value from p will be x
        lets say that we dont take from P as long as we can and put in another element x before we reach our final step with P
        it looks something like this:

            putting p till we can:

                p p p p x p p.. (number 1)

            not putting p till we can:

                p p x p p p p.. (number 2)

        lets call a p-step, a step that goes from i to i+p
        lets call the (s-1)-p the last step(the position from which u cant take a p-step without increasing the result)
        what can we see here? well because our last step is at the sum p+p+p+p(pppp from our number 1) and we evaded it
        with x-step, and in number 2 if we leave the x there, it will either cause us to hit s-1 faster and it definately wont decrease our result
        because if it doesnt make us hit s-1 faster then nothing happens upto the 5th position and we can put it in the 5th position to make
        it look like the number 1 because it wont increase our result and because it wont change anything that is right from our x
        because the sum upto the 5th position inclusive(in our example) stays the same

        but what about taking more than one element that is !=p in a row?
        that also doesnt improve our answer
        why? so we concluded that taking p greedily until the last step is the best
        if we take more than one element !=p in a row it looks like this

            p p p p x y p p p p p p w...

        remember that here also we take greedily p as long as we can,but putting xy doesnt make sense because lets say it was first like this

            p p p p x p p p p p y...

        and then we brought y back to x

            p p p p x y p p p p p...

        it either made us hit s-1 faster or it made no difference because at this position

             p p p p x p p p p p y| ...
             p p p p x y p p p p p| ...

        the sums are again the same and we continue from the same state


        lets call a pile, a pile of same values from a[]
        what happens when we have multiple piles with size>1?
        first thought was that we should somehow reduce our problem from x piles to x-1 piles
        we can take the smallest pile and remove it like we did it in the example above,
        because it is the smallest we will definately be able to remove it completely(bcs at least 1 other element is needed to remove
        1 element from it, and it is the smallest) and then we are left with x-1 piles
        so in the end we are left with just 1 pile which we greedily take from, but this idea doesnt seem too right to me(and it actually isnt,u can prove this for practice)
        lets look at the piles in space, bcs we can see more information that way, and lets sort them because giving them some order
        gives us easier manipulation


            *
            **
            **
            ****
            ****
            *****

        our first idea was a sweepline lets say from left to right,
        in our example above(with distinct elements) it is just one row

            ***********

        and we actually figured out how to clear a single row!!
        so we could try doing a sweepline from up to down
        lets say that we first encounter a row of >=2 elements
        we can clear it easily
        if we wanna take an element and cant take it, we will always have another one to take
        and if we are left in the row with just 1 element then if that row is the bottom row then we take it without increasing the answer
        and if it isnt the bottom row then we can take and element from the row below and then take the element from our current row(we will always have it
        because we had >=2 elements in our row)
        its easy to see why this works
  -      and then we cleared, and by doing this we can clear all the rows till the end without increasing the result, so it will definately be 0

        but what if in the beggining of sweeping we have a row with just one element?
        lets recall a few things:

            -if we get to have >=2 elements in a row we can solve it without increasing the result
            -while clearing a pile the optimal way to do it is taking from that pile while we can, and then taking some other element and continuing the process

        if we could somehow bring our bigest pile to be equal to some other pile, we have our solution
        lets analyse a bit:

            - if we cant clear the biggest pile using elements from other piles then we will be left with some amount on that pile which we must take one by one
            and our result probably wont be zero

            - if we can clear the biggest pile, that means that while doing that, we definately got it to a level same as some other pile, so we can get to that state and
            do our sweeping algorithm from there

            - while we are greedily taking from the biggest pile, when we cant take anymore, we proved that its optimal to take just one other element and
            then continue with taking from the biggest pile, that means that every element decreases our biggest pile by a strict value,so order doesnt matter

        now we can construct our final solution:

            - construct the piles
            - try to bring the biggest pilo to 0 size by greedily taking from it, and when we cant, taking ANY other element
            - if at some point our biggest pile is equal to some other pile, run our sweep algorithm
              else we will reach a point where our biggest pile is the only pile left, and we just simulate the process and calculate the result



        why is this correct?

        first case: we can get the biggest pile to a size of some other pile => result=0, we cant do better than that
        second case: the pile that will always be left last is the biggest pile(because otherwise we would have case 1 which is a contradiction)
        and the best score we can achieve is by decreasing the biggest pile as much as we can before its the only one left,
        because when its the only one left we cant evade s-1, and by making that pile the smallest as we can we make it step on s-1 the least
        number of times


        notice: all the zeroes from a[] we can put anywhere, get rid of them, because they make our algorithm false, i put them all first in the result

        ** there is probably a thing or two which i forgot to prove correctness for, but that can be proved using the concepts i used while proving the things above **

*/
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ff first
#define ss second
#define ll long long
typedef pair<int,int> pii;
typedef set<pii>::iterator sit;
const int maxn=5e5+10;
const int maxa=2*maxn;
int k,maxx,rezcnt,n;
vector<int>mapa[maxa],rez;
struct ss{
    int val;
    vector<int>pos;
}niz[maxn];
int br;
bool srt(int x,int y){
    return niz[x].pos.size()>niz[y].pos.size();
}
void regulate(int &x){
    x%=k;
    if(x<0)x+=k;
}
void reorder(){

    int ind[maxn];
    for(int i=1;i<k;i++){
        if(mapa[i].size()==0)continue;

        niz[++br].val=i;
        niz[br].pos=mapa[i];
        ind[br]=br;
    }
    sort(ind+1,ind+br+1,srt);

    ss niz2[br+1];
    for(int i=1;i<=br;i++)niz2[i]=niz[i];
    for(int i=1;i<=br;i++)niz[i]=niz2[ind[i]];
}
int skidanje(){

    int curr=0;
    for(int i=2;i<=br;i++){

        while(1){
            if(niz[1].pos.size()==0)return curr;
            if(niz[1].pos.size()==max(niz[i+1].pos.size(),niz[i].pos.size()))return curr;
            if(curr+maxx==k-1)break;
            curr+=maxx;
            regulate(curr);
            rez.pb(niz[1].pos.back());
            niz[1].pos.pop_back();
        }

        if(niz[i].pos.size()!=0){
            curr+=niz[i].val;
            regulate(curr);
            rez.pb(niz[i].pos.back());
            niz[i].pos.pop_back();
            i--;
        }

    }

    if(niz[1].pos.size()>0){

        int kk=niz[1].pos.size();
        for(int i=1;i<=kk;i++){

            if(curr+maxx==k-1){
                rez.pb(niz[1].pos.back());
                niz[1].pos.pop_back();
                curr+=maxx+1;
                regulate(curr);
                if(i<kk)rezcnt++;
            }
            else{
                rez.pb(niz[1].pos.back());
                niz[1].pos.pop_back();
                curr+=maxx;
                regulate(curr);
            }

        }

    }

    return curr;
}
void finisher(int curr){

    if(niz[1].pos.size()==0)return;

    set<pii>st;
    for(int i=1;i<=br;i++){
        if(niz[i].pos.size()==0)continue;
        st.insert({-niz[i].pos.size(),i});
    }

    while(st.size()){

        int x=(*st.begin()).ss;
        if(st.size()==1){
            rez.pb(niz[x].pos.back());
            niz[x].pos.pop_back();
            break;
        }

        if(niz[x].val+curr==k-1){
            sit it=st.begin();
            it++;
            x=(*it).ss;
        }

        st.erase({-niz[x].pos.size(),x});
        rez.pb(niz[x].pos.back());
        niz[x].pos.pop_back();
        curr+=niz[x].val;
        regulate(curr);
        if(niz[x].pos.size()>0)st.insert({-niz[x].pos.size(),x});
    }

}
int main(){

    ///freopen("test.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    scanf("%d %d",&n,&k);
    for(int i=1;i<=n;i++){
        int a;
        scanf("%d",&a);
        a++;
        a%=k;
        mapa[a].pb(i);
    }

    if(mapa[0].size()>0){
        for(int i=0;i<mapa[0].size();i++)rez.pb(mapa[0][i]);
    }

    reorder();
    maxx=niz[1].val;

    finisher(skidanje());

    printf("%d\n",rezcnt);
    for(int i=0;i<rez.size();i++){
        printf("%d ",rez[i]);
    }

    return 0;
}
