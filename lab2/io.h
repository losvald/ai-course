/*
 * io.h
 *
 *  Created on: Apr 24, 2011
 *      Author: leden
 */

#ifndef IO_H_
#define IO_H_

#include <iostream>
#include <string>

namespace logic {

namespace predicate {

class Formula;
class Interpretation;

namespace parser {

Formula& ParseFormula(std::istream& is);

}  // namespace parser

bool PrintAndEval(const Interpretation& inter, const Formula& f);

void ProcessQueries(std::istream& is, Interpretation* inter);

void ProcessQueries(const std::string& filename, Interpretation* inter);

}  // namespace predicate

}  // namespace logic



#endif /* IO_H_ */
