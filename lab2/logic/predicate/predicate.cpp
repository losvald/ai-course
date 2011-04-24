/*
 * predicate.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: Leo Osvald
 */

#include "atom.h"
#include "term_vector.h"
#include "predicate.h"
#include "term.h"

namespace logic {

namespace predicate {

Predicate::Predicate(const std::string& name) : name_(name) {}

std::ostream& operator<<(std::ostream& os, const Predicate& p) {
  os << p.name_;
  return os;
}

Atom Predicate::operator()(const TermVector& terms) {
  return Atom(*this, terms);
}

Atom Predicate::operator()() {
  return Atom(*this, TermVector());
}

Atom Predicate::operator()(const Term& term0) {
  return Atom(*this, TermVector(term0));
}

Atom Predicate::operator()(const Term& term0, const Term& term1) {
  return Atom(*this, TermVector(term0, term1));
}

Atom Predicate::operator()(const Term& term0, const Term& term1,
                           const Term& term2) {
  return Atom(*this, TermVector(term0, term1, term2));
}

Atom Predicate::operator()(const Term& term0, const Term& term1,
                           const Term& term2, const Term& term3) {
  return Atom(*this, TermVector(term0, term1, term2, term3));
}

const std::string& Predicate::name() const { return name_; }

bool Predicate::Less::operator()(const Predicate& lhs, const Predicate& rhs) const {
  return lhs.name_ < rhs.name_;
}

}  // namespace predicate

}  // namespace logic
