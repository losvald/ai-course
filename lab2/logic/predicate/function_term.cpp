/*
 * function.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "element.h"
#include "function_term.h"
#include "function.h"
#include "interpretation.h"
#include "variable.h"

namespace logic {

namespace predicate {

FunctionTerm::FunctionTerm(const Function& function)
: function_(function) {}

FunctionTerm::FunctionTerm(const Function& function, const TermVector& args)
: function_(function), args_(args) {}

FunctionTerm::FunctionTerm(const Function& function, const Term& arg0)
: function_(function), args_(arg0) {}

FunctionTerm::FunctionTerm(const Function& function, const Term& arg0,
                           const Term& arg1)
: function_(function), args_(arg0, arg1) {}

FunctionTerm::FunctionTerm(const Function& function, const Term& arg0,
                           const Term& arg1, const Term& arg2)
: function_(function), args_(arg0, arg1, arg2) {}

FunctionTerm::FunctionTerm(const Function& function, const Term& arg0,
                           const Term& arg1, const Term& arg2, const Term& arg3)
: function_(function), args_(arg0, arg1, arg2, arg3) {}

void FunctionTerm::Destroy() {
//  std::cerr << "FunctionTerm::Destroy(): " << *this << "\n";
  args_.clear();
  delete this;
}

Element FunctionTerm::operator()(const Interpretation& semantics,
                                 VariableValues* interpretation) const {
  std::vector<Element> simple_args;
  typedef TermVector::const_iterator ConstIterator;
  for (ConstIterator arg = args_.begin(), end = args_.end(); arg != end; ++arg) {
    //    simple_args.push_back((**arg)());
    if (Element::ConstPtr e = dynamic_cast<Element::ConstPtr>(*arg))
      simple_args.push_back(*e);
    else if (Variable::ConstPtr v = dynamic_cast<Variable::ConstPtr>(*arg)) {
      if (!interpretation->count(*v))
        throw UninterpretableException();
      simple_args.push_back(interpretation->at(*v));
    }
    else if (FunctionTerm::ConstPtr f = dynamic_cast<FunctionTerm::ConstPtr>(*arg))
      simple_args.push_back((*f)(semantics, interpretation));
  }
  return semantics.Evaluate(function_, Arguments(simple_args));
}

std::ostream& FunctionTerm::operator<<(std::ostream& os) const {
  os << function_ << '(' << args_ << ')';
  return os;
}

const Function& FunctionTerm::function() const {
  return function_;
}

bool FunctionTerm::Less::operator()(const FunctionTerm& lhs,
                                    const FunctionTerm& rhs) const {
  static Function::Less less;
  return less(lhs.function_, rhs.function_);
}


}  // namespace predicate

}  // namespace logic
