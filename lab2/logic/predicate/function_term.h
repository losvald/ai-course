/*
 * function_term.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef FUNCTION_TERM_H_
#define FUNCTION_TERM_H_

#include <string>
#include <vector>

#include "arguments.h"
#include "function.h"
#include "term.h"
#include "term_vector.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Element;
class Interpretation;

class FunctionTerm : public Term::DerivationHelper<FunctionTerm> {
public:
  typedef const FunctionTerm* ConstPtr;
  FunctionTerm(const Function& function, const TermVector& args);
  FunctionTerm(const Function& function);
  FunctionTerm(const Function& function, const Term& arg0);
  FunctionTerm(const Function& function, const Term& arg0, const Term& arg1);
  FunctionTerm(const Function& function, const Term& arg0, const Term& arg1,
               const Term& arg2);
  FunctionTerm(const Function& function, const Term& arg0, const Term& arg1,
               const Term& arg2, const Term& arg3);

  void Destroy();

  Element operator()(const Interpretation& semantics,
                     VariableValues* interpretation) const;
  std::ostream& operator<<(std::ostream& os) const;

  const Function& function() const;

  struct Less {
    bool operator()(const FunctionTerm& lhs, const FunctionTerm& rhs) const;
  };
private:
  Function function_;
  TermVector args_;
};


}  // namespace predicate

}  // namespace logic

#endif /* FUNCTION_TERM_H_ */
