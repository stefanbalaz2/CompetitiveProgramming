#include <bits/stdc++.h>

using namespace std;

int n,A[10001],DP[10002][2],l,r,M[10002][2],s,u;

int main()
{
    for(int i=1; i<=10001; i++)
    {
        DP[i][0] = 2000000001;
        DP[i][1] = 2000000001;
    }
    while(scanf("%d",&n)==1)
    {
        u = 0;

        vector<int>dp;

        for(int i=1; i<=n; i++)
        {
            scanf("%d",&A[i]);
            l = 0;
            r = M[i-1][0] + 1;


            while(l+1<r)
            {
                s = (l+r)/2;
                if(DP[s-1][0]<A[i] && DP[s][0]>=A[i])
                {
                    r = s;
                }
                else
                {
                    l = s;
                }
            }
            if(DP[r-1][0]<A[i] && DP[r][0]>=A[i])
            {
                DP[r][0] = A[i];
                M[i][0]=r;
                M[i][0] = max(M[i-1][0],r);
            }
            else
            {
                M[i][0] = M[i-1][0];
            }


            int rez=0;
            if(dp.size()==0){
                dp.push_back(a[i]);
                rez=0;
            }
            else if(dp[dp.size()-1]<A[i]){
                dp.push_back(A[i]);
                rez=dp.size()-1;
            }
            else{

                l=0;
                r=dp.size()-1;

                while(l<=r){

                    sr=(l+r)/2;

                    if(dp[sr]>=A[i]){
                        r=sr-1;
                        rez=sr;
                    }
                    else l=sr+1;

                }

            }

            M[i][0]=rez+1;/// M[i][0] je najveci LIS koji se zavrsava na i

        }

        for(int i=n; i>=1; i--)
        {
            l = 0;
            r = M[i+1][1] + 1;
            while(l+1<r)
            {
                s = (l+r)/2;
                if(DP[s-1][1]<A[i] && DP[s][1]>=A[i])
                {
                    r = s;
                }
                else
                {
                    l = s;
                }
            }
            if(DP[r-1][1]<A[i] && DP[r][1]>=A[i])
            {
                DP[r][1] = A[i];
                M[i][1] = max(M[i+1][1],r);
            }
            else
            {
                M[i][1] = M[i+1][1];
            }
            u = max(u,min(M[i][0],M[i][1])*2-1);
        }
        DP[0][0] = 0;
        DP[0][1] = 0;
        for(int i=1; i<=10001; i++)
        {
            //printf("%d: %d %d\n",i,M[i][0],M[i][1]);
            M[i][0] = 0;
            M[i][1] = 0;
            DP[i][0] = 2000000001;
            DP[i][1] = 2000000001;
        }
        printf("%d\n",u);
    }
    return 0;
}
