/*
 * solver.cpp
 *
 *  Created on: 17 Nov 2020
 *      Author: MeryKitty
 */

#include <any>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "algorithm/solver.h"
#include "basics/constant.h"
#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	solver<T>::solver(std::function<void(std::vector<std::raw_ptr<var_t<T>>>&,
			std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>&,
			std::any)> algo, std::any parameters) :
			_algo(algo),
			_parameters(parameters),
			_variables(std::vector<std::unique_ptr<var_t<T>>>()),
			_constraints(std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>()) {}

	template <class T>
	std::raw_ptr<var_t<T>> solver<T>::add_variable(T min, T max) {
		this->_variables.emplace_back(std::make_unique<var_t<T>>(this->_current_id++, min, max));
		return std::raw_ptr<var_t<T>>(this->_variables.back().get());
	}

	template <class T>
	void solver<T>::add_constraint(std::unique_ptr<constraint_t<T>> constraint, T weight) {
		this->_constraints.emplace_back(std::make_pair(weight, std::move(constraint)));
	}

	template <class T>
	std::vector<T> solver<T>::value() {
		std::size_t n = this->_variables.size();
		std::vector<T> _result(n);
		for (std::size_t i = 0; i < n; i++) {
			_result[i] = this->_variables[i]->value();
		}
		return _result;
	}

	template <class T>
	void solver<T>::clear() {
		this->_variables.clear();
		this->_constraints.clear();
	}

	template <class T>
	void solver<T>::solve() {
		std::vector<std::raw_ptr<var_t<T>>> _variables;
		for (auto&& var : this->_variables) {
			_variables.emplace_back(std::raw_ptr<var_t<T>>(var.get()));
		}
		this->_algo(_variables, this->_constraints, this->_parameters);
	}

	template <class T>
	void solver<T>::print_value() {
		for (auto&& _var : this->_variables) {
			std::cout << _var->value() << std::endl;
		}
	}

	template <class T>
	void solver<T>::print_violation() {
		for (auto&& _constraint : this->_constraints) {
			std::cout << _constraint.first << " - " << _constraint.second->violation() << std::endl;
		}
	}

	template class solver<int>;
}
