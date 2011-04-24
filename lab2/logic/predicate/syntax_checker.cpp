/*
 * syntax_checker.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef SYNTAX_CHECKER_CPP_
#define SYNTAX_CHECKER_CPP_

#include <set>

#include "composite_formula.h"
#include "quantified_formula.h"
#include "syntax_checker.h"
#include "variable.h"

namespace logic {

namespace predicate {

namespace {

void CheckSyntax(const Formula& formula,
                 std::set<Variable, Variable::Less>* variables) {
  if (const QuantifiedFormula* p =
      dynamic_cast<const QuantifiedFormula*>(&formula)) {
    const Variable& var = p->variable();
    if (variables->count(var))
      throw SyntaxErrorException();
    variables->insert(var);
    CheckSyntax(p->formula(), variables);
    variables->erase(var);
  } else if (const CompositeFormula* p =
      dynamic_cast<const CompositeFormula*>(&formula)) {
    for (std::size_t i = 0; i < p->formula_count(); ++i)
      CheckSyntax(p->formula(i), variables);
  }
}

}  // namespace

void CheckSyntax(const Formula& formula) {
  std::set<Variable, Variable::Less> cur_quantified_vars;
  CheckSyntax(formula, &cur_quantified_vars);
}



}  // namespace predicate

}  // namespace logic

#endif /* SYNTAX_CHECKER_CPP_ */
