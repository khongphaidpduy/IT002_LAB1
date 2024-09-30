#include <bits/stdc++.h> 

using namespace std;

// Số ngày mà tháng tương ứng có
// Notice: Ở bài này mình mặc định không có năm nhuận nhé
int lim[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//Cấu trúc đại diện cho ngày 
struct Date {
	int ngay;
	int thang;
	int nam;
	//kiểm tra ngày hợp lệ
	bool checkvalid() 
	{
		if (thang < 1 || thang > 12 || ngay < 1 || ngay > lim[thang]) return false;
		return true;
	}
};

//Cấu trúc đại diện sổ tiết kiệm
struct SoTietKiem {
	string id; //Mã sổ
	string type; //Loại tiết kiệm
	string name; //Họ và tên khách hàng
	string cmnd; // Chứng mình nhân dân
	Date OpenDate; //Ngày mở sổ
	double depositAmount; //Số tiền gửi

	void input();
	void display();
	double calcInterest (double interestRate);
	void withdraw();
};

//Hàm nhập dữ liệu
void SoTietKiem::input() {
	// Nhập mã số 
	do {
		cout << "Nhập mã số (tối đa 5 ký tự): " << "\n";
		cin >> id;
	} while (id.size() > 5 || id.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != string::npos);

	// Nhập loại tiết kiệm 
	do {
		cout << "Nhập loại tiết kiệm (tối đa 10 ký tự): " << "\n";
		cin >> type;
	} while (type.size() > 10);

	//Nhập họ và tên khách hàng 
	do {
		cout << "Nhập họ và tên khách hàng (tối đa 30 ký tự): " << "\n";
		cin.ignore();
		getline(cin, name);
	}	
	while (name.size() > 30 || name.find_first_of("0123456789,./;'[]=-`~!@#$%^&*()_+<>?:{}|)") != string::npos);

	// Nhập CMND 
	do {
		cout << "Nhập chứng minh nhân dân (số nguyên 4 byte): " << "\n";
		cin >> cmnd;
	} while (cmnd.size() != 9 && cmnd.size() != 12 || cmnd.find_first_not_of("1234567890") != string::npos);

	//Nhập ngày mở sổ 
	do {
		cout << "Nhập ngày mở sổ (dd mm yyyy): " << "\n";
		cin >> OpenDate.ngay >> OpenDate.thang >> OpenDate.nam;
	} while (!OpenDate.checkvalid());

	// Nhập số tiền gửi 
	do {
		cout << "Nhập số tiền gửi (số dương): " << "\n";
		cin >> depositAmount;
	} while (depositAmount <= 0);
}

//Hàm xuất dữ liệu 
void SoTietKiem::display()
{
	cout << "Mã sổ: " << id << "\n";
	cout << "Loại tiết kiệm: " << type << "\n";
	cout << "Họ tên khách hàng: " << name << "\n";
	cout << "Chứng minh nhân dân: " << cmnd << "\n";
	cout << "Ngày mở sổ: " << OpenDate.ngay << "/" << OpenDate.thang << "/" << OpenDate.nam << "\n";
	cout << "Số tiền gửi: " << depositAmount << "\n";
}

//Cập nhật lãi suất 
double SoTietKiem::calcInterest(double interestRate) {
    int months = 0; // Tính số tháng từ ngày mở sổ đến hiện tại
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    int currentday = ltm->tm_mday;
    int currentMonth = ltm->tm_mon + 1; // Tháng từ 0 đến 11
    int currentYear = ltm->tm_year + 1900;

    // Tính số tháng
    if (currentYear == OpenDate.nam) {
        months = currentMonth - OpenDate.thang;
    } else {
        months = (currentYear - OpenDate.nam) * 12 + (currentMonth - OpenDate.thang);
    }

    double interest = 0;
    if (type == "nganhan" && months <= 6) {
        interest = depositAmount * (interestRate / 100) * (months / 12.0);
    } else if (type == "daihan") {
        interest = depositAmount * (interestRate / 100) * (months / 12.0);
    }

    return interest;
}

// Chức năng rút tiền
void SoTietKiem::withdraw() {
    double withdrawAmount;
    cout << "Nhập số tiền muốn rút: ";
    cin >> withdrawAmount;

    if (withdrawAmount > depositAmount) {
        cout << "Số tiền rút không thể lớn hơn số tiền gửi." << endl;
        return;
    }

    depositAmount -= withdrawAmount;

    // Nếu rút trước hạn
    if (type == "nganhan") {
        cout << "Rút trước hạn, lãi suất sẽ được tính lại!" << endl;
        // Tính lãi suất thấp hơn
        double reducedInterest = calcInterest(0.5);
        cout << "Tiền lãi sau khi rút: " << reducedInterest << endl;
    }
    cout << "Số dư còn lại của tài khoản là: " << depositAmount << "\n";
}

// Chức năng tìm kiếm

void Search(vector<SoTietKiem> &books, const string &SearchTerm, int &index) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].cmnd == SearchTerm || books[i].id == SearchTerm) {
            books[i].display();
            cout << "\n";
           	index = i;
            return;
        }
    }
    cout << "Không tìm thấy sổ" << "\n";
    return;
} 

