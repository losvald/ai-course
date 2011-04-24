/*
 * formula_builder.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include <typeinfo>

#include "formula_builder.h"

#include "atom.h"
#include "composite_formula.h"
#include "exists.h"
#include "forall.h"
#include "formula.h"
#include "operator.h"

namespace logic {

namespace predicate {

namespace builder {

Formula& operator~(const Formula& f0) {
  return *CompositeFormula(UnaryOperator::kNot, f0).Clone();
}

Formula& operator&(const Formula& f0, const Formula& f1) {
  return *CompositeFormula(BinaryOperator::kAnd, f0, f1).Clone();
}

Formula& operator|(const Formula& f0, const Formula& f1) {
  return *CompositeFormula(BinaryOperator::kOr, f0, f1).Clone();
}

Formula& operator>(const Formula& f0, const Formula& f1) {
  return *CompositeFormula(BinaryOperator::kIf, f0, f1).Clone();
}

Formula& operator<(const Formula& f0, const Formula& f1) {
  return *CompositeFormula(BinaryOperator::kOnlyIf, f0, f1).Clone();
}

Formula& operator==(const Formula& f0, const Formula& f1) {
  return *CompositeFormula(BinaryOperator::kIff, f0, f1).Clone();
}

Formula& A(const Variable& variable, const Formula& f) {
  return *new ForAll(variable, f);
}

Formula& A(const std::string& variable_name, const Formula& f) {
  return A(Variable(variable_name), f);
}

Formula& E(const Variable& variable, const Formula& f) {
  return *new Exists(variable, f);
}

Formula& E(const std::string& variable_name, const Formula& f) {
  return E(Variable(variable_name), f);
}

}  // namespace builder

}  // namespace predicate

}  // namespace logic
