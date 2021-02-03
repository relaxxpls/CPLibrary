#include <bits/stdc++.h>
using namespace std;
#define int         long long
#define pii         pair<int, int>
#define F           first
#define S           second

void compress(vector<pii> &a) {                  // Old:[0, OO] | New:[0, ctr)
    map<int, int> cc; int ctr = 0;
    for(pii x:  a) cc[x.F]++, cc[x.S]++;
    for(pii x: cc) cc[x.F] = ctr, ctr += 2;
    for(pii &x: a) x.F = cc[x.F], x.S = cc[x.S]; }
void compress(vector<int> &a) {                  // Old:[0, OO] | New:[0, ctr)
    map<int, int> cc; int ctr=0;
    for(int x:  a) cc[x]++;
    for(pii x: cc) cc[x.F] = ctr, ctr += 2;
    for(int &x: a) x = cc[x]; }