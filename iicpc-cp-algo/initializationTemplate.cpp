/** 
This program uses pre-written templates. 
The templates have been created before the beginning of the contest and can be found at
https://github.com/mshandilya/cptemplates
**/

//required macros and template
#include <bits/stdc++.h>
using namespace std;

//modular arithmetics
#define ma ((long) 1e9+7)
#define mb ((long) 998244353)
#define mod_a % ma
#define mod_b % mb
#define modDiv(a, b, m) (((a % m) * cp::bex(b, m-2)) % m)
#define modDiv_a(a, b) modDiv(a, b, ma)
#define modDiv_b(a, b) modDiv(a, b, mb)
//type definitions
#define ll long long
#define ld long double
#define vc vector
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;
typedef vc<int> vi;
typedef vc<ll> vl;
typedef vc<ld> vd;
typedef vc<pii> vii;
typedef vc<pll> vll;
typedef vc<pdd> vdd;
typedef vc<list<int>> adjList;
typedef vc<list<pii>> w_adjList;
typedef complex<ld> point;

//cp functions
namespace cp{
    //binary exponentiation
    ll bex(ll a, ll b, ll mod = ma) {
        ll res = 1;
        while(b) {
            if(b&1) {
                res*=a;
                res%=mod;
            }
            a*=a;
            a%=mod;
            b>>=1;
        }
        return res;
    }

    //binary logarithm (returns floor of log(a)/log(2))
    int blog(ll a) {
        int res = -1;
        while(a) {
            a>>=1;
            res++;
        }
        return res;
    }

    //greatest common divisor
    ll gcd(ll a, ll b) {
        if(b)
            return gcd(b, a%b);
        return a;
    }

    //least common multiple
    ll lcm(ll a, ll b) {
        return a / gcd(a, b) * b;
    }
}
using namespace cp;

//main method
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    $COM$int t;
    $COM$cin>>t;
    $COM$while(t--) {
        //start here
        $END$
    $COM$}
    return 0;
}