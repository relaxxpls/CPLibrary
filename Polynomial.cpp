#include <bits/stdc++.h>
using namespace std;
#define int         long long
#define sz(x)       (int) x.size()
const int OO    = 1e18;

// Source: github.com/e-maxx-eng/e-maxx-eng-aux/blob/master/src/polynomial.cpp
#define MODULAR // Work under a finite field (modint, NTT, CRT)
template<typename T> struct poly {
    vector<T> a;
    poly(string S) : a(sz(S)) {
        for (int i=0, n=sz(S); i<n; i++) a[n-1-i] = S[i]-'0'; }
    template<typename... A> poly(A... x) : a(x...) {}
    poly(const initializer_list<T> &x)   : a(x) {}

    // Operators (Arithmatic):
    poly operator +  (const poly &p) const {
        vector<T> res(max(size(), sz(p)));
        for (int i=0; i<sz(res); i++) res[i] = coef(i) + p.coef(i);
        return res; }
    poly operator -  (const poly &p) const {
        vector<T> res(max(size(), sz(p)));
        for (int i=0; i<sz(res); i++) res[i] = coef(i) - p.coef(i);
        return res; }
    poly operator *  (const poly &p) {
        if (!sz(a) || !sz(p.a)) return {};
        vector<int> A(sz(a)), B(sz(p.a));
        for (int i=0; i<sz( a ); i++) A[i] = (int)a[i];
        for (int i=0; i<sz(p.a); i++) B[i] = (int)p.a[i];
        #ifdef MODULAR
            vector<int> res = NTT::operator*(A, B);
        #else
            vector<int> res = FFT::operator*(A, B);
        #endif
        return poly(res.begin(), res.end()); }
    poly operator /  (const poly &p) { return divmod(*this,  p).F; }
    poly operator %  (const poly &p) { return divmod(*this,  p).S; }
    poly operator += (const poly &p) { return *this = (*this) + p; }
    poly operator -= (const poly &p) { return *this = (*this) - p; }
    poly operator *= (const poly &p) { return *this = (*this) * p; }
    poly operator /= (const poly &p) { return *this = (*this) / p; }
    poly operator %= (const poly &p) { return *this = (*this) % p; }
    bool operator == (const poly &p) { return a == p.a; }
    bool operator != (const poly &p) { return a != p.a; }
    poly operator *  (const T &x) const {
        vector<T> res(size());
        for (int i=0; i<size(); i++) res[i] = a[i]*x;
        return res; }
    poly operator /  (const T &x) const {
        vector<T> res(size());
        for (int i=0; i<size(); i++) res[i] = a[i]/x;
        return res; }
    poly operator *= (const T &x)  { return *this = (*this) * x; }
    poly operator /= (const T &x)  { return *this = (*this) / x; }
    T&   operator [] (const int i) { assert(i<sz(a)); return a[i]; }
    T    operator () (const int x) {                // Evaluate polynomial at x
        T res=0; for(int i=deg(); i>=0; i--) res*=x, res+=a[i]; return res; }

    // Extra Functions:
    inline void normalize() { while (sz(a)>1 && lead()==T(0)) a.pop_back(); }
    inline T coef(int i) const { return (i<sz(a) ? a[i] : T(0)); } // 0 indexed
    inline T& lead()           { return a.back(); }
    inline int size()    const { return sz(a); }
    inline int deg()     const { return a.empty() ? -OO : sz(a)-1; } // Degree
    void push_back(int x) { normalize(), a.push_back(x); }
    poly shift(int k) const {       // k>=0 ? Multiply by x^k : Divide by x^k
        vector<T> res(a);
        if (k >= 0) res.insert(res.begin(), k, 0);
        else assert(sz(res)+k >= 0), res.erase(res.begin(), res.begin() - k);
        return res; }
    poly mod_xk(int k) const {                  // Modulo   by x^k
        return vector<T> (a.begin(), a.begin() + min(k, sz(a))); }
    poly substr(int l, int r) const {
        l = min(l, sz(a)), r = min(r, sz(a));
        return vector<T> (a.begin() + l, a.begin() + r); }
    poly inv(int n) const {                     // Inverse series (mod x^n)
        assert(size()), assert(a[0] != 0); poly r = T(1) / a[0];
        for (int i=1; i<n; i<<=1) r = (r*T(2) - r*r*mod_xk(2*i)).mod_xk(2*i);
        return r.mod_xk(n); }
    friend pair<poly, poly> divmod(poly a, poly b) { // Q = a/b, R = a - Q*b
        a.normalize(), b.normalize(); assert(sz(b));
        T lst = b.lead(), lstInv = T(1)/lst; int diff = sz(a)-sz(b);
        poly q(max(diff+1, 0LL));
        for (T &x: a.a) x *= lstInv;
        for (T &x: b.a) x *= lstInv;
        while (diff>=0) {
            q[diff] = a.lead();
            for (int i=0; i<sz(b); i++) a[i+diff] -= q[diff] * b[i];
            a.normalize(); diff = sz(a)-sz(b); }
        for (T &t: a.a) t *= lst;
        return {q, a}; }                        // (Quotient, Remainder)

    friend poly gcd(poly a, poly b) { return sz(b) ? gcd(b, a%b) : a; }

    // Chirp Z Transform O(NlogN):
    poly mulx(T x) {              // component-wise multiplication with x^k
        T cur = 1; poly res(*this);
        for(int i=0; i<size(); i++) res.a[i] *= cur, cur *= x;
        return res; }
    poly mulx_sq(T x) {           // component-wise multiplication with x^{k^2}
        T cur = x, total = 1, xx = x * x; poly res(*this);
        for(int i=0; i<size(); i++) res.a[i] *= total, total *= cur, cur *= xx;
        return res; }
    vector<T> chirpZEven(T z, int n) { // P(1), P(z^2), P(z^4),..., P(z^2(n-1))
        if(size() == 0) return vector<T>(n, 0);
        int m = deg();
        vector<T> vv(m + n), res(n);
        T zi = T(1)/z, zz = zi*zi, cur = zi, total = 1;
        for(int i=0; i<=max(n-1, m); i++, total *= cur, cur *= zz) {
            if(i<=m) vv[m - i] = total;
            if(i< n) vv[m + i] = total; }
        poly w = (mulx_sq(z) * poly(vv)).substr(m, m + n).mulx_sq(z);
        for(int i=0; i<n; i++) res[i] = w[i];
        return res; }
    vector<T> chirpZ(T z, int n) {      // P(1), P(z), P(z^2), ..., P(z^(n-1))
        vector<T> even = chirpZEven(z, (n+1)/2);
        vector<T> res(n), odd = mulx(z).chirpZEven(z, n/2);
        for(int i=0; i<n/2; i++) res[i<<1] = even[i], res[i<<1|1] = odd[i];
        if(n%2) res[n-1] = even.back();
        return res; }

    // Calculus:
    poly derivative() const {
        vector<T> res(size()-1);
        for(int i=1; i<size(); i++) res[i-1] = coef(i) * i;
        return res; }
    poly integral() const {                     // integration const = 0
        vector<T> res(size()+1); res[0] = 0;
        for(int i=0; i<size(); i++) res[i+1] = coef(i) / (i+1);
        return res; }

    // Input-Output:
    friend istream& operator>>(istream &cin, poly &p) {
        for(int i=0; i<sz(p); i++) cin>>p[i]; return cin; }
    friend ostream& operator<<(ostream &cout, poly p) {
        for(int i=0; i<sz(p); i++) cout<<p.coef(i)<<" "; return cout; }

    // Polynomial represents digits (normalize):
    friend poly base10(poly a) {                // Convert to base 10
        int c=0;
        for(int i=0; i<sz(a); i++) a[i] += c, c = a[i]/10, a[i] -= 10*c;
        while(c) a.pb(c%10), c /= 10;
        a.normalize(); return a; }
};