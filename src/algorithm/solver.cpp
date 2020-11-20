/*
 * solver.cpp
 *
 *  Created on: 17 Nov 2020
 *      Author: MeryKitty
 */

#include <memory>
#include <utility>
#include <vector>

#include "algorithm/solver.h"
#include "algorithm/algorithms.h"
#include "basics/constant.h"
#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T, class Algo>
	solver<T, Algo>::solver() :
			_variables(std::vector<std::unique_ptr<var_t<T>>>()),
			_constraints(std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>()) {}

	template <class T, class Algo>
	std::raw_ptr<var_t<T>> solver<T, Algo>::add_variable(T min, T max) {
		this->_variables.emplace_back(std::make_unique<var_t<T>>(this->_current_id++, min, max));
		return std::raw_ptr<var_t<T>>(this->_variables.back().get());
	}

	template <class T, class Algo>
	void solver<T, Algo>::add_constraint(std::unique_ptr<constraint_t<T>> constraint, T weight) {
		this->_constraints.emplace_back(std::make_pair(weight, std::move(constraint)));
	}

	template <class T, class Algo>
	std::vector<T> solver<T, Algo>::value() {
		std::size_t n = this->_variables.size();
		std::vector<T> _result(n);
		for (std::size_t i = 0; i < n; i++) {
			_result[i] = this->_variables[i]->value();
		}
		return _result;
	}

	template <class T, class Algo>
	void solver<T, Algo>::clear() {
		this->_variables.clear();
		this->_constraints.clear();
	}

	template <class T, class Algo>
	void solver<T, Algo>::solve() {
		_algo(this->_variables, this->_constraints);
	}

	template class solver<int, simple_hill_climbing<int>>;
}
