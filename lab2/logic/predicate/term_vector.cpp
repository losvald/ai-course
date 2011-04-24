/*
 * term_vector.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#include "term_vector.h"

namespace logic {

namespace predicate {

TermVector::TermVector() {}

TermVector::TermVector(const TermVector& clone) : super(clone) {}

TermVector::TermVector(const Term& term0, const TermVector& clone) {
  super::reserve(clone.size() + 1);
  super::Add(term0);
  super::Add(clone);
}

TermVector::TermVector(const Term& term0) : super(term0) {}

TermVector::TermVector(const Term& term0, const Term& term1)
: super(term0, term1) {}

TermVector::TermVector(const Term& term0, const Term& term1, const Term& term2)
: super(term0, term1, term2) {}

TermVector::TermVector(const Term& term0, const Term& term1, const Term& term2,
                       const Term& term3) : super(term0, term1, term2, term3) {}


//TermVector::TermVector() : super(0) {}
//
//TermVector::TermVector(const TermVector& clone) : super(clone.size()) {
//  for (size_type i = 0, count = size(); i < count; ++i)
//    (*this)[i] = clone[i]->Clone();
//}
//
//TermVector::TermVector(const Term& term0) : super(1) {
//  (*this)[0] = term0.Clone();
//}
//
//TermVector::TermVector(const Term& term0, const Term& term1) : super(2) {
//  (*this)[0] = term0.Clone(); (*this)[1] = term1.Clone();
//}
//
//TermVector::TermVector(const Term& term0, const Term& term1, const Term& term2)
//: super(3) {
//  (*this)[0] = term0.Clone(); (*this)[1] = term1.Clone();
//  (*this)[2] = term2.Clone();
//}
//
//TermVector::TermVector(const Term& term0, const Term& term1, const Term& term2,
//                       const Term& term3) : super(4) {
//  (*this)[0] = term0.Clone(); (*this)[1] = term1.Clone();
//  (*this)[2] = term2.Clone(); (*this)[3] = term3.Clone();
//}
//
//TermVector::~TermVector() {
//  for (const_iterator it = begin(), _end = end(); it != _end; ++it)
//    delete *it;
//}
//
//void TermVector::Add(const Term& term) {
//  push_back(term.Clone());
//}
//
//std::ostream& operator<<(std::ostream& os, const TermVector& v) {
//  typedef std::vector<Term::ConstPtr> super;
//  for (super::const_iterator it = v.begin(), end = v.end(); it != end; ) {
//    os << **it;
//    if (++it != end) os << ", ";
//  }
//  return os;
//}


}  // namespace predicate

}  // namespace logic
