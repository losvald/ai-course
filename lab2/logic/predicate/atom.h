/*
 * atom.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef ATOM_H_
#define ATOM_H_

#include <iostream>
#include <vector>

#include "arguments.h"
#include "formula.h"
#include "predicate.h"
#include "term.h"
#include "term_vector.h"
#include "variable.h"

namespace logic {

namespace predicate {

class Atom : public Formula::DerivationHelper<Atom> {
public:
  explicit Atom(const Predicate& pred, const TermVector& args);
  explicit Atom(const Predicate& predicate);
  explicit Atom(const Predicate& predicate, const Term& arg0);
  explicit Atom(const Predicate& predicate, const Term& arg0, const Term& arg1);
  explicit Atom(const Predicate& predicate, const Term& arg0, const Term& arg1,
                const Term& arg2);
  explicit Atom(const Predicate& predicate, const Term& arg0, const Term& arg1,
                const Term& arg2, const Term& arg3);

  ~Atom();

  void Destroy();

  bool operator()(const Interpretation& semantics,
                  VariableValues* interpretation) const;
  std::ostream& operator<<(std::ostream& os) const;

  const Predicate& predicate() const;

  struct Less {
    bool operator()(const Atom& lhs, const Atom& rhs) const;
  };
private:
  Predicate predicate_;
  TermVector args_;
};

}  // namespace predicate

}  // namespace logic


#endif /* ATOM_H_ */
