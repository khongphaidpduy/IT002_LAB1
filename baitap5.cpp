#include <bits/stdc++.h> 

using namespace std;

// Cấu trúc đại diện ngày tháng năm
struct Date{
    int ngay;
    int thang;
    int nam;
};

// Số ngày mà tháng tương ứng có
// Notice: Ở bài này mình mặc định không có năm nhuận nhé
int lim[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
// Hàm kiểm tra định dạng ngày tháng năm có hợp lệ hay không
bool CheckValidInput(string inp, Date &a) 
{
    stringstream ss(inp);
    char slash, slash2;
    int kiemtra_ngay, kiemtra_thang, kiemtra_nam;
    if (ss >> kiemtra_ngay >> slash >> kiemtra_thang >> slash >> kiemtra_nam) {
        if (kiemtra_thang < 1 && kiemtra_thang > 12) return false; // Chỉ tồn tại tháng 1 đến tháng 12 
        if (kiemtra_ngay < 1 && kiemtra_ngay > lim[kiemtra_thang]) return false;
        a.ngay = kiemtra_ngay;
        a.thang = kiemtra_thang;
        a.nam = kiemtra_nam;
        return true;
    }
    return false;
}

//Hàm tình ngày kế tiếp
Date NgayTiepTheo(Date a) {
    Date c = a;
    c.ngay = a.ngay + 1;
    if (c.ngay > lim[c.thang]) {
        c.ngay = 1;
        c.thang++;
        if (c.thang > 12) {
            c.thang = 1;
            c.nam ++;
        }
    }
    return c;
}

// Hàm tính ngày trước đó 
Date NgayTruocDo(Date a) {
    Date c = a;
    c.ngay = a.ngay - 1;
    if (c.ngay < 1) {
        c.thang--;
        if (c.thang < 1) {
            c.thang = 12;
            c.nam--;
        }
        c.ngay = lim[c.thang];
    }
    return c;
}

//Ham cho biet ngay do la ngay thu may trong nam 
int calc(Date a) {
    int res = 0;
    for (int i = 1; i <= a.thang - 1; i++) 
    {
        res += lim[i];
    }
    res += a.ngay;
    return res;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    Date a;
    while (true) {
        cout << "Nhap mot ngay thang: {dd/mm/yyyy}" << "\n";
        string inp;
        cin >> inp;
        if (!CheckValidInput(inp, a)) { 
            cout << "Vui long nhap ngay thang hop le" << "\n";
        }
        else break;
    }
    
    Date Next = NgayTiepTheo(a),
        Prev = NgayTruocDo(a);
    int ans = calc(a);
    cout << "Ngay ke tiep la: " << Next.ngay << "/" << Next.thang << "/" << Next.nam << "\n";
    cout << "Ngay truoc ngay nay la: " << Prev.ngay << "/" << Prev.thang << "/" << Prev.nam << "\n";
    cout << "Ngay "<< a.ngay << '/' << a.thang << '/' << a.nam << " la ngay thu " << ans << " trong nam" << "\n";
    return 0;
}

