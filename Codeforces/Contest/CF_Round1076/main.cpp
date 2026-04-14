#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using os = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using oms = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define mod  1000000007
#define mod2 998244353
#define ll long long
#define bl __int128_t
#define pb push_back
#define all(v) v.begin(),v.end()
#define bs binary_search
#define rall(v) v.rbegin(),v.rend()
#define lb lower_bound
#define ub upper_bound
#define pl pair<ll,ll>
#define f(i,n) for(ll i=0;i<n;i++)
#define inp(a,n) vector<ll> a(n); f(i,n) cin>>a[i]
#define pyes cout<<"YES\n"
#define pno cout<<"NO\n"
using Mat = array<array<ll,2>,2>;

#pragma GCC optimize("unroll-loops")
#pragma gcc optimize("Ofast")
#pragma GCC optimization("Ofast")
#pragma optimize(Ofast)
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("popcnt")

ll power(ll x,ll y,ll z=LLONG_MAX){
    ll res=1;
    while(y>0){
        if(y%2) res=(res*x)%z;
        y/=2;
        if(y) x=(x*x)%z;
    }return res%z;
}

ll gcd(ll a,ll b,ll& x,ll& y){
    x=1,y=0;
    ll x1=0,y1=1,a1=a,b1=b;
    while(b1){
        ll q=a1/b1;
        tie(x,x1)=make_tuple(x1,x-q*x1);
        tie(y,y1)=make_tuple(y1,y-q*y1);
        tie(a1,b1)=make_tuple(b1,a1-q*b1);
    }return a1;
}



int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll t=1,i,j,n,m,z=1e9+7,z2=998244353,k,x,y,q;
    // sieve(); // for SPF
    cin>>t;
    ll tt=t;
    string s,s2;
    while(tt--){
        ll n, ax, ay, bx, by;
        cin >> n >> ax >> ay >> bx >> by;

        inp(x, n);
        inp(y, n);

        map<ll, vector<ll>> mp;
        f(i, n) mp[x[i]].pb(y[i]);

        mp[ax].pb(ay);
        mp[bx].pb(by);

        ll ans = bx - ax;
        vector<ll> v1, v2;

        for(auto& [x, z] : mp){
            ans += (*max_element(all(z)) - *min_element(all(z)));
            v1.pb(*min_element(all(z)));
            v2.pb(*max_element(all(z)));
        }

        ll m = v1.size();
        vector<ll> dp1(m, (ll)1e18);
        vector<ll> dp2(m, (ll)1e18);

        dp1[0] = dp2[0] = 0;

        for(ll i = 1; i < m; i++){
            dp1[i] = min(dp1[i - 1] + abs(v2[i - 1] - v1[i]), dp2[i - 1] + abs(v1[i - 1] - v1[i]));
            dp2[i] = min(dp1[i - 1] + abs(v2[i - 1] - v2[i]), dp2[i - 1] + abs(v1[i - 1] - v2[i]));
        }

        cout << ans + min(dp1[m - 1], dp2[m - 1]) << '\n';
    }
    return 0;
}