// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <sstream>
#include <iostream>

void throw_error(const std::string& s, const std::string& err_s, const size_t pos)
{
	std::stringstream ss;
	ss << err_s
		<< ", position "
		<< pos + 1 << ": "
		<< s.substr(0, pos)
		<< "["
		<< s[pos]
		<< "]"
		<< s.substr(pos + 1, s.size());
	throw std::runtime_error(ss.str());
}

void throw_error(const std::string& s, const std::string& err_s, const std::string& t, const size_t pos)
{
	std::stringstream ss;
	ss << err_s
		<< ", position "
		<< pos + 1 << "-" << pos + t.size() << ": "
		<< s.substr(0, pos)
		<< "["
		<< t
		<< "]"
		<< s.substr(pos + t.size(), s.size());
	throw std::runtime_error(ss.str());
}

TPostfix::TPostfix()
{
	variables["e"] = 2.71828182845904523536;
	variables["pi"] = 3.14159265358979323846;
}

double TPostfix::evaluate(const std::string& s)
{
	try
	{
		size_t sz = 0;
		Token* tokens = t.tokenize(s, variables, sz);
		Token* postfix = p.convertToPostfix(tokens, sz);
		TStack<Token> tmp;

		for(size_t i = 0; i < sz; i++)
		{
			switch (postfix[i].type)
			{
			case NUM:
			{
				tmp.push(postfix[i]);
				break;
			}

			case VAR:
			{
				std::map<std::string, double>::iterator it = variables.find(postfix[i].s);
				if (it != variables.end())
					tmp.push(Token{ it->first, VAR, it->second });
				else
					tmp.push(postfix[i]);
				break;
			}

			case UN_OP:
			{
				if (postfix[i].s == "-")
					tmp.top().val *= -1.0;

				break;
			}

			case BIN_OP:
			{
				Token lhs = tmp.top(); tmp.pop();
				Token rhs = tmp.top(); tmp.pop();
				switch (postfix[i].s[0])
				{
				case '+':
					tmp.push(Token{ "", NUM, rhs.val + lhs.val });
					break;

				case '-':
					tmp.push(Token{ "", NUM, rhs.val - lhs.val });
					break;

				case '*':
					tmp.push(Token{ "", NUM, rhs.val * lhs.val });
					break;

				case '/':
					tmp.push(Token{ "", NUM, rhs.val / lhs.val });
					break;

				case '^':
					tmp.push(Token{ "", NUM, std::pow(rhs.val, lhs.val) });
					break;
				}

				break;
			}

			case FUNC:
			{
				Token arg = tmp.top(); tmp.pop();

				if(postfix[i].s == "sin")
					tmp.push(Token{ "", NUM, std::sin(arg.val) });

				else if (postfix[i].s == "cos")
					tmp.push(Token{ "", NUM, std::cos(arg.val) });

				else if (postfix[i].s == "tan")
					tmp.push(Token{ "", NUM, std::tan(arg.val) });

				else if (postfix[i].s == "asin")
					tmp.push(Token{ "", NUM, std::asin(arg.val) });

				else if (postfix[i].s == "acos")
					tmp.push(Token{ "", NUM, std::acos(arg.val) });

				else if (postfix[i].s == "atan")
					tmp.push(Token{ "", NUM, std::atan(arg.val) });

				else if (postfix[i].s == "exp")
					tmp.push(Token{ "", NUM, std::exp(arg.val) });

				else if (postfix[i].s == "ln")
					tmp.push(Token{ "", NUM, std::log(arg.val) });

				else if (postfix[i].s == "sqrt")
					tmp.push(Token{ "", NUM, std::sqrt(arg.val) });

				break;
			}

			case ASSGN:
			{
				Token lhs = tmp.top(); tmp.pop();
				Token rhs = tmp.top(); tmp.pop();

				std::map<std::string, double>::iterator it = variables.find(rhs.s);
				rhs.val = lhs.val;
				if (it != variables.end())
					it->second = lhs.val;
				else
					variables[rhs.s] = rhs.val;
				tmp.push(rhs);
				break;
			}

			}
		}

		delete[] tokens;
		delete[] postfix;
		return tmp.top().val;
	}

	catch (const std::exception& e)
	{
		throw e;
	}

	return 0.0;
}

const std::map<std::string, double>& TPostfix::getVariables() noexcept
{
	return variables;
}

void TPostfix::clearVariables()
{
	variables.clear();
	variables["e"] = 2.71828182845904523536;
	variables["pi"] = 3.14159265358979323846;
}

