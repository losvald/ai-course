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

#ifndef PROVER_H_
#define PROVER_H_

#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <iterator>
#include <functional>

#include "atom.h"
#include "literal.h"
#include "clause.h"

#include "../foreach.h"

namespace logic {

#define VERBOSITY 0
#define COMPARE_KB_AND_SOS_ONLY 1

template<class LiteralIdClass>
class Prover {
	typedef typename Clause<LiteralIdClass>::ConstPointer ConstClausePointer;
	typedef Clause<LiteralIdClass> ClauseType;
	typedef Literal<LiteralIdClass> LiteralType;
	typedef typename LiteralType::AtomType AtomType;

	typedef std::map<LiteralType, std::vector<ConstClausePointer> > LiteralMapType;

	template<typename InnerLiteralIdClass>
	class KnowledgeBase {
		typedef typename Prover<InnerLiteralIdClass>::ClauseType ClauseType;
		typedef typename Prover<InnerLiteralIdClass>::LiteralMapType LiteralMapType;

		LiteralMapType clauses_by_literal_;

		struct ConstClausePointerSetCmp {
			bool operator()(ConstClausePointer a, ConstClausePointer b) const {
				return *a < *b;
			}
		};

		std::set<ConstClausePointer, ConstClausePointerSetCmp> clauses_;

		template<typename InnermostLiteralIdClass>
		struct LiteralMapFiller {
			typedef typename Prover<InnermostLiteralIdClass>::ConstClausePointer ConstClausePointer;
			typedef typename Prover<InnermostLiteralIdClass>::LiteralMapType LiteralMapType;
			LiteralMapType& literal_map_;
			ConstClausePointer clause_;

			LiteralMapFiller(LiteralMapType& literal_map,
					ConstClausePointer clause)
			: literal_map_(literal_map), clause_(clause) { }

			void operator()(const LiteralType& literal) const {
				literal_map_[!literal].push_back(clause_);
			}
		};

	public:
		bool add(ClauseType clause) {
			if (clause.isTautology()) {
				if (VERBOSITY > 0)
					std::cerr << "Optimization: Tautology not added to KB: "
					<< clause << std::endl;
				return false;
			}

			if (!clauses_.count(&clause)) {
				ConstClausePointer ccp = new ClauseType(clause);
				clauses_.insert(ccp);
				clause.foreach(LiteralMapFiller<LiteralIdClass>(
						clauses_by_literal_, ccp));
				if (VERBOSITY > 0)
					std::cerr << "Added to KB: " << clause << std::endl;

				return true;
			}
			if (VERBOSITY > 1)
				std::cerr << "Already in KB: " << clause << std::endl;
			return false;
		}

		std::size_t size() const { return clauses_.size(); }

		bool mycmp(ConstClausePointer a, ConstClausePointer b) {
			return a->size() < b->size();
		}

		template<class Functor>
		void foreach(const LiteralType& literal, const Functor& f) const {
			if (clauses_by_literal_.count(literal)) {
				const std::vector<ConstClausePointer>& clauses
				= clauses_by_literal_.at(literal);

				FOREACH(it, clauses) {
					f(**it);
				}
			}
		}

		bool isSuperset(const ClauseType& clause) const {
			SubclauseIterator<InnerLiteralIdClass> it(clause);
			int itr = clauses_.size();
			for (; itr >= 0; --itr) {
				ClauseType subclause = it.next();
				if (subclause.size() == clause.size())
					break;
				if (clauses_.count(&subclause))
					return true;
			}
			if (itr < 0) {
				FOREACH(it, clauses_) {
					if ((*it)->entails(clause))
						return true;
				}
			}
			return false;
		}

		friend std::ostream& operator<<(std::ostream& os,
				const KnowledgeBase& kb) {
			os << "Premises (" << kb.size() << "):" << std::endl;
			FOREACH(it, kb.clauses_) {
				os << **it << std::endl;
			}
			return os;
		}
	};
	typedef KnowledgeBase<LiteralIdClass> KnowledgeBaseType;

	template<typename InnerLiteralIdClass>
	class SetOfSupport {
		typedef typename Prover<InnerLiteralIdClass>::ClauseType ClauseType;

		struct SosQueueCmp {
			bool operator()(const ClauseType& a, const ClauseType& b) const {
				return b.size() < a.size();
			}
		};

		std::priority_queue<ClauseType, std::vector<ClauseType>, SosQueueCmp> pq_;
		std::set<ClauseType> visited_;

