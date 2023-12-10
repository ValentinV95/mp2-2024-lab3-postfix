// реализация функций и классов для вычисления арифметических выражений

#include "arithmetic.h"
#include <vector>

using namespace std;

int Arithmetic::InfixCheck() {
    int len = infix.length();
    int tmp;
    int bracketNum = 0;
    for(int i = 0; i < len; i++){
        if(infix[i]<47 && infix[i]>58){ //valid character check
            if (infix[i]!= '+' && infix[i] != '-' && infix[i] != '*' && infix[i] != '/' && infix[i] != '(' && infix[i] != ')'
            && infix[i] != 'x' && infix[i] != 's' && infix[i] != 'i' && infix[i] != 'n' && infix[i] != 'c'
            && infix[i] != 'o' && infix[i] != 't' && infix[i] != 'g' && infix[i] != 'l' && infix[i] != 'e' && infix[i] != 'p');
        }
    }
    for(int i = 0; i < len; i++){
        if (infix[i] == '('){
            bracketNum++;
            if(i!=0 && (infix[i-1] != '*' && infix[i-1] != '/' && infix[i-1] != '+' && infix[i-1] != '-'  && infix[i-1] != 'n'  && infix[i-1] != 's' && infix[i-1] != 'g' && infix[i-1] != 'p')){
                //n => siN(; s => coS(; g => tG( or lG(; p => exP(
                //check for an operand before '('
                cout << "error in " << i-1 << "symbol";
                throw invalid_argument("syntax's error");
            }
        }
        else if(infix[i] == ')'){
            bracketNum--;
        }
        else if(infix[i] == 'x'){
            if (i != 0 && ((infix[i-1]>47 && infix[i-1]<58) ||infix[i-1]==')')){
                cout << "error in " << i-1 << "symbol";
                throw invalid_argument("syntax's error");
            }
        }
        else if (infix[i] == '.'){
            if (i==0 && int(infix[i+1]) <47 && int(infix[i+1] > 58)){
                if (infix[i+1] != 'e'){
                    cout << "error in " << i << "symbol";
                    throw invalid_argument("syntax's error");
                }
            }
            else if (i == len-1 && int(infix[i-1]) <47 && int(infix[i-1] > 58)){
                cout << "error in " << i << "symbol";
                throw invalid_argument("syntax's error");
            }
            else if((int(infix[i-1]) <47 && int(infix[i-1] > 58)) || (infix[i+1]) <47 && int(infix[i+1] > 58)){
                if (infix[i+1] != 'e'){
                    cout << "error in " << i << "symbol";
                    throw invalid_argument("syntax's error");
                }
            }
        }
        else if (infix[i] == 'e'){
            if((int(infix[i-1]) <47 && int(infix[i-1] > 58)) || (infix[i+1]) <47 && int(infix[i+1] > 58)){
                if (infix[i-1] != '.'){
                    cout << "error in " << i << "symbol";
                    throw invalid_argument("syntax's error");
                }
            }
        }
        else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '/' || infix[i] == '*'){
            if (infix[i-1] == '+' || infix[i-1] == '-' || infix[i-1] == '/' || infix[i-1] == '*'){
                cout << "error in " << i-1 << "symbol";
                throw invalid_argument("syntax's error");
            }
        }
    }
    if(bracketNum<0){
        tmp = 0;
        for (int i = 0; i < len; i++){
            if(infix[i] == ')'){
                tmp = i;
            }
        }
        cout << tmp;
    }
    if(bracketNum>0){
        tmp = 0;
        for (int i = 0; i < len; i++){
            if(infix[i] == '('){
                tmp = i;
                break;
            }
        }
        cout << "error in " << tmp << "symbol";
        throw invalid_argument("syntax's error");
    }
    return 1;
}

