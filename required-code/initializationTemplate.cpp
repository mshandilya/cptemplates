//required macros and template
#include <bits/stdc++.h>
using namespace std;

//modular arithmetics
#define mod_a % ((long) 1e9+7)
#define mod_b % ((long) 998244353)
#define ma ((long) 1e9+7)
#define mb ((long) 998244353)
#define modDiv_a(a, b) ((a mod_a) * cp::bex(b, ma-2)) mod_a
#define modDiv_b(a, b) ((a mod_b) * cp::bex(b, mb-2)) mod_b

//type definitions
#define ll long long
#define ld long double
#define vc vector
typedef vc<int> vi;
typedef vc<ll> vl;
typedef vc<double> vd;
typedef vc<list<int>> adjList;
typedef vc<list<pair<int, int>>> w_adjList;
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

//method implementing each test case (change parameters and return type)
void solve() {
    
}

//main method
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    while(t--) {
    	//start here    
        cout<<solve()<<endl;
    }
    return 0;
}
