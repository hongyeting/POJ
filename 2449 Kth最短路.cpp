#include<iostream>
#include<vector>
#include<queue>

#define INF 0x3f3f3f3f
#define start S
#define end T
#define maxtime K

using namespace std;

int N, M, S, T, K;
int nei[1000][2];//构造LINE时用于记录发射邻边/收束邻边
int t[1000] = { 0 };//求K短路时用于记录访问次数
int h[1000];//dijkstra时用于记录到终点的最短时间
bool vis[1000] = { false };//是否遍历

int lines_size = 0;
struct LINE {
	int from, to, time, s_to, s_from;
	LINE(int a, int b, int c) :from(a - 1), to(b - 1), time(c), s_from(nei[from][0]), s_to(nei[to][1]) {
		nei[from][0] = nei[to][1] = lines_size;lines_size++;
	}
};
vector<LINE>lines;

struct node {
	int id, f;
	node(int a,int b):id(a),f(b){}
	bool operator < (node o) const {
		return h[id] + f > h[o.id] + o.f;
	}//定义node比较大小的方式，使优先队列里和小的排前面
};

int main() {
	cin >> N >> M;
	memset(nei, 0x3f, sizeof(nei));
	int a, b, c;
	for (int m = 0;m < M;m++)
		cin >> a >> b >> c, lines.push_back(LINE(a, b, c));
	cin >> S >> T >> K;S--;T--;
	if (S == T)K++;
	memset(h, 0x3f, sizeof(h));
	priority_queue<pair<int, int>>Q;
	Q.push(make_pair(0, end));
	while (Q.size()) {
		pair<int, int>o = Q.top();Q.pop();
		int id = o.second;
		if (vis[id])continue;
		vis[id] = true;
		int t = -o.first;
		h[id] = t;
		for (int i = nei[id][1];i != INF;i = lines[i].s_to)
			if (t + lines[i].time < h[lines[i].from]) {
				h[lines[i].from] = t + lines[i].time;
				Q.push(make_pair(-t - lines[i].time, lines[i].from));
			}
	}//dijkstra完成h[](到终点的预期代价)
	if (!vis[start])
		cout << -1 << '\n';//到不了终点
	else {
		priority_queue<node>Q;
		Q.push(node(start, 0));
		bool find = false;
		while (Q.size()) {
			node o = Q.top();Q.pop();
			t[o.id]++;
			if (o.id == end && t[o.id] == maxtime) {
				cout << o.f << '\n';find = true;
				break;
			}
			if (t[o.id] > maxtime)continue;
			for (int i = nei[o.id][0];i != INF;i = lines[i].s_from)
				if (vis[lines[i].to])
					Q.push(node(lines[i].to, o.f + lines[i].time));
		}
		if (!find)
			cout << -1 << '\n';//到达终点的走法小于maxtime种
	}
	return 0;
}
