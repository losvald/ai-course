/*
 * variable.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#include "element.h"
#include "variable.h"

namespace logic {

namespace predicate {

Variable::Variable(const std::string& name) : name_(name) {}

//Element Variable::operator()() const {
//  return get();
//}

std::ostream& Variable::operator<<(std::ostream& os) const {
  os << name_; // << '(' << (is_set() ? get() : "(null)") << ')';
  return os;
}

//const Element& Variable::get() const {
//  return val_;
//}
//
//void Variable::set(const Element& value) {
//  val_ = value;
//  set_ = true;
//}
//
//void Variable::unset() {
//  set_ = false;
//}

const std::string& Variable::name() const { return name_; }

//bool Variable::is_set() const { return set_; }

bool Variable::Less::operator()(const Variable& lhs, const Variable& rhs) const {
  return lhs.name_ < rhs.name_;
}

}  // namespace predicate

}  // namespace logic
