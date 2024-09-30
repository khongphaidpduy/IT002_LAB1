#include <bits/stdc++.h> 

using namespace std;

int n, m, a[1000001], b[1000001];

// Thủ tục đọc dữ liệu
void input()
{
	//n là độ dài mảng A, m là độ dài mảng B
	cin >> n >> m; //Đọc số phần tử mảng a và mảng b
	for (int i = 1; i <= n; i++) 
		cin >> a[i]; // Đọc mảng A
	for (int i = 1; i <= m; i++) 
		cin >> b[i]; // Đọc mảng B
}
int f[1000001];
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
   	input();
   	int res = 0; // Số lần xuất hiện của A trong B
   	vector <int> v; // Danh sách các chỉ số xuất hiện
   	
	// Thuật toán KMP
	int k = 0;
	for (int i = 2; i <= n; i++) 
	{
		k = f[i - 1];
		while (k > 0 && a[k + 1] != a[i]) 
		{
			k = f[k];
		}
		if (a[k + 1] == a[i]) f[i] = k + 1;
		else f[i] = 0;
	}
	//for (int i = 1; i <= m; i++) cout << f[i] << " "; cout << "\n";
	k = 0;
	for (int i = 1; i <= m; i++) 
	{	
		while (k > 0 && a[k + 1] != b[i]) 
			k = f[k];
		if (a[k + 1] == b[i]) 
		{
			k++;
		}
		if (k == n) {v.push_back(i - n); res++; k = f[k];}
	}
	cout << res << "\n";
	for (auto j : v) 
		cout << j << " ";
    return 0;
}

