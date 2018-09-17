/* -------------------------------- */
/* Name: MD. Khairul Basar          */
/* Institute: HSTU                  */
/* Dept: CSE                        */
/* Email: khairul.basar93@gmail.com */
/* -------------------------------- */

#include <bits/stdc++.h>
/* all header files */

#define fs            first
#define sc            second
#define sp            printf(" ")
#define nl            printf("\n")
#define pb(a)         push_back(a)

#define setzero(a)    memset(a,0,sizeof(a))
#define setneg(a)     memset(a,-1,sizeof(a))
#define setinf(a)     memset(a,126,sizeof(a))

#define tc1(x)        printf("Case %d: ",x)
#define tc2(x)        printf("Case #%d: ",x)
#define tc3(x)        printf("Case %d:\n",x)
#define tc4(x)        printf("Case #%d:\n",x)

#define iin(x)        scanf("%d",&x)
#define din(x)        scanf("%lf",&x)
#define lin(x)        scanf("%lld",&x)
#define clin(x)       scanf("%I64d",&x)

#define pr1(x)        cout<<x<<"\n"
#define pr2(x,y)      cout<<x<<" "<<y<<"\n"
#define pr3(x,y,z)    cout<<x<<" "<<y<<" "<<z<<"\n"
#define pr4(w,x,y,z)  cout<<w<<" "<<x<<" "<<y<<" "<<z<<"\n"
#define fast          ios::sync_with_stdio(0)
#define read          freopen("input.txt","r",stdin)
#define write         freopen("output.txt","w",stdout)
#define prflag1(flag) printf("%s\n",(flag)?"YES":"NO")
#define prflag2(flag) printf("%s\n",(flag)?"Yes":"No")
#define prflag3(flag) printf("%s\n",(flag)?"yes":"no")
/* macro definitions */

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int>pii;
typedef pair<LL, LL>pll;
typedef vector<int>vi;
typedef vector<LL>vll;
typedef vector<pii>vpii;
typedef vector<pll>vpll;
/* type definitions */

LL MOD_EXPO(LL b, LL p, LL m)
{
    if(p==0) return 1;
    LL ret=MOD_EXPO(b,p/2,m)%m;
    ret=(ret*ret)%m;
    return ((p&1) ? (ret*b)%m : ret%m);
}
LL POWER(LL N, LL K)
{
    LL i,ans=1;
    for(i=1; i<=K; i++) ans*=N;
    return ans;
}
int SET(int N, int pos)
{
    return (N | (1<<pos));
}
int RESET(int N, int pos)
{
    return (N & !(1<<pos));
}
bool CHECK(int N, int pos)
{
    return (N & (1<<pos));
}
/* necessary functions */

int dx4[]= {1,-1,0,0};
int dy4[]= {0,0,1,-1};
int dx6[]= {0,0,1,-1,0,0};
int dy6[]= {1,-1,0,0,0,0};
int dz6[]= {0,0,0,0,1,-1};
int dx8[]= {1,-1,0,0,-1,1,-1,1};
int dy8[]= {0,0,1,-1,1,1,-1,-1};
int dkx8[]= {-1,1,-1,1,-2,-2,2,2};
int dky8[]= {2,2,-2,-2,1,-1,1,-1};
/* direction arrays */

int tc=1;
const double eps=1e-9;
const double pi=acos(-1.0);
const long long int mn=30;
const long long int mx=1e5;
const long long int mod=1e9+7;
/* global declarations */

LL prefix[mx+5][mn+5];
LL kdivs_cnt[mn+5];
LL kdivs[mn+5];
LL arr[mx+5];
bool x[mx+5];
vll primes;
LL ksize;
LL n,k;

void sieve(void)
{
    LL i,j,s;
    s=sqrt(mx);
    for(i=2; i<=s; i++)
    {
        if(!x[i])
        {
            for(j=i+i; j<=mx; j+=i) x[j]=true;
        }
    }
    for(i=2; i<=mx; i++)
    {
        if(!x[i]) primes.push_back(i);
    }
}

void prime_factorization(LL n)
{
    LL i,s,cnt;
    vll factors;
    vll fact_cnt;
    s=sqrt(n);
    for(i=0; primes[i]<=s; i++)
    {
        if(n%primes[i]==0)
        {
            cnt=0;
            while(n%primes[i]==0)
            {
                cnt++;
                n/=primes[i];
            }
            fact_cnt.push_back(cnt);
            factors.push_back(primes[i]);
        }
    }
    if(n>1)
    {
        factors.push_back(n);
        fact_cnt.push_back(1ll);
    }
    ksize=0;
    for(i=0; i<factors.size(); i++)
    {
        ksize++;
        kdivs[i+1]=factors[i];
        kdivs_cnt[i+1]=fact_cnt[i];
    }
    return;
}

void prime_factorization(LL n, LL idx)
{
    LL i,s,cnt;
    s=sqrt(n);
    for(i=1; i<=ksize; i++)
    {
        cnt=0;
        while(n%kdivs[i]==0)
        {
            cnt++;
            n/=kdivs[i];
        }
        prefix[idx][i]=prefix[idx-1][i] + cnt;
    }
    return;
}

LL BS(LL low, LL high)
{
    LL i,mid,ans,a,b,idx;
    ans=-1;
    idx=low-1;
    while(low<=high)
    {
        mid=(low+high)/2;
        for(i=1; i<=ksize ; i++)
        {
            a=kdivs[i];
            b=kdivs_cnt[i];
            if(prefix[mid][i]-prefix[idx][i] < b) break;
        }
        if(i>ksize)
        {
            ans=mid;
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }
    }
    return ans;
}

int main()
{
    LL i,a,b,j,ans;
    sieve();

    cin>>n>>k;

    prime_factorization(k);
    for(i=1; i<=n; i++)
    {
        lin(arr[i]);
        prime_factorization(arr[i],i);
    }
    ans=0;
    for(i=1; i<=n; i++)
    {
        a=BS(i,n);
        if(a>0) ans+=(n-a+1);
    }
    pr1(ans);
    return 0;
}