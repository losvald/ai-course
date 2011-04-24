/*
 * exists.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "formula.h"
#include "interpretation.h"
#include "variable.h"

#include "exists.h"

namespace logic {

namespace predicate {

Exists::Exists(const Variable& var, const Formula& formula)
: super(var, formula) {}

bool Exists::operator()(const Interpretation& semantics,
                        VariableValues* interpretation) const {
  for (Domain::const_iterator it = semantics.domain().begin(),
      end = semantics.domain().end(); it != end; ++it) {
    (*interpretation)[variable()] = *it;
    if (formula().operator()(semantics, interpretation)) {
      interpretation->erase(variable());
      return true;
    }
  }
  interpretation->erase(variable());
  return false;
}

std::ostream& Exists::operator<<(std::ostream& os) const {
  os << "E" << variable() << ' ' << formula();
  return os;
}

ExistsVariable::ExistsVariable(const Variable& variable) : var_(variable) {}

Exists ExistsVariable::operator()(const Formula& formula) const {
  return Exists(var_, formula);
}

}  // namespace predicate

}  // namespace logic
