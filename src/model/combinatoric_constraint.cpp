/*
 * combinatorial_constraint.cpp
 *
 *  Created on: 13 Nov 2020
 *      Author: MeryKitty
 */

#include <iostream>
#include <vector>

#include "basics/constant.h"
#include "basics/utility.h"
#include "model/expression.h"
#include "model/combinatoric_constraint.h"

namespace opencbls {
	template <class T>
	constraint_all_not_equal<T>::constraint_all_not_equal(std::vector<expr_t<T>> operands) :
			constraint_t<T>::constraint_t(std::vector<bool>()),
			_operands(std::move(operands)) {
		for (auto&& _operand : this->_operands) {
			this->_related_var = this->_related_var || _operand.related_var();
		}
	}

	template <class T>
	T constraint_all_not_equal<T>::violation() {
		T result = 0;
		for (std::size_t i = 0; i < this->_operands.size(); i++) {
			T _current = this->_operands[i].value();
			for (std::size_t j = i + 1; j < this->_operands.size(); j++) {
				T _other = this->_operands[j].value();
				T _difference = _current - _other;
				_difference = _difference > 0 ? _difference : -_difference;
				if (_difference < constant::tolerance<T>) {
					result += constant::false_violation<T>;
				}
			}
		}
		return result;
	}

	template <class T>
	T constraint_all_not_equal<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		std::vector<T> _new_value(this->_operands.size());
		for (std::size_t i = 0; i < this->_operands.size(); i++) {
			_new_value[i] = this->_operands[i].value() + this->_operands[i].delta(var, value);
		}
		T new_result = 0;
		for (std::size_t i = 0; i < this->_operands.size(); i++) {
			for (std::size_t j = i + 1; j < this->_operands.size(); j++) {
				T _difference = _new_value[i] - _new_value[j];
				_difference = _difference > 0 ? _difference : -_difference;
				if (_difference < constant::tolerance<T>) {
					new_result += constant::false_violation<T>;
				}
			}
		}
		return new_result - this->violation();
	}

	template class constraint_all_not_equal<int>;
}
