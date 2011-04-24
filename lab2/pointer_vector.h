/*
 * pointer_vector.h
 *
 *  Created on: Apr 16, 2011
 *      Author: Leo Osvald
 */

#ifndef POINTER_VECTOR_H_
#define POINTER_VECTOR_H_

template<typename T>
class PointerVector : public std::vector<T*> {
public:
  PointerVector() {}
  PointerVector(const PointerVector& clone) : super(clone.size()) {
    for (typename super::size_type i = 0, count = super::size(); i < count; ++i)
      (*this)[i] = clone[i]->Clone();
//    std::cerr << "(Clone vector pointer): " << *this << std::endl;
  }
  PointerVector(const T& p0) : super(1) {
    (*this)[0] = p0.Clone();
  }
  PointerVector(const T& p0, const T& p1) : super(2) {
    (*this)[0] = p0.Clone(); (*this)[1] = p1.Clone();
  }
  PointerVector(const T& p0, const T& p1, const T& p2) : super(3) {
    (*this)[0] = p0.Clone(); (*this)[1] = p1.Clone();
    (*this)[2] = p2.Clone();
  }
  PointerVector(const T& p0, const T& p1, const T& p2,const T& p3)
  : super(4) {
    (*this)[0] = p0.Clone(); (*this)[1] = p1.Clone();
    (*this)[2] = p2.Clone(); (*this)[3] = p3.Clone();
  }
  virtual ~PointerVector() {
    for (typename super::iterator it = super::begin(), _end = super::end();
        it != _end; ++it) {
//      std::cerr << "Destroy: " << **it << '[' << *it << ']' << std::endl;
      (*it)->Destroy();
    }
  }

  void Add(const T& p) {
    push_back(p.Clone());
  }

  void Add(const PointerVector& terms) {
    for (typename super::size_type i = 0, count = terms.size(); i < count; ++i)
      push_back(terms[i]->Clone());
  }

  friend std::ostream& operator<<(std::ostream& os, const PointerVector& v) {
    typedef std::vector<T*> super;
    for (typename super::const_iterator it = v.begin(), end = v.end();
        it != end; ) {
      os << **it;
      if (++it != end) os << ", ";
    }
//    os << "[";
//    for (typename super::const_iterator it = v.begin(), end = v.end();
//            it != end; ) {
//          os << *it;
//          if (++it != end) os << " ";
//        }
//    os << "]";
    return os;
  }

private:
  typedef std::vector<T*> super;
};

#endif /* POINTER_VECTOR_H_ */
