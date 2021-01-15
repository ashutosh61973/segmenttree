#include "bits/stdc++.h"

using namespace std;
#define inti long long
#define ll long long
const long long INF = 1e18;
const int32_t M = 1e9 + 7;
const int32_t mod = 1e9 + 7;
const int32_t MM = 998244353;

/////////**********************---/|\---************************///////////
/////////**********************---\|/---***********************///////////

void buildSegmentTree(int idx, int l, int r, vector<int> &seg, vector<int> &arr)
{
    if (l == r)
    {
        seg[idx] = arr[l];
        return;
    }
    //recursive intuition
    int mid = (l + r) / 2;
    buildSegmentTree(2 * idx + 1, l, mid, seg, arr);
    buildSegmentTree(2 * idx + 2, mid + 1, r, seg, arr);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    return;
}

int sum_query(int idx, int ql, int qr, int l, int r, vector<int> &seg)
{
    if (qr < l || ql > r)
    {
        return 0;
    }
    if (ql <= l && qr >= r)
        return seg[idx];
    int mid = (l + r) / 2;
    int x = sum_query(2 * idx + 1, ql, qr, l, mid, seg);
    int y = sum_query(2 * idx + 2, ql, qr, mid + 1, r, seg);
    return x + y;
}
void update(int idx, int l, int r, int pos, int val, vector<int> &seg)
{
    if (l == r)
    {
        seg[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (mid >= pos)
    {
        update(2 * idx + 1, l, mid, pos, val, seg);
    }
    else
    {
        update(2 * idx + 2, mid + 1, r, pos, val, seg);
    }
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<int> seg(4 * n); //to store the node of the segment tree
    //befor building of segment tree you have to know two things
    //first-what each node is repersent ..in here it is sum of the rnage
    //second-how to merge
    buildSegmentTree(0, 0, n - 1, seg, arr);
    int q;
    cin >> q;
    int type; //if type is 0 then get the sum // if 1 then update
    while (q--)
    {
        cin >> type;
        if (type == 0)
        {
            //sum
            int ql, qr;
            cin >> ql >> qr;
            cout << sum_query(0, ql, qr, 0, n - 1, seg) << endl;
        }
        else
        {
            //update;
            int pos, val;
            cin >> pos >> val;
            update(0, 0, n - 1, pos, val, seg);
        }
    }
}
