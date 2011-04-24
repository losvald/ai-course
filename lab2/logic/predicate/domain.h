/*
 * domain.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef DOMAIN_H_
#define DOMAIN_H_

#include <set>

#include "element.h"

namespace logic {

namespace predicate {

typedef std::set<Element, Element::Less> Domain;

}  // namespace predicate

}  // namespace logic

#endif /* DOMAIN_H_ */