	public:
		bool empty() const { return pq_.empty(); }
		std::size_t size() const { return pq_.size(); }

		bool add(const ClauseType& clause) {
			if (!visited_.count(clause)) {
				visited_.insert(clause);
				pq_.push(clause);
				return true;
			}
			return false;
		}

		ClauseType pop() {
			ClauseType ret = pq_.top();
			pq_.pop();
			return ret;
		}

		bool isSuperset(const ClauseType& clause) const {
			SubclauseIterator<InnerLiteralIdClass> it(clause);
			int itr = visited_.size();
			for (; itr >= 0; --itr) {
				ClauseType subclause = it.next();
				if (subclause.size() == clause.size())
					break;
				if (visited_.count(subclause))
					return true;
			}
			if (itr < 0) {
				FOREACH(it, visited_) {
					if (it->entails(clause))
						return true;
				}
			}
			return false;
		}
	};

	template<typename InnerLiteralIdClass>
	class SosQueueFiller {
		typedef typename Prover<InnerLiteralIdClass>::ClauseType ClauseType;
		typedef typename Prover<InnerLiteralIdClass>::LiteralMapType LiteralMapType;
		typedef typename Prover<InnerLiteralIdClass>::LiteralType LiteralType;
		typedef typename Prover<InnerLiteralIdClass>::SetOfSupportType SetOfSupportType;
		typedef typename Prover<InnerLiteralIdClass>::KnowledgeBaseType KnowledgeBaseType;


		const ClauseType& clause_;
		const KnowledgeBaseType& kb_;
		SetOfSupportType& sos_;
		bool& resolved_;

		bool isSuperset(const ClauseType& clause) const {
			return kb_.isSuperset(clause) || sos_.isSuperset(clause);
		}

	public:
		SosQueueFiller(const ClauseType& clause, const KnowledgeBaseType& kb,
				SetOfSupportType& sos, bool& resolved)
		: clause_(clause),
		  kb_(kb), sos_(sos), resolved_(resolved) { }

		void operator()(const ClauseType& clause) const {
			ClauseType resolvent_clause = clause + clause_;
			if (VERBOSITY > 0) {
				std::cerr << "Resolution: "
						<< clause_ << " & " << clause << " => "
						<< resolvent_clause << std::endl;
			}
			if (resolvent_clause.isNil()) {
				resolved_ = true;
				return ;
			} else if (!resolvent_clause.isTautology() // if not tautology
					&& !isSuperset(resolvent_clause)) { // nor superset
				sos_.add(resolvent_clause); // push it to the SoS queue
			}
		}

		void operator()(const LiteralType& literal) const {
			resolved_ = false;
			// pass this because KnowledgeBaseType expects operator()(const ClauseType&)
			// in foreach method
			kb_.foreach(literal, *this);
		}
	};
	typedef SetOfSupport<LiteralIdClass> SetOfSupportType;

	KnowledgeBaseType knowledge_base_;

	bool prove0(SetOfSupportType& sos) const {
		/**
		 * Dummy knowledge base containing clauses popped from SoS
		 * (this enables easy resolution among two clauses from SoS)
		 */
		KnowledgeBaseType popped;
		bool resolved = false;
		while (!sos.empty() && !resolved) {
			if (VERBOSITY > 1)
				std::cerr << sos.size() << std::endl;
			// extract a clause from set of support
			ClauseType clause = sos.pop();
			clause.foreach(SosQueueFiller<LiteralIdClass>(clause,
					knowledge_base_, sos, resolved));

			if (!COMPARE_KB_AND_SOS_ONLY) {
				clause.foreach(SosQueueFiller<LiteralIdClass>(clause,
						popped, sos, resolved));
				popped.add(clause);
			}
		}
		return resolved;
	}

public:

	bool addClause(const ClauseType& clause) {
		return knowledge_base_.add(clause);
	}


	bool prove(const LiteralType& literal) const {
		SetOfSupportType sos;
		sos.add(ClauseType(!literal)); // add negated clause to SoS
		return prove0(sos);
	}

	std::size_t size() const { return knowledge_base_.size(); }

	friend std::ostream& operator<<(std::ostream& os, const Prover& prover) {
		os << "----Set of Support prover----" << std::endl;
		os << prover.knowledge_base_;
		os << "-----------------------------" << std::endl;
		return os;
	}
};

} // namespace logic

#endif /* PROVER_H_ */
