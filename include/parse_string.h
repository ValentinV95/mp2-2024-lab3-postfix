#pragma once
#define _USE_MATH_DEFINES
#include "parse_digits.h"
#include "lexem.h"
#include <cmath>
#define en_l(a) (a>=97 && a<=122)	//english lower
#define en_u(a) (a>=65 && a<=90)	//english upper
#define _dig(a) (a>=48 && a<=57)	//digits
#define func(a) (a=="cos" || a=="sin" || a=="tan" || a=="cot")
#define _opers(a) (a>=42 && a<=47 && a!=46 && a!=44)
#define _opers_with_b(a) (_opers(a) || a==40 || a==41)
#define _right_symbols(a) (a!=44 && a>=40 && (!(a>=58 && a<=64)) && (!(a>=91 && a<=94)) && a!=96 && a<=122)
#define func_sym 78	//i dont use it now



void USER_SET_VAR(lexem* l_) {
	if (l_->Get_VAL_NAME() == "e") {
		std::string q = "w";
		while (q != "y" && q != "n") {
			std::cout << "the variable name looks like a mathematical constant e = 2,7182818284... Use it?\ny/n\n";
			getline(std::cin, q);
			if (q != "y" && q != "n") {
				std::cout << "unknow answer!\n";
			}
		}
		if (q == "y") {
			l_->setValue_(M_E);
			return;
		}
	}
	else if (l_->Get_VAL_NAME() == "pi") {
		std::string q = "w";
		while (q != "y" && q != "n") {
			std::cout << "the variable name looks like a mathematical constant pi = 3,1415926535... Use it?\ny/n\n";
			getline(std::cin,q);
			if (q != "y" && q != "n") {
				std::cout << "unknow answer!\n";
			}
		}
		if (q == "y") {
			l_->setValue_(M_PI);
			return;
		}
	}
	std::cout << "Pls, type you variable \"";
	l_->print();
	std::cout << "\":  ";

	std::string s; getline(std::cin, s);
	l_->setValue_(parser(s));
	return;
}

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
		exit(1986);
		break;
	case -1:
		std::cout << "There is no opening parenthesis for ')' in position " << ind << std::endl;
		exit(-1);
		break;
	case 1:
		std::cout << "There is no closing parenthesis for '(' in position " << ind << std::endl;
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
	case 4:
		std::cout << "You cant do the operation in position " << ind << " after operation" << std::endl;
		exit(4);
		break;
	case -4:
		std::cout << "You must write digits in digit after point in position " << ind <<std::endl;
		exit(-4);
		break;
	case 5:
		std::cout << "You cant write second point in digit in position " << ind << std::endl;
		exit(5);
		break;
	case -5:
		std::cout << "You cant use points in variable's name in position " << ind << std::endl;
		exit(-5);
		break;
	case 6:
		std::cout << "You cant write digit after digit in position " << ind << std::endl;
		exit(6);
		break;
	case -6:
		std::cout << "You cant start expression with non-unar operation in position " << ind << std::endl;
		exit(-6);
		break;
	}

}

