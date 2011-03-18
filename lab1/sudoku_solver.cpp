/*
 * zad-1_5.cpp
 *
 *  Created on: Mar 9, 2011
 *      Author: Leo Osvald
 */

#include <iostream>

#include "base_solver.h"
#include "test/backtrack_solver.h"

#include "logic/atom.h"
#include "logic/literal.h"
#include "logic/clause.h"
#include "logic/prover.h"

template<typename T, int Rows, int Columns = Rows, T ZERO = T()>
class PropositionalLogicSudokuSolver : public BaseSolver<T, Rows, Columns, ZERO> {
public:
	typedef std::size_t SizeType;
	typedef T ValueType;
	static const SizeType R = Rows, C = Columns;
	static const SizeType RC = R * C;

private:

	template<typename ValueClass, typename SizeTypeClass>
	class AtomId {
		SizeTypeClass row_, col_;
		ValueClass val_;
	public:
		AtomId(SizeTypeClass row, SizeTypeClass col, ValueClass val)
		: row_(row), col_(col), val_(val) { }

		SizeTypeClass row() const { return row_; }
		SizeTypeClass col() const { return col_; }
		ValueClass value() const { return val_; }

		friend bool operator<(const AtomId& a, const AtomId& b) {
			return a.row_ < b.row_
					|| (!(b.row_ < a.row_) && (a.col_ < b.col_
							|| (!(b.col_ < a.col_) && a.val_ < b.val_)));
		}

		friend bool operator==(const AtomId& a, const AtomId& b) {
			return a.row_ == b.row_ && a.col_ == b.col_ && a.val_ == b.val_;
		}

		friend std::ostream& operator<<(std::ostream& os, const AtomId& a) {
			os << '[' << a.row_ << ' ' << a.col_ << '|' << a.val_ << ']';
			return os;
		}
	};

public:
	typedef AtomId<T, SizeType> AtomIdType;
	typedef logic::Atom<AtomIdType> AtomType;
	typedef logic::Literal<AtomIdType> LiteralType;
private:
	typedef logic::Clause<AtomIdType> ClauseType;
	typedef logic::Prover<AtomIdType> ProverType;

	T table_[RC][RC];

	static LiteralType createLiteral(SizeType row, SizeType col, T value,
			bool negated) {
		return LiteralType(AtomType(AtomIdType(row, col, value)), negated);
	}

	static bool addClausesForColumn(ProverType& prover,
			SizeType row, SizeType col, T value) {
		for (SizeType r = 0; r < RC; ++r)
			if (r != row) {
				ClauseType clause;
				clause.add(createLiteral(row, col, value, true));
				clause.add(createLiteral(r, col, value, true));
				prover.addClause(clause);
			}
		return true;
	}

	static bool addClausesForRow(ProverType& prover,
			SizeType row, SizeType col, T value) {
		for (SizeType c = 0; c < RC; ++c)
			if (c != col) {
				ClauseType clause;
				clause.add(createLiteral(row, col, value, true));
				clause.add(createLiteral(row, c, value, true));
				prover.addClause(clause);
			}
		return true;
	}

	static bool addClausesForSquare(ProverType& prover,
			SizeType row, SizeType col, T value) {
		SizeType row_off = row / R * R, col_off = col / C * C;
		for (SizeType r = row_off; r < row_off + R; ++r)
			for (SizeType c = col_off; c < col_off + C; ++c)
				if (r != row || c != col) {
					ClauseType clause;
					clause.add(createLiteral(row, col, value, true));
					clause.add(createLiteral(r, c, value, true));
					prover.addClause(clause);
				}
		return true;
	}

public:
	void set(SizeType row, SizeType col, T value) {
		table_[row][col] = value;
	}

	bool query(SizeType row, SizeType col, T target) const {
		for (SizeType r = 0; r < RC; ++r) {
			for (SizeType c = 0; c < RC; ++c) {
				std::cerr << table_[r][c] << " ";
			}
			std::cerr << std::endl;
		}

		for (SizeType r = 0; r < RC; ++r) {
					for (SizeType c = 0; c < RC; ++c) {
						std::cerr << "("<< (table_[r][c] != ZERO) << ")";
					}
					std::cerr << std::endl;
				}


		ProverType prover;
		for (SizeType r = 0; r < RC; ++r)
			for (SizeType c = 0; c < RC; ++c) {
				T value = ZERO;
				ClauseType clause;
				for (SizeType itr = 0; itr++ < RC; ) {
					++value;
					addClausesForRow(prover, r, c, value);
					addClausesForColumn(prover, r, c, value);
					addClausesForSquare(prover, r, c, value);
					clause.add(createLiteral(r, c, value, false));
				}
				prover.addClause(clause);

				if (table_[r][c] != ZERO) {
					prover.addClause(ClauseType(createLiteral(r, c, table_[r][c], false)));
				}
			}

//		std::cout << "Clauses" << std::endl;
		std::cout << prover << std::endl;

		return prover.prove(createLiteral(row, col, target, false));
	}

