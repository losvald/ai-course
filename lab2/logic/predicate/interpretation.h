/*
 * interpretation.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef INTERPRETATION_H_
#define INTERPRETATION_H_

#include <exception>
#include <set>
#include <map>

#include "domain.h"
#include "function_map.h"
#include "interpretation.h"
#include "predicate_map.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Formula;
class Predicate;

class Interpretation {
public:
  typedef Element (*FunctionFuncPtr)(const Arguments& args);
  typedef bool (*PredicateFuncPtr)(const Arguments& args);

  void Bind(const Function& function, FunctionFuncPtr func_ptr);
  void Bind(const Predicate& predicate, PredicateFuncPtr func_ptr);
  Element Evaluate(const Function& function, const Arguments& args) const;
  bool Evaluate(const Predicate& predicate, const Arguments& args) const;
  bool Evaluate(const Formula& formula) const;

  friend std::ostream& operator<<(std::ostream& os, const Interpretation& s);

  const Domain& domain() const;
  Domain& domain();
  const VariableValues& interpretation() const;
  const PredicateMap& predicate_map() const;
  PredicateMap& predicate_map();
  const FunctionMap& function_map() const;
  FunctionMap& function_map();

private:

  Domain domain_;
  VariableValues interpretation_;
  PredicateMap pred_map_;
  FunctionMap func_map_;
  std::map<Function, FunctionFuncPtr, Function::Less> function_func_ptrs_;
  std::map<Predicate, PredicateFuncPtr, Predicate::Less> predicate_func_ptrs_;
};

struct UninterpretableException : std::exception {
};

struct IncompleteFunctionException : std::exception {
};

struct IncompletePredicateException : std::exception {
};

}  // namespace predicate

}  // namespace logic

#endif /* INTERPRETATION_H_ */
