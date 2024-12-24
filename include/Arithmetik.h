#pragma once
#include "Poliz.h"
#include <cmath>

class Arithmetik {
private:
	Poliz poliz;
public:
	Arithmetik(string str = "") {
		poliz = Poliz(str);
	}
	~Arithmetik() = default;
	void setVar(int n, double k) {
		poliz.SetVar(n, k);
	}
	double calculate() {
		double left, right;
		Table table = poliz.Getvariables();
		Stack<double> st(poliz.GetCount());
		for (int i = 0; i < poliz.GetCount(); i++) {
			double val = table.searchInfo(poliz[i]);
			if (val != -1) {
				st.push(val);
			}
			else {
				right = st.pop();
				left = st.pop();
				if (poliz[i] == "+") {
					st.push(left + right);
				}
				if (poliz[i] == "-") {
					st.push(left - right);
				}
				if (poliz[i] == "*") {
					st.push(left * right);
				}
				if (poliz[i] == "^") {
					st.push(pow(left, right));
				}
				if (poliz[i] == "/") {
					st.push(left / right);
				}
			}
		}
		return st.pop(); 
	}
	Table getVariables() {
		return poliz.Getvariables();
	}
};