#include <bits/stdc++.h>
using namespace std;
#define int     long long
#define sz(x)   (int) x.size()

struct dsu {                                                // 0 indexed
    int n; vector<int> p, sz;
    dsu(int N) : n(N) {
        p = vector<int>(n, 0), sz = vector<int>(n, 1);
        for(int i=0; i<n; i++) p[i] = i; }
    inline int find(int v) {                                // Path Compression
        if(v != p[v]) p[v] = find(p[v]);
        return p[v]; }
    inline bool unite(int u, int v) {                       // Union by Size
        u = find(u), v = find(v);
        if(u != v) {                                        // merge v into u
            if(sz[u] < sz[v]) swap(u, v);
            p[v] = u, n--, sz[u] += sz[v];
            return true; }
        return false; }
    int size()      { return n; }
    int size(int u) { return sz[find(u)]; }
};
