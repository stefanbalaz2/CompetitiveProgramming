#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
typedef pair<ld, ld> pdd;
typedef pair<int, int> pii;


pdd gen_150(int _l, int _r) {

    if (_l >= 150 && _r >= 150)
        return {0, 1};
    if (_l < 150 && _r < 150)
        return {0, 0};


    ld l = (ld)_l;
    ld r = (ld)_r;

    ld x = (150 - l) / (r - l);
    if (_l > _r)
        return {0, x};
    return {x, 1};
}

pdd gen_75(int _l, int _r) {
    if (_l <= 75 && _r <= 75)
        return {0, 1};

    if (_l > 75 && _r > 75)
        return {0, 0};


    ld l = (ld)_l;
    ld r = (ld)_r;

    ld x = (75 - l) / (r - l);
    if (_l < _r)
        return {0, x};
    return {x, 1};
}

pdd intersect(pdd a, pdd b) {
    pdd temp = {max(a.first, b.first), min(a.second, b.second)};
    if (temp.first >= temp.second)
        return {0, 0};
    return temp;
}

pdd intersect(pdd a, pdd b, pdd c) {
    return intersect(intersect(a, b), c);
}
ld len(pdd a, ld dy1, ld dy2) {
    ld x = max((ld)0, a.first);
    ld y = min((ld)1, a.second);
    if (x >= y)
        return 0;

    ld xval = x * dy2 + (1-x)*dy1;
    ld yval = y * dy2 + (1-y)*dy1;

    return (y - x) * (xval + yval) / 2;
}

int main() {
    ld x1, y1, y2;
    int rl, gl, bl;
    ld x2, y3, y4;
    int rr, gr, br;
    scanf("%Lf %Lf %Lf %d %d %d", &x1, &y1, &y2, &rl, &gl, &bl);
    scanf("%Lf %Lf %Lf %d %d %d", &x2, &y3, &y4, &rr, &gr, &br);

    auto R = gen_150(rl, rr), R1 = gen_75(rl, rr);
    auto G = gen_150(gl, gr), G1 = gen_75(gl, gr);
    auto B = gen_150(bl, br), B1 = gen_75(bl, br);

    auto r = intersect(R, G1, B1);
    auto g = intersect(R1, G, B1);
    auto b = intersect(R1, G1, B);

    ld dy1 = abs(y2 - y1);
    ld dy2 = abs(y3 - y4);
    ld scale = abs(x2 - x1);
    printf("%.10Lf\n", scale * len(r, dy1, dy2));
    printf("%.10Lf\n", scale * len(g, dy1, dy2));
    printf("%.10Lf\n", scale * len(b, dy1, dy2));

    return 0;
}
/*

0 0 50 255 0 0
100 0 100 0 255 0
R = {0.000000 0.588235}
G = {0.411765 1.000000}
B = {0.000000 0.000000}
R1 = {0.705882 1.000000}
G1 = {0.000000 0.294118}
B1 = {0.000000 1.000000}
r = {0.000000 0.294118}
g = {0.705882 1.000000}
b = {0.000000 0.000000}
0.294118
0.294118
0.000000
2205.882353
2205.882353
0.000000

*/
