#pragma once
#include "operations/Multiply.h"
#include <stdexcept>

std::string Multiply::getName() const {
	return std::string("*");
};
int Multiply::getArity() const {
	return 2;
};
int Multiply::getPriority() const {
	return 2;
};

Fixity Multiply::getFixity() const {
	return Fixity::Infix;
};

Associativity Multiply::getAssociativity() const {
	return Associativity::Left;
};

double Multiply::execute(const std::vector<double>& args) const {
	if (args.size() != 2) {
		throw std::invalid_argument("Expected 2 arguments");
	}
	return args[0] * args[1];
};
