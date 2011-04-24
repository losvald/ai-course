/*
 * function.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#include "function.h"
#include "function_term.h"
#include "term_vector.h"

namespace logic {

namespace predicate {

Function::Function(const std::string& name) : name_(name) {}

std::ostream& operator<<(std::ostream& os, const Function& f) {
  os << f.name_;
  return os;
}

FunctionTerm Function::operator()(const TermVector& terms) {
  return FunctionTerm(*this, terms);
}

FunctionTerm Function::operator()() {
  return FunctionTerm(*this, TermVector());
}

FunctionTerm Function::operator()(const Term& term0) {
  return FunctionTerm(*this, TermVector(term0));
}

FunctionTerm Function::operator()(const Term& term0, const Term& term1) {
  return FunctionTerm(*this, TermVector(term0, term1));
}

FunctionTerm Function::operator()(const Term& term0, const Term& term1,
                           const Term& term2) {
  return FunctionTerm(*this, TermVector(term0, term1, term2));
}

FunctionTerm Function::operator()(const Term& term0, const Term& term1,
                           const Term& term2, const Term& term3) {
  return FunctionTerm(*this, TermVector(term0, term1, term2, term3));
}

const std::string& Function::name() const { return name_; }

bool Function::Less::operator()(const Function& lhs, const Function& rhs) const {
  return lhs.name_ < rhs.name_;
}

}  // namespace predicate

}  // namespace logic
