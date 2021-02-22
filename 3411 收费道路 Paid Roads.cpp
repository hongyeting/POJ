#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int n, m, f[10][1024];//f[a][x]到城市a+1时所需费用，经过的城市压缩为x
bool vis[10][1024] = { false };//与f对应，已经经过记为true

struct edge {
    int a, b, c, x, y;
}w[10];

int main() {
    int n, m, ans = ~0u >> 1;cin >> n >> m;
    for (int i = 0;i < m;i++) {
        cin >> w[i].a >> w[i].b >> w[i].c >> w[i].x >> w[i].y;
        w[i].a--, w[i].b--, w[i].c--;
    }
    memset(f, 0x3f, sizeof(f));
    f[0][1 << 0] = 0;//在城市1的状态
    priority_queue<pair<int, pair<int, int> > >Q;//优先队列，花钱少的排在前面
    Q.push(make_pair(0, make_pair(0, 1 << 0)));
    while (Q.size()) {
        pair<int, pair<int, int> >t = Q.top();Q.pop();//取出第一个并删除
        int a = t.second.first, s = t.second.second;
        if (a == n - 1 && ans > f[a][s])ans = f[a][s];
        if (vis[a][s])continue;
        vis[a][s] = true;
        for (int i = 0;i < m;i++)
            if (w[i].a == a) {
                int b = w[i].b;//下一个去城市b+1
                int d = f[a][s], S = s | 1 << b;//状态压缩
                if (s >> w[i].c & 1)d += w[i].x;//到过中间城市
                else d += w[i].y;
                if (d < f[b][S]) {
                    f[b][S] = d;//发现到城市b+1更省钱的走法
                    Q.push(make_pair(-d, make_pair(b, S)));
                }
            }
    }
    if (ans != ~0u >> 1)cout << ans << "\n";
    else cout << "impossible\n";
    return 0;
}
