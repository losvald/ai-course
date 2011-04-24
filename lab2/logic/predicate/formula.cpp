/*
 * formula.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "formula.h"

namespace logic {

namespace predicate {

Formula::~Formula() {}

void Formula::Destroy() {
  std::cerr << "BUG - Formula::Destroy() should not be called: " << *this << "\n";
  delete this;
}

std::ostream& operator<<(std::ostream& os, const Formula& f) {
  return f.operator<<(os);
}

}  // namespace predicate

}  // namespace logic