TPostfix::Token* TPostfix::Tokenizer::tokenize(const std::string& s, std::map<std::string, double>& vars, size_t& sz)
{
	TStack<Token> tmp;
	// стек для помещения позиций скобок в данной строке
	TStack<size_t> parenthesis;
	TokenizerState ts = TOKEN_INIT;
	bool unary = true;
	long parenthesisCount = 0;
	long assignmentCount = 0;
	long expressionLen = 0;
	size_t tokens_count = 0;

	if (s.size() == 0) throw std::runtime_error("An empty string was given");

	for (size_t i = 0; i < s.size();)
	{
		Token t;
		std::string token_string;

		switch (ts)
		{
		case TOKEN_INIT:
			if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n' || s[i] == '\v' || s[i] == '\f') i++;
			else if (s[i] == '.' || (s[i] >= '0' && s[i] <= '9')) ts = TOKENIZE_NUM;
			else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^') ts = TOKENIZE_OP;
			else if (s[i] == '(') ts = TOKENIZE_LEFT_PAR;
			else if (s[i] == ')') ts = TOKENIZE_RIGHT_PAR;
			else if (s[i] == '=') ts = TOKENIZE_ASSGN;
			else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) ts = TOKENIZE_WORD;
			else throw_error(s, "Unexpected character", i);
			continue;

		case TOKENIZE_NUM:
			if (!tmp.isEmpty())
			{
				if ((assignmentCount < 1 || tmp.top().type == ASSGN) && (tmp.top().type == NUM || tmp.top().type == VAR || tmp.top().type == UNRECG || tmp.top().type == RIGHT_PARS))
					throw_error(s, "Unexpected token", i);
			}

			t = tokenizeNumber(s, i);
			tmp.push(t);
			ts = TOKEN_INIT;
			expressionLen++;
			tokens_count++;
			unary = false;
			continue;

		case TOKENIZE_OP:
			t = tokenizeOperation(s, i, unary);

			if (!tmp.isEmpty())
			{
				if (t.type == UN_OP)
				{
					if ((assignmentCount < 1 || tmp.top().type != ASSGN) && tmp.top().type != UN_OP && tmp.top().type != BIN_OP && tmp.top().type != FUNC && tmp.top().type != LEFT_PARS && tmp.top().type != UNRECG)
						throw_error(s, "Unexpected token", i-1);
				}

				else
				{
					if ((assignmentCount < 1|| tmp.top().type != ASSGN) && tmp.top().type != NUM && tmp.top().type != VAR && tmp.top().type != RIGHT_PARS && tmp.top().type != UNRECG)
						throw_error(s, "Unexpected token", i-1);
				}
			}

			tmp.push(t);
			ts = TOKEN_INIT;
			expressionLen++;
			tokens_count++;
			unary = true;
			continue;

		case TOKENIZE_WORD:
			t = tokenizeWord(s, i);

			if (vars.count(t.s) > 0)
			{
				t.val = vars[t.s];
				t.type = VAR;
			}

			if (!tmp.isEmpty())
			{
				if ((assignmentCount < 1 || tmp.top().type != ASSGN) && tmp.top().type != UN_OP && tmp.top().type != BIN_OP && tmp.top().type != FUNC && tmp.top().type != LEFT_PARS && tmp.top().type != UNRECG)
						throw_error(s, "Unexpected token", t.s, i-t.s.size());
			}

			tmp.push(t);
			ts = TOKEN_INIT;
			expressionLen++;
			tokens_count++;
			t.type == FUNC ? unary = true : unary = false;
			continue;

		case TOKENIZE_LEFT_PAR:
			if (!tmp.isEmpty())
			{
				if ((assignmentCount < 1 || tmp.top().type != ASSGN) && tmp.top().type != LEFT_PARS && tmp.top().type != UN_OP && tmp.top().type != BIN_OP && tmp.top().type != FUNC && tmp.top().type != UNRECG)
					throw_error(s, "Unexpected token", i);
			}

			parenthesis.push(i);
			t.s = s[i++];
			t.type = LEFT_PARS;
			parenthesisCount++;

			tmp.push(t);
			ts = TOKEN_INIT;
			tokens_count++;
			unary = true;
			continue;

		case TOKENIZE_RIGHT_PAR:
			if (parenthesis.isEmpty()) throw_error(s, "Misplaced parenthesis", i);
			parenthesis.pop();

			if (!tmp.isEmpty())
			{
				if (tmp.top().type != RIGHT_PARS && tmp.top().type != NUM && tmp.top().type != VAR && tmp.top().type != UNRECG) throw_error(s, "Unexpected token", i);
			}

			t.s = s[i++];
			t.type = RIGHT_PARS;

			tmp.push(t);
			ts = TOKEN_INIT;
			tokens_count++;
			unary = false;
			continue;

		case TOKENIZE_ASSGN:
			if (tmp.isEmpty()) throw_error(s, "Unexpected token", i);
			if (isInvalidVariableName(tmp.top().s)) throw_error(s, "Invalid variable name", tmp.top().s, i-tmp.top().s.size());
			if (tmp.top().type != VAR && tmp.top().type != UNRECG) throw_error(s, "Unexpected token", i);
			else if (expressionLen > 1) throw_error(s, "Unexpected token", i);
			if (tmp.top().type == UNRECG) tmp.top().type = VAR;

			t.s = s[i++];
			t.type = ASSGN;
			assignmentCount++;

			tmp.push(t);
			ts = TOKEN_INIT;
			unary = true;
			expressionLen = 0;
			tokens_count++;
			continue;
		}
	}

	if (tokens_count == 0) throw std::runtime_error("An empty string was given");
	if (tmp.top().type == UN_OP || tmp.top().type == BIN_OP || tmp.top().type == FUNC || tmp.top().type == ASSGN) throw_error(s, "Missing operand", tmp.top().s, tmp.size()-1);
	if (!parenthesis.isEmpty()) throw_error(s, "Unclosed parenthesis", parenthesis.top());

	Token* tokens = new Token[tokens_count];
	size_t i = tokens_count - 1;
	size_t pos = s.size() - 1;
	sz = tokens_count;
	while(!tmp.isEmpty())
	{
		while (s[pos] == ' ' || s[pos] == '\t' || s[pos] == '\r' || s[pos] == '\n' || s[pos] == '\v' || s[pos] == '\f') pos--;
		pos -= tmp.top().s.size();

		switch (tmp.top().type)
		{
		case UNRECG:
			throw_error(s, "Unrecognized token", tmp.top().s, pos+1);
			break;
		default:
			tokens[i--] = tmp.top();
			tmp.pop();
			break;
		}

	}

	return tokens;
}

