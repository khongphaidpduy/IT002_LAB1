#include <bits/stdc++.h>

using namespace std;

class Flight {
public:
    string flightCode;
    string departureDate; // dd/mm/yyyy
    string departureTime; // HH:MM
    string origin;
    string destination;

    Flight(string code, string date, string time, string orig, string dest)
        : flightCode(code), departureDate(date), departureTime(time), origin(orig), destination(dest) {}

    void display() const {
        cout << flightCode << " - " << departureDate << " " << departureTime << " - "
             << origin << " -> " << destination << endl;
    }
};

bool isValidFlightCode(const string &code) {
    return code.length() <= 5 && all_of(code.begin(), code.end(), [](char c) { return isalnum(c); });
}

bool isValidDate(const string &dateStr) {
    struct tm tm;
    return strptime(dateStr.c_str(), "%d/%m/%Y", &tm) != nullptr;
}

bool isValidTime(const string &timeStr) {
    struct tm tm;
    return strptime(timeStr.c_str(), "%H:%M", &tm) != nullptr;
}

bool isValidLocation(const string &location) {
    return location.length() <= 20 && all_of(location.begin(), location.end(), [](char c) { return isalpha(c) || c == ' '; });
}

Flight inputFlight() {
    string flightCode, departureDate, departureTime, origin, destination;

    while (true) {
        cout << "Nhập mã chuyến bay (tối đa 5 ký tự): ";
        cin >> flightCode;
        if (!isValidFlightCode(flightCode)) {
            cout << "Mã chuyến bay không hợp lệ. Vui lòng nhập lại." << endl;
            continue;
        }

        cout << "Nhập ngày bay (dd/mm/yyyy): ";
        cin >> departureDate;
        if (!isValidDate(departureDate)) {
            cout << "Ngày bay không hợp lệ. Vui lòng nhập lại." << endl;
            continue;
        }

        cout << "Nhập giờ bay (HH:MM): ";
        cin >> departureTime;
        if (!isValidTime(departureTime)) {
            cout << "Giờ bay không hợp lệ. Vui lòng nhập lại." << endl;
            continue;
        }

        cout << "Nhập nơi đi: ";
        cin.ignore();
        getline(cin, origin);
        if (!isValidLocation(origin)) {
            cout << "Nơi đi không hợp lệ. Vui lòng nhập lại." << endl;
            continue;
        }

        cout << "Nhập nơi đến: ";
        getline(cin, destination);
        if (!isValidLocation(destination)) {
            cout << "Nơi đến không hợp lệ. Vui lòng nhập lại." << endl;
            continue;
        }

        return Flight(flightCode, departureDate, departureTime, origin, destination);
    }
}

void displayFlights(const vector<Flight> &flights) {
    for (const auto &flight : flights) {
        flight.display();
    }
}

vector<Flight> findFlight(const vector<Flight> &flights, const string &searchTerm) {
    vector<Flight> results;
    for (const auto &flight : flights) {
        if (flight.flightCode == searchTerm || flight.origin == searchTerm || flight.destination == searchTerm) {
            results.push_back(flight);
        }
    }
    return results;
}

vector<Flight> sortFlights(vector<Flight> &flights) {
    sort(flights.begin(), flights.end(), [](const Flight &a, const Flight &b) {
        struct tm tmA, tmB;
        strptime((a.departureDate + " " + a.departureTime).c_str(), "%d/%m/%Y %H:%M", &tmA);
        strptime((b.departureDate + " " + b.departureTime).c_str(), "%d/%m/%Y %H:%M", &tmB);
        return mktime(&tmA) < mktime(&tmB);
    });
    return flights;
}

vector<Flight> listFlightsFromLocation(const vector<Flight> &flights, const string &location, const string &date) {
    vector<Flight> results;
    for (const auto &flight : flights) {
        if (flight.origin == location && flight.departureDate == date) {
            results.push_back(flight);
        }
    }
    return results;
}

int countFlights(const vector<Flight> &flights, const string &origin, const string &destination) {
    int count = 0;
    for (const auto &flight : flights) {
        if (flight.origin == origin && flight.destination == destination) {
            count++;
        }
    }
    return count;
}

int main() {
    vector<Flight> flights;
    int numFlights;

    cout << "Nhập số lượng chuyến bay: ";
    cin >> numFlights;
    cin.ignore();

    for (int i = 0; i < numFlights; i++) {
        flights.push_back(inputFlight());
    }

    // Hiển thị danh sách chuyến bay đã sắp xếp
    flights = sortFlights(flights);
    cout << "\nDanh sách chuyến bay đã sắp xếp theo ngày và giờ khởi hành:\n";
    displayFlights(flights);

    // Tìm kiếm chuyến bay
    string searchTerm;
    cout << "\nNhập mã chuyến bay, nơi đi hoặc nơi đến để tìm kiếm: ";
    getline(cin, searchTerm);
    vector<Flight> foundFlights = findFlight(flights, searchTerm);
    cout << "\nKết quả tìm kiếm:\n";
    displayFlights(foundFlights);

    // Liệt kê chuyến bay từ nơi nhất định trong ngày
    string location, date;
    cout << "\nNhập nơi cần liệt kê chuyến bay: ";
    getline(cin, location);
    cout << "Nhập ngày (dd/mm/yyyy): ";
    getline(cin, date);
    vector<Flight> flightsFromLocation = listFlightsFromLocation(flights, location, date);
    cout << "\nDanh sách chuyến bay từ " << location << " vào ngày " << date << ":\n";
    displayFlights(flightsFromLocation);

    // Đếm số lượng chuyến bay từ nơi đi đến nơi đến
    string origin, destination;
    cout << "\nNhập nơi đi: ";
    getline(cin, origin);
    cout << "Nhập nơi đến: ";
    getline(cin, destination);
    int count = countFlights(flights, origin, destination);
    cout << "\nSố lượng chuyến bay từ " << origin << " đến " << destination << ": " << count << endl;

    return 0;
}
