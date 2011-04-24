/*
 * formula_vector.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#ifndef FORMULA_VECTOR_H_
#define FORMULA_VECTOR_H_

#include <iostream>
#include <vector>

#include "../../pointer_vector.h"
#include "formula.h"

namespace logic {

namespace predicate {

class FormulaVector : public PointerVector<Formula> {
public:
  FormulaVector();
  FormulaVector(const FormulaVector& clone);
  FormulaVector(const Formula& Formula0);
  FormulaVector(const Formula& Formula0, const Formula& Formula1);
  FormulaVector(const Formula& Formula0, const Formula& Formula1, const Formula& Formula2);
  FormulaVector(const Formula& Formula0, const Formula& Formula1, const Formula& Formula2,
             const Formula& Formula3);
  ~FormulaVector();
private:
  typedef PointerVector<Formula> super;
};

}  // namespace predicate

}  // namespace logic

#endif /* FORMULA_VECTOR_H_ */