void Arithmetic::Parse() {
    int len = infix.length();
    int j;
    string tmp = "";
    for(int i = 0; i< len;i++){
        tmp = "";
        if ((infix[i] > 47 && infix[i] < 58) || infix[i] == '.'){
            while(i<len && ((int(infix[i]) > 47 && int(infix[i]) < 58) || (int(infix[i]) == 101) || (int(infix[i]) == 46) || (int(infix[i-1]) == 101) && int(infix[i]) == 45)){
                //47-58 == 0-9; 101 == e; 46 == .; 45 == -;
                tmp+=infix[i];
                i++;
            }
            i--;
            lexems.push_back(tmp);
        }
        else if (infix[i] == 'x'){
            tmp+=infix[i];
            i++;
            while(infix[i] > 47 && infix[i] < 58 && i < len){
                tmp+=infix[i];
                i++;
            }
            i--;
            lexems.push_back(tmp);
        }
        else if(infix[i] == '-'){ //минус выделяется скобками или первый
            if (i == 0 || infix[i-1] == '('){
                tmp+='~';
            }
            else{
                tmp+=infix[i];
            }
            lexems.push_back(tmp);
        }
        else if(infix[i] == 'c'){
            if (len-i<6 || infix[i+1] != 'o' || infix[i+2] != 's' || infix[i+3] != '(' ){
                cout << "Error in cos in" << i << "symbol";
                throw logic_error("Error in cos");
            }
            else{
                tmp+= infix[i];
                tmp+= infix[i+1];
                tmp+= infix[i+2];
                lexems.push_back(tmp);
                lexems.push_back("(");
                tmp = "";
                i+=3;
            }

        }
        else if(infix[i] == 's'){
            if (infix[i+1] != 'i' || infix[i+2] != 'n' || infix[i+3] != '(' ){
                cout << "Error in sin in" << i << "symbol";
                throw logic_error("Error in sin");
            }
            else{
                tmp+= infix[i];
                tmp+= infix[i+1];
                tmp+= infix[i+2];
                lexems.push_back(tmp);
                lexems.push_back("(");
                tmp = "";
                i+=3;
            }
        }
        else if(infix[i] == 't'){
            if (infix[i+1] != 'g' || infix[i+2] != '('){
                cout << "Error in th in" << i << "symbol";
                throw logic_error("Error in tg");
            }
            else{
                tmp+= infix[i];
                tmp+= infix[i+1];
                lexems.push_back(tmp);
                lexems.push_back("(");
                tmp = "";
                i+=2;
            }
        }
        else if(infix[i] == 'e'){
            if (infix[i+1] != 'x' || infix[i+2] != 'p' || infix[i+3] != '(' ){
                cout << "Error in exp in" << i << "symbol";
                throw logic_error("Error in exp");
            }
            else{
                tmp+= infix[i];
                tmp+= infix[i+1];
                tmp+= infix[i+2];
                lexems.push_back(tmp);
                lexems.push_back("(");
                tmp = "";
                i+=3;
            }
        }
        else if(infix[i] == 'l'){
            if (infix[i+1] != 'g' || infix[i+2] != '('){
                cout << "Error in lg in" << i << "symbol";
                throw logic_error("Error in lg");
            }
            else{
                tmp+= infix[i];
                tmp+= infix[i+1];
                lexems.push_back(tmp);
                lexems.push_back("(");
                tmp = "";
                i+=2;
            }
        }
        else{
            tmp+=infix[i];
            lexems.push_back(tmp);
        }

    }
    tmp = "!";
    lexems.push_back(tmp);
}

