#include<iostream> 
using namespace std ; 

// �洢���н�
int a[100];

// ���һ�����н�
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

// ��֤��ǰ���Ƿ����
bool IsOk(int* a, int curIndex, int curValue) {
	for(int i = 0; i < curIndex; ++i)
		if(a[i] == curValue) return false;
		return true;
}

// ����Ȼ��n���в�֣�t�������Ʋ�ָ���
void Partition(int n, int t, int *b) {
	if (n < 0) return;
	if (n == 0) // �ҵ�һ����� 
		Output(a, t); //���֮
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
	cout << "�����뱳���������"; 
	cin >> T;
	int n;
	cout << "��������Ʒ������";
	cin >> n;
	int b[n];
	cout << "������"<< n <<"����Ʒ�ĸ������" <<endl;
	for (int i = 0; i < n; i++) {
		int g;
		cin >> g;
		b[i] = g;
	}
	if (T < 0) return 0;
 	Partition(T, 0, b);
	return 0 ; 
}
