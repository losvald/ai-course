/*
 * foreach.h
 *
 *  Created on: Mar 9, 2011
 *      Author: leden
 */

#ifndef FOREACH_H_
#define FOREACH_H_

#define FOREACH(it, c) for (__typeof((c).begin()) it = (c).begin(); it != (c).end(); ++it)

#endif /* FOREACH_H_ */
