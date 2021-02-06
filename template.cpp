//****************************//   RELAXXPLS   //****************************//
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
#define int         long long
#define double      long double
#define pb          push_back
#define ts          to_string
#define sz(x)       (int) x.size()
#define szr(x)      (int) (sizeof(x) / sizeof(x[0]))
#define F           first
#define S           second
#define endl        "\n"
#define all(x)      x.begin(), x.end()
#define allr(x)     x, x + szr(x)
#define vi          vector<int>
#define vvi         vector<vi>
#define mii         map<int, int>
#define pii         pair<int, int>
#define piii        pair<int, pii>
#define mem(x, v)   memset(x, v, sizeof(x))
template<typename T> using pqd = priority_queue<T>;    // MaxHeap (Descending)
template<typename T> using pqa = priority_queue<T, vector<T>, greater<T>>;
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>//  Debug Begin  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
#ifdef RELAXXPLS
    #define cerr cout
    #define deb(x...) cerr<<#x<<": ", _deb(x)
#else
    #define deb(x...) cerr<<endl
#endif
string ts(string c) { return string(c); }
string ts(char ch)  { return string(1, ch); }
string ts(bool b)   { return b ? "true" : "false"; }
template<size_t N> string ts(bitset<N> B) {
    string S=""; for (int i=0; i<(int)N; i++) S += (char)'0'+B[i]; return S; }
template<typename T, typename U> string ts(pair<T, U> P) {
    return "{"+ts(P.first)+","+ts(P.second)+"}"; }
template<typename T> string ts(T A) { string S="["; bool F=0;
    for (auto x: A) { if (F) S+=" "; F=1; S += ts(x); } return S+"]"; }
template<typename T, size_t N> string ts(T (&A)[N]) { string S="["; bool F=0;
    for (int i=0; i<N; i++) { if(F) S+=" "; F=1, S+=ts(A[i]); } return S+"]"; }
void _deb() { cerr<<endl; }
template<typename T, typename... U> void _deb(const T& t, const U&... u) {
    cerr<<ts(t); if (sizeof...(u)) cout<<", "; _deb(u...); }
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>//   Debug End   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<//
const int MX    = 5e5 + 5, BLOCK = 500;                 // BLOCK = sqrt(MX)
const int OO    = 1e18;
const int MOD   = 1e9 + 7;
const double ER = 1e-9;                                 // Double Comparisons
const int DX[8] = {1,0,-1,0,1,-1,1,-1}, DY[8] = {0,1,0,-1,1,-1,-1,1};
int ceil (int a, int b) { return a/b +  (a%b && (a^b)>0); }
int floor(int a, int b) { return a/b -  (a%b && (a^b)<0); }
int SBITS(int n)        { return __builtin_popcountll(n); }
int BITS (int n)        { return 63 - __builtin_clzll(n); }
template<typename T, typename U> T fstTrue(U f, T L=0LL, T R=OO) {  // FFFTTTT
    T mid; while(R-L+1.0>ER) mid=L+(R-L)/2, f(mid)? R=mid: L=mid+1; return L; }
template<typename T, typename U> T lstTrue(U f, T L=0LL, T R=OO) {  // TTTFFFF
    T mid; while(R-L+1.0>ER) mid=L+(R-L+1)/2, f(mid)?L=mid:R=mid-1; return L; }
//============================//  Code Start  //=============================//

void solve() {
    int n, ans=0; cin>>n;
    vi a(n);
    for (int i=0; i<n; i++) cin>>a[i];

    cout<<ans<<endl;
}

//============================//   Code End   //=============================//
signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.precision(9), cout<<fixed;
    int t = 1;  cin>>t;
    while (t--)  solve();
    #undef cerr
    cerr<<"Time: "<<(float)clock()/CLOCKS_PER_SEC<<" s";
    return 0; }