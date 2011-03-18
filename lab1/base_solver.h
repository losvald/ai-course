/*
 * base_solver.h
 *
 *  Created on: Mar 9, 2011
 *      Author: leden
 */

#ifndef BASE_SOLVER_H_
#define BASE_SOLVER_H_

template<typename T, int Rows, int Columns = Rows, T ZERO = T()>
class BaseSolver {
	virtual bool solve() = 0;
	virtual T query(int row, int col) const = 0;
};


#endif /* BASE_SOLVER_H_ */