	T query(int row, int col) const {
		T value = ZERO;
		for (SizeType itr = 0; itr++ < RC; ) {
			++value;
			if (query(row, col, value))
				return value;
		}
		return ZERO;
	}

	bool solve() {
		for (SizeType r = 0; r < RC; ++r)
			for (SizeType c = 0; c < RC; ++c)
				if (table_[r][c] == ZERO) {
					if ((table_[r][c] = query(r, c)) == ZERO) {
						std::cerr << "CANNOTDEDUCE" << std::endl;
						//return false;
					}
					else {
						std::cerr << "COMPUTED" << std::endl;
					}
				}

		return true;
	}

	friend std::ostream& operator<<(std::ostream& os,
			const PropositionalLogicSudokuSolver& s) {
		os << std::endl;
		for (SizeType i = 0; i < RC; ++i, os << std::endl)
			for (SizeType j = 0; j < RC; ++j)
				os << s.table_[i][j] << ' ';
		os << std::endl;
		return os;
	}
};


typedef PropositionalLogicSudokuSolver<int, 2> MySudokuSolver;

namespace {

using namespace logic;

typedef MySudokuSolver::AtomIdType MyAtomIdType;

template<> const Atom<MyAtomIdType> Atom<MyAtomIdType>::TRUE(
		MyAtomIdType(-1, -1, 0));
template<> const Atom<MyAtomIdType> Atom<MyAtomIdType>::FALSE(
		MyAtomIdType(-2, -1, 0));
template<> const Literal<MyAtomIdType> Literal<MyAtomIdType>::TRUE(
			Atom<MyAtomIdType>::TRUE, false);
template<> const Literal<MyAtomIdType> Literal<MyAtomIdType>::FALSE(
			Atom<MyAtomIdType>::FALSE, false);

} // end namespace


using namespace std;

template<typename T, int R, int C>
istream& operator>>(istream& is, SudokuSolver<T, R, C>& solver) {
	static const int RC = R * C;
	for (int r = 0; r < RC; ++r)
		for (int c = 0; c < RC; ++c) {
			char ch[2];
			cin >> ch;
			solver.set(r, c, (ch[0] == '.' ? 0 : ch[0] - '0'));
		}
	return is;
}

template<typename T, int R, int C>
istream& operator>>(istream& is, PropositionalLogicSudokuSolver<T, R, C>& solver) {
	static const int RC = R * C;
	for (int r = 0; r < RC; ++r)
		for (int c = 0; c < RC; ++c) {
			char ch[2];
			cin >> ch;
			solver.set(r, c, (ch[0] == '.' ? 0 : ch[0] - '0'));
		}
	return is;
}

void doQueries(const MySudokuSolver& solver) {
	while (true) {
		MySudokuSolver::SizeType r, c;
		MySudokuSolver::ValueType target_value;
		cout << solver;
		cin >> r >> c >> target_value;
		if (r >= MySudokuSolver::RC
				|| c >= MySudokuSolver::RC)
			return;
		cout << solver.query(r, c, target_value) << endl;
	}
}

void printHelp() {
}

#if 1

int main(int argc, char** argv) {
	MySudokuSolver solver;
	cin >> solver;
	doQueries(solver);
	cout << "Solving whole puzzle" << endl;
	solver.solve();
	cout << solver;
	return 0;
}

#endif

/*

. . 1 .
. 3 . 4
3 . 4 .
. 2 . .

2 4 1 3
1 3 2 4
3 1 4 2
4 2 3 1

. . 3 .
. 4 . .
. . 1 .
. 2 . .

2 1 3 4
3 4 2 1
4 3 1 2
1 2 4 3


. 1 4 .
. 3 . .
. . 2 .
. . . .

2 1 4 3
4 3 1 2
3 4 2 1
1 2 3 4

1 .
. 1

 */
