#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include "stack.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <functional>

using namespace std;

class TPostfix
{
    static map<string, function<double(double, double)> > binaryOperations; 
    double to_double(const string& str);
    static map<string, function<double(double)>> unaryOperations;           
    static map<string, unsigned int> priority;                              
    string infix = "";                                                      
    string postfix = "";                                                    
    map<string, double> operands;                                           
    vector<string> lexems;                                                  
    inline bool isOperator(const string s);                                 
    void split();                                                           
    void toPostfix();                                                       
    inline void updatePostfix(const string s) noexcept;                     

public:
    TPostfix();                                                             
    TPostfix(string str);                                                   
    string getInfix() const noexcept;                                       
    string getPostfix() const noexcept;                                     
    map<string, double> getOperands() const noexcept;                       
    double calculate(map<string, double> values);                           
};
#endif
