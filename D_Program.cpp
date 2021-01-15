#include "bits/stdc++.h"

using namespace std;
////////////////////////////////segment tree //////////////////////////////////
pair<int, int> min_max(pair<int, int> a, pair<int, int> b)
{
    return make_pair(max(a.first, b.first), min(a.second, b.second));
}
void buildseg(int idx, int l, int r, vector<pair<int, int>> &seg, vector<int> &v)
{
    if (l == r)
    {
        seg[idx] = make_pair(v[l], v[l]);
        return;
    }
    int mid = (l + r) / 2;
    buildseg(2 * idx + 1, l, mid, seg, v);
    buildseg(2 * idx + 2, mid + 1, r, seg, v);
    seg[idx] = min_max(seg[2 * idx + 1], seg[2 * idx + 2]);
    return;
}
pair<int, int> get_min_max(int idx, int ql, int qr, int l, int r, vector<pair<int, int>> &seg)
{
    if ((ql <= l) and (qr >= r))
    {
        return seg[idx];
    }
    if (ql > r || qr < l)
    {
        return make_pair(INT32_MIN, INT32_MAX);
    }
    int mid = ((l + r) / 2);
    auto x = get_min_max(2 * idx + 1, ql, qr, l, mid, seg);
    auto y = get_min_max(2 * idx + 2, ql, qr, mid + 1, r, seg);
    return min_max(x, y);
}
void solve(vector<int> &v, int n, int m)
{
    //pair<max,min>
    vector<pair<int, int>> seg((4 * n) + 1);
    buildseg(0, 0, n, seg, v);
    while (m--)
    {
        int ql, qr;
        cin >> ql >> qr;
        int mini = 0,
            maxi = 0;
        if (ql > 1)
        {
            auto x = get_min_max(0, 0, ql - 1, 0, n, seg); //max,min
            maxi = max(maxi, x.first);
            mini = min(mini, x.second);
        }
        if (qr < n)
        {
            auto y = get_min_max(0, qr + 1, n, 0, n, seg); //max,min
            int balance_factor = v[qr] - v[ql - 1];
            y.first = y.first - balance_factor;
            y.second = y.second - balance_factor;
            maxi = max(maxi, y.first);
            mini = min(mini, y.second);
        }

        cout << (maxi - mini + 1) << endl;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    // memset(prime, true, sizeof(prime));
    //primes(); // primes under 1lakh

    /*
  #ifdef NCR
        init();
    #endif
*/
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        int m;
        cin >> n >> m;
        string str;
        cin >> str;
        vector<int> v(n + 1);
        v[0] = 0;
        for (int i = 1; i <= n; i++)
        {
            v[i] = (str[i - 1] == '+') ? 1 : -1;
            v[i] = v[i] + v[i - 1];
        }
        solve(v, n, m);
    }
}