void Arithmetic::toPostfix() {
    int sz = lexems.size();
    string tmp;
    for (int i = 0; i< sz; i++){
        if ((int(lexems[i][0]) > 47 && int(lexems[i][0]) < 58)|| lexems[i][0] == 'x'){
            if (lexems[i][0] == 'x'){
                var[lexems[i]] = 0;   //по дефолту всегда 0
            }
            postfix.push_back(lexems[i]);
        }
        else{
            switch (lexems[i][0]){

                case '(':
                    stack.push(lexems[i]);
                    break;
                case ')':
                    if (stack.isEmpty()){
                        cout << "Error in " << i << " symbol";
                        throw logic_error("syntax's error");
                    }
                    tmp = stack.pop();
                    while(tmp!="("){
                        postfix.push_back(tmp);
                        if (!stack.isEmpty()){
                            tmp = stack.pop();
                        }
                    }
                    if (!stack.isEmpty()){
                        tmp = stack.current();
                        if (tmp == "cos" || tmp == "tg" || tmp == "exp" || tmp =="sin"){
                            tmp = stack.pop();
                            postfix.push_back(tmp);
                        }
                    }
                    break;
                case '*':
                case '/':
                    if (!stack.isEmpty()){
                        tmp = stack.current();
                        while(tmp == "~" || tmp == "*" || tmp == "/" ||  tmp == "c" || tmp == "s" || tmp == "t" || tmp == "e" || tmp == "l"){
                            tmp = stack.pop();
                            postfix.push_back(tmp);
                            if(!stack.isEmpty())
                                tmp = stack.current();
                            break;
                        }
                    }
                    stack.push(lexems[i]);
                    break;

                case '+':
                case '-':
                    if(!stack.isEmpty()){
                        tmp = stack.current();
                        while(tmp == "~" || tmp == "*" || tmp == "-" || tmp == "+" || tmp == "/" || tmp == "c" || tmp == "s" || tmp == "t" || tmp == "e" || tmp == "l"){
                            tmp = stack.pop();
                            postfix.push_back(tmp);
                            if(!stack.isEmpty())
                                tmp = stack.current();
                            break;
                        }
                    }
                    stack.push(lexems[i]);
                    break;
                case '~':
                case 's':
                case 'c':
                case 't':
                case 'e':
                case 'l':
                    stack.push(lexems[i]);
                    break;
                default:
                    while(!stack.isEmpty()){
                        tmp = stack.pop();
                        postfix.push_back(tmp);
                    }
                    break;
            }
        }
    }
}

Arithmetic::Arithmetic(string infix_) {
    infix = infix_;
    int check = InfixCheck();
    if(check == 1){
        Parse();
        toPostfix();
    }
}

Arithmetic::~Arithmetic() {
    infix = "";
    postfix.clear();
    lexems.clear();
    stack.del();
    var.clear();
}

string Arithmetic::GetInfix() const {
    return infix;
}

vector<string> Arithmetic::GetPostfix() const {
    return postfix;
}

void Arithmetic::GetVars() {
    int sz = lexems.size();
    bool wasX = false;
    string tmp = "";
    for (int i = 0; i< sz; i++){
        if(lexems[i][0]=='x'){
            wasX = true;
            tmp = 'x';
            for (int j = 1; j < lexems[i].length(); j++){
                tmp+=lexems[i][j];
            }
            var[tmp] = 0.0;
        }
    }
    if(wasX){
        cout << "Enter the values of variables: " << endl;
    }
    for(auto& item : var)
    {
        cout << item.first << "= ";
        cin >> item.second;
    }
}

double Arithmetic::StringToDouble(std::string str) {
    int sz = str.size();
    bool wasDot = false;
    bool wasE = false;
    bool wasEMinus = false;
    double res = 0.0;
    int indE = 0;
    int indDot = 0;
    int numE = 0;
    int numDot = 0;
    int tmp;
    //Check correct of num
    for (int i = 0; i< sz;i++){
        if (str[i] == '.'){
            if (!wasDot){
                wasDot = true;
                indDot = i;
            }
            else if (wasE){
                throw logic_error ("dot after e");
            }
            else
                throw logic_error ("double dot");
        }
        else if(str[i] == 'e'){
            if(!wasE){
                wasE = true;
                indE = i;
            }
            else if(i == sz-1){
                throw logic_error ("e in the end");
            }
            else
                throw logic_error ("double e");
        }
        else if(str[i] == ' '){
            throw logic_error ("space in num");
        }
        else if(str[i] == '-'){
            if(wasE && !wasEMinus){
                wasEMinus = true;
            }
            else if(!wasE){
                throw logic_error ("minus not after e");
            }
            else if (wasEMinus){
                throw logic_error ("double minus");
            }
        }
    }
    //transformation...
    if (wasE){
        tmp = sz - 1 - indE - 1;
        if(wasEMinus){
            tmp--;
        }
        for (int i = indE+1 +(1*wasEMinus); i<sz; i++){
            numE += (int(str[i])-48)*int(pow(10, tmp));
            tmp--;
        }
    }

    if(wasDot){
        if(wasE){
            numDot = indE-indDot-1;
        }
        else{
            numDot = sz-1-indDot;
        }
    }
    tmp = 0;
    for(int i = 0; i< sz; i++){
        if(int(str[i]) > 47 && int(str[i]) < 58){
            res+= (int(str[i])-48)*int(pow(10, (indDot-1+numDot-tmp)*wasDot+(sz-(sz-indE)-tmp-1)*wasE*!wasDot+(sz-1-tmp)*!wasE*!wasDot));
            tmp++;
        }
        else if(str[i] == 'e'){
            break;
        }
    }
    if(wasE && wasEMinus){
        res/=pow(10,numE+numDot) ;
    }
    else if (wasE && !wasEMinus){
        res*=pow(10,numE-numDot);
    }
    else{
        res/=pow(10,numDot);
    }
    return res;
}

