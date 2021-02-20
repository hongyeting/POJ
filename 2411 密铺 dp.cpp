#include<iostream>

using namespace std;

unsigned int o[11][1 << 11];//o[y][i]表示前y-1行填满，第y行状态为i时的个数
bool p[1 << 11] = { false };//o[0][1<<11]
unsigned int Y, T;//减少函数参数
unsigned int s[4][2];//非1凸起的开始位置和长度

unsigned int f(unsigned int state, unsigned int ti) {//在已有状态的情况下，讨论第ti+1个凸起
	unsigned int ans = 0;
	for (unsigned int i = 0;i < (1 << s[ti][1]);i++) {
		unsigned int len = 0;
		bool rslt = true;
		for (unsigned int j = 0;j < s[ti][1] + 1;j++) {//+1考虑到连续到尾
			if (i & (1 << j))
				len++;
			else if (len & 1) {
				rslt = false;break;//不能为奇数
			}
			else
				len = 0;
		}
		if (rslt) {
			if (ti + 1 < T)ans += f(state | (i << s[ti][0]), ti + 1);
			else ans += o[Y][state | (i << s[ti][0])];
		}
	}
	return ans;
}

unsigned int main() {
	for (unsigned int i = 0;i < (1 << 11);i++) {
		unsigned int len = 0;//一段凸起的长度
		bool rslt = true;
		for (unsigned int j = 0;j < 12;j++) {//12是考虑到连续到尾的凸起
			if (i & (1 << j))
				len++;
			else if (len & 1) {
				rslt = false;break;//不能为奇数
			}
			else
				len = 0;
		}
		if (rslt)
			p[i] = true;
	}
	while (true) {
		unsigned int a, b;cin >> a >> b;
		if (a == 0)break;
		if (a & 1 && b & 1) {//全是奇数
			cout << 0 << '\n';
			continue;
		}
		if (a > b) {
			unsigned int c = a;a = b;b = c;
		}
		memset(o, 0, sizeof(o));
		for (unsigned int i = 0;i < (1 << a);i++) {
			if (p[i])o[0][i] = 1;
		}
		for (unsigned int y = 1;y < b;y++) {
			unsigned int i = (a * y) & 1 ? 1 : 0;
			for (;i < (1 << a);i++) {
				unsigned int p = a * y & 1;
				for (unsigned int k = 0;k < a + 1;k++) {
					if (i & (1 << k))p++;
				}
				if (p & 1)continue;
				unsigned int ii = 0;
				for (unsigned int k = 0;k < a;k++) {
					if (i & (1 << k))ii = ii | (1 << a - 1 - k);
				}
				if (ii < i) {
					o[y][i] = o[y][ii];
					continue;
				}
				memset(s, 0, sizeof(s));//非1凸起的开始位置和长度
				unsigned int t = 0;//非1凸起的个数，至多4个
				unsigned int len = 0;//凸起的长度
				unsigned int state = 0;//先记录凸起的位置，再变成上一行的初始情况
				for (unsigned int k = 0;k < a + 1;k++) {//a+1考虑到连续到尾的凸起
					if (i & (1 << k)) {
						len++;
						state = state | (1 << k);
					}
					else if (len) {
						if (len > 1) {
							s[t][0] = k - len;
							s[t][1] = len;
							t++;
						}
						len = 0;
					}
				}
				state = ~state;//变成上一行的初始情况
				for (unsigned int k = a;k < 32;k++)state = state ^ (1 << k);
				Y = y - 1, T = t;
				o[y][i] = f(state, 0);
			}
		}
		cout << o[b - 1][(1 << a) - 1] << '\n';
	}
	return 0;
}
