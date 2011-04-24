/*
 * exists.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef EXISTS_H_
#define EXISTS_H_

#include "quantified_formula.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Interpretation;

class Exists : public QuantifiedFormula::DerivationHelper<Exists> {
public:
  Exists(const Variable& var, const Formula& formula);
  bool operator()(const Interpretation& semantics,
                  VariableValues* interpretation) const;
  std::ostream& operator<<(std::ostream& os) const;
private:
  typedef QuantifiedFormula::DerivationHelper<Exists> super;
};

class ExistsVariable {
public:
  ExistsVariable(const Variable& variable);
  Exists operator()(const Formula& formula) const;
private:
  Variable var_;
};

}  // namespace predicate

}  // namespace logic

#endif /* EXISTS_H_ */
