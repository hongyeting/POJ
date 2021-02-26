#include<iostream>
#include<queue>
#define INF 0x3f3f3f3f

using namespace std;

int S, F, N, M;
int head[1000];
int dist[1000][2];
int ans[1000][2];
bool vis[1000][2];

int edge_size;
struct EDGE {
	int from, to, dis, nxt;
	EDGE(int a, int b, int c) :from(a - 1), to(b - 1), dis(c), nxt(head[a - 1]) {
		head[a - 1] = edge_size;edge_size++;
	}
};
vector<EDGE>edges;

struct NODE {
	int dis, id, order;
	NODE(int a, int b, int c) :dis(a), id(b), order(c) {}
    bool operator<(NODE o)const {
        return dis > o.dis;
    }
};

int main() {
	int Z;cin >> Z;
	for (int z = 0;z < Z;z++) {
		cin >> N >> M;
		edges.clear();edge_size = 0;
		memset(head, 0x3f, sizeof(head));
        memset(dist, 0x3f, sizeof(dist));
        memset(ans, 0, sizeof(ans));
        memset(vis, 0, sizeof(vis));
		int a, b, c;
		for (int m = 0;m < M;m++)
			cin >> a >> b >> c, edges.push_back(EDGE(a, b, c));
        cin >> S >> F;S--, F--;
        ans[S][0] = 1, dist[S][0] = 0;
        priority_queue<NODE>Q;
        Q.push(NODE(0, S, 0));
        while (!Q.empty()) {
            NODE q = Q.top();Q.pop();
            if (vis[q.id][q.order])continue;
            vis[q.id][q.order] = true;
            for (int i = head[q.id];i != INF;i = edges[i].nxt) {
                int dis = q.dis + edges[i].dis;
                int& from = q.id, & to = edges[i].to;
                if (dis < dist[to][0]) {//发现更短路，更新最短路长度、数目，次短路长度、数目
                    if (dist[to][0] != INF) {
                        dist[to][1] = dist[to][0];
                        ans[to][1] = ans[to][0];
                        Q.push(NODE(dist[to][1], to, 1));//次短路
                    }
                    dist[to][0] = dis;
                    ans[to][0] = ans[from][0];
                    Q.push(NODE(dis, to, 0));//最短路
                }
                else if (dis == dist[to][0])//等于最短路，更新最短路次数
                    ans[to][0] += ans[from][0];
                else if (dis < dist[to][1]) {//发现更短的次短路，更新次短路长度、数目
                    dist[to][1] = dis;
                    ans[to][1] = ans[from][q.order];
                    Q.push(NODE(dis, to, 1));//次短路
                }
                else if (dis == dist[to][1])//等于次短路，更新次短路数目
                    ans[to][1] += ans[from][q.order];
            }
        }
        if (dist[F][1] == dist[F][0] + 1)
            cout << ans[F][1] + ans[F][0] << '\n';
        else cout << ans[F][0] << '\n';
	}
    return 0;
}
