#include "j_error.h"

j_error::j_error() = default;
j_error::j_error(const std::string& str) noexcept {
	this->str = new char[str.length() + 1];
	std::copy(str.begin(), str.end(), this->str);
	this->str[str.length()] = '\0';
}
j_error::~j_error() {
	delete[] str;
}
const char* j_error::what() const noexcept {
	return str;
}