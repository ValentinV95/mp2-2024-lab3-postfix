#include "parsers.h"
#include "expr_err.h"
#define IsLetter(c)		(( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' ))
#define IsDigit(c)		('0' <= c && c <= '9')
#define IsMath(c)		((c=='*') || (c=='+') || (c=='-') || (c=='/') || (c=='^'))

double ToDouble(char c)
{
	return static_cast<double>(c - '0');
}

unsigned int ToInt(char c)
{
	return static_cast<unsigned int>(c - '0');
}

double POW(unsigned long long pw)
{
	double a = 10.0;
	double tmp = a, res=1.0;
	unsigned long long int _tmp = 1;
	for (int i = 0; i < 64 && _tmp <= pw; i++)
	{
		if (_tmp & pw)
			res *= tmp;
		tmp *= tmp;
		_tmp <<= 1;
	}
	return res;
}

string PreParse(string const& s)
{
	string s_res("");
	size_t i = 0, sz = s.size();
	int bracket_counter = 0;
	bool sp_prev = false;
	while (s[i] == ' ' && i<sz)
		i++;
	for (; i < sz; i++)
	{
		if (s[i] == ' ')
			sp_prev = true;
		else
		{
			if (s[i] == '(')
				bracket_counter++;
			else if (s[i] == ')')
				bracket_counter--;
			if (sp_prev)
			{
				s_res += ' ';
				sp_prev = false;
			}
			s_res += s[i];
		}
		if (bracket_counter < 0)
			throw expression_error("No oppening bracket for ) at " + to_string(i + 1) + " symbol");
	}
	if (bracket_counter > 0)
		throw expression_error(to_string(bracket_counter) + " closing brackets are missing");
	return s_res;
}

double NumParse(string const& s)
{
	double res = 0.0, sign = 1.0, frac = 0.0;
	int pow = 0, foo = 0, bar = 0, pow_s = 1, prec = 0;
	size_t i = 0, sz = s.size();
	if (s[0] == '-')
	{
		sign = -1.0;
		i++;
	}
	if (s[i] == '.')
		throw expression_error("Real number can't begin without explicit integer part");
	while (i < sz && IsDigit(s[i]))
	{
		if (prec < 16)
		{
			res *= 10.0;
			res += ToDouble(s[i]);
			if (res != 0)
				prec++;
		}
		else
			bar++;
		i++;
	}
	if (i < sz && s[i] == '.')
	{
		i++;
		if (i == sz || !IsDigit(s[i]))
			throw expression_error("Fractional part must follow '.' in real numbers");
	}
	while (i < sz && IsDigit(s[i]))
	{
		if (prec < 16)
		{
			frac *= 10.0;
			frac += ToDouble(s[i]);
			if (frac != 0.0)
				prec++;
			foo += 1;
		}
		i++;
	}
	res += frac / POW(foo);
	if (i < sz && (s[i] == 'e' || s[i] == 'E'))
	{
		i++;
		if (i < sz && IsMath(s[i]))
		{
			if (s[i] == '+')
				pow_s = 1;
			else { pow_s = -1; };
			i++;
			if(i==sz)
				throw expression_error("Number has no digits in exponential part");
			while (i < sz && s[i] == '0')
				i++;
			while (i < sz && IsDigit(s[i]))
			{
				pow *= 10;
				pow += ToInt(s[i]);
				i++;
				if (i != sz && pow > 65536)
					throw expression_error("Too large power");
			}
			if (pow == 0)
				pow_s = 1;
		}
		else { throw expression_error("If number has exponential part it must have explicit sign of power"); };
	}
	if (pow_s == 1)
		res *= POW(pow);
	else
		res /= POW(pow);
	res *= sign;
	return res;
}

Vec<lexem*> MainParse(string const& s)
{
	Vec<lexem*> VL;
	return VL;
}