// Chức năng liệt kê 

void lists(vector<SoTietKiem> &books) {
    for (int i = 0; i < books.size(); i++) {
        books[i].display();
        cout << "\n";
    }
} 

//Sắp xếp danh sách 
void sortByDepositAmount(vector<SoTietKiem> &books) {
    sort(books.begin(), books.end(), [](const SoTietKiem &a, const SoTietKiem &b) {
        return a.depositAmount > b.depositAmount; // Số tiền gửi giảm dần
    });
}

void sortByOpenDate(vector<SoTietKiem> &books) {
    sort(books.begin(), books.end(), [](const SoTietKiem &a, const SoTietKiem &b) {
        // So sánh ngày mở sổ
        if (a.OpenDate.nam != b.OpenDate.nam)
            return a.OpenDate.nam < b.OpenDate.nam;
        if (a.OpenDate.thang != b.OpenDate.thang)
            return a.OpenDate.thang < b.OpenDate.thang;
        return a.OpenDate.ngay < b.OpenDate.ngay;
    });
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    vector <SoTietKiem> Danhsach;
    int choice;
    do {
    	cout << "---QUẢN LÝ SỔ TIẾT KIỆM---" << endl;
    	cout << "1. Thêm sổ tiết kiệm" << endl;
        cout << "2. Tìm kiếm sổ tiết kiệm" << endl;
        cout << "3. Liệt kê sổ tiết kiệm" << endl;
        cout << "4. Cập nhật lãi suất" << endl;
        cout << "5. Rút tiền" << endl;
        cout << "6. Sắp xếp" << endl;
        cout << "0. Thoát" << endl;
        cout << "Nhập lựa chọn: ";
        cin >> choice;

        switch (choice) {
        	case 1: {
        		SoTietKiem book;
        		book.input();
        		Danhsach.push_back(book);
        		break;	
        	}
        	case 2: {
        		string curID;
        		cout << "Nhập CMND hoặc mã số để tìm " << "\n";
        		cin >> curID;
        		int index;
        		Search(Danhsach, curID, index);
        		break;
        	}
        	case 3: {
        		lists(Danhsach);
        		break;
        	}
        	case 4: {
        		//Xin thua, em k biết xử lý ;-;
        		cout << "Coming Soon" << "\n";
        		break;
        	}
        	case 5: {
        		string curID;
        		cout << "Nhập CMND hoặc mã số để truy cập sổ " << "\n";
      			cin >> curID;
      			int index;
        		Search(Danhsach, curID, index);
        		Danhsach[index].withdraw();
        		break;
        	}
        	case 6: {
        		int opt;
        		cout << "1. Để sắp xếp theo số dư" << "\n";
        		cout << "2. Để sắp xếp theo ngày mở sổ" << "\n";
        		cout << "Nhập lựa chọn "<< "\n";
        		cin >> opt;
        		if (opt == 1) sortByDepositAmount(Danhsach);
        		if (opt == 2) sortByOpenDate(Danhsach);
        		break;
              	}
        }
    } while (choice != 0);
    cout << "SEE YOU LATER!!!!!" << "\n";
    return 0;
}

