/*
 * forall.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "formula.h"
#include "interpretation.h"
#include "variable.h"

#include "forall.h"

namespace logic {

namespace predicate {

ForAll::ForAll(const Variable& var, const Formula& formula)
: super(var, formula) {}

ForAll::~ForAll() {
//  std::cerr << "~ForAll(): " << *this << '[' << this << ']' << std::endl;
}

bool ForAll::operator()(const Interpretation& semantics,
                        VariableValues* interpretation) const {
  for (Domain::const_iterator it = semantics.domain().begin(),
      end = semantics.domain().end(); it != end; ++it) {
    (*interpretation)[variable()] = *it;
    if (!formula().operator()(semantics, interpretation)) {
      interpretation->erase(variable());
      return false;
    }
  }
  interpretation->erase(variable());
  return true;
}

std::ostream& ForAll::operator<<(std::ostream& os) const {
  os << "A" << variable() << ' ' << formula();
//  os << "[" << &formula() << "]";
  return os;
}

ForAllVariable::ForAllVariable(const Variable& variable) : var_(variable) {}

ForAll ForAllVariable::operator()(const Formula& formula) const {
  return ForAll(var_, formula);
}

}  // namespace predicate

}  // namespace logic
