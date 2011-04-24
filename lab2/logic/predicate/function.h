/*
 * function.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>

namespace logic {

namespace predicate {

class FunctionTerm;
class Term;
class TermVector;

class Function {
public:
  typedef const Function* ConstPtr;

  Function(const std::string& name);
  friend std::ostream& operator<<(std::ostream& os, const Function& f);
  const std::string& name() const;

  FunctionTerm operator()(const TermVector& terms);
  FunctionTerm operator()();
  FunctionTerm operator()(const Term& term0);
  FunctionTerm operator()(const Term& term0, const Term& term1);
  FunctionTerm operator()(const Term& term0, const Term& term1,
                          const Term& term2);
  FunctionTerm operator()(const Term& term0, const Term& term1,
                          const Term& term2, const Term& term3);

  struct Less {
    bool operator()(const Function& lhs, const Function& rhs) const;
  };
private:
  std::string name_;
};

}  // namespace predicate

}  // namespace logic

#endif /* FUNCTION_H_ */
