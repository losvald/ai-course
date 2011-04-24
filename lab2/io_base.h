/*
 * io_base.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef IO_BASE_H_
#define IO_BASE_H_

#include <sstream>

namespace logic {

namespace predicate {

class MakeString {
public:
   template <typename T>
   MakeString& operator<<(const T& datum) {
      buffer_ << datum;
      return *this;
   }
   operator std::string() const {
      return buffer_.str();
   }
private:
   std::ostringstream buffer_;
};


}  // namespace predicate

}  // namespace logic

#endif /* IO_BASE_H_ */
