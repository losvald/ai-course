/*
 * predicate_map.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef PREDICATE_MAP_H_
#define PREDICATE_MAP_H_

#include <map>
#include <set>

#include "arguments.h"
#include "predicate.h"

namespace logic {

namespace predicate {

typedef std::set<Arguments, Arguments::Less> PredicateExtension;
typedef std::map<std::string, PredicateExtension>
PredicateExtensionMap;

typedef std::map<Arguments, bool, Arguments::Less> PredicateMapping;
typedef std::map<Predicate, PredicateMapping, Predicate::Less> PredicateMap;


}  // namespace predicate

}  // namespace logic

#endif /* PREDICATE_MAP_H_ */
