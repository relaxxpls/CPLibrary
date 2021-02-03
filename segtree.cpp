#include <bits/stdc++.h>
using namespace std;
#define int     long long
#define sz(x)   (int) x.size()
const int OO    = 1e18;

struct NODE {
    int val;
    NODE()      { val = 0; }
    NODE(int x) { val = x; }
    friend ostream& operator<<(ostream &cout, NODE x) { return cout<<x.val; }
};
string ts(NODE x) { return ts(x.val); }
const NODE DEF = 0;

struct segtree {                                        // 0 indexed array
    int n; vector<NODE> t;
    segtree(int N) : n(N) {
        assert(N>0); t.resize(4*n); build(1, 0, n-1); }
    segtree(const vector<int> &a) : n(sz(a)) {
        assert(n>0); t.resize(4*n); build(1, 0, n-1, a); }

    NODE merge(const NODE &l, const NODE &r) {          // Add merge function
        NODE res;
        res.val = l.val + r.val;
        return res; }

    void build(int node, int l, int r, const vector<int> &a = {}) {
        if(l==r) {                                      // Leaves
            if(sz(a)) t[node] = a[l];
            else t[node] = DEF;
            return; }
        int mid = (l+r)>>1;
        build(node<<1, l, mid, a), build(node<<1|1, mid+1, r, a);
        t[node] = merge(t[node<<1], t[node<<1|1]); }

    void update(int node, int l, int r, int pos, int val) {
        if(l==r) {                                      // Leaves
            t[node] = val;
            return; }
        int mid = (l+r)>>1;
        if(pos<=mid) update(node<<1, l, mid, pos, val);
        else         update(node<<1|1, mid+1, r, pos, val);
        t[node] = merge(t[node<<1], t[node<<1|1]); }
    void update(int pos, int val) {
        assert(0<=pos && pos<n); update(1, 0, n-1, pos,  val); }

    NODE query(int node, int l, int r, int L, int R) {  // L, R = our query range
        if(R<l || L>r)   return DEF;                    // Neutral Query Value
        if(L<=l && R>=r) return t[node];
        int mid = (l+r)>>1;
        return merge(query(node<<1, l, mid, L, R),
                     query(node<<1|1, mid+1, r, L, R)); }
    NODE query(int node, int l, int r, int pos) {
        if(l == r) return t[node];
        int mid = (l+r)>>1;
        if(pos<=mid) return query(node*2, l, mid, pos);
        else         return query(node*2+1, mid+1, r, pos); }
    NODE query(int pos) {
        assert(0<=pos && pos<n);     return query(1, 0, n-1, pos ); }
    NODE query(int L, int R) {
        assert(0<=L && L<=R && R<n); return query(1, 0, n-1, L, R); }

    int lower_bound(int node, int l, int r, int x) {
        if(x>=t[node].val) return r;
        else if(l==r) return r;
        int mid = (l+r)>>1;
        if(x<=t[node<<1].val) return lower_bound(node<<1, l, mid, x);
        else return lower_bound(node<<1|1, mid+1, r, x-t[node<<1].val); }
    int lower_bound(int x) { return lower_bound(1, 0, n-1, x); };
    int upper_bound(int node, int l, int r, int x) {
        if(x>=t[node].val) return r;
        else if(l==r) return r;
        int mid = (l+r)>>1;
        if(x<t[node<<1].val) return upper_bound(node<<1, l, mid, x);
        else return upper_bound(node<<1|1, mid+1, r, x-t[node<<1].val); }
    int upper_bound(int x) { return upper_bound(1, 0, n-1, x); }
};
