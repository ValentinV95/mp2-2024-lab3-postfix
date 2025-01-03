#include "StringToDouble.h"

double StringToDouble_1(const std::string& v) {
	bool isPoint = 0;
	int ind = 0;
	double result = 0.0;
	int start = v[0] == '-';
	std::string integer_part = "";
	std::string floating_part = "";
	std::string power_part = "";
	if (v.size() == 0) {
		throw std::logic_error("Error at position 0: Empty string");
	}
	if (!(v.back() >= '0' && v.back() <= '9')) {
		throw std::logic_error("Error at position " + std::to_string(v.size() - 1) + ": Ends with an invalid character");
	}
	for (int i = start; i < v.size(); i++) {
		ind = i;
		if (v[i] == '.') {
			isPoint = 1;
			break;
		}
		else if (v[i] == 'e' || v[i] == 'E') {
			break;
		}
		if (!((i == 0 && v[i] == '-') || (v[i] >= '0' && v[i] <= '9'))) {
			throw std::logic_error("Error at position " + std::to_string(i) + ": Invalid character '" + v[i] + "'");
		}
		integer_part += v[i];
	}
	double ten = pow(10.0, integer_part.size() - 1);
	if (isPoint)
		for (int i = ind + 1; i < v.size(); i++) {
			ind = i;
			if (v[i] == 'e' || v[i] == 'E') {
				break;
			}
			if (!(v[i] >= '0' && v[i] <= '9')) {
				throw std::logic_error("Error at position " + std::to_string(i) + ": Invalid character '" + v[i] + "'");
			}
			floating_part += v[i];
		}
	if (ind + 1 < v.size() && v[ind + 1] != '+' && v[ind + 1] != '-') {
		throw std::logic_error("Error at position " + std::to_string(ind + 1) + ": There must be a plus or minus after 'e'");
	}
	for (int i = ind + 2; i < v.size(); i++) {
		if (v[i] < '0' || v[i]>'9') {
			throw std::logic_error("Error at position " + std::to_string(i) + ": The power of 'e' must be an integer. Found: '" + v[i] + "'");
		}
		power_part += v[i];
	}
	for (int i = 0; i < integer_part.size(); i++) {
		result += (integer_part[i] - '0') * ten;
		ten /= 10.0;
	}
	for (int i = 0; i < floating_part.size(); i++) {
		result += (floating_part[i] - '0') * ten;
		ten /= 10.0;
	}
	double s = 0;
	ten = pow(10.0, power_part.size() - 1);
	for (int i = 0; i < power_part.size(); i++) {
		s += (power_part[i] - '0') * ten;
		ten /= 10.0;
	}
	double f = pow(10.0, s);
	if (v[ind + 1] == '+') {
		result *= f;
	}
	else if (v[ind + 1] == '-') {
		result /= f;
	}
	if (v[0] == '-') {
		result *= (-1);
	}
	return result;
}