/*
 * arguments.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <iostream>
#include <vector>

#include "element.h"

namespace logic {

namespace predicate {

class Arguments {
public:
  explicit Arguments(std::vector<Element> args);
  Arguments(const Element& arg1);
  Arguments(const Element& arg0, const Element& arg1);
  Arguments(const Element& arg0, const Element& arg1, const Element& arg2);
  Arguments(const Element& arg0, const Element& arg1,
            const Element& arg2, const Element& arg3);

  const Element& operator[](std::size_t i) const;

  std::size_t Count() const;
  Element Get(int n) const;
  template<typename T> T Get(int n) const {
    return Get(n).As<T>();
  }

  friend std::ostream& operator<<(std::ostream& os, const Arguments& args);

  friend class LessComparator;

  struct Less {
    bool operator()(const Arguments& lhs, const Arguments& rhs) const {
      if (lhs.args_.size() != rhs.args_.size()) {
        return lhs.args_.size() < rhs.args_.size();
      }
      for (std::vector<Element>::const_iterator lit = lhs.args_.begin(),
          lend = lhs.args_.end(), rit = rhs.args_.begin(); lit != lend;
          ++lit, ++rit) {
        if (lit->string() != rit->string())
          return lit->string() < rit->string();
      }
      return false;
    }
  };

private:
  std::vector<Element> args_;
};

}  // namespace predicate

}  // namespace logic


#endif /* ARGUMENTS_H_ */
