/*
 * predicate.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "atom.h"
#include "function_term.h"
#include "interpretation.h"
#include "predicate.h"
#include "term.h"
#include "variable.h"

namespace logic {

namespace predicate {

Atom::Atom(const Predicate& predicate) : predicate_(predicate) {}

Atom::Atom(const Predicate& predicate, const TermVector& args)
: predicate_(predicate), args_(args) {}

Atom::Atom(const Predicate& predicate, const Term& arg0)
: predicate_(predicate), args_(arg0) {}

Atom::Atom(const Predicate& predicate, const Term& arg0, const Term& arg1)
: predicate_(predicate), args_(arg0, arg1) {}

Atom::Atom(const Predicate& predicate, const Term& arg0,
           const Term& arg1, const Term& arg2)
: predicate_(predicate), args_(arg0, arg1, arg2) {}

Atom::Atom(const Predicate& predicate, const Term& arg0, const Term& arg1,
           const Term& arg2, const Term& arg3)
: predicate_(predicate), args_(arg0, arg1, arg2, arg3) {}

Atom::~Atom() {
//  std::cerr << "~Atom(): " << *this << '[' << this << ']' << std::endl;
}

void Atom::Destroy() {
//  std::cerr << "Atom::Destroy(): " << *this << "\n";
  args_.clear();
  delete this;
}

bool Atom::operator()(const Interpretation& semantics,
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
  return semantics.Evaluate(predicate_, Arguments(simple_args));
}

std::ostream& Atom::operator<<(std::ostream& os) const {
  os << predicate_ << '(' << args_ << ')';
  return os;
}

const Predicate& Atom::predicate() const {
  return predicate_;
}

bool Atom::Less::operator()(const Atom& lhs, const Atom& rhs) const {
  static Predicate::Less less;
  return less(lhs.predicate_, rhs.predicate_);
}

}  // namespace predicate

}  // namespace logic
