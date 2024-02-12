#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "stack.h"

using namespace std;



class TCalculator
{
    string  infix, postfix,str;
    TStack<char> c = TStack <  char > (10); // стек для операций
    TStack<double> d = TStack<double>(10); // стек для чисел
    int prioritet(char op);
public:
    TCalculator(string _str);
    TCalculator(const  TCalculator& C);
    void SetInfix(string str);
    string GetPostfix();
    string GetInfix();
    double Calc();
    double CalcPostfix();
    void ToPostfix();


};// объявление функций и классов для вычисления арифметических выражений
