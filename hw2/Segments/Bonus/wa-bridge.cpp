#include <bits/stdc++.h>
using namespace std;
#define maxn 200005

int n;
pair<int, int> p[maxn];
long double angle, cos_v, sin_v;

bool cmp(pair<int, int> a, pair<int, int> b) {
    auto v1 = make_pair(a.first * cos_v - a.second * sin_v
                      , a.first * sin_v + a.second * cos_v);
    auto v2 = make_pair(b.first * cos_v - b.second * sin_v
                      , b.first * sin_v + b.second * cos_v);
    return v1 < v2;
}

int main() {
    cin.tie(0), cout.sync_with_stdio(0);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // random number generator
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> p[i].first >> p[i].second;

    long long times = 1, ans = 3e18, magic = 200;
    while (times --) {
        angle = rng();
        cos_v = cos(angle);
        sin_v = sin(angle);
        sort(p + 1, p + 1 + n, cmp);
        for (int i = 1; i <= n; ++ i) {                                  // Sweep backward magic points
            for (int j = i + 1; j <= i + magic && j <= n; ++ j) {
                long long v1 = (p[i].first - p[j].first);
                long long v2 = (p[i].second - p[j].second);
                long long dis = v1 * v1 + v2 * v2;
                ans = min(ans, dis);
            }
        }
    }
    cout << -ans << "\n";
    return 0;
}
