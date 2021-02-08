#include <bits/stdc++.h>
using namespace std;

template<typename T> struct matrix {
    int R, C; vector<vector<T>> M;
    matrix() : R(0), C(0) { }
    matrix(int n) : matrix(n, n) { for(int i=0; i<n; i++) M[i][i] = 1; }
    matrix(int n, int m, T v=0) : R(n), C(m) {
        assert(n>0 && m>0); M.assign(n, vector<T> (m, v)); }
    matrix operator+=(const matrix &m) { *this = *this + m; return *this; }
    matrix operator-=(const matrix &m) { *this = *this - m; return *this; }
    matrix operator*=(const matrix &m) { *this = *this * m; return *this; }
    matrix operator- ()                { return matrix(R, C) - *this; }
    friend matrix operator+(matrix a, const matrix &b) {
        int R = a.R, C = a.C; assert(R>0 && R==b.R && C==b.C);
        for(int r=0; r<R; r++) for(int c=0; c<C; c++) a.M[r][c] += b.M[r][c];
        return a; }
    friend matrix operator-(matrix a, const matrix &b) {
        int R = a.R, C = a.C; assert(R>0 && R==b.R && C==b.C);
        for(int r=0; r<R; r++) for(int c=0; c<C; c++) a.M[r][c] -= b.M[r][c];
        return a; }
    friend matrix operator*(matrix a, const matrix &b) {
        assert(a.C>0 && a.C==b.R); matrix res(a.R, b.C);
        for(int r=0; r<a.R; r++) for(int c=0; c<b.C; c++)
            for(int i=0; i<a.C; i++) res.M[r][c] += a.M[r][i]*b.M[i][c];
        return res; }                           // a.R|a.C * b.R|b.C = a.R|b.C
    friend matrix pow(matrix m, int n) {
        assert(n>=0 && m.R == m.C); matrix res(m.R);
        while(n) res = (n&1) ? res*m : res, m *= m, n>>=1;
        return res; }
    friend istream& operator>>(istream &cin, matrix &m) {
        for(int r=0; r<m.R; r++) for(int c=0; c<m.C; c++) cin>>m.M[r][c];
        return cin; }
    friend ostream& operator<<(ostream &cout, matrix &m) {
        for(int r=0; r<m.R; r++) for(int c=0; c<m.C; c++)
            cout<<m.M[r][c]<<" \n"[c==m.C-1];
        return cout; }
};
template<typename T> string ts(matrix<T> m) { cout<<endl<<m; return ""; }
