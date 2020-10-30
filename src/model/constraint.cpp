/*
 * constraint.cpp
 *
 *  Created on: 29 Oct 2020
 *      Author: MeryKitty
 */

#include <exception>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "model/constraint.h"
#include "model/expression.h"
#include "basics/constant.h"

namespace opencbls {
	template <class T>
	constraint_and<T>::constraint_and(std::unique_ptr<constraint_t<T>> oprand1, std::unique_ptr<constraint_t<T>> oprand2) :
			oprand1(std::move(operand1)),
			oprand2(std::move(operand2)) {}

	template <class T>
	T constraint_and<T>::violation() {
		T _operand1_value = this->operand1->violation();
		T _operand2_value = this->operand2->violation();
		return _operand1_value + _operand2_value;
	}

	template <class T>
	constraint_or<T>::constraint_or(std::unique_ptr<constraint_t<T>> oprand1, std::unique_ptr<constraint_t<T>> oprand2) :
			oprand1(std::move(operand1)),
			oprand2(std::move(operand2)) {};

	template <class T>
	T constraint_or<T>::violation() {
		T _operand1_value = this->operand1->violation();
		if (_operand1_value == 0) {
			return 0;
		}
		T _operand2_value = this->operand2->violation();
		return _operand1_value < _operand2_value ? _operand1_value : _operand2_value;
	}

	template <class T>
	constraint_not<T>::constraint_not(std::unique_ptr<constraint_t<T>> operand) :
			operand(std::move(operand)) {}

	template <class T>
	T constraint_not<T>::violation() {
		T _operand_value = this->operand->violation();
		return _operand_value > constant::false_violation ? 0 : constant::false_violation - _operand_value;
	}

	template <class T>
	constraint_xor<T>::constraint_xor(std::unique_ptr<constraint_t<T>> operand1, std::unique_ptr<constraint_t<T>> operand2) :
			operand1(std::move(operand1)),
			operand2(std::move(operand2)) {
		throw std::exception();
	}

	template <class T>
	T constraint_xor<T>::violation() {
		throw std::exception();
	}

	template <class T>
	constraint_multi_and<T>::constraint_multi_and(std::vector<std::unique_ptr<constraint_t<T>>> operands) :
			operands(std::move(operands)) {
		if (this->operands.empty()) {
			throw std::exception();
		}
	}

	template <class T>
	T constraint_multi_and<T>::violation() {
		T _sum = 0;
		for (auto&& operand : this->operands) {
			_sum += operand->violation();
		}
		return _sum;
	}

	template <class T>
	constraint_multi_or<T>::constraint_multi_or(std::vector<std::unique_ptr<constraint_t<T>>> operands) :
			operands(std::move(operands)) {}

	template <class T>
	T constraint_multi_or<T>::violation() {
		T _min = this->operands[0]->violation();
		for (auto&& _operand : this->operands) {
			T _temp = _operand->violation();
			if (_temp == 0) {
				return 0;
			} else if (_temp < _min) {
				_min = _temp;
			}
		}
		return _min;
	}
}
