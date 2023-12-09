// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"

double string_to_decimal(const string &expr) {
	double res = 0.0;
	if (expr.size() == 0) {
		throw invalid_argument("Empty string");
	}
	for (int i = expr.size() - 1; i > 0; i--) {
		res += static_cast<double>(expr[i]) - static_cast<double>('0');
		res /= 10;
	}
	if (expr[0] == '-') {
		res *= -1;
	}
	else {
		res += static_cast<double>(expr[0]) - static_cast<double>('0');
		res /= 10;
	}
	return res;
}

int string_to_integer(const string &expr) {
	int res = 0;
	if (expr.size() == 0) {
		throw invalid_argument("Empty string");
	}
	for (int i = expr.size() - 1; i >= 0; i--) {
		res += static_cast<double>(expr[i]) - static_cast<double>('0');
		res *= 10;
	}
	if (expr[0] == '-') {
		res *= -1;
	}
	else {
		res += static_cast<double>(expr[0]) - static_cast<double>('0');
		res *= 10;
	}
	return res;
}

double exp_form_to_double(const string &expr) {
	// init state machine matrix
	const size_t TRASH = 0;
	const size_t a_size = 6;
	const size_t s_size = 10;
	const size_t a0[a_size] = { 0, 0, 0, 0, 0, 0 };
	const size_t a1[a_size] = { 4, 3, 2, 6, 0, 0 };
	const size_t a2[a_size] = { 4, 3, 0, 6, 0, 0 };
	const size_t a3[a_size] = { 3, 3, 0, 5, 7, 0 };
	const size_t a4[a_size] = { 0, 0, 0, 5, 7, 0 };
	const size_t a5[a_size] = { 5, 5, 0, 0, 7, 0 };
	const size_t a6[a_size] = { 5, 5, 0, 0, 0, 0 };
	const size_t a7[a_size] = { 0, 0, 8, 0, 0, 8 };
	const size_t a8[a_size] = { 0, 9, 0, 0, 0, 0 };
	const size_t a9[a_size] = { 9, 9, 0, 0, 0, 0 };
	const size_t *states_array[s_size] = { a0, a1, a2, a3, a4, a5, a6, a7, a8, a9 };
	// get 3 nums
	string first_num = "";
	string mov = "";
	string second_num = "";
	size_t i = 0;
	size_t cur_state = 1;
	size_t cur_slot = 0;
	while (i < expr.size()) {
		// move
		if (expr[i] == '0') { cur_state = states_array[cur_state][0]; }
		else if (expr[i] >= '1' && expr[i] <= '9') { cur_state = states_array[cur_state][1]; }
		else if (expr[i] == '-') { cur_state = states_array[cur_state][2]; }
		else if (expr[i] == '.') { cur_state = states_array[cur_state][3]; }
		else if (expr[i] == 'e') { cur_state = states_array[cur_state][4]; }
		else if (expr[i] == '+') { cur_state = states_array[cur_state][5]; }
		else {
			throw std::invalid_argument("Bad number");
		}
		if (cur_state == 0) {
			break;
		}
		if (expr[i] == '.') {
			cur_slot = 1;
		}
		else if (expr[i] == 'e') {
			cur_slot = 2;
		}
		else if (expr[i] == '-' || (expr[i] >= '0' && expr[i] <= '9')) {
			// add to corresponding num
			switch (cur_slot) {
			case 0:
				first_num += expr[i];
				break;
			case 1:
				second_num += expr[i];
				break;
			case 2:
				mov += expr[i];
				break;
			}
		}
		i++;
	}
	// find result
	double res;
	res = string_to_integer(first_num) + string_to_decimal(second_num);
	res *= std::pow(10, string_to_integer(mov));
	return res;
}