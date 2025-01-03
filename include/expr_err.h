#pragma once
#include <stdexcept>
class expression_error : std::exception
{
private:
	std::string const message;
public:
	expression_error() = default;
	expression_error(std::string const& mes) : message{ mes } {};
	char const* what() const noexcept override { return message.c_str(); };
};