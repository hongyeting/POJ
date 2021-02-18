#include<iostream>
#include<iomanip>

using namespace std;

double item_c[100] = { 0 };//weight
double item_v[100] = { 0 };//value

double capacity[10000];//as expected, the two sequences should both go up
double value[10000];
int length;

int main()
{
	double C = 0;int N = 0;cin >> N >> C;
	for (int t = 0;t < N;t++)
		cin >> item_c[t] >> item_v[t];
	length = 2, capacity[1] = item_c[0], value[1] = item_v[0];//initialize, keep the first (0, 0)
	for (int i = 1;i < N;i++)
	{
		double capa[10000] = { 0 }, valu[10000] = { 0 };
		int p1 = 0, p2 = 0, p3 = 0;//put (capacity, value) and (capacity + item_c, value + item_v) into one sequence in capacity-up order
		while (p1 < length && p2 < length)
		{
			if (capacity[p1] > C && capacity[p2] + item_c[i] > C)break;
			if (capacity[p1] < capacity[p2] + item_c[i])
			{
				capa[p3] = capacity[p1];valu[p3] = value[p1];
				p1++;p3++;
			}
			else if (capacity[p1] > capacity[p2] + item_c[i])
			{
				capa[p3] = capacity[p2] + item_c[i];valu[p3] = value[p2] + item_v[i];
				p2++;p3++;
			}
			else
			{
				capa[p3] = capacity[p1];
				if (value[p1] < value[p2] + item_v[i])
					valu[p3] = value[p2] + item_v[i];
				else
					valu[p3] = value[p1];
				p1++;p2++;p3++;
			}
		}
		if (p2 < length && capacity[p2] + item_c[i] <= C)//p1 < length is impossible
		{
			for (;p2 < length;)
			{
				if (capacity[p2] + item_c[i] > C)break;
				capa[p3] = capacity[p2] + item_c[i];valu[p3] = value[p2] + item_v[i];
				p2++;p3++;
			}
		}
		//now rebuild capacity and value from capa and valu while skipping lessening valu ( overlarge capacities are already filtered out )
		//the first (0, 0) is always there, no need to change
		int len = 1, p = 1, q = 0;
		for (;p < 2 * length;p++)
		{
			if (valu[p] < valu[q])continue;
			else
			{
				capacity[len] = capa[p];value[len] = valu[p];
				q = p;len++;
			}
		}
		length = len;
	}
	cout << fixed << setprecision(5) << value[length - 1];
	return 0;
}
