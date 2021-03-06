#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class BadArgumentException : exception {
public:
	explicit BadArgumentException(string const &msg) {message = msg;}
	BadArgumentException() {message = "";}

	virtual const char* what() const throw() {
		return message.c_str();
	}

private:
	string message;
};

class Date {
public:
	Date(int year, int month, int day) {
		if (month < 1 || month > 12) {
			throw BadArgumentException("Month value is invalid: " + to_string(month));
		} else if (day < 1 || day > 31) {
			throw BadArgumentException("Day value is invalid: " + to_string(day));
		}
		this->year = year;
		this->month = month;
		this->day = day;
	}

	int GetYear() const {return year;}
	int GetMonth() const {return month;}
	int GetDay() const {return day;}

private:
	int year;
	int month;
	int day;

	Date() {
		this->year = 0;
		this->month = 0;
		this->day = 0;
	}
};

bool operator<(const Date& lhs, const Date& rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
            vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		m[date].insert(event);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		auto it = m.find(date);
		if (it != m.end()) {
			auto itSet = it->second.find(event);
			if (itSet != it->second.end()) {
				it->second.erase(event);
				return true;
			}
		}
		return false;
	}

	int  DeleteDate(const Date& date) {
		auto it = m.find(date);
		int n;
		if (it != m.end()) {
			n = it->second.size();
			m.erase(it);
		} else {
			n = 0;
		}
		return n;
	}

	void Find(const Date& date) const {
		auto it = m.find(date);
		if (it != m.end())
			PrintSet(it->second);
	}

	void	PrintSet(set<string> const &s) const {
		for (auto const &i : s) {
			cout << i << endl;
		}
	}

	void Print() const {
		for (auto const &i : m) {
			stringstream ss;
			ss << setfill('0') << setw(4) << i.first.GetYear() << '-'
				 << setw(2) << i.first.GetMonth() << '-' << setw(2) << i.first.GetDay();
			string date = ss.str();
			for (auto const &s: i.second) {
				cout << date << " " << s << endl;
			}
		}
	}

private:
	map<Date, set<string> > m;

};

Date ParseDate(string const &date) {
	istringstream input(date);
	int year;
	char dash1, dash2;
	int month;
	int day;
	input >> year >> dash1 >> month >> dash2 >> day;
	if (input.fail() || !input.eof() || (dash1 != '-' || dash2 != '-'))
		throw BadArgumentException("Wrong date format: " + date);
	return Date(year, month, day);
}

int main() {
	Database db;

  	string command;
  	try {
  		while (getline(cin, command)) {
  			istringstream input(command);
		  	if (input) {
		  		string cmd;
		  		input >> cmd;
		  		if (cmd == "Add") {
		  			string date, event;
		  			input >> date >> event;
		  			db.AddEvent(ParseDate(date), event);
		  		} else if (cmd == "Del") {
		  			string date;
		  			input >> date;
		  			if (!input.eof()) {
		  				string event;
		  				input >> event;
		  				if (db.DeleteEvent(ParseDate(date), event)) {
		  					cout << "Deleted successfully" << endl;
		  				} else {
		  					cout << "Event not found" << endl;
		  				}
		  			} else {
		  				int n = db.DeleteDate(ParseDate(date));
		  				cout << "Deleted " << n << " events" << endl;
		  			}
		  		} else if (cmd == "Find") {
		  			string date;
					input >> date;
					db.Find(ParseDate(date));
		  		} else if (cmd == "Print") {
		  			db.Print();
		  		} else if (cmd.empty()) {
		  			continue ;
		  		} else {
		  			throw BadArgumentException("Unknown command: " + cmd);
		  		}
		  	}
  		}
  	} catch (BadArgumentException &ex) {
  		cout << ex.what() << endl;
  		return 1;
  	}

  	return 0;
}
