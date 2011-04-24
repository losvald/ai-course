/*
 * operator.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef OPERATOR_H_
#define OPERATOR_H_

#include <iostream>

#include "variable.h"

namespace logic {

namespace predicate {

//enum BinaryOperator { kAnd, kOr, kIff, kIf, kOnlyIf };
//enum UnaryOperator { kNeg };

class Interpretation;

struct Operator {
  typedef const Operator* ConstPtr;
  virtual ~Operator();
  virtual int arity() const = 0;
  virtual std::ostream& operator<<(std::ostream& os) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const Operator& op);
};

class Formula;

struct UnaryOperator : Operator {
  typedef const UnaryOperator* ConstPtr;
  int arity() const;
  virtual bool operator()(const Formula& f, const Interpretation& semantics,
                          VariableValues* interpretation) const = 0;
  static UnaryOperator::ConstPtr kNot;
};

struct BinaryOperator : Operator {
  typedef const BinaryOperator* ConstPtr;
  int arity() const;
  virtual bool operator()(const Formula& lhs, const Formula& rhs,
                          const Interpretation& semantics,
                          VariableValues* interpretation) const = 0;

  static BinaryOperator::ConstPtr kAnd;
  static BinaryOperator::ConstPtr kOr;
  static BinaryOperator::ConstPtr kIf;
  static BinaryOperator::ConstPtr kOnlyIf;
  static BinaryOperator::ConstPtr kIff;
};


}  // namespace predicate

}  // namespace logic

#endif /* OPERATOR_H_ */
