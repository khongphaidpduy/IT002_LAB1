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

//Phép cộng phân số
Phanso Cong(Phanso a, Phanso b) 
{
    Phanso c;
    c.mau = a.mau * b.mau;
    c.tu = a.mau * b.tu + b.mau * a.tu;
    return Rutgon(c);
}

//Phép trừ phân số 
Phanso Tru(Phanso a, Phanso b) 
{
    Phanso c;
    c.mau = a.mau * b.mau;
    c.tu = -a.mau * b.tu + b.mau * a.tu;
    return Rutgon(c);
}

//Phép nhân phân số
Phanso Nhan(Phanso a, Phanso b) 
{
    Phanso c;
    c.mau = a.mau * b.mau;
    c.tu = a.tu * b.tu;
    return Rutgon(c);
}

//Phép chia phân số
Phanso Chia(Phanso a, Phanso b) 
{
    Phanso c;
    c.mau = a.mau * b.tu;
    c.tu = b.mau * a.tu;
    return Rutgon(c);
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
    Phanso a, b;
    string frac; //xâu định dạng input
    while (true) {
        // Nhập phần số thứ nhất
        cout << "Nhap phan so thu nhat: {tu/mau}" << "\n";
        cin >> frac;
        if (!CheckValidInput(frac, a)) { //Nếu phân số không hợp lệ thì nhập lại
            cout << "Vui long nhap phan so hop le!!!!!" << "\n";
        } else break;
    }
    while (true) {
        // Nhập phân số thứ hai
        cout << "Nhap phan so thu hai: {tu/mau}" << "\n";
        cin >> frac;
        if (!CheckValidInput(frac, b)) { //Nếu phân số không hợp lệ thì nhập lại
            cout << "Vui long nhap phan so hop le!!!!!" << "\n";
        } else {
            break;
        }
    }
    
    // Lần lượt thực hiện phép tính
    Phanso Tong = Cong(a, b), 
           Hieu = Tru(a, b),
           Tich = Nhan(a, b),
        Thuong = Chia(a, b);

    // In các kết quả
    cout << "Tong hai phan so la: " << Tong.tu << '/' << Tong.mau << "\n";
    cout << "Hieu hai phan so la: " << Hieu.tu << '/' << Hieu.mau << "\n";
    cout << "Tich hai phan so la: " << Tich.tu << '/' << Tich.mau<< "\n";
    cout << "Thuong hai phan so la: " << Thuong.tu << '/' << Thuong.mau << "\n";
    return 0;
}
