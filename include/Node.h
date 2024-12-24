#pragma once
#include <string>

class Node {
private:
	std::string name;
	double value;
public:
	Node(std::string _name = "", double _value = 0) {
		name = _name;
		value = _value;
	}
	std::string getName() {
		return name;
	}
	double getValue() {
		return value;
	}
	void setValue(double _value) {
		value = _value;
	}
};