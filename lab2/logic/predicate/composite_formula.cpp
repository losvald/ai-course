/*
 * composite_formula.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "formula.h"
#include "interpretation.h"
#include "predicate.h"
#include "composite_formula.h"

namespace logic {

namespace predicate {

CompositeFormula::CompositeFormula(UnaryOperator::ConstPtr op, const Formula& f0)
: op_(op), children_(f0) {}

CompositeFormula::CompositeFormula(BinaryOperator::ConstPtr op,
                                   const Formula& f0, const Formula& f1)
: op_(op), children_(f0, f1) {}

CompositeFormula::CompositeFormula(Operator::ConstPtr op,
                                   const FormulaVector& f)
: op_(op), children_(f) {
  // TODO check op->arity() == f.size()
}

CompositeFormula::~CompositeFormula() {
//  std::cerr << "~CompositeFormula(): " << *this << "\n";
}

void CompositeFormula::Destroy() {
//  std::cerr << "CompositeFormula::Destroy(): " << *this << "\n";
  children_.clear();
  delete this;
}

bool CompositeFormula::operator()(const Interpretation& semantics,
                                  VariableValues* interpretation) const {
  if (UnaryOperator::ConstPtr op = dynamic_cast<UnaryOperator::ConstPtr>(op_))
    return (*op)(*children_[0], semantics, interpretation);
  if (BinaryOperator::ConstPtr op = dynamic_cast<BinaryOperator::ConstPtr>(op_))
    return (*op)(*children_[0], *children_[1], semantics, interpretation);
  // TODO check error
  return false;
}

std::ostream& CompositeFormula::operator<<(std::ostream& os) const {
  if (formula_count() == 1)
    os << '(' << *op_ << *children_[0] << ')';
  else if (formula_count() == 2)
    os << '(' << *children_[0] << ' ' << *op_ <<  ' ' << *children_[1] << ')';
//
//  os << "[";
//  if (formula_count() == 1)
//      os << children_[0];
//  else if (formula_count() == 2)
//    os << children_[0] << ' ' << children_[1];
//  os << "]";
  return os;
}

std::size_t CompositeFormula::formula_count() const {
  return children_.size();
}

const Formula& CompositeFormula::formula(std::size_t n) const {
  return *children_[n];
}

}  // namespace predicate

}  // namespace logic
