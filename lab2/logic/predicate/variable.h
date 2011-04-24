/*
 * variable.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <map>

#include "element.h" // XXX
#include "term.h"

namespace logic {

namespace predicate {

//class Element;

class Variable : public Term::DerivationHelper<Variable> {
  std::string name_;
//  Element val_;
  bool set_;
public:
  typedef const Variable* ConstPtr;
  typedef Variable* Ptr;

  explicit Variable(const std::string& name);

  Element operator()() const;
  std::ostream& operator<<(std::ostream& os) const;

//  const Element& get() const;
//  void set(const Element& value);
//  void unset();
  const std::string& name() const;
  bool is_set() const;

  struct Less {
    bool operator()(const Variable& lhs, const Variable& rhs) const;
  };
};

typedef std::map<Variable, Element, Variable::Less> VariableValues;

}  // namespace predicate

}  // namespace logic

#endif /* VARIABLE_H_ */