TPostfix::Token TPostfix::Tokenizer::tokenizeNumber(const std::string& s, size_t& i)
{
	NumberTokenizerState ntst = NT_INIT;
	Token num;

	TStack<char> beforePointChars;
	TStack<char> afterPointChars;
	TStack<char> expChars;

	size_t first_char = i;
	size_t last_char = i;
	double val = 0.0;
	double pow = 1.0;
	double pow_frac = 0.1;
	double sign = 1.0;
	double exp = 0.0;

	for (; i < s.size();)
	{
		switch (ntst)
		{
		case NT_INIT:
			last_char = i;
			if (s[i] == '.') { i++; ntst = NUM2; }
			else if (s[i] >= '1' && s[i] <= '9') { ntst = NUM1; }
			else if (s[i] == '0') { ntst = ZERO_FIRST; }
			continue;

		case NUM1:
			last_char = i;
			if (s[i] >= '0' && s[i] <= '9') beforePointChars.push(s[i++]);
			else if (s[i] == '.') { i++; ntst = NUM2; }
			else if (s[i] == 'e') { i++; ntst = EXP; }
			else break;
			continue;

		case NUM2:
			last_char = i;
			if (s[i] >= '0' && s[i] <= '9') afterPointChars.push(s[i++]);
			else if (s[i] == 'e') { i++; ntst = EXP; }
			else break;
			continue;

		case NUM3:
			last_char = i;
			if (s[i] >= '0' && s[i] <= '9') expChars.push(s[i++]);
			else if (s[i] == '.') { throw_error(s, "Invalid number format", last_char); }
			else break;
			continue;

		case EXP:
			last_char = i;
			if (s[i] == '+') i++;
			else if (s[i] == '-') { i++; sign = -1.0; }
			else throw_error(s, "Invalid number format", last_char);

			if (s[i] >= '1' && s[i] <= '9') ntst = NUM3;
			else throw_error(s, "Invalid number format", (i < s.size() ? i : i-1));
			continue;

		case ZERO_FIRST:
			last_char = i;
			if (s[++i] == '.') { i++; ntst = NUM2; }
			else break;
			continue;
		}

		break;
	}

	if (s[i-1] == '.' && (i - first_char < 2)) throw_error(s, "Invalid number format", last_char);
	if (ntst != NUM1 && ntst != NUM2 && ntst != NUM3 && ntst != ZERO_FIRST)
		throw_error(s, "Invalid number format", last_char);

	while (!beforePointChars.isEmpty())
	{
		val += pow * (beforePointChars.top() - '0');
		pow *= 10;
		beforePointChars.pop();
	}

	// перевод в double
	TStack<char> tmp;
	while (!afterPointChars.isEmpty())
	{
		tmp.push(afterPointChars.top());
		afterPointChars.pop();
	}

	while (!tmp.isEmpty())
	{
		val += pow_frac * (tmp.top() - '0');
		pow_frac *= 0.1;
		tmp.pop();
	}

	pow = 1;
	while (!expChars.isEmpty())
	{
		exp += pow * (expChars.top() - '0');
		pow *= 10;
		expChars.pop();
	}

	num.s = s.substr(first_char, i-first_char);
	num.type = NUM;
	num.val = val * std::pow(10, sign * exp);
	return num;
}

