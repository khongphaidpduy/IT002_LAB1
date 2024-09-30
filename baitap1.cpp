#include <bits/stdc++.h> 

using namespace std;

// Cấu trúc đại diện phân số 
struct Phanso{
    int tu, mau;
};

// Hàm tính ucln của 2 số nguyên 
int gcd(int a, int b) 
{
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Hàm rút gọn phân số 
Phanso Rutgon(Phanso a) 
{
    Phanso c = a;
    c.tu = a.tu / gcd(a.tu, a.mau);
    c.mau = a.mau / gcd(a.tu, a.mau);
    return c;
}

// Hàm kiểm tra phân số vừa nhập có hợp lệ hay không
bool CheckValidInput(string frac, Phanso &a) 
{
    stringstream ss(frac);
    char slash; // dấu gạch phân số
    int kiemtra_tu, kiemtra_mau;
    if (ss >> kiemtra_tu >> slash >> kiemtra_mau) {
        a.tu = kiemtra_tu;
        a.mau = kiemtra_mau;
        return true;
    }
    return false;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Phanso a;
    while (true) {
        string frac; //xâu định dạng  input
        cout << "Nhap phan so: {tu/mau}" << "\n";
        cin >> frac;
        if (!CheckValidInput(frac, a)) { //Nếu phân số không hợp lệ thì nhập lại
            cout << "Vui long nhap phan so hop le!!!!!" << "\n";
        } else {
            break;
        }
    }

    Phanso c = Rutgon(a);
    //In ra phân số đã được rút gọn
    cout << "Phan so duoc rut gon la: " << c.tu << "/" << c.mau << "\n";
    return 0;
}

