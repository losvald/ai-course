/*
 * arguments.cpp
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef ARGUMENTS_CPP_
#define ARGUMENTS_CPP_

#include <vector>

#include "arguments.h"

namespace logic {

namespace predicate {

Arguments::Arguments(std::vector<Element> args) : args_(args) {}
Arguments::Arguments(const Element& arg1) : args_(1) {
  args_[0] = arg1;
}
Arguments::Arguments(const Element& arg0, const Element& arg1)
: args_(2) {
  args_[0] = arg0;
  args_[1] = arg1;
}
Arguments::Arguments(const Element& arg0, const Element& arg1,
                     const Element& arg2)
: args_(3) {
  args_[0] = arg0;
  args_[1] = arg1;
  args_[2] = arg2;
}
Arguments::Arguments(const Element& arg0, const Element& arg1,
                     const Element& arg2, const Element& arg3)
: args_(4) {
  args_[0] = arg0;
  args_[1] = arg1;
  args_[2] = arg2;
  args_[3] = arg3;
}

const Element& Arguments::operator[](std::size_t i) const {
  return args_.at(i);
}

std::ostream& operator<<(std::ostream& os, const Arguments& args) {
  bool first = true;
  for (std::vector<Element>::const_iterator a = args.args_.begin(),
      end = args.args_.end(); a != end; ++a) {
    if (first) first = false;
    else os << ", ";
    os << *a;
  }
  return os;
}

std::size_t Arguments::Count() const {
  return args_.size();
}

Element Arguments::Get(int n) const {
  return args_.at(n);
}

}  // namespace predicate

}  // namespace logic



#endif /* ARGUMENTS_CPP_ */
