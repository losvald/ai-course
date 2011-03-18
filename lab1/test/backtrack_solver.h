/*
 *  Copyright (C) 2010 Leo Osvald <leo.osvald@gmail.com>
 *
 *  Licensed to the Apache Software Foundation (ASF) under one or more
 *  contributor license agreements.  See the NOTICE file distributed with
 *  this work for additional information regarding copyright ownership.
 *  The ASF licenses this file to You under the Apache License, Version 2.0
 *  (the "License"); you may not use this file except in compliance with
 *  the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <iostream>
#include <cstddef>

#include "../base_solver.h"

template<typename T, int Rows, int Columns = Rows, T ZERO = T()>
class SudokuSolver : public BaseSolver<T, Rows, Columns, ZERO> {
public:
	typedef std::size_t SizeType;
	static const SizeType R = Rows, C = Columns;
	static const SizeType RC = R * C;

private:

	T table_[RC][RC];

	bool checkColumn(SizeType row, SizeType col) const {
		T val = table_[row][col];
		for (SizeType r = 0; r < RC; ++r)
			if (r != row && table_[r][col] == val)
				return false;
		return true;
	}

	bool checkRow(SizeType row, SizeType col) const {
		T val = table_[row][col];
		for (SizeType c = 0; c < RC; ++c)
			if (c != col && table_[row][c] == val)
				return false;
		return true;
	}

	bool checkSquare(SizeType row, SizeType col) const {
		SizeType row_off = row / R * R, col_off = col / C * C;
		T val = table_[row][col];
		for (SizeType r = row_off; r < row_off + R; ++r)
			for (SizeType c = col_off; c < col_off + C; ++c)
				if ((r != row || c != col) && table_[r][c] == val)
					return false;
		return true;
	}

	bool backtrack(SizeType row, SizeType col) {
		if (row == RC)
			return true;

		SizeType next_row = row, next_col = col + 1, itr = 0;
		if (next_col == RC) {
			next_col = 0;
			++next_row;
		}

		if (table_[row][col] == ZERO) {
			for (T broj = ZERO; itr++ < RC; ) {
				table_[row][col] = ++broj;
				if (checkRow(row, col)
						&& checkColumn(row, col)
						&& checkSquare(row, col)
						&& backtrack(next_row, next_col))
					return true;
			}
			table_[row][col] = ZERO;
			return false;
		}
		return backtrack(next_row, next_col);
	}

public:
	SudokuSolver() {
		for (SizeType row = 0; row < RC; ++row)
			for (SizeType col = 0; col < RC; ++col)
				table_[row][col] = ZERO;
	}

	bool solve() {
		return backtrack(0, 0);
	}

	void set(SizeType row, SizeType col, T value) {
		table_[row][col] = value;
	}

	friend std::ostream& operator<<(std::ostream& os, const SudokuSolver& s) {
		os << std::endl;
		for (SizeType i = 0; i < RC; ++i, os << std::endl)
			for (SizeType j = 0; j < RC; ++j)
				os << s.table_[i][j] << ' ';
		os << std::endl;
		return os;
	}

	T query(int row, int col) const {
		return table_[row][col];
	}

};