TPostfix::Token TPostfix::Tokenizer::tokenizeOperation(const std::string& s, size_t& i, bool unary)
{
	Token op;
	op.val = std::numeric_limits<double>::quiet_NaN();

	if (unary && s[i] == '-') op.type = UN_OP;
	else if (unary && s[i] != '-') throw_error(s, "Missing operand.", i);
	else op.type = BIN_OP;

	op.s = s[i++];
	return op;
}

TPostfix::Token TPostfix::Tokenizer::tokenizeWord(const std::string& s, size_t& i)
{
	Token word;
	word.val = std::numeric_limits<double>::quiet_NaN();
	std::string t = "";
	size_t first_char = i;

	for (; i < s.size();)
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') break;
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '=' || s[i] == '^') break;
		else if (s[i] == '(' || s[i] == ')') break;
		t += s[i++];
	}

	word.s = t;
	if (t == "sin" || t == "cos" || t == "tan" || t == "asin" || t == "acos" || t == "atan" || t == "ln" || t == "exp" || t == "sqrt")
		word.type = FUNC;
	else word.type = UNRECG;

	return word;
}

inline bool TPostfix::Tokenizer::isInvalidVariableName(const std::string& s) noexcept
{
	if (s == "sin" || s == "cos" || s == "tan" || s == "asin" || s == "acos" || s == "atan" || s == "ln" || s == "exp" || s == "sqrt" ||
		s == "" || s == " " || s == "\t" || s == "\n" ||
		s == "+" || s == "-" || s == "*" || s == "/" || s == "^" || s == "(" || s == ")" || s == "=" || s == "e" || s == "pi" || s == "help" || s == "quit" || s == "vars" || s == "clear") return true;
	else
	{
		for (size_t i = 0; i < s.size(); i++)
			if ( !( (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') ) ) return true;
	}

	return false;
}

TPostfix::Token* TPostfix::Parser::convertToPostfix(Token* tokens, size_t& sz)
{
	TStack<Token> postfix;
	TStack<Token> tmp;
	size_t inp_sz = sz;

	for(size_t i = 0; i < inp_sz; i++)
	{
		switch (tokens[i].type)
		{
		case NUM: {}
		case VAR:
		{
			postfix.push(tokens[i]);
			break;
		}

		case LEFT_PARS:
		{
			tmp.push(tokens[i]);
			sz--;
			break;
		}

		case RIGHT_PARS:
		{
			while (tmp.top().type != LEFT_PARS)
			{
				postfix.push(tmp.top());
				tmp.pop();
			}

			tmp.pop();
			sz--;
			break;
		}

		case UN_OP: {}
		case ASSGN: {}
		case FUNC: {}
		case BIN_OP:
		{
			while((!tmp.isEmpty()) && (operatorPriority(tmp.top()) > operatorPriority(tokens[i]) 
				|| (operatorPriority(tmp.top()) == operatorPriority(tokens[i]) && isLeftAssoc(tokens[i]))))
			{
				postfix.push(tmp.top());
				tmp.pop();
			}

			tmp.push(tokens[i]);
			break;
		}

		default:
			throw std::runtime_error("Unknown error");
			break;
		}
	}

	while (!tmp.isEmpty())
	{
		postfix.push(tmp.top());
		tmp.pop();
	}

	Token* res = new Token[sz];
	size_t j = sz - 1;
	while (!postfix.isEmpty())
	{
		res[j--] = postfix.top();
		postfix.pop();
	}

	return res;
}

inline int TPostfix::Parser::operatorPriority(const Token& t) noexcept
{
	if (t.type == BIN_OP)
	{
		if (t.s == "+" || t.s == "-") return 2;
		else if (t.s == "*" || t.s == "/") return 3;
		else if (t.s == "^") return 4;
	}

	else if (t.type == UN_OP) return 4;
	else if (t.type == FUNC) return 5;
	else if (t.type == ASSGN) return 1;
	return -1;
}

inline bool TPostfix::Parser::isLeftAssoc(const Token& t) noexcept
{
	if (t.type == UN_OP || t.type == FUNC || t.type == ASSGN) return false;
	else if (t.s == "^") return false;
	return true;
}