int prepars(std::string& s, vector<int>& spaces, int& ind) {

	std::string new_s = "";
	int cnt_o = 0,cnt_c = 0;
	for (auto i = 0; i < s.size();i++) {
		
		if (s.at(i) == ' ') {
			spaces.push_back(i);
			if (s.at(s.size() - i - 1) == ')') {
				cnt_c++;
			}
			else if (s.at(s.size() - i - 1) == '(') {
				cnt_c--;
			}
			if (cnt_c < 0) {
				ind = s.size() - 1 - i;
				return 1;
			}
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
		if (new_s.size() == 1 && new_s != "-" &&  _opers(new_s.back()) ) {
			ind = i;
			return -6;
		}
		if (new_s.size() > 1 && new_s.back() == ')' && new_s.at(new_s.size() - 2) == '(') {
			ind = i-1;
			while (s.at(ind) == ' ') ind--;
			return 2;
		}
		if (new_s.size() > 1) {
			if (_opers(new_s.back()) && _opers(new_s.at(new_s.size()-2)) && new_s.back()!='-') {
				ind = i;
				return 4;
			}
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

vector<lexem*> Main_Parser(std::string original) {
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
			size_t l_aft_point = 0;
			int ind_point = i;
			while (true) {
				if (i == original.size())break;
				
				if (point_cnt == 0 && original.at(i) == '.') {
					point_cnt++;
					ind_point = i;
					digit += original.at(i);
					i++;
				}
				else if (_dig(original.at(i))) {
					if (point_cnt) l_aft_point++;
					digit += original.at(i);
					i++;
				}
				else {
					if (original.at(i) == '.' && point_cnt) {
						error(5, i);
					}
					break;
				}
				
			}
			if (point_cnt && !l_aft_point) {
				error(-4, i-1);
			}
			raw_parse.push_back(digit);
			if (i == original.size())continue;
			if (!((original.at(i) == 'e' || original.at(i) == 'E') && i < (original.size() - 2) && (original.at(i + 1) == '+' || original.at(i + 1) == '-') && (_dig(original.at(i + 2))))) {
				i--;
				continue;
			}
			else {
				std::string pre_s = "";
				int pre_i = i;

				pre_s += original.at(i);
				pre_s += original.at(i+1);
				i += 2;
				while (i < original.size() && _dig(original.at(i))) {
					pre_s += original.at(i);
					i++;
				}
				if (i < original.size() && original.at(i) == '.') {
					i = pre_i;
				}
				else {
					raw_parse.back() += pre_s;
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
			if (i < original.size() && original.at(i) == '.') {
				error(-5, i);
			}
			raw_parse.push_back(r);

			i--;
		}
	}
	st = check_raw(raw_parse, ind_err);
	error(st, ind_err);

	vector<lexem*> LEXEM;
	vector<int> var_ind;
	vector<std::string> vars;
	size_t was_op = 0;
	for (int i = 0; i < raw_parse.size(); i++) {

		if (raw_parse.at(i) != "*" && i < raw_parse.size() - 1 && raw_parse.at(i + 1) == "(" && raw_parse[i]==")") {
		
				LEXEM.push_back(new operation(raw_parse[i], i, 0, false, true));//this sth
				LEXEM.push_back(new operation("*", i, 2, false, false));//*
				LEXEM.push_back(new operation(raw_parse[i + 1], i, 0, false, true));//(
				i++;
				was_op++;
				continue;
		}
		if (raw_parse.at(i) == "(" || raw_parse.at(i) == ")") {
			LEXEM.push_back(new operation(raw_parse[i], i, 0, false, true));
		}
		else if (raw_parse.at(i) == "+") {
			was_op++;
			LEXEM.push_back(new operation(raw_parse[i], i, 1, false,false));
		}else if (raw_parse.at(i) == "-") {
			if (i > 0 && LEXEM.back()->isOperation() && !(LEXEM.back()->Get_Lexem_ID() == -7) || was_op == 0) {
				//LEXEM.push_back(new operation(raw_parse[i], i, 1, true, false));
				auto tmp = 0;
				if(LEXEM.size())tmp=LEXEM.back()->Get_Lexem_ID();
				LEXEM.push_back(new operation("(", i, 0, false, true));
				LEXEM.push_back(new constant("-1", i, -1.0));
				LEXEM.push_back(new operation(")", i, 0, false, true));
				if (tmp == -6) {
					LEXEM.push_back(new operation("/", i, 2, false, false));
				}else{ LEXEM.push_back(new operation("*", i, 2, false, false)); }
			}
			else {
				
				LEXEM.push_back(new operation(raw_parse[i], i, 1, false, false));
			}
			was_op++;
		}
		else if (raw_parse.at(i) == "*") {
			LEXEM.push_back(new operation(raw_parse[i], i, 2, 0, false));
			was_op++;
		}
		else if (raw_parse.at(i) == "/") {
			LEXEM.push_back(new operation(raw_parse[i], i, 2, 0, false));
			was_op++;
		}
		else if (raw_parse.at(i).at(0) == '.' || _dig(raw_parse.at(i).at(0))) {
			if (i > 0 && !LEXEM.back()->isOperation() && LEXEM.back()->isConstanta()) {
				error(6, i);
			}
			LEXEM.push_back(new constant(raw_parse[i], i, parser(raw_parse[i])));
			was_op++;
		}
		else {
			bool isF = false;
			if (LEXEM.size() > 0 && LEXEM.back()->Get_Lexem_ID() == 1) {
				LEXEM.push_back(new operation("*", i, 2, false, false));
			}
			if (raw_parse.at(i) == "sin" || raw_parse.at(i) == "cos" || raw_parse.at(i) == "tan" || raw_parse.at(i) == "cot") {
				isF = true;
			}
			LEXEM.push_back(new variable(raw_parse[i], i, 0.0, isF));
			if (!LEXEM.back()->isFunction()) {
				int was = -1;
				for (size_t pt = 0; pt < vars.size(); pt++) {
					if (vars[pt] == raw_parse[i]) {
						was = pt;
						break;
					}
				}
				if (was == -1) {
					USER_SET_VAR(LEXEM.back());
					vars.push_back(raw_parse[i]);
					var_ind.push_back(LEXEM.size()-1);
				}
				else {
					LEXEM.back()->setValue_(LEXEM[var_ind[was]]->getValue());
				}
			}
			was_op++;
		}

	}
	return LEXEM;
}
