/*
 * quantified_formula.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#ifndef QUANTIFIED_FORMULA_H_
#define QUANTIFIED_FORMULA_H_

#include "formula.h"
#include "interpretation.h"
#include "variable.h"

namespace logic {

namespace predicate {

class QuantifiedFormula : public Formula {
public:
  QuantifiedFormula(const Variable& variable, const Formula& formula);
  virtual ~QuantifiedFormula();

  void Destroy();

  const Variable& variable() const;
  const Formula& formula() const;

  template<class Derived>
  class DerivationHelper;
private:
  Variable var_;
  Formula* formula_;
};

template<class Derived>
class QuantifiedFormula::DerivationHelper : public QuantifiedFormula {
public:
  DerivationHelper(const Variable& variable, const Formula& formula)
  : QuantifiedFormula(variable, formula) {}
//  virtual ~DerivationHelper() {}
  virtual Formula* Clone() const {
    return new Derived(static_cast<const Derived&>(*this));
  }
};

}  // namespace predicate

}  // namespace logic


#endif /* QUANTIFIED_FORMULA_H_ */
