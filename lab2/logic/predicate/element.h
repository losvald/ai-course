/*
 * element.h
 *
 *  Created on: Apr 15, 2011
 *      Author: leden
 */

#ifndef ELEMENT_H_
#define ELEMENT_H_

#include <iostream>

#include "../../io_base.h"
#include "term.h"

namespace logic {

namespace predicate {

class Element : public Term::DerivationHelper<Element> {
public:
  typedef const Element* ConstPtr;

  Element();
  Element(const std::string& val);
  Element(const char* val);
  template<typename T> Element(const T& val) : val_(MakeString() << val) {}
  template<typename T> T As() const;
//  Element operator()() const;
  std::ostream& operator<<(std::ostream& os) const;
  friend bool operator==(const Element& e1, const Element& e2);
  friend bool operator!=(const Element& e1, const Element& e2);
  const std::string& string() const;

  struct Less {
    bool operator()(const Element& lhs, const Element& rhs) const;
  };

private:
  std::string val_;
};

}  // namespace predicate

}  // namespace logic



#endif /* ELEMENT_H_ */
