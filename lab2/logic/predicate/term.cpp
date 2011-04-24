/*
 * term.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "term.h"

namespace logic {

namespace predicate {

Term::~Term() {
}

void Term::Destroy() {
  delete this;
}

std::ostream& operator<<(std::ostream& os, const Term& term) {
  return term.operator<<(os);
}

}  // namespace predicate

}  // namespace logic
