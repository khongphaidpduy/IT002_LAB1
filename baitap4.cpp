#include <bits/stdc++.h> 

using namespace std;

double Sin(double x)
{
	// Giới hạn x trong khoảng [0, 2π]
	x = fmod(x, 2 * M_PI); // M_PI là số pi chính xác nhất trong thư viện cmath
	if (x < 0) x += 2 * M_PI;

	double term = x; // Khởi tạo số hạng ban đầu
	double sum = term; // Khởi tạo tổng
	int n = 1; // chỉ số chuỗi
	while (fabs(term) > 0.00001) {
		term = (double) (term * (-1) * x * x) / ((2 * n) * (2 * n + 1)); // Tính số hạng tiếp theo
        sum += term; // Cộng số hạng vừa tính được vào kết quả 
        n++;
	}
	//return sin(x);
	return sum;
}
signed main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	double x;
	cout << "Hay nhap so X: (don vi radian)" << "\n";
	cin >> x;

	//In kết quả 
	cout << "Sin(x) = " << Sin(x) << "\n";
	return 0;
}