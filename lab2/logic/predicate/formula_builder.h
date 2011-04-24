/*
 * formula_builder.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef FORMULA_BUILDER_H_
#define FORMULA_BUILDER_H_

#include "formula.h"

namespace logic {

namespace predicate {

namespace builder {

Formula& operator~(const Formula& f0);

Formula& operator&(const Formula& f0, const Formula& f1);
Formula& operator|(const Formula& f0, const Formula& f1);
Formula& operator>(const Formula& f0, const Formula& f1);
Formula& operator<(const Formula& f0, const Formula& f1);
Formula& operator==(const Formula& f0, const Formula& f1);

Formula& A(const Variable& variable, const Formula& f);
Formula& A(const std::string& variable_name, const Formula& f);
Formula& E(const Variable& variable, const Formula& f);
Formula& E(const std::string& variable_name, const Formula& f);

}  // namespace builder

}  // namespace predicate

}  // namespace logic

#endif /* FORMULA_BUILDER_H_ */
