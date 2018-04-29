#include<iostream> 
using namespace std ; 

// 存储可行解
int a[100];

// 输出一个可行解
void Output(int *a, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[j] < a[j-1]) {
				int t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (a[i] != 0) {
			cout << a[i] << " ";
		}
	}
	cout << endl;
} 

// 验证当前解是否可行
bool IsOk(int* a, int curIndex, int curValue) {
	for(int i = 0; i < curIndex; ++i)
		if(a[i] == curValue) return false;
		return true;
}

// 对自然数n进行拆分，t用来控制拆分个数
void Partition(int n, int t, int *b) {
	if (n < 0) return;
	if (n == 0) // 找到一个拆分 
		Output(a, t); //输出之
	else { 
		for (int i = 0; i < n; i++) { 
			a[t] = b[i];
			if(IsOk(a, t, b[i]))
				Partition(n - b[i], t + 1, b);
		} 
	} 
} 

int main(void) 
{ 
	int T;
	cout << "请输入背包总体积："; 
	cin >> T;
	int n;
	cout << "请输入物品总数：";
	cin >> n;
	int b[n];
	cout << "请输入"<< n <<"件物品的各体积：" <<endl;
	for (int i = 0; i < n; i++) {
		int g;
		cin >> g;
		b[i] = g;
	}
	if (T < 0) return 0;
 	Partition(T, 0, b);
	return 0 ; 
}
