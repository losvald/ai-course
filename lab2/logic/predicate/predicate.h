/*
 * predicate.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#ifndef PREDICATE_H_
#define PREDICATE_H_

#include <iostream>
#include <string>

namespace logic {

namespace predicate {

class Atom;
class Term;
class TermVector;

class Predicate {
public:
  Predicate(const std::string& name);
  friend std::ostream& operator<<(std::ostream& os, const Predicate& p);
  const std::string& name() const;

  Atom operator()(const TermVector& terms);
  Atom operator()();
  Atom operator()(const Term& term0);
  Atom operator()(const Term& term0, const Term& term1);
  Atom operator()(const Term& term0, const Term& term1, const Term& term2);
  Atom operator()(const Term& term0, const Term& term1, const Term& term2,
                  const Term& term3);

  struct Less {
    bool operator()(const Predicate& lhs, const Predicate& rhs) const;
  };
private:
  std::string name_;
};


}  // namespace predicate

}  // namespace logic


#endif /* PREDICATE_H_ */
