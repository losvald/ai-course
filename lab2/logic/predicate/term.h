/*
 * term.h
 *
 *  Created on: Apr 15, 2011
 *      Author: leden
 */

#ifndef TERM_H_
#define TERM_H_

#include <iostream>

namespace logic {

namespace predicate {

class Element;

class Term {
public:
  typedef const Term* ConstPtr;

  virtual ~Term();
  virtual Term* Clone() const = 0;
  virtual void Destroy();
//  virtual Element operator()() const = 0;
  virtual std::ostream& operator<<(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Term& term);

  template<class Derived>
  class DerivationHelper;
};

template<class Derived>
class Term::DerivationHelper : public Term {
public:
  virtual ~DerivationHelper() {}
  virtual Term* Clone() const {
    return new Derived(static_cast<const Derived&>(*this));
  }
};

}  // namespace predicate

}  // namespace logic


#endif /* TERM_H_ */
