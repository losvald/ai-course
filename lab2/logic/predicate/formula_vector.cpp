/*
 * formula_vector.cpp
 *
 *  Created on: Apr 22, 2011
 *      Author: Leo Osvald
 */

#include "formula_vector.h"

namespace logic {

namespace predicate {

FormulaVector::FormulaVector() {}

FormulaVector::FormulaVector(const FormulaVector& clone) : super(clone) {}

FormulaVector::FormulaVector(const Formula& formula0) : super(formula0) {}

FormulaVector::FormulaVector(const Formula& formula0, const Formula& formula1)
: super(formula0, formula1) {}

FormulaVector::FormulaVector(const Formula& formula0, const Formula& formula1,
                             const Formula& formula2)
: super(formula0, formula1, formula2) {}

FormulaVector::FormulaVector(const Formula& formula0, const Formula& formula1,
                             const Formula& formula2, const Formula& formula3)
: super(formula0, formula1, formula2, formula3) {}

FormulaVector::~FormulaVector() {
//  std::cerr << "~FormulaVector: " << *this << '[' << this << ']' << std::endl;
}


}  // namespace predicate

}  // namespace logic
