#include <iostream>
#include <vector>
#include <string>

using namespace std;

double parser(string& s) {
	double res = 0.0;
	double bad = 0.0/0.0;
	double ten = 10.0;
	int counter = 0;
	bool flag = true;
	string::iterator it = s.begin();
	if (it == s.end()) return 0.0;

	if (*it == '-') {
		flag = false;
		++it;
		if (!('0' <= *it && *it <= '9') && (*it != '.')) return bad;
	}

	if (it == s.end()) return bad;

	while ('0' <= *it && *it <= '9' && it != s.end()) {
		res *= 10;
		res += *it - '0';
		++it;
	}


	if (it == s.end()) { 
		if (flag == false) res *= (-1);
		return res;
	}

	if (*it != '.' && *it != 'e') return bad;

	if (*it == '.') {
		++it;
	}

	if (it == s.end()) return bad;

	while ('0' <= *it && *it <= '9') {

		res += double(*it - '0')/(ten);
		++it;
		ten *= 10.0;
	}

	if (it == s.end()) {
		if (flag == false) res *= (-1);
		return res;
	}

	if (it == s.begin()) return bad;

	if (flag == false) res *= (-1);

	if (*it == 'e') { ++it;

		if (*it == '-') {
		flag = false;
		++it;
		}
		else if (*it == '+') {
			flag = true;
			++it;
		}
		else return bad;
	}

	if (it == s.end() || !('0' <= *it && *it <= '9')) return bad;
	counter = 0;
	while (it != s.end()) {
		counter *= 10;
		counter += (*it - '0');
		++it;
	}
	for (; counter > 0; --counter) {
		if (flag) res *= 10;
		else res /= 10;
	}
	return res;
}

int main() {
	double a = 0.0;
	string s;
	cin >> s;
	try {
		cout << (parser(s) == stod(s)) << endl;
	}
	catch(exception& e) {

	}
	cout << parser(s) << endl;
	return 0;
}