#pragma once
#include "operations/Divide.h"
#include <stdexcept>

std::string Divide::getName() const {
	return std::string("/");
};
int Divide::getArity() const {
	return 2;
};
int Divide::getPriority() const {
	return 2;
};

Fixity Divide::getFixity() const {
	return Fixity::Infix;
};

Associativity Divide::getAssociativity() const {
	return Associativity::Left;
};

double Divide::execute(const std::vector<double>& args) const {
	if (args.size() != 2) {
		throw std::invalid_argument("Expected 2 arguments");
	}
	if (args[1] == 0) {
		throw std::domain_error("Division by zero");
	}
	return args[0] / args[1];
};
