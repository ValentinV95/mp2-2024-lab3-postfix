// объявление функций и классов для вычисления арифметических выражений

#include "stack.h"
#include <map>
#include <string>

class TPostfix
{
public:
	TPostfix();

	// Вычисление значения арифмитического выражения
	double evaluate(const std::string& s);
	const std::map<std::string, double>& getVariables() noexcept;
	void clearVariables();

private:
	// Хранение пользовательских переменных
	std::map<std::string, double> variables;

	// Типы токенов
	enum TokenType
	{
		UN_OP, // Унарная операция
		BIN_OP, // Бинарная операция
		FUNC, // Функция
		NUM, // Число
		VAR, // Переменная
		ASSGN, // Оператор присваивания, используется для создания переменных и присвоения им значений
		LEFT_PARS, // Левые круглые скобки
		RIGHT_PARS, // Правые круглые скобки
		UNRECG, // Нераспознанное сочетание символов
	};

	// Любой токен можно представить как совокупность символов, его образующих, его тип и его численное значение.
	// По умолчанию всем нечисловым токенам в численное значение присваивается NaN
	struct Token
	{
		std::string s;
		TokenType type;
		double val;
	};
	
	// Класс Parser обеспечивает перевод инфиксной формы записи в постфиксную
	class Parser
	{
	public:
		Parser() noexcept { }
		Token* convertToPostfix(Token* tokens, size_t& sz);

	private:
		inline int operatorPriority(const Token& t) noexcept;
		inline bool isLeftAssoc(const Token& t) noexcept;
	};

	// Класс Tokenizer обеспечивает разбиение введённого выражения на токены
	class Tokenizer
	{
	public:
		Tokenizer() noexcept { }
		Token* tokenize(const std::string& expr, std::map<std::string, double>& vars, size_t& sz);
		Token tokenizeNumber(const std::string& s, size_t& cur_pos);
		Token tokenizeOperation(const std::string& s, size_t& cur_pos, bool unary);
		Token tokenizeWord(const std::string& s, size_t& cur_pos);

	private:
		// Состояния конечного автомата, используемого в процессе токенизации
		enum TokenizerState
		{
			TOKEN_INIT,
			TOKENIZE_NUM,
			TOKENIZE_OP,
			TOKENIZE_ASSGN,
			TOKENIZE_LEFT_PAR,
			TOKENIZE_RIGHT_PAR,
			TOKENIZE_WORD, // Обработка буквосочетаний
		};

		// Состояния конечного автомата, используемого для обработки чисел
		enum NumberTokenizerState
		{
			NT_INIT,
			ZERO_FIRST, // первая цифра - ноль
			NUM1, // часть числа до точки
			NUM2, // часть числа после точки
			EXP, // обработка знака степени
			NUM3, // степень
		};

		inline bool isInvalidVariableName(const std::string& s) noexcept;
	};

	Parser p;
	Tokenizer t;
};