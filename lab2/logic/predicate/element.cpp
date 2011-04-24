/*
 * element.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "element.h"

#include <cstdlib>

#include <iostream>
#include <string>

#include "../../io_base.h"

namespace logic {

namespace predicate {

Element::Element() : val_() {}
Element::Element(const std::string& val) : val_(val) {}
Element::Element(const char* val) : val_(val) {}

bool operator==(const Element& e1, const Element& e2) {
  return e1.val_ == e2.val_;
}

bool operator!=(const Element& e1, const Element& e2) {
  return e1.val_ != e2.val_;
}

//Element Element::operator()() const {
//  return *this;
//}

std::ostream& Element::operator<<(std::ostream& os) const {
  os << val_;
  return os;
}

template<> std::string Element::As() const { return val_; }
template<> int Element::As() const { return atoi(val_.c_str()); }

const std::string& Element::string() const {
  return val_;
}

bool Element::Less::operator()(const Element& lhs, const Element& rhs) const {
  return lhs.val_ < rhs.val_;
}

}  // namespace predicate

}  // namespace logic


