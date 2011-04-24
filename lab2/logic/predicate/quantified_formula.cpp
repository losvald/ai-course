/*
 * quantified_formula.cpp
 *
 *  Created on: Apr 23, 2011
 *      Author: leden
 */

#include "formula.h"
#include "quantified_formula.h"
#include "variable.h"

namespace logic {

namespace predicate {

QuantifiedFormula::QuantifiedFormula(const Variable& variable,
                                     const Formula& formula)
: var_(variable), formula_(formula.Clone()) {}

QuantifiedFormula::~QuantifiedFormula() {
  if (formula_ != NULL)
    formula_->Destroy();
}

void QuantifiedFormula::Destroy() {
//  std::cerr << "QuantifiedFormula::Destroy(): " << *this << "\n";
  formula_ = NULL;
  delete this;
}

const Variable& QuantifiedFormula::variable() const { return var_; }
const Formula& QuantifiedFormula::formula() const { return *formula_; }

}  // namespace predicate

}  // namespace logic
