/*
 * operator.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "formula.h"

#include "interpretation.h"
#include "operator.h"

namespace logic {

namespace predicate {

Operator::~Operator() {}

std::ostream& operator<<(std::ostream& os, const Operator& op) {
  return op.operator<<(os);
}

int UnaryOperator::arity() const { return 1; }
int BinaryOperator::arity() const { return 2; }

namespace {

struct Not : UnaryOperator {
  bool operator()(const Formula& f, const Interpretation& semantics,
                  VariableValues* interpretation) const {
    return !f(semantics, interpretation);
  }
  std::ostream& operator<<(std::ostream& os) const {
    os << "~";
    return os;
  }
};

struct And : BinaryOperator {
  bool operator()(const Formula& lhs, const Formula& rhs,
                  const Interpretation& semantics,
                  VariableValues* interpretation) const {
    return lhs(semantics, interpretation) && rhs(semantics, interpretation);
  }
  std::ostream& operator<<(std::ostream& os) const {
    os << "&";
    return os;
  }
};

struct Or : BinaryOperator {
  bool operator()(const Formula& lhs, const Formula& rhs,
                  const Interpretation& semantics,
                  VariableValues* interpretation) const {
    return lhs(semantics, interpretation) || rhs(semantics, interpretation);
  }
  std::ostream& operator<<(std::ostream& os) const {
    os << "|";
    return os;
  }
};

struct If : BinaryOperator {
  bool operator()(const Formula& lhs, const Formula& rhs,
                  const Interpretation& semantics,
                  VariableValues* interpretation) const {
    return !lhs(semantics, interpretation) || rhs(semantics, interpretation);
  }
  std::ostream& operator<<(std::ostream& os) const {
    os << "->";
    return os;
  }
};

struct OnlyIf : BinaryOperator {
  bool operator()(const Formula& lhs, const Formula& rhs,
                  const Interpretation& semantics,
                  VariableValues* interpretation) const {
    return lhs(semantics, interpretation) || !rhs(semantics, interpretation);
  }
  std::ostream& operator<<(std::ostream& os) const {
    os << "<-";
    return os;
  }
};

struct Iff : BinaryOperator {
  bool operator()(const Formula& lhs, const Formula& rhs,
                  const Interpretation& semantics,
                  VariableValues* interpretation) const {
    return lhs(semantics, interpretation) == rhs(semantics, interpretation);
  }
  std::ostream& operator<<(std::ostream& os) const {
    os << "<->";
    return os;
  }
};

} // namespace

UnaryOperator::ConstPtr UnaryOperator::kNot = new Not();

BinaryOperator::ConstPtr BinaryOperator::kAnd = new And();
BinaryOperator::ConstPtr BinaryOperator::kOr = new Or();
BinaryOperator::ConstPtr BinaryOperator::kIf = new If();
BinaryOperator::ConstPtr BinaryOperator::kOnlyIf = new OnlyIf();
BinaryOperator::ConstPtr BinaryOperator::kIff = new Iff();

}  // namespace predicate

}  // namespace logic

