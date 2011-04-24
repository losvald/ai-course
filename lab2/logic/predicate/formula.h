/*
 * formula.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef FORMULA_H_
#define FORMULA_H_

#include <iostream>
#include <vector>

#include "term.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Interpretation;

class Formula {
public:
  typedef const Formula* ConstPtr;

  virtual ~Formula();
  virtual Formula* Clone() const = 0;
  virtual void Destroy();
  virtual bool operator()(const Interpretation& semantics,
                          VariableValues* interpretation) const = 0;
  virtual std::ostream& operator<<(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Formula& f);

  template<class Derived>
  class DerivationHelper;
};

template<class Derived>
class Formula::DerivationHelper : public Formula {
public:
//  virtual ~DerivationHelper() {}
  virtual Formula* Clone() const {
    return new Derived(static_cast<const Derived&>(*this));
  }
};


}  // namespace predicate

}  // namespace logic

#endif /* FORMULA_H_ */
