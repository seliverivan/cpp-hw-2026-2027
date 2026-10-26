#pragma once
#include "operations/Add.h"
#include <stdexcept>

std::string Add::getName() const {
	return std::string("+");
};
int Add::getArity() const {
	return 2;
};
int Add::getPriority() const {
	return 1;
};

Fixity Add::getFixity() const {
	return Fixity::Infix;
};

Associativity Add::getAssociativity() const {
	return Associativity::Left;
};

double Add::execute(const std::vector<double>& args) const {
	if (args.size() != 2) {
		throw std::invalid_argument("Expected 2 arguments");
	}
	return args[0] + args[1];
};
