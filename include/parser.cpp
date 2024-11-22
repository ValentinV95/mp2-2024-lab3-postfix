#include "parser.h"

using namespace std;

double parser(string& s) {
	double res = 0.0;
	double ten = 10.0;
	int counter = 0;
	bool flag = true;
	int it = 0;
	if (it == s.length()) return 0.0;
	if (s[it] == '-') {
		flag = false;
		++it;
	}
	if (it == s.length()) throw invalid_argument(to_string(it - 1));
	if (!('0' <= s[it] && s[it] <= '9') && (s[it] != '.')) throw invalid_argument(to_string(it));

	while ('0' <= s[it] && s[it] <= '9' && it != s.length()) {
		res *= ten;
		res += s[it] - '0';
		++it;
	}

	if (it == s.length()) {
		if (flag == false) res *= (-1);
		return res;
	}
	if (s[it] != '.' && s[it] != 'e' && s[it] != 'E') throw invalid_argument(to_string(it));

	if (s[it] == '.') {
		++it;
		if (it == s.length()) throw invalid_argument(to_string(it - 1));
		if (!('0' <= s[it] && s[it] <= '9')) throw invalid_argument(to_string(it));
	}

	while ('0' <= s[it] && s[it] <= '9') {

		res += double(s[it] - '0')/(ten);
		++it;
		ten *= 10.0;
	}

	if (it == s.length()) {
		if (flag == false) res *= (-1);
		return res;
	}

	if (it == 0) throw invalid_argument(to_string(it));

	if (flag == false) res *= (-1);

	if (s[it] == 'e' || s[it] == 'E') {
		if (++it == s.length()) throw invalid_argument(to_string(it - 1));
		if (s[it] == '-') {
			flag = false;
			++it;
		}
		else if (s[it] == '+') {
			flag = true;
			++it;
		}
		else throw invalid_argument(to_string(it));
	}
	ten = 10.0;
	if (it == s.length()) throw invalid_argument(to_string(it - 1));
	if (!('0' <= s[it] && s[it] <= '9')) throw invalid_argument(to_string(it));
	counter = 0;
	while (it != s.length()) {
		if (!('0' <= s[it] && s[it] <= '9')) throw invalid_argument(to_string(it));
		counter *= ten;
		counter += (s[it] - '0');
		++it;
	}
	for (; counter > 0; --counter) {
		if (flag) res *= ten;
		else res /= ten;
	}
	return res;
}