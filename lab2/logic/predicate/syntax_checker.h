/*
 * syntax_checker.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef SYNTAX_CHECKER_H_
#define SYNTAX_CHECKER_H_

namespace logic {

namespace predicate {

class Formula;

struct SyntaxErrorException : std::exception {
};

void CheckSyntax(const Formula& formula);

}  // namespace predicate

}  // namespace logic

#endif /* SYNTAX_CHECKER_H_ */
