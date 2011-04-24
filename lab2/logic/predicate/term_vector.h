/*
 * term_vector.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#ifndef TERM_VECTOR_H_
#define TERM_VECTOR_H_

#include <iostream>
#include <vector>

#include "term.h"

#include "../../pointer_vector.h"

namespace logic {

namespace predicate {

class TermVector : public PointerVector<Term> {
public:
    TermVector();
    TermVector(const TermVector& clone);
    TermVector(const Term& term0, const TermVector& clone);
    TermVector(const Term& term0);
    TermVector(const Term& term0, const Term& term1);
    TermVector(const Term& term0, const Term& term1, const Term& term2);
    TermVector(const Term& term0, const Term& term1, const Term& term2,
               const Term& term3);
private:
  typedef PointerVector<Term> super;
};

//class TermVector : public std::vector<Term::ConstPtr> {
//public:
//  TermVector();
//  TermVector(const TermVector& clone);
//  TermVector(const Term& term0);
//  TermVector(const Term& term0, const Term& term1);
//  TermVector(const Term& term0, const Term& term1, const Term& term2);
//  TermVector(const Term& term0, const Term& term1, const Term& term2,
//             const Term& term3);
//  ~TermVector();
//  void Add(const Term& term);
//  friend std::ostream& operator<<(std::ostream& os, const TermVector& v);
//private:
//  typedef std::vector<Term::ConstPtr> super;
//};

}  // namespace predicate

}  // namespace logic

#endif /* TERM_VECTOR_H_ */
