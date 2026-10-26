#pragma once
#include "operations/Substract.h"
#include <stdexcept>

std::string Substract::getName() const {
	return std::string("-");
};
int Substract::getArity() const {
	return 2;
};
int Substract::getPriority() const {
	return 1;
};

Fixity Substract::getFixity() const {
	return Fixity::Infix;
};

Associativity Substract::getAssociativity() const {
	return Associativity::Left;
};

double Substract::execute(const std::vector<double>& args) const {
	if (args.size() != 2) {
		throw std::invalid_argument("Expected 2 arguments");
	}
	return args[0] - args[1];
};
