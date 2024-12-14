#include "parse_digits.h"

#define isDigit(t) (0<=(t) && (t)<=9)

double bin_pow(double a, int b) {
	double res = 1.0;
	while (b) {
		if (b & 1) {
			res = res * a;
		}
		b /= 2;
		a = a * a;
	}
	return res;
}

bool dfs(std::string& s, int pos, int r,std::string& error) {	//Это тот самый автомат
	switch (r)
	{
	default:
		return false;
	case 1:
		if (s[pos] == '.' || s[pos] == '-' || isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, (s[pos] == '.') ? 4 : (s[pos] == '-' ? 2 : 3),error);
		}
		else {
			return false;
		}
	case 2:
		if (s[pos] == '.' || isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, (s[pos] == '.') ? 4 : 3,error);
		}
		else {
			return false;
		}
	case 3:
		if (s.size() == pos) { return true; }
		if (s[pos] == '.' || (s[pos] == 'e' || s[pos] == 'E') || isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, (s[pos] == '.') ? 4 : ((s[pos] == 'e'|| s[pos] == 'E') ? 6 : 3), error);
		}
		else {
			return false;
		}
	case 4:
		if (isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, 5,error);
		}
		else {
			return false;
		}
	case 5:
		if (s.size() == pos) return true;
		if ((s[pos] == 'e' || s[pos] == 'E') || isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, ((s[pos] == 'e' || s[pos] == 'E')) ? 6 : 5,error);
		}
		else {
			return false;
		}
	case 6:
		if (s[pos] == '-' || s[pos] == '+') {
			return dfs(s, pos + 1, 7,error);
		}
		else {
			return false;
		}
	case 7:
		if (isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, 8,error);
		}
		else {
			return false;
		}
	case 8:
		if (s.size() == pos) return true;
		if (isDigit(s[pos]-'0')) {
			return dfs(s, pos + 1, 8,error);
		}
		else {
			return false;
		}
	}
}

double re_ans(std::string& s) {
	int pos = 0;
	int mn = 1;
	if (s[0] == '-') {
		mn = -1; pos++;
	}
	vector<int> r, im, e;
	while (s.size() > pos && isDigit(s[pos]-'0'))
	{
		r.push_back(s[pos++] - '0');
	}
	if (s[pos] == '.') {
		pos++;
		while (s.size() > pos && isDigit(s[pos]-'0')) {
			im.push_back(s[pos++] - '0');
		}
	}
	bool min_e = 0;
	if (s[pos] == 'e'|| s[pos] == 'E') {
		pos++;
		if (s[pos++] == '-') min_e = 1;

		while (s.size() > pos && isDigit(s[pos]-'0')) {
			e.push_back(s[pos++] - '0');
		}
	}
	double ans = 0.0;
	if (r.size()) {
		double p1 = bin_pow(10.0, r.size() - 1);
		for (auto& el : r) {
			ans += el * p1;
			p1 /= 10.0;
		}
	}
	if (im.size()) {
		double p1 = 1.0 / 10.0;
		for (auto& el : im) {
			ans += el * p1;
			p1 /= 10.0;
		}
	}
	if (e.size() != 0) {
		int y = 0;
		double p1 = bin_pow(10.0, e.size() - 1);
		for (auto& el : e) {
			y += p1 * el;
			p1 /= 10;
		}
		double uwu = bin_pow(10.0, y);
		if (min_e) {
			ans *= 1.0 / uwu;
		}
		else {
			ans *= uwu;
		}
	}
	return ans * mn;
}



double parser(std::string& s) {
	std::string err = "";
	if (!dfs(s, 0, 1,err)) {
		throw std::exception("dsfgf");
	}
	const double res = re_ans(s);
	return res;
}