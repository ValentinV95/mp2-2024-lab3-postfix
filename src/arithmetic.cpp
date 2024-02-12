

#include "arithmetic.h"

int TCalculator::prioritet(char op)
{
    if (op == '(' || op == ')')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return -1; 
}

TCalculator::TCalculator(string _str) //конструктор
    {
        str = _str;
    }
TCalculator::TCalculator(const  TCalculator& C) //конструктор копирования
    {
        str = C.str;
    }
    void TCalculator::SetInfix(string str)
    {
        infix = str;
    }

    string TCalculator::GetPostfix()
    {
        return postfix;
    }

    string TCalculator::GetInfix()
    {
        return infix;
    }

    double TCalculator::Calc()
    {
        c.Clear(); d.Clear();
        string str = '(' + infix + ')';
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '(') c.Push(str[i]);
            if (str[i] == ')')
            {
                char el = c.Pop();
                while (el != '(')
                {
                    double x2 = d.Pop();
                    double x1 = d.Pop();
                    double y = 0;
                    if (el == '+') y = x1 + x2;
                    d.Push(y);
                    el = c.Pop();
                }
            }
            if ((str[i] >= '0') && (str[i] <= '9'))
            {
                size_t pos; //номер нечислового символа
                double x = stod(&str[i], &pos);
                d.Push(x);
                i = i + pos - 1;
            }
            if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '^'))
            {
                char el = c.Pop();
                while (prioritet(el) >= prioritet(str[i]))
                {
                    double y;
                    double x2 = d.Pop(); double x1 = d.Pop();
                    if (el == '+') y = x1 + x2;
                    d.Push(y); el = c.Pop();
                }
                c.Push(el);
                c.Push(str[i]);
            }
        }
        return d.Pop();
    }

    double TCalculator::CalcPostfix()
    {
        if (d.IsEmpty() == false)
        {
            this->d.Clear();
        }
        for (int i = 0; i < postfix.length(); i++)
        {
            if (postfix[i] >= '0' && postfix[i] <= '9')
            {
                d.Push(postfix[i] - '0');
            }

            if ((postfix[i] == '+') || (postfix[i] == '-') || (postfix[i] == '*') || (postfix[i] == '/') || (postfix[i] == '^'))
            {
                double x1 = 0; double x2 = 0; double  y = 0;
                if (d.IsEmpty() == false)
                {
                    x2 = d.Pop();
                }
                if (d.IsEmpty() == false)
                {
                    x1 = d.Pop();
                }
                if (postfix[i] == '+')
                    y = x1 + x2;
                if (postfix[i] == '-')
                    y = x1 - x2;
                if (postfix[i] == '*')
                    y = x1 * x2;
                if (postfix[i] == '/')
                    y = x1 / x2;
                if (postfix[i] == '^')
                    y = pow(x1, x2);
                d.Push(y);
            }
        }
        double res;
        if (d.IsEmpty() == false)
        {
            res = d.Pop();
        }
        else
        {
            throw "Empty";
        }
        if (!d.IsEmpty())
        {
            throw "troubles with result";
        }
        return res;
    }

    void TCalculator::ToPostfix()
    {

        if (c.IsEmpty() == false)
        {
            this->c.Clear();
        }
        std::string str = '(' + infix + ')';
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '(')
            {
                c.Push('(');
            }
            if (str[i] >= '0' && str[i] <= '9')
            {
                postfix += str[i];
            }
            if (str[i] == ')')
            {
                char opelement = c.Pop();
                while (opelement != '(')
                {
                    postfix += opelement;
                    opelement = c.Pop();
                }
            }
            if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/') || (str[i] == '^'))
            {
                char opelement = c.Pop();
                /*while (prioritet(opelement) >= prioritet(str[i]))
                {
                    postf += opelement;
                    opelement = c.Pop();
                }*/
                if (prioritet(opelement) >= prioritet(str[i]))
                {
                    postfix += opelement;
                    opelement = c.Pop();
                }
                else
                {
                    c.Push(opelement);
                }
                c.Push(str[i]);
            }
          
        }

        }

    }

;



