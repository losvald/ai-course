/*
 * composite_formula.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef COMPOSITE_FORMULA_H_
#define COMPOSITE_FORMULA_H_

#include "formula.h"
#include "formula_vector.h"
#include "operator.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Atom;
class Interpretation;

class CompositeFormula : public Formula::DerivationHelper<CompositeFormula> {
public:
  CompositeFormula(UnaryOperator::ConstPtr op, const Formula& f0);
  CompositeFormula(BinaryOperator::ConstPtr op, const Formula& f0,
                   const Formula& f1);
  CompositeFormula(Operator::ConstPtr op, const FormulaVector& f);
  ~CompositeFormula();

  void Destroy();

  bool operator()(const Interpretation& semantics,
                  VariableValues* interpretation) const;
  std::ostream& operator<<(std::ostream& os) const;

  std::size_t formula_count() const;
  const Formula& formula(std::size_t n) const;

private:
  Operator::ConstPtr op_;
  FormulaVector children_;
};

}  // namespace predicate

}  // namespace logic

#endif /* COMPOSITE_FORMULA_H_ */
