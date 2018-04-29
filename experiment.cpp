#include<iostream>
#include<stack>
using namespace std;

void backbag(int w[], int T, int n, int time) {
	int flag = 0;
	for (int i = 0; i < time; i++) {
		flag += w[i];
		if (flag == T) {
			cout << w[i] << endl;
		}
	}
}
int main() {
	int T;
	cout << "请输入背包总体积："; 
	cin >> T;
	int n;
	cout << "请输入物品总数：";
	cin >> n;
	int w[n];
	cout << "请输入"<< n <<"件物品的各体积：" <<endl;
	for (int i = 0; i < n; i++) {
		int g;
		cin >> g;
		w[i] = g;
	}
	if (T <= 0) return 0;
	backbag(w, T, n, 0);
}
