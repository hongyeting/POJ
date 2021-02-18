#include<iostream>
#include<vector>

using namespace std;

int C, G;
int hook[20] = { 0 }, weight[20] = { 0 };
vector<pair<int, int>>Q[2];int q = 0;

int main() {
	cin >> C >> G;
	for (int i = 0;i < C;i++)cin >> hook[i];
	for (int i = 0;i < G;i++)cin >> weight[i];
	for (int h = 0;h < C;h++)Q[0].push_back(make_pair(weight[0] * hook[h], 1));
	for (int w = 1;w < G;w++) {
		q = 1 - q;Q[q].clear();
		for (int i = 0;i < Q[1 - q].size();i++) {
			int mi = Q[1 - q][i].second;
			for (int h = 0;h < C;h++) {
				int add = Q[1 - q][i].first + weight[w] * hook[h];
				bool find = false;
				for (int f = 0;f < Q[q].size();f++) {
					if (Q[q][f].first == add) {
						Q[q][f].second += mi;find = true;
						break;
					}
				}
				if (!find)
					Q[q].push_back(make_pair(add, mi));
			}
		}
	}
	for (int i = 0;i < Q[q].size();i++) {
		if (Q[q][i].first == 0) {
			cout << Q[q][i].second;
			break;
		}
	}
	return 0;
}
