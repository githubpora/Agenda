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
	cout << "�����뱳���������"; 
	cin >> T;
	int n;
	cout << "��������Ʒ������";
	cin >> n;
	int w[n];
	cout << "������"<< n <<"����Ʒ�ĸ������" <<endl;
	for (int i = 0; i < n; i++) {
		int g;
		cin >> g;
		w[i] = g;
	}
	if (T <= 0) return 0;
	backbag(w, T, n, 0);
}
