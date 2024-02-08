#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long double ld;
typedef pair<ld, ld> pdd;
int n;
typedef long long ll;
const ld eps = 0.0001;
const ld E = exp((ld)1);
const ld PI = acos(-1.0);

pdd rotated(pdd A, ld theta) {

    ld c = cos(theta);
    ld s = sin(theta);
    return {A.first * c - A.second * s, A.first * s + A.second * c};
}

ld ln(ld x) {
    return log(x) / log(E);
}

ld F(ld phi) {
    return ln(sin(phi / 2)) - ln(cos(phi / 2));
}

ld handle(pii _A, pii _B) {
    pdd A = {_A.first, _A.second};
    pdd B = {_B.first, _B.second};

    ld theta = atan2(A.second, A.first);

    A = rotated(A, -theta);
    B = rotated(B, -theta);

    assert(abs(A.second) < eps);



    ld xa = A.first;
    if (abs(xa) < eps)
        return 0;
    ld x = B.first / xa;
    ld y = B.second / xa;
    if (y < 0)
        y = -y;
    if (y < eps)
        return 0;
    cerr << "--------------------\n";
    cerr << "A = " << A.first << ", " << A.second << "\n";
    cerr << "B = " << B.first << ", " << B.second << "\n";
    cerr << "handling " << x << "  " << y << " with scale = " << xa << "\n";
    ld alpha = atan2(y, x);

    ld sq = sqrt(y * y + (1-x)*(1-x));

    ld beta = atan2(y / sq, (1-x)/ sq);

    cerr << "alpha = " << alpha << "\n";
    cerr << "beta  = " << beta << "\n";
    cerr << "sq    = " << sq << "\n";
    ld phi1 = (alpha + beta) / 2;
    ld phi2 = beta / 2;


    ld ret = (y / sq) * ln((sin(phi1) * cos(phi2)) / (cos(phi1) * sin(phi2)));


    cerr << " -> " << ret * xa * xa << "\n";
    return ret * xa ;
}
ll cross(pii a, pii b) {
    return a.first * 1LL * b.second - a.second * 1LL * b.first;
}

bool ccw(pii a, pii b) {
    return cross(a, b) > 0;
}

int main() {

    freopen("test.txt","r",stdin);

    // printf("pi = %.5lf\ne = %.5lf\n", (double)PI, (double)E);
    int x0, y0;
    scanf("%d %d %d", &n, &x0, &y0);
    vector<pii> pts;
    for (int i = 0; i < n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        pts.push_back({x - x0, y - y0});
    }
    pts.push_back({pts[0].first, pts[0].second});


    ld sol = 0;
    for (int i = 1; i < pts.size(); i++) {
        auto temp = handle(pts[i-1], pts[i]);
        if (ccw(pts[i-1], pts[i]))
            sol += abs(temp);
        else
            sol -= abs(temp);
    }

    printf("%.10lf\n", (double)(abs(sol / PI)));

    return 0;
}
