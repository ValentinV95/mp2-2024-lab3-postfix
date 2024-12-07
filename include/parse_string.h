#include <string>
#include <vector.h>
#define en_l(a) (a>=97 && a<=122)
#define en_u(a) (a>=65 && a<=90)
#define _dig(a) (a>=48 && a<=57)
#define _right_symbols(a) (a!=44 && a>=40 && (!(a>=58 && a<=64)) && (!(a>=91 && a<=94)) && a!=96 && a<=122)
#define func_sym 78

bool split_sym(const char& t) {

	vector<char> sp = { '+','-','/',' ','*' };
	for (auto& el : sp) {
		if (el == t) {
			return true;
		}
	}
	return false;
}

std::string substr(int l, int r,const std::string& d)
{
	std::string s = "";
	for (int i = l; i < r; i++) {
		s += d[i];
	}
	return s;
}


void error(int st, int ind) {
	if (!st) return;
	
	switch (st)
	{
	default:
		std::cout << "incorrect input!\n";
		exit(2768);
		break;
	case -1:
		std::cout << "There is no opening parenthesis for ')' in position " << ind << std::endl;
		exit(-1);
		break;
	case 1:
		std::cout << "There is no closing parenthesis for ')' in position " << ind << std::endl;
		exit(1);
		break;
	case 2:
		std::cout << "The brackets do not contain anything from position " << ind << std::endl;
		exit(2);
		break;
	case -2:
		std::cout << "incorrect symbol at the end (position " << ind << ")\n";
		exit(-2);
		break;
	case -3:
		std::cout << "incorrect symbol in position " << ind << std::endl;
		exit(-3);
		break;
	case 3:
		std::cout << "incorrect point in expression in position " << ind << std::endl;
		exit(3);
		break;
	}

}

int prepars(std::string& s, vector<int>& spaces, int& ind) {

	std::string new_s = "";
	int cnt_o = 0,cnt_c = 0;
	for (auto i = 0; i < s.size();i++) {
		
		if (s.at(i) == ' ') {
			spaces.push_back(i);
			continue;
		}
		if (!_right_symbols(s.at(i))) {
			ind = i;
			return -3;
		}
		if (s.at(i) == '(') {
			cnt_o++;
		}else if (s.at(i) == ')') {
			cnt_o--;
		}	
		if (cnt_o < 0) {
			ind = i;
			return -1;
		}
		if (s.at(s.size() - i - 1) == ')') {
			cnt_c++;
		}
		else if (s.at(s.size() - i - 1) == '(') {
			cnt_c--;
		}
		if (cnt_c < 0) {
			ind = s.size()-1-i;
			return 1;
		}

		new_s.push_back(s.at(i));
		if (new_s.size() > 1 && new_s.back() == ')' && new_s.at(new_s.size() - 2) == '(') {
			ind = i-1;
			while (s.at(ind) == ' ') ind--;
			return 2;
		}
	}
	if (new_s.back() != ')' && (!_dig(new_s.back())) && (!en_l(new_s.back())) && (!en_u(new_s.back())) && new_s.back()!='_') {
		ind = s.size()-1;
		while (s.at(ind) == ' ') ind--; return -2;
	}
	swap(new_s, s);
	return 0;
}
int check_raw(const vector<std::string>& vs,int& ind) {
	size_t real_ind = 0;
	for (int i = 0; i < vs.size(); i++) {
		if (vs.at(i).back() == '.') {
			ind = real_ind + vs.at(i).size() - 1;
			return 3;
		}
		real_ind += vs.at(i).size();
		
	}
	return 0;
}

void Main_Parser(std::string original) {
	int ind_err = 0;
	std::string s = original;
	vector<std::string> raw_parse;
	vector<int> spaces_ind;
	int st = prepars(s,spaces_ind,ind_err);
	error(st, ind_err);
	
	for (int i = 0; i < original.size(); i++) {
		if (original.at(i) == ' ')continue;
		if (original.at(i) == '(') {
			raw_parse.push_back("(");
		}
		else if (original.at(i) == ')') {
			raw_parse.push_back(")");
		}
		else if (original.at(i) == '+') {
			raw_parse.push_back("+");
		}
		else if (original.at(i) == '-') {
			raw_parse.push_back("-");
		}
		else if (original.at(i) == '*') {
			raw_parse.push_back("*");
		}
		else if (original.at(i) == '/') {
			raw_parse.push_back("/");
		}
		else if (original.at(i) == '.' || _dig(original.at(i))) {
			std::string digit = "";
			int point_cnt = 0;
			while (true) {
				if (i == original.size())break;
				if (point_cnt == 0 && original.at(i) == '.') {
					point_cnt++;
					digit += original.at(i);
					i++;
				}
				else if (_dig(original.at(i))) {
					digit += original.at(i);
					i++;
				}
				else {
					break;
				}
			}
			raw_parse.push_back(digit);
			if (i == original.size())continue;
			if (!((original.at(i) == 'e' || original.at(i) == 'E') && i < (original.size() - 2) && (original.at(i + 1) == '+' || original.at(i + 1) == '-') && (_dig(original.at(i + 2))))) {
				i--;
				continue;
			}
			else {
				raw_parse.back() += original.at(i);
				raw_parse.back() += original.at(i+1);
				i += 2;
				while (i < original.size() && _dig(original.at(i))) {
					raw_parse.back() += original.at(i);
					i++;
				}
				i--;
			}
		}
		else {
			std::string r = "";
			while (i < original.size() && (_dig(original.at(i)) || en_u(original.at(i)) || en_l(original.at(i)) || original.at(i) == '_')) {
				r += original.at(i);
				i++;
			}
			raw_parse.push_back(r);
			i--;
		}
	}
	st = check_raw(raw_parse, ind_err);
	error(st, ind_err);
	std::cout << raw_parse << std::endl;
}