#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
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

bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
	void AddEvent(const Date& date, const string& event);
	bool DeleteEvent(const Date& date, const string& event);
	int  DeleteDate(const Date& date);

	/* ??? */ Find(const Date& date) const;

	void Print() const;

private:
	map<Date, string> m;

};

int main() {
  Database db;

  string command;
  while (getline(cin, command)) {
  	try {
		istringstream input(command);
		if (input) {
			string cmd;
			input >> cmd;
			if (cmd == "Add") {
				try {
					string date, event;
					input >> date >> event;
				} catch (exception &ex) {
					cout << ex.what() << endl;
				}
			} else {
				throw BadArgumentException("Unknown command: " + cmd);
			}
		}
  	} catch (BadArgumentException &ex) {
		cout << ex.what() << endl;
	}
  }

  return 0;
}