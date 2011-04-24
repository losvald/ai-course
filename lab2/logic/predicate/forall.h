/*
 * forall.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef FORALL_H_
#define FORALL_H_

#include "quantified_formula.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Interpretation;
class Variable;

class ForAll : public QuantifiedFormula::DerivationHelper<ForAll> {
public:
  ForAll(const Variable& variable, const Formula& formula);
  ~ForAll();
  bool operator()(const Interpretation& semantics,
                  VariableValues* interpretation) const;
  std::ostream& operator<<(std::ostream& os) const;
private:
  typedef QuantifiedFormula::DerivationHelper<ForAll> super;
};

class ForAllVariable {
public:
  ForAllVariable(const Variable& variable);
  ForAll operator()(const Formula& formula) const;
private:
  Variable var_;
};

}  // namespace predicate

}  // namespace logic

#endif /* FORALL_H_ */
