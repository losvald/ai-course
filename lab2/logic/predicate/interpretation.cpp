/*
 * interpretation.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "domain.h"
#include "interpretation.h"
#include "function_map.h"
#include "formula.h"
#include "predicate_map.h"
#include "syntax_checker.h"

namespace logic {

namespace predicate {

void Interpretation::Bind(const Function& function, FunctionFuncPtr func_ptr) {
  function_func_ptrs_[function] = func_ptr;
}

void Interpretation::Bind(const Predicate& predicate, PredicateFuncPtr func_ptr) {
  predicate_func_ptrs_[predicate] = func_ptr;
}

Element Interpretation::Evaluate(const Function& function,
                            const Arguments& args) const {
  if (!func_map_.count(function) || !func_map_.at(function).count(args)) {
    if (!function_func_ptrs_.count(function))
      throw IncompleteFunctionException();
    return function_func_ptrs_.at(function)(args);
  }
  return func_map_.at(function).at(args);
}

bool Interpretation::Evaluate(const Predicate& predicate,
                         const Arguments& args) const {
  if (!pred_map_.count(predicate) || !pred_map_.at(predicate).count(args)) {
    if (!predicate_func_ptrs_.count(predicate))
      throw IncompletePredicateException();
    return predicate_func_ptrs_.at(predicate)(args);
  }
  return pred_map_.at(predicate).at(args);
}

bool Interpretation::Evaluate(const Formula& formula) const {
  CheckSyntax(formula);
  VariableValues interpretation;
  return formula(*this, &interpretation);
}

std::ostream& operator<<(std::ostream& os, const Interpretation& s) {
  os << "Domain = {";
  for (std::set<Element>::const_iterator it = s.domain_.begin(),
      end = s.domain_.end(); it != end; ) {
    os << *it;
    if (++it != end) os << ", ";
  }
  os << '}' << std::endl;

  os << "Functions:" << std::endl;
  for (FunctionMap::const_iterator func = s.func_map_.begin(),
      end = s.func_map_.end(); func != end; ++func) {
    if (s.function_func_ptrs_.count(func->first))
      os << func->first << " is bound to a function" << std::endl;
    for (FunctionMapping::const_iterator it = (func->second).begin(),
        end2 = (func->second).end(); it != end2; ++it)
      os << func->first << '(' << it->first << ") = " << it->second << std::endl;
  }
  os << "Predicates:" << std::endl;
  for (PredicateMap::const_iterator pred = s.pred_map_.begin(),
      end = s.pred_map_.end(); pred != end; ++pred) {
    if (s.predicate_func_ptrs_.count(pred->first))
      os << pred->first << " is bound to a function" << std::endl;
    for (PredicateMapping::const_iterator it = (pred->second).begin(),
        end2 = (pred->second).end(); it != end2; ++it)
      os << pred->first << '(' << it->first << ") = " << it->second << std::endl;
  }

  return os;
}

const Domain& Interpretation::domain() const {
  return domain_;
}

Domain& Interpretation::domain() {
  return domain_;
}

const VariableValues& Interpretation::interpretation() const {
  return interpretation_;
}

const PredicateMap& Interpretation::predicate_map() const {
  return pred_map_;
}

PredicateMap& Interpretation::predicate_map() {
  return pred_map_;
}

const FunctionMap& Interpretation::function_map() const {
  return func_map_;
}

FunctionMap& Interpretation::function_map() {
  return func_map_;
}

namespace {


}  // namespace

}  // namespace predicate

}  // namespace logic
