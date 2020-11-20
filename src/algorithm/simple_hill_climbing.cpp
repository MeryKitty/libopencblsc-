/*
 * hill_climbing.cpp
 *
 *  Created on: 17 Nov 2020
 *      Author: MeryKitty
 */

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "algorithm/algorithms.h"
#include "model/expression.h"
#include "model/constraint.h"

namespace opencbls {
	template <class T>
	void simple_hill_climbing<T>::operator() (std::vector<std::unique_ptr<var_t<T>>>& variables,
			std::vector<std::pair<T, std::unique_ptr<constraint_t<T>>>>& constraints) {
		std::cout << "Number of variables: " << variables.size() << std::endl;
		std::cout << "Number of constraints: " << constraints.size() << std::endl;
		auto violation = [&variables, &constraints]() {
			T _violation = T(0);
			for (auto&& constraint : constraints) {
				_violation += constraint.first * constraint.second->violation();
			}
			return _violation;
		};

		auto delta = [&variables, &constraints](std::raw_ptr<var_t<T>> var, T value) {
			T _delta = T(0);
			for (auto&& constraint : constraints) {
				_delta += constraint.first * constraint.second->violation_delta(var, value);
			}
			return _delta;
		};

		auto search = [&variables, &constraints, delta]() {
			for (auto&& _uvar : variables) {
				std::raw_ptr<var_t<T>> _var(_uvar.get());
				for (T _value = _var->min(); _value < _var->max(); _value += constant::tolerance<T>) {
					T _delta = delta(_var, _value);
					if (_delta < 0) {
						_var->assign(_value);
						return true;
					}
				}
			}
			return false;
		};

		while (true) {
			std::cout << "Current violation: " << violation() << std::endl;
			if (!search()) {
				break;
			}
		}
	}

	template class simple_hill_climbing<int>;
}
