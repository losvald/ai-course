/*
 * function_map.h
 *
 *  Created on: Apr 16, 2011
 *      Author: leden
 */

#ifndef FUNCTION_MAP_H_
#define FUNCTION_MAP_H_

#include <map>

#include "arguments.h"
#include "element.h"
#include "function.h"

namespace logic {

namespace predicate {

typedef std::map<Arguments, Element, Arguments::Less> FunctionMapping;
typedef std::map<Function, FunctionMapping, Function::Less> FunctionMap;

}  // namespace predicate

}  // namespace logic

#endif /* FUNCTION_MAP_H_ */