vector<string> Arithmetic::GetLexems() const {
    return lexems;
}

double Arithmetic::Calculate() {
    int sz = postfix.size();
    double res = 0.0;
    double first;
    double second;
    string tmp = "";
    DStack <double> cal;
    for (int i = 0; i < sz; i++){
        tmp = postfix[i];
        if (tmp[0] > 47 && tmp[0] < 58 || tmp[0]=='.'){
            cal.push(StringToDouble(tmp));
        }
        else if (tmp[0] == 'x'){
            cal.push(var[tmp]);
        }
        else{
            switch (tmp[0]) {
                case '+':
                    if (cal.isEmpty()){
                        cout << "Not all operands with + in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        if (cal.isEmpty()) {
                            cout << "Not all operands with + in " << i << " symbol";
                            throw logic_error("Error");
                        }
                        second = cal.pop();
                        cal.push(second + first);
                    }
                    break;
                case '-':
                    if (cal.isEmpty()){
                        cout << "Not all operands with - in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        if (cal.isEmpty()) {
                            cout << "Not all operands with - in " << i << " symbol";
                            throw logic_error("Error");
                        }
                        second = cal.pop();
                        cal.push(second - first);
                    }
                    break;
                case '*':
                    if (cal.isEmpty()){
                        cout << "Not all operands with * in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        if (cal.isEmpty()) {
                            cout << "Not all operands with * in " << i << " symbol";
                            throw logic_error("Error");
                        }
                        second = cal.pop();
                        cal.push(second * first);
                    }
                    break;
                case '/':
                    if (cal.isEmpty()){
                        cout << "Not all operands with / in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        if (cal.isEmpty()) {
                            cout << "Not all operands with / in " << i << " symbol";
                            throw logic_error("Error");
                        }
                        second = cal.pop();
                        cal.push(second / first);
                    }
                    break;
                case '~':
                    if (cal.isEmpty()){
                        cout << "Not all operands with unar minus in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        cal.push(first*(-1));
                    }
                    break;
                case 's':
                    if (cal.isEmpty()){
                        cout << "Not all operands with sin() in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        cal.push(sin(first));
                    }
                    break;
                case 'c':
                    if (cal.isEmpty()){
                        cout << "Not all operands with cos() in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        cal.push(cos(first));
                    }
                    break;
                case 't':
                    if (cal.isEmpty()){
                        cout << "Not all operands with tg() in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        cal.push(tan(first));
                    }
                    break;
                case 'e':
                    if (cal.isEmpty()){
                        cout << "Not all operands with exp() in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        cal.push(exp(first));
                    }
                    break;
                case 'l':
                    if (cal.isEmpty()){
                        cout << "Not all operands with lg() in " << i << " symbol";
                        throw logic_error("Error");
                    }
                    else{
                        first = cal.pop();
                        cal.push(log(first));
                    }
                    break;
            }
        }
    }
    res = cal.pop() * cal.isEmpty();
    return res;
}