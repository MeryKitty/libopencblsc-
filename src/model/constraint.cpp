/*
 * constraint.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: MeryKitty
 */

#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "basics/constant.h"
#include "basics/utility.h"
#include "model/constraint.h"
#include "model/expression.h"

namespace opencbls {
	template <class T>
	constraint_t<T>::constraint_t(std::vector<bool> related_var) : _related_var(std::move(related_var)) {}

	template <class T>
	std::vector<bool>& constraint_t<T>::related_var() {
		return this->_related_var;
	}

	template <class T>
	T constraint_t<T>::violation_delta(std::raw_ptr<var_t<T>> var, T value) {
		std::size_t _id = var->id();
		bool _relate = this->_related_var.size() > _id && this->_related_var[_id];
		return _relate ? this->violation_delta_helper(var, value) : T(0);
	}

	template <class T>
	constraint_t<T>::~constraint_t() = default;

	template <class T>
	constraint_and<T>::constraint_and(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2) :
			constraint_t<T>::constraint_t(operand1->related_var() || operand2->related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {}

	template <class T>
	T constraint_and<T>::violation() {
		T _operand1_value = this->_operand1->violation();
		T _operand2_value = this->_operand2->violation();
		return _operand1_value + _operand2_value;
	}

	template <class T>
	T constraint_and<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		return this->_operand1->violation_delta(var, value) + this->_operand2->violation_delta(var, value);
	}

	template <class T>
	constraint_or<T>::constraint_or(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2) :
			constraint_t<T>::constraint_t(operand1->related_var() || operand2->related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {};

	template <class T>
	T constraint_or<T>::violation() {
		T _operand1_value = this->_operand1->violation();
		if (_operand1_value < constant::tolerance<T>) {
			return T(0);
		}
		T _operand2_value = this->_operand2->violation();
		return _operand1_value < _operand2_value ? _operand1_value : _operand2_value;
	}

	template <class T>
	T constraint_or<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _value1 = this->_operand1->violation() + this->_operand1->violation_delta(var, value);
		if (_value1 < constant::tolerance<T>) {
			return T(0);
		}
		T _value2 = this->_operand2->violation() + this->_operand2->violation_delta(var, value);
		return _value1 > _value2 ? _value2 : _value1;
	}

	template <class T>
	constraint_not<T>::constraint_not(std::unique_ptr<constraint_t<T>> operand) :
			constraint_t<T>::constraint_t(operand->related_var()),
			_operand(std::move(operand)) {}

	template <class T>
	T constraint_not<T>::violation() {
		T _operand_value = this->_operand->violation();
		return _operand_value > constant::false_violation<T> ? T(0) : constant::false_violation<T> - _operand_value;
	}

	template <class T>
	T constraint_not<T>::violation_delta_helper(std::raw_ptr<var_t<T>>, T value) {
		throw std::exception();
	}

	template <class T>
	constraint_xor<T>::constraint_xor(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2) :
			constraint_t<T>::constraint_t(operand1->related_var() || operand2->related_var()),
			_operand1(std::move(operand1)),
			_operand2(std::move(operand2)) {
		throw std::exception();
	}

	template <class T>
	T constraint_xor<T>::violation() {
		throw std::exception();
	}

	template <class T>
	T constraint_xor<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		throw std::exception();
	}

	template <class T>
	constraint_multi_and<T>::constraint_multi_and(std::vector<std::unique_ptr<constraint_t<T>>> operands) :
			constraint_t<T>::constraint_t(std::vector<bool>()),
			_operands(std::move(operands)) {
		for (auto&& _operand : this->_operands) {
			this->_related_var = this->_related_var || _operand->related_var();
		}
	}

	template <class T>
	T constraint_multi_and<T>::violation() {
		T _sum = T(0);
		for (auto&& _operand : this->_operands) {
			_sum += _operand->violation();
		}
		return _sum;
	}

	template <class T>
	T constraint_multi_and<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		T _sum = T(0);
		for (auto&& _operand : this->_operands) {
			_sum += _operand->violation_delta(var, value);
		}
		return _sum;
	}

	template <class T>
	constraint_multi_or<T>::constraint_multi_or(std::vector<std::unique_ptr<constraint_t<T>>> operands) :
			constraint_t<T>::constraint_t(std::vector<bool>()),
			_operands(std::move(operands)) {
		for (auto&& _operand : this->_operands) {
			this->_related_var = this->_related_var || _operand->related_var();
		}
	}

	template <class T>
	T constraint_multi_or<T>::violation() {
		T _min = this->_operands[0]->violation();
		for (auto&& _operand : this->_operands) {
			T _temp = _operand->violation();
			if (_temp < constant::false_violation<T>) {
				return T(0);
			} else if (_temp < _min) {
				_min = _temp;
			}
		}
		return _min;
	}

	template <class T>
	T constraint_multi_or<T>::violation_delta_helper(std::raw_ptr<var_t<T>> var, T value) {
		throw std::exception();
	}

	template class constraint_t<int>;
	template class constraint_and<int>;
	template class constraint_or<int>;
	template class constraint_not<int>;
	template class constraint_xor<int>;
	template class constraint_multi_and<int>;
	template class constraint_multi_or<int>;

}
