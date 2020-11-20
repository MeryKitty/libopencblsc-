/*
 * solver.h
 *
 *  Created on: 17 Nov 2020
 *      Author: MeryKitty
 */

#ifndef ALGORITHM_SOLVER_H_INCLUDED
#define ALGORITHM_SOLVER_H_INCLUDED

#include <memory>
#include <utility>
#include <vector>

#include "basics/constant.h"
#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T, class Algo>
	class solver {
	private:
		inline static Algo _algo;
		std::size_t _current_id = 0;
		std::vector<std::unique_ptr<var_t<T>>> _variables;
		std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>> _constraints;
	public:
		solver();
		void add_constraint(std::unique_ptr<constraint_t<T>> constraint, T weight = T(1));
		std::raw_ptr<var_t<T>> add_variable(T min, T max);
		std::vector<T> value();
		void solve();
		void clear();
	};
}

#endif /* ALGORITHM_SOLVER_H_INCLUDED */
