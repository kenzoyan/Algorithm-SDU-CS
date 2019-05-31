//#include "pch.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#define maxn 20
int n;
int Graph[maxn][maxn];
int d[maxn][1 << maxn];
int route[maxn][1 << maxn];

int dp(int m, int s)
{
	if (d[m][s] != -1) {
		return d[m][s];
	}

	if (!s) {
		return d[m][s] = Graph[m][0];
	}
	d[m][s] = INT_MAX;
	for (int i = 1; i < n; i++)
	{
		if (s & (1 << i))
		{
			int p = s;
			p ^= 1 << i;
			int k = dp(i, p) + Graph[m][i];
			if (k < d[m][s]) {
				d[m][s] = k;
				route[m][s] = i;
			}
		}
	}
	return d[m][s];
}
int main()
{
	cout << "请输入点数：";
	cin >> n;
	int x;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j)
				Graph[i][j] = 0;
			else {
				cout << "请输入点" << i << "到点" << j << "的距离：";
				cin >> x;
				Graph[i][j] = x;
			}
		}
	}
	cout << "----------------------------------------------------------" << endl;
	int s = (1 << n) - 1;
	s ^= 1;
	memset(d, -1, sizeof(d));
	memset(route, 0, sizeof(route));
	dp(0, s);
	cout << "最小的TSP圈的权值为：" << d[0][s] << endl;
	cout << "----------------------------------------------------------" << endl;
	int k = 0;
	cout << "圈的路径为：";
	cout << k;
	while (route[k][s])
	{
		cout << "→" << route[k][s];
		k = route[k][s];
		s ^= 1 << k;
	}
	cout << "→" << 0 << endl;
	system("pause");
	return 0;
}
