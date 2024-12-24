#pragma once
#include "Table.h"
#include "Stack.h"
#include "Node.h"
#include <string>
#include <iostream>

using namespace std;

class Poliz {
private:
	void StringToWond(string str, int& k, string* w) {
		string zn = "+-*/^()";
		k = 0;
		str += " ";
		for (int i = 0; i < str.length(); i++) {
			int l = zn.find(str[i]);
			if (l >= 0 && l < zn.length()) {
				if (w[k].length() > 0) {
					k++;
				}
				w[k] = str[i];
				w[++k] = "";
			}
			else {
				if (str[i] == ' ') {
					if (w[k].length() > 0) {
						w[++k] = "";
					}
				}
				else {
					w[k] = w[k] + str[i];
				}
			}
		}
	}
	string* lex;
	int count, countlex, size, sizelex;
	string* mem;
	Stack<Node> st;
	Table PriorityTable;
	Table variables;
	void madePriorityTable() {
		PriorityTable = Table(20);
		PriorityTable.add("+", 0.0);
		PriorityTable.add("-", 0.0);
		PriorityTable.add("*", 1.0);
		PriorityTable.add("/", 1.0);
		PriorityTable.add("^", 2.0);
	}
	void workLeft() {
		st.push(Node("(", -1.0));
	}
	void workRight() {
		while ((st.is_empty() == 0) && (st.top().getName() != "(")) {
			mem[count++] = st.pop().getName();
		}
		if (st.top().getName() == "(") {
			st.pop();
		}
	}
	void workOperand(string tmp) { 
		mem[count++] = tmp;
		if (tmp[0] >= '0' && tmp[0] <= '9') {
			variables.add(tmp, stof(tmp));
		}
		else {
			variables.add(tmp, 0.0);
		}
	}
	void workOperator(string str, int p) { //?????? ? ?????????
		while ((st.is_empty() == 0) && (st.top().getValue() >= p)) {
			mem[count++] = st.pop().getName();
		}
		st.push(Node(str, p));
	}
	void workEnd() {
		while (st.is_empty() == 0) {
			mem[count++] = st.pop().getName();
		}
	}
	void madePolis() {
		count = 0;
		for (int i = 0; i < countlex; i++) {
			if (lex[i] == "(") { workLeft(); }
			else {
				if (lex[i] == ")") { workRight(); }
				else {
					int p = PriorityTable.searchInfo(lex[i]);
					if (p > -1) { workOperator(lex[i], p); }
					else { workOperand(lex[i]); }
				}
			}
		}
		workEnd();
	}
public:
	Poliz(string str = "") {
		size = str.length() + 1;
		variables = Table(size);
		mem = new string[size];
		count = 0;
		sizelex = size + 1;
		lex = new string[sizelex];
		countlex = 0;
		StringToWond(str, countlex, lex);
		madePriorityTable();
		st = Stack<Node>(20);
		madePolis();
	}
	Poliz(const Poliz& tmp) {
		size = tmp.size;
		count = tmp.count;
		mem = new string[size];
		for (int i = 0; i < size; i++) {
			mem[i] = tmp.mem[i];
		}
		PriorityTable = tmp.PriorityTable;
		st = tmp.st;
		variables = tmp.variables;
	}
	Poliz& operator =(Poliz tmp) {
		if (size != tmp.size) {
			if (size != 0) {
				delete[]mem;
			}
			size = tmp.size;
			mem = new string[size];
		}
		for (int i = 0; i < size; i++) {
			mem[i] = tmp.mem[i];
		}
		count = tmp.count;
		PriorityTable = tmp.PriorityTable;
		st = tmp.st;
		variables = tmp.variables;
		return *this;
	}
	~Poliz() {
		delete[]mem;
	}
	int GetCount() {
		return count;
	}
	string operator[](int n) {
		if (n >= 0 && n < count) {
			return mem[n];
		}
		return "?";
	}
	string GetStringPolis() {
		string str = "";
		str += mem[0];
		for (int i = 1; i < count; i++) {
			str += " " + mem[i];
		}
		return str;
	}
	Table Getvariables() {
		return variables;
	}
	void SetVar(int n, double k) {
		variables.setVar(n, k);
	}
};